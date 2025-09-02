// 맨체스터 전송 안할대는 TXDis 끄기
#include <intrinsics.h>
#include <stdlib.h>
#include <iods4835.h>
#include <string.h>
#include "includes.h"

char cnt_hi = 0;
static uint8_t los_prev_state = 0; // 이전 LOS 상태 저장 (main에서 사용)

// 맨체스터 출력 제어 변수
typedef enum
{
	MANCHESTER_DISABLED = 0, // 해제 모드 (맨체스터 출력없음)
	MANCHESTER_1MIN = 1,	 // 1분 모드
	MANCHESTER_5MIN = 5		 // 5분 모드
} ManchesterMode;

ManchesterMode manchester_mode = MANCHESTER_5MIN; // 기본값 5분 모드
uint32_t manchester_wait_timer = 0;				  // 맨체스터 대기 타이머 (1ms 단위)

uint16_t timeslot_delay = 1000; // 1초~30초 (1000ms~30000ms) 사이의 랜덤 지연값
uint8_t reset_request = 0;		// 리셋 요청 플래그
int main_Cnt = 0;				// 상태 머신 카운터

// 간단한 LFSR 기반 랜덤 번호 생성
uint16_t lfsr_seed = 0xACE1;
uint16_t generate_random(void)
{
	lfsr_seed = (lfsr_seed >> 1) ^ (-(lfsr_seed & 1u) & 0xB400u);
	return lfsr_seed;
}

// 1초~30초 사이의 랜덤 지연값 생성
void set_random_timeslot_delay(void)
{
	uint16_t random_val = generate_random();

	// 실제 사용: 1초~30초 (1000ms~30000ms)
	timeslot_delay = 1000 + (random_val % 29001); // 1000 + (0~29000)
}

#pragma required = password

// #define GP15_DIR PD1_bit.PD15
// #define GP15_OUT PO1_bit.PO15
// #define GP15_IN PI1_bit.PI15

// #define GP26_DIR PD2_bit.PD26
// #define GP26_OUT PO2_bit.PO26
// #define GP26_IN PI2_bit.PI26

#define GP00_DIR PD0_bit.PD00 // 1 : output, 0 : input
#define GP00_OUT PO0_bit.PO00 // TXDIS

#define GP07_DIR PD0_bit.PD07 // 1 : output, 0 : input
#define GP07_IN PI0_bit.PI07  // GP07 입력
#define GP07_OUT PO0_bit.PO07 // GP07 출력

#define GP24_DIR PD2_bit.PD24 // 1 : output, 0 : input
#define GP24_IN PI2_bit.PI24  // GP24 입력
#define GP24_OUT PO2_bit.PO24 // GP24 출력

#define GP22_DIR PD2_bit.PD22 // 1 : output, 0 : input
#define GP22_OUT PO2_bit.PO22

#define GP23_DIR PD2_bit.PD23 // 1 : output, 0 : input
#define GP23_OUT PO2_bit.PO23 // GP23 출력

typedef enum
{
	false = 0,
	true = 1
} bool;

typedef struct
{
	uint8_t data[8][3];	  // 8개 프레임 x 3바이트
	uint8_t currentFrame; // 현재 프레임
	uint8_t currentByte;  // 현재 바이트
	uint8_t currentBit;	  // 현재 비트
	uint8_t txStep;		  // 전송 단계
} ManchesterData;

static ManchesterData manData;

// 함수 프로토타입 선언
void Out_HI(void);
void Out_LO(void);

void Timer3Setup()
{
	TBCN3_bit.TBR = 0;
	TBV3 = 0x0000;
	TBC3 = 250; // 1ms 주기
	TBCN3_bit.TBPS = 3;
	TBCN3_bit.MODE = 1;
	TBCN3_bit.TBIE = 1;
	TBCN3_bit.TBIF = 0;
	IMR_bit.IM3 = 0;   // 인터럽트 비활성화
	TBCN3_bit.TBR = 0; // 타이머 정지 상태로 유지
}

