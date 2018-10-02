#include "include.h"

void main(void)
{
	UART_init(UART0 , NONE_PARITY , T2 , 460800);
	
	REPLACE(P_SW2,5,4,0);
	PWMCFG  = 0x38;
	PWMIF   = 0x00;
	PWMFDCR = 0x32;
	BIT_SET(P_SW2,7);
	PWMCH   = 0x7f;
	PWMCL   = 0xff;
	PWMCKS  = 0x00;
	PWM2T1H = 0x00;
	PWM2T1L = 0x00;
	PWM2T2H = 0x40;
	PWM2T2L = 0x00;
	PWM2CR  = 0x00;//
	PWM3T1H = 0x00;
	PWM3T1L = 0x00;
	PWM3T2H = 0x40;
	PWM3T2L = 0x00;
	PWM3CR  = 0x08;//
	PWM4T1H = 0x00;
	PWM4T1L = 0x00;
	PWM4T2H = 0x40;
	PWM4T2L = 0x00;
	PWM4CR  = 0x00;//
	PWM5T1H = 0x00;
	PWM5T1L = 0x00;
	PWM5T2H = 0x40;
	PWM5T2L = 0x00;
	PWM5CR  = 0x08;//
	PWM6T1H = 0x00;
	PWM6T1L = 0x00;
	PWM6T2H = 0x40;
	PWM6T2L = 0x00;
	PWM6CR  = 0x00;//
	PWM7T1H = 0x00;
	PWM7T1L = 0x00;
	PWM7T2H = 0x40;
	PWM7T2L = 0x00;
	PWM7CR  = 0x08;//
	BIT_CLR(P_SW2,7);
	PWMCR  = 0xbf;
	
	DELAY_MS(1000);
	printf("Procedure start ->\r\n");
	while(1)
	{
		;
	}
}