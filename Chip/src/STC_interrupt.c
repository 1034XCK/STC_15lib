#include "common.h"
#include "STC_interrupt.h"

void (*INT0_VECTOR)(void);
void (*TIMER0_VECTOR)(void);
void (*INT1_VECTOR)(void);
void (*TIMER1_VECTOR)(void);
void (*UART0_VECTOR)(void);
void (*ADC_VECTOR)(void);
void (*LVD_VECTOR)(void);
void (*CCP_VECTOR)(void);
void (*UART1_VECTOR)(void);
void (*SPI_VECTOR)(void);
void (*INT2_VECTOR)(void);
void (*INT3_VECTOR)(void);
void (*TIMER2_VECTOR)(void);
void (*PWM_VECTOR)(void);
void (*INT4_VECTOR)(void);
void (*UART2_VECTOR)(void);
void (*UART3_VECTOR)(void);
void (*TIMER3_VECTOR)(void);
void (*TIMER4_VECTOR)(void);
void (*CMPIF_VECTOR)(void);

/*!
 *	@brief		设置中断函数到中断向量
 *	@param		VECTORn				中断向量名
							pfunc_handler	中断函数名
 *	@warning	中断函数请直接写函数名
 *	@sampleusage:	set_vector_handler(TIMER0_VECTORn , TIMER0_IRQHandler);//将定时器T0中断的服务函数设定为TIMER0_IRQHandler()
 */

void set_vector_handler(VECTORn_t VECTORn , void pfunc_handler(void))
{
	switch(VECTORn)
	{
		case INT0_VECTORn		: INT0_VECTOR		= pfunc_handler;break;
		case TIMER0_VECTORn	: TIMER0_VECTOR	= pfunc_handler;break;
		case INT1_VECTORn		: INT1_VECTOR		= pfunc_handler;break;
		case TIMER1_VECTORn	: TIMER1_VECTOR	= pfunc_handler;break;
		case UART0_VECTORn	: UART0_VECTOR	= pfunc_handler;break;
		case ADC_VECTORn		: ADC_VECTOR		= pfunc_handler;break;
		case LVD_VECTORn		: LVD_VECTOR		= pfunc_handler;break;
		case CCP_VECTORn		: CCP_VECTOR		= pfunc_handler;break;
		case UART1_VECTORn	: UART1_VECTOR	= pfunc_handler;break;
		case SPI_VECTORn		: SPI_VECTOR		= pfunc_handler;break;
		case INT2_VECTORn		: INT2_VECTOR		= pfunc_handler;break;
		case INT3_VECTORn		: INT3_VECTOR		= pfunc_handler;break;
		case TIMER2_VECTORn	: TIMER2_VECTOR	= pfunc_handler;break;
		case PWM_VECTORn		: PWM_VECTOR		= pfunc_handler;break;
		case INT4_VECTORn		: INT4_VECTOR		= pfunc_handler;break;
		case UART2_VECTORn	: UART2_VECTOR	= pfunc_handler;break;
		case UART3_VECTORn	: UART3_VECTOR	= pfunc_handler;break;
		case TIMER3_VECTORn	: TIMER3_VECTOR	= pfunc_handler;break;
		case TIMER4_VECTORn	: TIMER4_VECTOR	= pfunc_handler;break;
		case CMPIF_VECTORn	: CMPIF_VECTOR	= pfunc_handler;break;
	}
}

/*!
 *	@brief		中断开启或关闭控制函数
 *	@param		VECTORn		控制的中断
							able			关闭或开启控制位
 *	@warning	关闭后，该中断将被屏蔽不再响应
 *	@sampleusage:	Whether_IRQ(TIMER0_VECTORn , IRQ_enable);//使能定时器T0中断
 */

void Whether_IRQ(VECTORn_t VECTORn , bit able)
{
	switch(VECTORn)
	{
		case INT0_VECTORn		: if(able){EX0=1;EA=1;}else EX0=0;break;
		case TIMER0_VECTORn	: if(able){ET0=1;EA=1;}else ET0=0;break;
		case INT1_VECTORn		: if(able){EX1=1;EA=1;}else EX1=0;break;
		case TIMER1_VECTORn	: if(able){ET1=1;EA=1;}else ET1=0;break;
		case UART0_VECTORn	: break;
		case ADC_VECTORn		: if(able){EADC=1;EA=1;}else EADC=0;break;
		case LVD_VECTORn		: break;
		case CCP_VECTORn		: break;//已在CCP初始化时允许中断
		case UART1_VECTORn	:	break;
		case SPI_VECTORn		: break;
		case INT2_VECTORn		: break;
		case INT3_VECTORn		: break;
		case TIMER2_VECTORn	: if(able){BIT_SET(IE2,2);EA=1;}else BIT_CLR(IE2,2);break;
		case PWM_VECTORn		: break;
		case INT4_VECTORn		: break;
		case UART2_VECTORn	: break;
		case UART3_VECTORn	: break;
		case TIMER3_VECTORn	: if(able){BIT_SET(IE2,5);EA=1;}else BIT_CLR(IE2,5);break;
		case TIMER4_VECTORn	: if(able){BIT_SET(IE2,6);EA=1;}else BIT_CLR(IE2,6);break;
		case CMPIF_VECTORn	: break;
	}
}

void INT0_HANDLER() interrupt 0
{
	(*INT0_VECTOR)();
}

void TIMER0_HANDLER() interrupt 1
{
	(*TIMER0_VECTOR)();
}

void INT1_HANDLER() interrupt 2
{
	(*INT1_VECTOR)();
}

void TIMER1_HANDLER() interrupt 3
{
	(*TIMER1_VECTOR)();
}

void UART0_HANDLER() interrupt 4
{
	(*UART0_VECTOR)();
}

void ADC_HANDLER() interrupt 5
{
	(*ADC_VECTOR)();
}

void LVD_HANDLER() interrupt 6
{
	(*LVD_VECTOR)();
}

void CCP_HANDLER() interrupt 7
{
	(*CCP_VECTOR)();
}

void UART1_HANDLER() interrupt 8
{
	(*UART1_VECTOR)();
}

void SPI_HANDLER() interrupt 9
{
	(*SPI_VECTOR)();
}

void INT2_HANDLER() interrupt 10
{
	(*INT2_VECTOR)();
}

void INT3_HANDLER() interrupt 11
{
	(*INT3_VECTOR)();
}

void TIMER2_HANDLER() interrupt 12
{
	(*TIMER2_VECTOR)();
}

void PWM_HANDLER() interrupt 13
{
	(*PWM_VECTOR)();
}

void INT4_HANDLER() interrupt 16
{
	(*INT4_VECTOR)();
}

void UART2_HANDLER() interrupt 17
{
	(*UART2_VECTOR)();
}

void UART3_HANDLER() interrupt 18
{
	(*UART3_VECTOR)();
}

void TIMER3_HANDLER() interrupt 19
{
	(*TIMER3_VECTOR)();
}

void TIMER4_HANDLER() interrupt 20
{
	(*TIMER4_VECTOR)();
}

void CMPIF_HANDLER() interrupt 21
{
	(*CMPIF_VECTOR)();
}