// 타이머 동작 상태 확인 함수
bool isTimerRunning(void)
{
	return (TBCN3_bit.TBR == 1) ? true : false;
}

void startTimer(void)
{
	// 타이머 시작 시 모드에 맞게 대기 시간 설정
	if (manchester_mode == MANCHESTER_1MIN)
		manchester_wait_timer = 60000; // 1분
	else if (manchester_mode == MANCHESTER_5MIN)
		manchester_wait_timer = 300000; // 5분

	TBCN3_bit.TBR = 1;
	IMR_bit.IM3 = 1;
	Out_HI();
}

void stopTimer(void)
{
	TBCN3_bit.TBR = 0;
	IMR_bit.IM3 = 0;

	// 맨체스터 관련 상태 초기화
	cnt_hi = 0;
	manchester_wait_timer = 0;
	main_Cnt = 0;

	PLACNT1 = 0x80C0; // PLA 활성화 상태로 복원
}

// GP00_OUT 은 1157의 TXDIS 핀에 해당함
// 이를 이용하기 위해서는 PLACNT1 을 사용중지 해야함
void pulse_Out(bool value)
{
	GP00_OUT = value; // GP00 핀으로 직접 출력
}

uint8_t calculateHamming_Little(uint8_t startBits, uint8_t data1, uint8_t data2)
{
	uint32_t fullData = ((uint32_t)startBits << 16) | ((uint32_t)data1 << 8) | data2;

	int data[19];
	for (int i = 0; i < 19; i++)
		data[i] = (fullData >> i) & 0x01;

	uint8_t p1 = data[1] ^ data[3] ^ data[5] ^ data[7] ^ data[8] ^ data[10] ^ data[12] ^ data[14] ^ data[15] ^ data[17] ^ data[18];
	uint8_t p2 = data[1] ^ data[2] ^ data[5] ^ data[6] ^ data[8] ^ data[9] ^ data[12] ^ data[13] ^ data[15] ^ data[16] ^ data[18];
	uint8_t p3 = data[1] ^ data[2] ^ data[3] ^ data[4] ^ data[8] ^ data[9] ^ data[10] ^ data[11] ^ data[15] ^ data[16] ^ data[17];
	uint8_t p4 = data[0] ^ data[8] ^ data[9] ^ data[10] ^ data[11] ^ data[12] ^ data[13] ^ data[14];
	uint8_t p5 = data[0] ^ data[1] ^ data[2] ^ data[3] ^ data[4] ^ data[5] ^ data[6] ^ data[7];

	return (0x1F & ((p1 << 4) | (p2 << 3) | (p3 << 2) | (p4 << 1) | p5));
}

// I2C 명령을 통한 맨체스터 출력 제어
void Manchester_Control_I2C(uint8_t command)
{
	switch (command)
	{
	case 0: // 해제 모드
		manchester_mode = MANCHESTER_DISABLED;
		stopTimer(); // 타이머 정지 및 상태 초기화
		break;

	case 1: // 1분 모드
		manchester_mode = MANCHESTER_1MIN;
		manchester_wait_timer = 60000; // 1분
		break;

	default: // 5분 모드
		manchester_mode = MANCHESTER_5MIN;
		manchester_wait_timer = 300000; // 5분 타이머 값 설정
		break;
	}
}

static const char *currentHexString;
static uint8_t bitCounter = 0;		 // 비트 타이밍을 위한 카운터 추가
static char vendorPN[17] = {0};		 // 16글자 + null terminator 추가
static char prevVendorPN[17] = {0};	 // 이전 vendorPN 값 저장용
static uint8_t vendorPN_changed = 0; // vendorPN 변경 여부 플래그
uint16_t time_Chk = 0;				 // int에서 uint16_t로 변경하여 음수 방지
int frame;
uint8_t hammingCode;

void Out_HI()
{ // TXDIS HI - PLA 소프트웨어 비트로 제어
  // PLACNT1이 GP00을 제어하므로 소프트웨어 비트 사용
  // SBEN1이 이미 활성화(0x80C0에서 비트6=1)되어 있음
  // PLACNT1_bit.SB1 = 1; // SB1=1이면 PLA 출력 HIGH
	GP00_OUT = 1;
}

