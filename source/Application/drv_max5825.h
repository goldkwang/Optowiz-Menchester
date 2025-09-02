#ifndef _MAX5825_H_
#define _MAX5825_H_


void Delay(long time);

void Delay_m(int msec);


void Max5825_dac_set(unsigned char dac_no, unsigned char ch, unsigned int Data);
unsigned int Max5825_dac_get(unsigned char dac_no, unsigned char ch);
void Max5825_dac_init(void);
void Max5825_dac_Clear(unsigned char dac_no);




#endif

