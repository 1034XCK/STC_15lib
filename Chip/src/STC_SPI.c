#include "common.h"
#include "STC_SPI.h"
#include "STC_interrupt.h"
#include "STC_gpio.h"
#include "STC_UART.h"//SPIת����ʱʹ��

bit SPI_BUSY = 0;//SPI����æ״̬��æʱ���ö����ݼĴ���д����

/*!
 *	@brief		SPI��ʼ��
 *	@param		M_S_MODE		����ģʽѡ��
							BIT_ERDER		λ����˳�򣨸�λ��ǰ���ǵ�λ��ǰ��
							SPI_MODEn		SPIģʽѡ��0~4��
							SCLK_SPEADn	SPI����ѡ��
 *	@warning	SPI���ݻ�ʱ����������IO�ڹ���ģʽ��ע�⣬�ϵ��ʼ��Ϊ׼˫���
              ����STC��Ƭ���Դ���Ӳ��SPI��ÿ��ֻ֧��8λ���䣬�����������е�SPI��������Ӳ��SPI���㲻�˿ɲο�STC_soft_SPI
 *	@sampleusage:	SPI_init(MASTER,MSB_SPI,SPI_MODE0,FRAC_128_SPEAD);//SPI����������ģʽ����λ�ȷ��ͣ�ģʽ0��ϵͳ128��Ƶ����
 */

void SPI_init(M_S_MODE_e M_S_MODE , BIT_ERDER_e BIT_ERDER , SPI_MODEn_e SPI_MODEn , SCLK_SPEADn_e SCLK_SPEADn)
{
	if(SPI_MOSI==p13 && SPI_MISO==p14 && SPI_SCLK==p15)	REPLACE(P_SW1,3,2,0);
	else if(SPI_MOSI==p23 && SPI_MISO==p22 && SPI_SCLK==p21)	REPLACE(P_SW1,3,2,1);
			 else if(SPI_MOSI==p40 && SPI_MISO==p41 && SPI_SCLK==p43)	REPLACE(P_SW1,3,2,2);
	SPDAT  = 0x00;//���SPI���ݼĴ���
	SPSTAT = 0xff;//���SPI������ɼ�д��ͻ��־
	BIT_SET(SPCTL,7);//����SS���ţ��������������
	REPLACE(SPCTL,4,4,M_S_MODE);//����ģʽѡ��
	REPLACE(SPCTL,5,5,BIT_ERDER);//SPI���ݷ��ͺͽ��յ�λ˳��ѡ��
	REPLACE(SPCTL,3,2,SPI_MODEn);//SPIģʽѡ��
	REPLACE(SPCTL,1,0,SCLK_SPEADn);//SPIʱ������ѡ��
	
	BIT_SET(SPCTL,6);//����SPIģ��
	set_vector_handler(SPI_VECTORn , SPI_IRQHandler);//SPI���жϷ�����ΪSPI_IRQHandler
	BIT_SET(IE2,1);//����SPI�ж�
	EA=1;
}

/*!
 *	@brief		SPI�жϣ�����Ϊ����
 *	@param		
 *	@warning	�ɴ˽���SPI������
 *	@sampleusage:	������һ���ֹ�����жϺ���
 */

void SPI_IRQHandler(void)
{
	SPSTAT = 0xff;//���SPI������ɼ�д��ͻ��־
	SPI_BUSY = 0;
	//��������SPDAT
	//Uart_SendData(UART0,SPDAT);//����SPI��ͨ��UART�ش����ݡ�SPIת����ʱʹ�á�
}

/*!
 *	@brief		SPI����1�ֽ�����
 *	@param		dat	Ҫ���͵�1�ֽ�����
 *	@warning	
 *	@sampleusage:	SPI_SendData(0x10);//��SPI���߷���8λ����0x10
 */

void SPI_SendData(uint8 dat)
{
	while(SPI_BUSY);//�ȴ���һ֡���ݷ������
	SPI_BUSY = 1;
	SPDAT = dat;
}