void Out_LO()
{ // TXDIS Low - PLA 소프트웨어 비트로 제어
  // PLACNT1이 GP00을 제어하므로 소프트웨어 비트 사용
  // SBEN1이 이미 활성화(0x80C0에서 비트6=1)되어 있음
  // PLACNT1_bit.SB1 = 0; // SB1=0이면 PLA 출력 LOW
	GP00_OUT = 0;
}
int time_Check = 0;

#pragma vector = 3
__interrupt void module3_int()
{
	if (TBCN3_bit.TBIF)
	{
		TBCN3_bit.TBIF = 0;
		IMR_bit.IM3 = 1;

		// 맨체스터 대기 타이머 처리 및 PLACNT1 초기화
		if (manchester_wait_timer > 0)
		{
			manchester_wait_timer--;

			// 타이머가 0이 되는 순간 PLACNT1 초기화 (1회만 실행됨)
			if (manchester_wait_timer == 0)
			{
				PLACNT1 = 0x00C0; // PLA 비활성화 (맨체스터 출력 시)
				GP00_DIR = 1;
			}

			return; // 대기 중에는 맨체스터 출력하지 않음
		}

		switch (main_Cnt)
		{
		case 0: // delay 시작 및 데이터 배열에 넣기
		{
			Out_HI();

			// 이전 값을 prev 버퍼에 저장하고, 새 값을 읽으면서 동시에 비교
			vendorPN_changed = 0;
			for (int i = 0; i < 16; i++)
			{
				prevVendorPN[i] = vendorPN[i];							  // 이전 값 저장
				vendorPN[i] = I2C_Slave_Buffer_A0_Local_Memory[0x44 + i]; // 새 값 읽기

				// 값이 달라졌는지 확인
				if (vendorPN[i] != prevVendorPN[i])
					vendorPN_changed = 1;
			}
			vendorPN[16] = '\0';
			prevVendorPN[16] = '\0';
			currentHexString = vendorPN;

			bitCounter = 0;
			manData.currentFrame = 0;
			manData.currentByte = 0;
			manData.currentBit = 0;
			manData.txStep = 0;
			main_Cnt++;
			break;
		}

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8: // 8프레임의 데이터 구성
			Out_HI();
			// vendorPN이 변경되었을 때만 데이터 업데이트
			if (manData.currentFrame == 0 && vendorPN_changed == 1)
			{
				frame = main_Cnt - 1;

				manData.data[frame][0] = (frame << 5) | (currentHexString[frame * 2] >> 3);
				manData.data[frame][1] = (currentHexString[frame * 2] << 5) | (currentHexString[frame * 2 + 1] >> 3);
				hammingCode = calculateHamming_Little(frame, currentHexString[frame * 2], currentHexString[frame * 2 + 1]);
				manData.data[frame][2] = (currentHexString[frame * 2 + 1] << 5) | hammingCode;
			}
			main_Cnt++;
			break;

		case 9: // Delay 10ms 시간 맞추기 위해 삽입
			Out_HI();
			main_Cnt++;
			break;

		case 10: // 시간 맞추기용
			Out_LO();
			if (bitCounter != 0)
				main_Cnt++;
			bitCounter ^= 1;
			break;

		case 11: // SOF
			if (bitCounter == 0)
			{
				Out_LO();
			}
			else
			{
				Out_HI();
				main_Cnt++;
			}
			bitCounter ^= 1;
			break;

		case 36: // EOF
			if (bitCounter == 0)
				Out_HI();
			else
			{
				Out_LO();
				main_Cnt++;
			}
			bitCounter ^= 1;
			break;

		case 37:
			Out_LO();
			manData.currentFrame++;
			if (manData.currentFrame >= 8)
			{
				manData.currentFrame = 0;
				time_Chk = 9;
			}
			else
				time_Chk = 6;

			main_Cnt = 38;
			break;

		case 38: // Hold Time 대기
			Out_LO();
			if (time_Chk > 0)
				time_Chk--;
			else
			{
				if (manData.currentFrame == 0)
				{
					set_random_timeslot_delay(); // 새로운 랜덤 지연값 생성
					time_Chk = timeslot_delay;	 // 1초~30초 사이의 랜덤 지연
					main_Cnt = 39;
				}
				else
				{
					bitCounter = 0;
					main_Cnt = 10;
				}
			}
			break;

		case 39:
			Out_HI(); // 프레임 간 대기 중에는 HIGH 유지

			// time_Chk 감소 및 상태 전환
			if (time_Chk > 0)
				time_Chk--;
			else
			{
				main_Cnt = 0;
				bitCounter = 0;
			}
			break;

		default:
			if (main_Cnt >= 12 && main_Cnt <= 35)
			{
				if (bitCounter == 0)
				{
					pulse_Out((manData.data[manData.currentFrame][(main_Cnt - 12) / 8] >> (7 - ((main_Cnt - 12) % 8))) & 0x01);
				}
				else
				{
					pulse_Out(!((manData.data[manData.currentFrame][(main_Cnt - 12) / 8] >> (7 - ((main_Cnt - 12) % 8))) & 0x01));
					main_Cnt++;
				}
				bitCounter ^= 1;
			}
			break;
		}
	}
}

