/*
 * 包含头文件
 */
#include "common.h"
#include "STC_CCP.h"
#include "STC_gpio.h"
#include "STC_interrupt.h"

/*!
 *	@brief		PWM模式初始化
 *	@param		CCPn						CCP模块号选择
							IDLE_PCA_STATE	空闲模式下如何处置CCP状态(主要是CCP中的PCA计数器)
							PCA_CLK_SOURCE	PCA计数器计数脉冲源选择
							PWM_ACCURACY		PWM控制精度
							freq						PWM初始频率
							duty						PWM初始占空比
							CCF_INTERRUPT		如何捕获触发中断请求
 *	@warning	CCP_PWM模式输出所在IO口工作模式不得为浮空输入，上电初始化为准双向口
              要想引发中断应该要置位MAT,但手册上没写
							当PCA计数器计数脉冲由外部输入时不能调节其频率，就算初始化输入了频率也没作用，PWM输出频率等于外部输入频率/256
							freq可以改变PWM频率，但会影响其他模块的频率，因为三个模块共用一个时钟源
							freq参数有上限，不得大于最高可设置频率max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)))
 *	@sampleusage:	CCP_pwm_init(CCP0,IDLE_PCA_RUN,INTERNAL,PWM_8bit,50,26,CCF_INTERRUPT_DIS); //在CCP0模块、当空闲状态下任然运行、使用内部时钟、8位精度PWM、初始频率50Hz、初始占空比26/255、不启用中断
 */
 
