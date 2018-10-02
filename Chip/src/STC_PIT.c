#include "common.h"
#include "STC_PIT.h"

/*!
 *	@brief		�ر�PIT��ʱ
 *	@param		
 *	@warning	
 *	@sampleusage:	
 */
 
void pit_close(TIMERn_e timer)//�ر�PIT��ʱ
{
	switch(timer)
	{
		case T0 : TR0=0;break;
		case T1 : TR1=0;break;
		case T2 : BIT_CLR(AUXR,4); break;
		case T3 : BIT_CLR(T4T3M,3);break;
		case T4 : BIT_CLR(T4T3M,7);break;
	}
}

/*!
 *	@brief		��ʼ��PIT�����ö�ʱʱ��
 *	@param		timer		��ʱ��ģ���
							num			��ʱʱ��
 *	@warning	Ĭ��ʹ��16λ�Զ���װģʽ
 *	@sampleusage:	pit_init(T0,10000);//����T0��ʱ��,���Ҷ�ʱʱ��Ϊ10000��ϵͳ����
 */

void pit_init(TIMERn_e timer , uint16 num)//��ʼ����������ʱ��
{
	num = 0xffff - num;//�������Ҫ���붨ʱ�������Ĵ�����ֵ
	if(timer == T0)//��ʹ��T0��ʱ��
		{
			TF0 = 0;//�������жϱ�־
			BIT_SET(AUXR,7);//T0��ʱ��������1Tģʽ��ϵͳʱ�Ӳ���Ƶ��Ϊ��ʱ�����ࣩ
			REPLACE(TMOD,3,0,0);//16λ�Զ���װ�������ⲿ���ſ��ƣ���ʱ��
			TL0 = num;//���ö�ʱ����ʱ����
			TH0 = num>>8;////���ö�ʱ����ʱ����
			TR0 = 1;//T0��ʱ����ʼ��ʱ
		}
		else if(timer == T1)
				 {
					 TF1 = 0;//�������жϱ�־
					 BIT_SET(AUXR,6);//T1��ʱ��������1Tģʽ��ϵͳʱ�Ӳ���Ƶ��Ϊ��ʱ�����ࣩ
					 REPLACE(TMOD,7,4,0);//16λ�Զ���װ�������ⲿ���ſ��ƣ���ʱ��
					 TL1 = num;//���ö�ʱ����ʱ����
					 TH1 = num>>8;//���ö�ʱ����ʱ����
					 TR1 = 1;//T1��ʱ����ʼ��ʱ
				 }
				 else if(timer == T2)
							{
								BIT_SET(AUXR,2);//T2��ʱ��������1Tģʽ��ϵͳʱ�Ӳ���Ƶ��Ϊ��ʱ�����ࣩ
								T2L = num;//���ö�ʱ����ʱ����
								T2H = num>>8;//���ö�ʱ����ʱ����
								BIT_CLR(AUXR,3);//T2������ʱ��
								BIT_SET(AUXR,4);//T2��ʱ����ʼ��ʱ
							}
							else if(timer == T3)
									 {
										 BIT_SET(T4T3M,1);//T3��ʱ��������1Tģʽ��ϵͳʱ�Ӳ���Ƶ��Ϊ��ʱ�����ࣩ
										 T3L = num;//���ö�ʱ����ʱ����
										 T3H = num>>8;//���ö�ʱ����ʱ����
										 BIT_CLR(T4T3M,2);//T3������ʱ��
										 BIT_SET(T4T3M,3);//T3��ʱ����ʼ��ʱ
									 }
									 else if(timer == T4)
												{
													BIT_SET(T4T3M,5);//T4��ʱ��������1Tģʽ��ϵͳʱ�Ӳ���Ƶ��Ϊ��ʱ�����ࣩ
													T4L = num;//���ö�ʱ����ʱ����
													T4H = num>>8;//���ö�ʱ����ʱ����
													BIT_CLR(T4T3M,6);//T4������ʱ��
													BIT_SET(T4T3M,7);//T4��ʱ����ʼ��ʱ
												}
}

/*!
 *	@brief		���Ķ�ʱʱ��
 *	@param		timer		��ʱ��ģ���
							num			��ʱʱ��
 *	@warning	
 *	@sampleusage:	pit_change(T0,500);//��T0��ʱ���Ķ�ʱʱ�����Ϊ500��ϵͳ����
 */

void pit_change(TIMERn_e timer , uint16 num)
{
	num = 0xffff - num;//�������Ҫ���붨ʱ�������Ĵ�����ֵ
	if(timer == T0)//��ʹ��T0��ʱ��
		{
			TL0 = num;//���ö�ʱ����ʱ����
			TH0 = num>>8;////���ö�ʱ����ʱ����
		}
		else if(timer == T1)
				 {
					 TL1 = num;//���ö�ʱ����ʱ����
					 TH1 = num>>8;//���ö�ʱ����ʱ����
				 }
				 else if(timer == T2)
							{
								T2L = num;//���ö�ʱ����ʱ����
								T2H = num>>8;//���ö�ʱ����ʱ����
							}
							else if(timer == T3)
									 {
										 T3L = num;//���ö�ʱ����ʱ����
										 T3H = num>>8;//���ö�ʱ����ʱ����
									 }
									 else if(timer == T4)
												{
													T4L = num;//���ö�ʱ����ʱ����
													T4H = num>>8;//���ö�ʱ����ʱ����
												}
}

/*!
 *	@brief		��ȡ��ʱ����ǰ��ʱ��ֵ
 *	@param		timer   	��ʱ��ģ���
 *	@warning  ��ʱ����ʱ�����Ǵ�0��ʼ��ÿ��һ����ʱ������ֵ����1
 *	@sampleusage:	pit_get(T0); //��ȡT0��ʱ����ǰ����ֵ
 */
uint16 pit_get(TIMERn_e timer)
{
	if(timer == T0) return (TH0<<8)|TL0;//��ʹ��T0��ʱ��
		else if(timer == T1) return (TH1<<8)|TL1;
				 else if(timer == T2) return (T2H<<8)|T2L;
							else if(timer == T3) return (T3H<<8)|T3L;
									 else if(timer == T4) return (T4H<<8)|T4L;
												else return 0;
}