void main(void)
{
	Initialization();
	Timer3Setup();

	// GP15_DIR = 1; // set pin P2.0 as an output
	// GP15_OUT = 0; // set pin P2.0 low
	// GP26_DIR = 1; // set pin P2.0 as an output
	// GP26_OUT = 0; // set pin P2.0 low
	// GP27_DIR = 1; // set pin P2.0 as an output
	// GP27_OUT = 0; // set pin P2.0 low

	// GP22_DIR = 1;
	// GP07_DIR = 1; // GP07을 출력으로 설정 (LOS 신호 토글용)
	// GP07_OUT = 0; // GP07 초기값 LOW
	// GPIO 초기화
	// GP00은 PLACNT1이 제어하므로 별도 설정 불필요

	I2CS_Init();
	IMR_bit.IM2 = 1;
	__enable_interrupt();
	main_Cnt = 0;

	// LFSR 시드 초기화 - 매번 다른 랜덤 값 생성을 위해
	lfsr_seed = (uint16_t)(TBV3 ^ 0xACE1);

	// 맨체스터 제어 초기화 - 기본값 5분 모드
	I2C_Slave_Buffer_A2_P81H_Up[0x02] = MANCHESTER_5MIN;
	Manchester_Control_I2C(MANCHESTER_5MIN);

	while (1)
	{
		WDCN_bit.RWT = 1;

		// LOS 신호 체크 (PLACNT2_bit.PLA_OUT) - main에서 처리
		if (PLACNT2_bit.PLA_OUT == 1)
		{
			if (++cnt_hi >= 20)
			{
				cnt_hi = 20; // LOS 발생후 20ms 지나면 Cable Sensing 동작

				// 20ms가 되는 시점에 타이머 시작 (한 번만)
				if (!isTimerRunning() && manchester_mode != MANCHESTER_DISABLED)
					startTimer(); // 타이머 시작
			}
			los_prev_state = 1;
		}
		else
		{
			// LOS가 LOW로 변경되면 모든 것을 리셋
			if (los_prev_state == 1) // HIGH에서 LOW로 전환 시
				stopTimer();		 // 타이머 정지 및 상태 초기화
			else
				cnt_hi = 0;
			los_prev_state = 0;
		}

		// I2C 명령을 통한 맨체스터 제어는 이제 exec_upper_page81H_memory 함수에서 처리됨
		// A2 PAGE 81H의 0x7E 주소에 값을 써서 맨체스터 모드 제어
		// 0: 해제 모드, 1: 1분 모드, 5: 5분 모드

		// 아래 4개의 구문은 약 1ms 소요됨 ( 대략 923us~ )
		MasterI2CArbitration();
		DDM_Read();
		state_transition_control();
		update_faws_summary_registers();
	}
}
