1. GN1157의 TXDIS 핀을 CPU의 GP00에서 ON/OFF 해서 선번센싱 출력 (모듈의 시리얼번호 출력)
2. 광모듈 외부에서 입력되는 TXDIS 신호는 무시됨
    TXDIS HI -> LD 출력 HI
    TXDIS LOW -> LD 출력 Low

3. 선번센싱 출력신호 좋음, 타이밍 잘 맞음
4. 광모듈의 다른 동작도 대부분 잘됨
5. 광모듈에서 출력되는 LOS 신호 무시할것 
    TXDIS 에 Low Edge 신호 입력될때마다 LOS 에 짧은 HI 펄스 생김 (30us ~1.2ms)
    광입력이 없으면 LOS -> Low

