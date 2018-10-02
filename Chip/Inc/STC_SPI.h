#ifndef __STC_SPI_H__
#define __STC_SPI_H__

typedef enum
{
	SLAVE, //SPI�ӻ�
	MASTER,//SPI����
}M_S_MODE_e;//����ģʽѡ��

typedef enum
{
	MSB_SPI,//��λ�ȷ��ͻ����
	LSB_SPI,//��λ�ȷ��ͻ����
}BIT_ERDER_e;//SPI���ݷ��ͺͽ��յ�λ˳��ѡ��

typedef enum
{
	SPI_MODE0,//SPIģʽ0������ʱSCLK=0��ǰʱ���ز�������ȡ���ݣ���
	SPI_MODE1,//SPIģʽ1������ʱSCLK=0����ʱ���ز�������ȡ���ݣ���
	SPI_MODE2,//SPIģʽ2������ʱSCLK=1��ǰʱ���ز�������ȡ���ݣ���
	SPI_MODE3,//SPIģʽ3������ʱSCLK=1����ʱ���ز�������ȡ���ݣ���
}SPI_MODEn_e;//SPI����ģʽ

typedef enum
{
	FRAC_4_SPEAD,		//4��Ƶϵͳʱ���ٶ�
	FRAC_16_SPEAD,	//16��Ƶϵͳʱ���ٶ�
	FRAC_64_SPEAD,	//64��Ƶϵͳʱ���ٶ�
	FRAC_128_SPEAD,	//128��Ƶϵͳʱ���ٶ�
}SCLK_SPEADn_e;//SPIʱ������

extern void SPI_init(M_S_MODE_e , BIT_ERDER_e , SPI_MODEn_e , SCLK_SPEADn_e);//SPI��ʼ��
extern void SPI_SendData(uint8 dat);//����1�ֽ�����
	
void SPI_IRQHandler(void);//SPI�ж�

#endif //__STC_SPI_H__