void CCP_pwm_init(CCPn_e CCPn  ,  IDLE_PCA_STATE_e IDLE_PCA_STATE  ,  PCA_CLK_SOURCE_e PCA_CLK_SOURCE  ,
								  PWM_ACCURACY_e PWM_ACCURACY  ,  uint32 freq , uint8 duty , CCF_INTERRUPT_e CCF_INTERRUPT)
{
	uint32 max_freq = 0;//最大频率
	uint32 divide_factor=0;//分频系数
	
	if(ECI==p12 && CCP_0==p11 && CCP_1==p10 && CCP_2==p37)REPLACE(P_SW1,5,4,0);//配置CCP端口
	if(ECI==p34 && CCP_0==p35 && CCP_1==p36 && CCP_2==p37)REPLACE(P_SW1,5,4,1);//配置CCP端口
	if(ECI==p24 && CCP_0==p25 && CCP_1==p26 && CCP_2==p27)REPLACE(P_SW1,5,4,2);//配置CCP端口
	
	BIT_CLR(CCON,7);//清除计数器溢出标志
	BIT_CLR(CCON,6);//停止计数
	CH=0;CL=0;//清除PCA计数器
	
	if(IDLE_PCA_STATE == IDLE_PCA_RUN)	BIT_CLR(CMOD,7);//空闲模式下PCA计数器继续工作
	else if(IDLE_PCA_STATE == IDLE_PCA_STOP)	BIT_SET(CMOD,7);//空闲状态下PCA计数器停止工作
			 else return;//空闲模式下CCP工作状态配置错误
	
	if(CCPn == CCP0)
	{
		BIT_CLR(CCON,0);//清除捕获/匹配中断标志
		if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM0=0x42;//禁止触发中断
		else
		{
			if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM0=0x63;//允许当出现上升沿时发起中断请求
			else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM0=0x53;//允许当出现下降沿时发起中断请求
			else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM0=0x73;//允许当出现跳变沿时发起中断请求
		}
		
		if(PWM_ACCURACY == PWM_8bit)
	  {
			REPLACE(PCA_PWM0,7,6,0);//8位PWM
			max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
			if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
			else {CCAP0L = (0xff-duty);CCAP0H = (0xff-duty);BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
		}
		else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM0,7,6,1);//7位PWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
				   else {CCAP0L = (0x7f-(duty>>1));CCAP0H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
				 }
				 else if(PWM_ACCURACY == PWM_6bit)
				 {
					 REPLACE(PCA_PWM0,7,6,2);//6位PWM
					 max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0){CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
					 else {CCAP0L = (0x3f-(duty>>2));CCAP0H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
				 }
				 else return;//PWM精度设置错误
	}
	else if(CCPn == CCP1)
			 {
				 BIT_CLR(CCON,1);//清除捕获/匹配中断标志
				 if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM1=0x42;//禁止触发中断
				 else
				 {
					 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM1=0x63;//允许当出现上升沿时发起中断请求
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM1=0x53;//允许当出现下降沿时发起中断请求
								else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM1=0x73;//允许当出现跳变沿时发起中断请求
				 }
				 
				 if(PWM_ACCURACY == PWM_8bit)
				 {
					 REPLACE(PCA_PWM1,7,6,0);//8位PWM
					 max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
					 else {CCAP1L = (0xff-duty);CCAP1H = (0xff-duty);BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
				 }
				 else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM1,7,6,1);//7位PWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
					 else {CCAP1L = (0x7f-(duty>>1));CCAP1H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
				 }
						 else if(PWM_ACCURACY == PWM_6bit)
									{
										REPLACE(PCA_PWM1,7,6,2);//6位PWM
										max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
										if(duty==0){CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
										else {CCAP1L = (0x3f-(duty>>2));CCAP1H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
									}
									else return;//PWM精度设置错误
			 }
			 else if(CCPn == CCP2)
			 {
				 BIT_CLR(CCON,2);//清除捕获/匹配中断标志
				 if(CCF_INTERRUPT == CCF_INTERRUPT_DIS)	CCAPM2=0x42;//禁止触发中断
				 else
				 {
					 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM2=0x63;//允许当出现上升沿时发起中断请求
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM2=0x53;//允许当出现下降沿时发起中断请求
					 else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM2=0x73;//允许当出现跳变沿时发起中断请求
				 }
				 
				 if(PWM_ACCURACY == PWM_8bit)
				 {
					 REPLACE(PCA_PWM2,7,6,0);//8位PWM
					 max_freq = EXTAL_IN_Hz/(256*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
					 else {CCAP2L = (0xff-duty);CCAP2H = (0xff-duty);BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
				 }
				 else if(PWM_ACCURACY == PWM_7bit)
				 {
					 REPLACE(PCA_PWM2,7,6,1);//7位PWM
					 max_freq = EXTAL_IN_Hz/(128*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
					 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
					 else {CCAP2L = (0x7f-(duty>>1));CCAP2H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
				 }
							else if(PWM_ACCURACY == PWM_6bit)
							{
								REPLACE(PCA_PWM2,7,6,2);//6位PWM
								max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
								if(duty==0){CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
								else {CCAP2L = (0x3f-(duty>>2));CCAP2H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
							}
							else return;//PWM精度设置错误
			 }
			 else return;//CCP模块号配置错误
	
	if(PCA_CLK_SOURCE == EXTERNAL_ECI)	REPLACE(CMOD,3,1,3);//PCA计数器计数脉冲由外部输入（当需要和外部PWM保持相位时可用到）
	else if(PCA_CLK_SOURCE == INTERNAL)
			 {
				 if(freq!=0)
				 {
					 if(freq > max_freq)	return;//设置频率过高
					 else if(freq == max_freq)	REPLACE(CMOD,3,1,4);//使用系统时钟不分频作为PCA计数器计数脉冲时钟
								else if(freq >= (max_freq/2))	 REPLACE(CMOD,3,1,1);//使用系统时钟2分频作为PCA计数器计数脉冲时钟
										 else if(freq >= ((max_freq/4)-4) && freq <= (5+(max_freq/4)))	 REPLACE(CMOD,3,1,5);//使用系统时钟4分频作为PCA计数器计数脉冲时钟
													else if(freq >= ((max_freq/6)-4) && freq <= (5+(max_freq/6)))	 REPLACE(CMOD,3,1,6);//使用系统时钟6分频作为PCA计数器计数脉冲时钟
															 else if(freq >= ((max_freq/8)-4) && freq <= (5+(max_freq/8)))	 REPLACE(CMOD,3,1,7);//使用系统时钟8分频作为PCA计数器计数脉冲时钟
																		else if(freq >= ((max_freq/12)-4) && freq <= (5+(max_freq/12))) REPLACE(CMOD,3,1,0);//使用系统时钟12分频作为PCA计数器计数脉冲时钟
																				 else
																				 {
																					 divide_factor=max_freq/freq;//计算分频系数
																					 if(divide_factor > 0xffff) divide_factor = 0xffff;//设置分频系数限额
																					 divide_factor = 0xffff-divide_factor;//准备载入T0定时器填值
																					 
																					 REPLACE(CMOD,3,1,2);//使用定时器0的溢出作为PCA计数器计数脉冲时钟
																					 BIT_SET(AUXR,7);//T0时钟工作在1T模式下
																					 REPLACE(TMOD,3,0,0);//T0用作16位自动重装定时器
																					 TL0 = divide_factor;//分频系数
																					 TH0 = divide_factor >> 8;//分频系数
																					 TF0 = 0;//清除T0溢出标志
																					 TR0 = 1;//开启T0定时时器
																				 }
				}//若频率设置为“0”则频率为上一次初始化的频率或上电复位默认频率EXTAL_IN_Hz/12
			}
			else return;//PCA计数器计数脉冲输入源配置错误
	
	CR=1;//PCA计数器开始工作
}

/*!
 *	@brief		改变PWM频率
 *	@param		PWM_ACCURACY	PWM使用的精度			
							freq					要改变的频率
 *	@warning	三个CCP模块共用一个时钟源，所以频率是三个一起变的；若CCP0为PWM模式、CCP1是捕捉模式，则改变PWM频率后捕捉到的值也会随之改变
              freq参数有上限，不得大于最高可设置频率max_freq = EXTAL_IN_Hz/(64*(1+ACQUIRE(CLK_DIV,2,0)))
 *	@sampleusage:	CCP_pwm_freq(PWM_8bit,1400); //使用8位精度，设置为1400Hz
 */

void CCP_pwm_freq(PWM_ACCURACY_e PWM_ACCURACY , uint32 freq)//改变PWM频率
{
	uint32 max_freq = 0;
	uint32 divide_factor=0;
	
	max_freq = EXTAL_IN_Hz/(0xff >> PWM_ACCURACY*(1+ACQUIRE(CLK_DIV,2,0)));//解算出最大PWM频率
	if(freq!=0)
	{
		if(freq > max_freq)	return;//设置频率过高
		else if(freq == max_freq)	REPLACE(CMOD,3,1,4);//使用系统时钟不分频作为PCA计数器计数脉冲时钟
				 else if(freq >= (max_freq/2))	 REPLACE(CMOD,3,1,1);//使用系统时钟2分频作为PCA计数器计数脉冲时钟
							else if(freq >= ((max_freq/4)-4) && freq <= (5+(max_freq/4)))	 REPLACE(CMOD,3,1,5);//使用系统时钟4分频作为PCA计数器计数脉冲时钟
									 else if(freq >= ((max_freq/6)-4) && freq <= (5+(max_freq/6)))	 REPLACE(CMOD,3,1,6);//使用系统时钟6分频作为PCA计数器计数脉冲时钟
												else if(freq >= ((max_freq/8)-4) && freq <= (5+(max_freq/8)))	 REPLACE(CMOD,3,1,7);//使用系统时钟8分频作为PCA计数器计数脉冲时钟
														 else if(freq >= ((max_freq/12)-4) && freq <= (5+(max_freq/12))) REPLACE(CMOD,3,1,0);//使用系统时钟12分频作为PCA计数器计数脉冲时钟
																	else
																	{
																		divide_factor=max_freq/freq;//计算分频系数
																		if(divide_factor > 0xffff) divide_factor = 0xffff;//设置分频系数限额
																		divide_factor = 0xffff-divide_factor;//准备载入T0定时器填值
																		
																		REPLACE(CMOD,3,1,2);//使用定时器0的溢出作为PCA计数器计数脉冲时钟
																		BIT_SET(AUXR,7);//T0时钟工作在1T模式下
																		REPLACE(TMOD,3,0,0);//T0用作16位自动重装定时器
																		TL0 = divide_factor;//分频系数
																		TH0 = divide_factor >> 8;//分频系数
																		TF0 = 0;//清除T0溢出标志
																		TR0 = 1;//开启T0定时时器
																	}
	}//若频率设置为“0”则频率为上一次初始化的频率
}

/*!
 *	@brief		更新PWM占空比
 *	@param		CCPn				模块号
							duty				占空比
 *	@warning	占空比的范围是0~255
 *	@sampleusage:	CCP_pwm_duty(CCP0 , 12); //将CCP0的PWM的占空比设置为12/255
 */

void CCP_pwm_duty(CCPn_e CCPn , uint8 duty)
{
	if(CCPn == CCP0)
	{
		if(0 == ACQUIRE(PCA_PWM0,7,6))//获取PWM设置精度值
		{
			if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
			else {CCAP0L = (0xff-duty);CCAP0H = (0xff-duty);BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
		}
		else if(1 == ACQUIRE(PCA_PWM0,7,6))//获取PWM设置精度值
				 {
					 if(duty==0) {CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
				   else {CCAP0L = (0x7f-(duty>>1));CCAP0H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
				 }
				 else if(2 == ACQUIRE(PCA_PWM0,7,6))//获取PWM设置精度值
							{
								if(duty==0){CCAP0L=0xff;CCAP0H=0xff;BIT_SET(PCA_PWM0,1);BIT_SET(PCA_PWM0,0);}//设置0占空比
								else {CCAP0L = (0x3f-(duty>>2));CCAP0H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM0,0);BIT_CLR(PCA_PWM0,1);}//设置占空比
							}
	}
	else if(CCPn == CCP1)
			 {
				 if(0 == ACQUIRE(PCA_PWM1,7,6))//获取PWM设置精度值
				 {
					 if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
					 else {CCAP1L = (0xff-duty);CCAP1H = (0xff-duty);BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
				 }
				 else if(1 == ACQUIRE(PCA_PWM1,7,6))//获取PWM设置精度值
							{
								if(duty==0) {CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
								else {CCAP1L = (0x7f-(duty>>1));CCAP1H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
							}
							else if(2 == ACQUIRE(PCA_PWM1,7,6))//获取PWM设置精度值
									 {
										 if(duty==0){CCAP1L=0xff;CCAP1H=0xff;BIT_SET(PCA_PWM1,1);BIT_SET(PCA_PWM1,0);}//设置0占空比
										 else {CCAP1L = (0x3f-(duty>>2));CCAP1H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM1,0);BIT_CLR(PCA_PWM1,1);}//设置占空比
									 }
			 }
			 else if(CCPn == CCP2)
						{
							if(0 == ACQUIRE(PCA_PWM2,7,6))//获取PWM设置精度值
							{
								if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
								else {CCAP2L = (0xff-duty);CCAP2H = (0xff-duty);BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
							}
							else if(1 == ACQUIRE(PCA_PWM2,7,6))//获取PWM设置精度值
									 {
										 if(duty==0) {CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
										 else {CCAP2L = (0x7f-(duty>>1));CCAP2H = (0x7f-(duty>>1));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
									 }
									 else if(2 == ACQUIRE(PCA_PWM2,7,6))//获取PWM设置精度值
												{
													if(duty==0){CCAP2L=0xff;CCAP2H=0xff;BIT_SET(PCA_PWM2,1);BIT_SET(PCA_PWM2,0);}//设置0占空比
													else {CCAP2L = (0x3f-(duty>>2));CCAP2H = (0x3f-(duty>>2));BIT_CLR(PCA_PWM2,0);BIT_CLR(PCA_PWM2,1);}//设置占空比
												}
						}
}

/*!
 *	@brief		捕获模式初始化
 *	@param		CCPn						CCP模块号选择
							IDLE_PCA_STATE	空闲模式下如何处置CCP状态(主要是CCP中的PCA计数器)
							PCA_CLK_SOURCE	PCA计数器计数脉冲源选择
							freq						时钟源频率 = 数值/时间（秒为单位）
															如：想要测量0.02ms的脉宽显示数值想要为“256”，则freq = 256/0.02
							CCF_INTERRUPT		如何捕获触发中断请求
 *	@warning	单位脉宽时间=1/freq，它影响着脉宽采集的精度，时钟频率越高、单位脉宽时间越短、采集脉宽时间精度越高，但会影响其他模块的频率，因为三个模块共用一个时钟源
              freq参数有上限，最大不得大于晶振频率EXTAL_IN_Hz！
              CCF_INTERRUPT当需要测量的是信号周期时，则可用CCF_INTERRUPT_RISE或CCF_INTERRUPT_FALL或CCF_INTERRUPT_JUMP三种触发方式，建议使用前两种，因为这样可以测量更高频率的信号，具体选择依据信号类型而定。
                           当需要测量的是信号的正或负脉宽时，则只能使用CCF_INTERRUPT_JUMP触发方式，否则不能工作。
              CCP捕获模式所在IO口的工作模式不得为强推挽输出模式，上电初始化为准双向口
              经过测试得出：在高频信号下且CCP捕获时钟速率达到晶振频率时，要求两次触发时间间隔大于256倍的晶振周期方可获得稳定数据，待测量信号速度必须低于这个要求。
 *	@sampleusage:	CCP_input_init(CCP0  ,  IDLE_PCA_RUN  ,  INTERNAL  ,  EXTAL_IN_Hz  ,  CCF_INTERRUPT_JUMP);//CCP0用于信号捕获模式、空闲模式下CCP模块依旧工作、使用内部时钟作为计数源、捕获时钟频率设置为晶振频率、触发方式为跳变沿触发
 */

void CCP_input_init(CCPn_e CCPn  ,  IDLE_PCA_STATE_e IDLE_PCA_STATE  ,  PCA_CLK_SOURCE_e PCA_CLK_SOURCE  ,  uint32 freq  ,  CCF_INTERRUPT_e CCF_INTERRUPT)
{
	uint32 divide_factor=0;//分频系数
	if(ECI==p12 && CCP_0==p11 && CCP_1==p10 && CCP_2==p37)REPLACE(P_SW1,5,4,0);//配置CCP0端口
	if(ECI==p34 && CCP_0==p35 && CCP_1==p36 && CCP_2==p37)REPLACE(P_SW1,5,4,1);//配置CCP0端口
	if(ECI==p24 && CCP_0==p25 && CCP_1==p26 && CCP_2==p27)REPLACE(P_SW1,5,4,2);//配置CCP0端口
	
	BIT_CLR(CCON,7);//清除计数器溢出标志
	BIT_CLR(CCON,6);//停止计数
	CH=0;CL=0;//清除PCA计数器
	
	if(IDLE_PCA_STATE == IDLE_PCA_RUN)	BIT_CLR(CMOD,7);//空闲模式下PCA计数器继续工作
	else if(IDLE_PCA_STATE == IDLE_PCA_STOP)	BIT_SET(CMOD,7);//空闲状态下PCA计数器停止工作
			 else return;//空闲模式下CCP工作状态配置错误
	
	if(CCPn == CCP0)
	{
		BIT_CLR(CCON,0);//清除中断标志
		CCAP0L=0;//清除捕捉保存值
		CCAP0H=0;//清除捕捉保存值
		PCA_PWM0=0x00;//清除PWM模式寄存器
		if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM0=0x21;//上升沿捕获
		else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM0=0x11;//下降沿捕获
		else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM0=0x31;//跳变沿捕获
	}
	else if(CCPn == CCP1)
			 {
				 BIT_CLR(CCON,1);//清除捕获/匹配中断标志
				 CCAP1L=0;//清除捕捉保存值
				 CCAP1H=0;//清除捕捉保存值
				 PCA_PWM1=0x00;//清除PWM模式寄存器
				 if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM1=0x21;//上升沿捕获
				 else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM1=0x11;//下降沿捕获
				 else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM1=0x31;//跳变沿捕获
			 }
			 else if(CCPn == CCP2)
						{
							BIT_CLR(CCON,2);//清除捕获/匹配中断标志
							CCAP2L=0;//清除捕捉保存值
							CCAP2H=0;//清除捕捉保存值
							PCA_PWM2=0x00;//清除PWM模式寄存器
							if(CCF_INTERRUPT == CCF_INTERRUPT_RISE)	 CCAPM2=0x21;//上升沿捕获
							else if(CCF_INTERRUPT == CCF_INTERRUPT_FALL)	CCAPM2=0x11;//下降沿捕获
							else if(CCF_INTERRUPT == CCF_INTERRUPT_JUMP)	CCAPM2=0x31;//跳变沿捕获
						}
						else return;//CCP模块号配置错误
	if(PCA_CLK_SOURCE == EXTERNAL_ECI)	REPLACE(CMOD,3,1,3);//PCA计数器计数脉冲由外部输入（当需要和外部PWM保持相位时可用到）
	else if(PCA_CLK_SOURCE == INTERNAL)
			 {
				 if(freq!=0)
				 {
					 if(freq > EXTAL_IN_Hz)	return;//设置频率过高
					 else if(freq == EXTAL_IN_Hz)	REPLACE(CMOD,3,1,4);//使用系统时钟不分频作为PCA计数器计数脉冲时钟
								else if(freq >= (EXTAL_IN_Hz/2))	 REPLACE(CMOD,3,1,1);//使用系统时钟2分频作为PCA计数器计数脉冲时钟
										 else if(freq >= ((EXTAL_IN_Hz/4)-4) && freq <= (5+(EXTAL_IN_Hz/4)))	 REPLACE(CMOD,3,1,5);//使用系统时钟4分频作为PCA计数器计数脉冲时钟
													else if(freq >= ((EXTAL_IN_Hz/6)-4) && freq <= (5+(EXTAL_IN_Hz/6)))	 REPLACE(CMOD,3,1,6);//使用系统时钟6分频作为PCA计数器计数脉冲时钟
															 else if(freq >= ((EXTAL_IN_Hz/8)-4) && freq <= (5+(EXTAL_IN_Hz/8)))	 REPLACE(CMOD,3,1,7);//使用系统时钟8分频作为PCA计数器计数脉冲时钟
																		else if(freq >= ((EXTAL_IN_Hz/12)-4) && freq <= (5+(EXTAL_IN_Hz/12))) REPLACE(CMOD,3,1,0);//使用系统时钟12分频作为PCA计数器计数脉冲时钟
																				 else
																				 {
																					 divide_factor=EXTAL_IN_Hz/freq;//计算分频系数
																					 if(divide_factor > 0xffff) divide_factor = 0xffff;//设置分频系数限额
																					 divide_factor = 0xffff-divide_factor;//准备载入T0定时器填值
																					 
																					 REPLACE(CMOD,3,1,2);//使用定时器0的溢出作为PCA计数器计数脉冲时钟
																					 BIT_SET(AUXR,7);//T0时钟工作在1T模式下
																					 REPLACE(TMOD,3,0,0);//T0用作16位自动重装定时器
																					 TL0 = divide_factor;//分频系数
																					 TH0 = divide_factor >> 8;//分频系数
																					 TF0 = 0;//清除T0溢出标志
																					 TR0 = 1;//开启T0定时时器
																				 }
				}
			}//若频率设置为“0”则频率为上一次初始化的频率或上电复位默认频率EXTAL_IN_Hz/12
	set_vector_handler(CCP_VECTORn , PCA_IRQHandler);//将PCA中断的服务函数设定为PCA_IRQHandler()
	BIT_SET(CMOD,0);//允许PCA计数溢出中断
	CR = 1;
	EA = 1;
}

/*!
 *	@brief		获取信号时间长度特征
 *	@param		CCPn						CCP模块号选择
							SIGNAL_FEATURE	信号时间特征
 *	@warning	
 *	@sampleusage:	CCP_input_PULSE_WIDTH(CCP0,POSITIVE_PULSE_WIDTH);//获取CCP0捕获信号的正脉宽
 */

uint32 data CCP0_PULSE0_WIDTH = 0 , CCP0_PULSE1_WIDTH = 0,
			      CCP1_PULSE0_WIDTH = 0 , CCP1_PULSE1_WIDTH = 0,
			      CCP2_PULSE0_WIDTH = 0 , CCP2_PULSE1_WIDTH = 0;

uint32 CCP_input_PULSE_WIDTH(CCPn_e CCPn ,  SIGNAL_FEATURE_e SIGNAL_FEATURE)//获取信号时间长度特征
{
	if(CCPn == CCP0)
	{
		if(ACQUIRE(CCAPM0,5,4)==3)//跳变沿触发
		{
			if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP0_PULSE1_WIDTH;//正脉宽
			else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP0_PULSE0_WIDTH;//负脉宽
					 else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP0_PULSE1_WIDTH + CCP0_PULSE0_WIDTH;//周期
		}
		else//单上升沿或单下降沿触发
		{
			if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP0_PULSE0_WIDTH;//周期
			else return 0;//该触发方式不能测量此时间特征
		}
	}
	else if(CCPn == CCP1)
			 {
				 if(ACQUIRE(CCAPM1,5,4)==3)//跳变沿触发
				 {
					 if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP1_PULSE1_WIDTH;//正脉宽
					 else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP1_PULSE0_WIDTH;//负脉宽
								else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP1_PULSE1_WIDTH + CCP1_PULSE0_WIDTH;//周期
				 }
				 else//单上升沿或单下降沿触发
				 {
					 if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP1_PULSE0_WIDTH;//周期
					 else return 0;//该触发方式不能测量此时间特征
				 }
			 }
			 else if(CCPn == CCP2)
						{
							if(ACQUIRE(CCAPM2,5,4)==3)//跳变沿触发
							{
								if(SIGNAL_FEATURE == POSITIVE_PULSE_WIDTH) return CCP2_PULSE1_WIDTH;//正脉宽
								else if(SIGNAL_FEATURE == NEGATIVE_PULSE_WIDTH)	return CCP2_PULSE0_WIDTH;//负脉宽
										 else if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP2_PULSE1_WIDTH + CCP2_PULSE0_WIDTH;//周期
							}
							else//单上升沿或单下降沿触发
							{
								if(SIGNAL_FEATURE == CYCLE_LENGTH)	return CCP2_PULSE0_WIDTH;//周期
								else return 0;//该触发方式不能测量此时间特征
							}
						}
	return 0;////CCP模块号配置错误
}

/*!
 *	@brief		CCP中断函数
 *	@param		
 *	@warning	CCP所有中断都会进入，因此每次进入中断都需要判断引发中断的原因
 *	@sampleusage:	
 */

uint16 data CCP0_LAST_STIGGER_MODE_TIME = 0 , CCAP0_LAST_DATA = 0 , CCAP0_NOW_DATA = 0,
			      CCP1_LAST_STIGGER_MODE_TIME = 0 , CCAP1_LAST_DATA = 0 , CCAP1_NOW_DATA = 0,
			      CCP2_LAST_STIGGER_MODE_TIME = 0 , CCAP2_LAST_DATA = 0 , CCAP2_NOW_DATA = 0;

void	PCA_IRQHandler (void)
{
	if(CF)//定时器溢出中断
	{
		CF = 0;
		CCP0_LAST_STIGGER_MODE_TIME++;
		CCP1_LAST_STIGGER_MODE_TIME++;
		CCP2_LAST_STIGGER_MODE_TIME++;
	}
	
	if(CCF0 && (BIT_GET(CCAPM0,1)==0) && (BIT_GET(CCAPM0,3)==0))//CCP0捕获模式捕捉中断
	{
		if(ACQUIRE(CCAPM0,5,4)==3)//跳变沿触发
		{
			if(gpio_get(CCP_0))//记录的数据为负脉宽
			{
				CCF0 = 0;
				CCAP0_LAST_DATA = CCAP0_NOW_DATA;
				((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
				((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
				if(CCP0_LAST_STIGGER_MODE_TIME==0)
				{
					CCP0_PULSE0_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP0_PULSE0_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//记录的数据为正脉宽
			{
				CCF0 = 0;
				CCAP0_LAST_DATA = CCAP0_NOW_DATA;
				((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
				((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
				if(CCP0_LAST_STIGGER_MODE_TIME==0)
				{
					CCP0_PULSE1_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP0_PULSE1_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
					CCP0_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//单上升沿或单下降沿触发
		{
			CCF0 = 0;
			CCAP0_LAST_DATA = CCAP0_NOW_DATA;
			((uint8 *) & CCAP0_NOW_DATA)[0] = CCAP0H;
			((uint8 *) & CCAP0_NOW_DATA)[1] = CCAP0L;
			if(CCP0_LAST_STIGGER_MODE_TIME==0)
			{
				CCP0_PULSE0_WIDTH = CCAP0_NOW_DATA - CCAP0_LAST_DATA;
				CCP0_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP0_PULSE0_WIDTH = (--CCP0_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP0_NOW_DATA+0x10000-CCAP0_LAST_DATA);
				CCP0_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
	
	if(CCF1 && (BIT_GET(CCAPM1,1)==0) && (BIT_GET(CCAPM1,3)==0))//CCP1捕获模式捕捉中断
	{
		if(ACQUIRE(CCAPM1,5,4)==3)//跳变沿触发
		{
			if(gpio_get(CCP_1))//记录的数据为负脉宽
			{
				CCF1 = 0;
				CCAP1_LAST_DATA = CCAP1_NOW_DATA;
				((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
				((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
				if(CCP1_LAST_STIGGER_MODE_TIME==0)
				{
					CCP1_PULSE0_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP1_PULSE0_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//记录的数据为正脉宽
			{
				CCF1 = 0;
				CCAP1_LAST_DATA = CCAP1_NOW_DATA;
				((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
				((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
				if(CCP1_LAST_STIGGER_MODE_TIME==0)
				{
					CCP1_PULSE1_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP1_PULSE1_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
					CCP1_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//单上升沿或单下降沿触发
		{
			CCF1 = 0;
			CCAP1_LAST_DATA = CCAP1_NOW_DATA;
			((uint8 *) & CCAP1_NOW_DATA)[0] = CCAP1H;
			((uint8 *) & CCAP1_NOW_DATA)[1] = CCAP1L;
			if(CCP1_LAST_STIGGER_MODE_TIME==0)
			{
				CCP1_PULSE0_WIDTH = CCAP1_NOW_DATA - CCAP1_LAST_DATA;
				CCP1_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP1_PULSE0_WIDTH = (--CCP1_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP1_NOW_DATA+0x10000-CCAP1_LAST_DATA);
				CCP1_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
	
	if(CCF2 && (BIT_GET(CCAPM2,1)==0) && (BIT_GET(CCAPM2,3)==0))//CCP2捕获模式捕捉中断
	{
		if(ACQUIRE(CCAPM2,5,4)==3)//跳变沿触发
		{
			if(gpio_get(CCP_2))//记录的数据为负脉宽
			{
				CCF2 = 0;
				CCAP2_LAST_DATA = CCAP2_NOW_DATA;
				((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
				((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
				if(CCP2_LAST_STIGGER_MODE_TIME==0)
				{
					CCP2_PULSE0_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP2_PULSE0_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
			}
			else//记录的数据为正脉宽
			{
				CCF2 = 0;
				CCAP2_LAST_DATA = CCAP2_NOW_DATA;
				((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
				((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
				if(CCP2_LAST_STIGGER_MODE_TIME==0)
				{
					CCP2_PULSE1_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
				else
				{
					CCP2_PULSE1_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
					CCP2_LAST_STIGGER_MODE_TIME = 0;
				}
			}
		}
		else//单上升沿或单下降沿触发
		{
			CCF2 = 0;
			CCAP2_LAST_DATA = CCAP2_NOW_DATA;
			((uint8 *) & CCAP2_NOW_DATA)[0] = CCAP2H;
			((uint8 *) & CCAP2_NOW_DATA)[1] = CCAP2L;
			if(CCP2_LAST_STIGGER_MODE_TIME==0)
			{
				CCP2_PULSE0_WIDTH = CCAP2_NOW_DATA - CCAP2_LAST_DATA;
				CCP2_LAST_STIGGER_MODE_TIME = 0;
			}
			else
			{
				CCP2_PULSE0_WIDTH = (--CCP2_LAST_STIGGER_MODE_TIME)*0x10000+(CCAP2_NOW_DATA+0x10000-CCAP2_LAST_DATA);
				CCP2_LAST_STIGGER_MODE_TIME = 0;
			}
		}
	}
}