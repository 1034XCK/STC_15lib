/*
 * ����ͷ�ļ�
 */
#include "common.h"
#include "STC_gpio.h"

/*!
 *	@brief		��ʼ������gpio��
 *	@param		pxn				IO��
 *	@param		mode			����ģʽ��
 *																WEAKPULLUP		//������˫��ڡ�����״̬���������IO=1->0��15uA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																STRONGPULLUP	//ǿ����˫��ڡ���ģʽǿ�ҽ����������������������룬����״̬���������IO=1->0��>25mA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																FLOATEDINPUT	//�������롾��֧������״̬�������������������Ϊ0A��IO�ڳʸ���̬���������״̬��
 *																DRAIN_OPEN		//��©˫��ڡ�����״̬���������IO=1->0��0A,IO=0->1��>50mA�����״̬�ṩ������֮��
 *	@param	  level_state	��ʼ��ƽ��0=�͵�ƽ��1=�ߵ�ƽ	��������ģʽ��Ч��
 *  @warning  �����������ŵ�IO��ģʽ����Ϊǿ����˫���
 *	@Sampleusage:	gpio_init(p25, STRONGPULLUP, 0);
 */
void gpio_init(pxn_e pxn,  port_mode mode,  uint8 level_state)//��ʼ��GPIO����(�ĸ����ţ�ʲôģʽ����ʼ��ƽ)
{
	switch(px(pxn))
	{
		case 0 :
			//����P0M0��P0M1������IO��ģʽ
			if(BIT_GET(mode,0)) BIT_SET(P0M0,pn(pxn));else BIT_CLR(P0M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P0M1,pn(pxn));else BIT_CLR(P0M1,pn(pxn));
			//IO���������
			if(level_state)     BIT_SET(P0,pn(pxn));  else BIT_CLR(P0,pn(pxn));
			break;
		case 1 :
			if(BIT_GET(mode,0)) BIT_SET(P1M0,pn(pxn));else BIT_CLR(P1M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P1M1,pn(pxn));else BIT_CLR(P1M1,pn(pxn));
			if(level_state)     BIT_SET(P1,pn(pxn));  else BIT_CLR(P1,pn(pxn));
			break;
		case 2 :
			if(BIT_GET(mode,0)) BIT_SET(P2M0,pn(pxn));else BIT_CLR(P2M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P2M1,pn(pxn));else BIT_CLR(P2M1,pn(pxn));
			if(level_state)     BIT_SET(P2,pn(pxn));  else BIT_CLR(P2,pn(pxn));
			break;
		case 3 :
			if(BIT_GET(mode,0)) BIT_SET(P3M0,pn(pxn));else BIT_CLR(P3M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P3M1,pn(pxn));else BIT_CLR(P3M1,pn(pxn));
			if(level_state)     BIT_SET(P3,pn(pxn));  else BIT_CLR(P3,pn(pxn));
			break;
		case 4 :
			if(BIT_GET(mode,0)) BIT_SET(P4M0,pn(pxn));else BIT_CLR(P4M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P4M1,pn(pxn));else BIT_CLR(P4M1,pn(pxn));
			if(level_state)     BIT_SET(P4,pn(pxn));  else BIT_CLR(P4,pn(pxn));
			break;
		case 5 :
			if(BIT_GET(mode,0)) BIT_SET(P5M0,pn(pxn));else BIT_CLR(P5M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P5M1,pn(pxn));else BIT_CLR(P5M1,pn(pxn));
			if(level_state)     BIT_SET(P5,pn(pxn));  else BIT_CLR(P5,pn(pxn));
			break;
		case 6 :
			if(BIT_GET(mode,0)) BIT_SET(P6M0,pn(pxn));else BIT_CLR(P6M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P6M1,pn(pxn));else BIT_CLR(P6M1,pn(pxn));
			if(level_state)     BIT_SET(P6,pn(pxn));  else BIT_CLR(P6,pn(pxn));
			break;
		case 7 :
			if(BIT_GET(mode,0)) BIT_SET(P7M0,pn(pxn));else BIT_CLR(P7M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P7M1,pn(pxn));else BIT_CLR(P7M1,pn(pxn));
			if(level_state)     BIT_SET(P7,pn(pxn));  else BIT_CLR(P7,pn(pxn));
			break;
		default:
			;//���ԣ����ݹܽŲ�����
	}
	
}

/*!
 *	@brief		��ʼ��һ��gpio�˿�
 *	@param		px				�˿�
 *	@param		mode			����ģʽ��
 *																WEAKPULLUP		//������˫��ڡ�����״̬���������IO=1->0��15uA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																STRONGPULLUP	//ǿ����˫��ڡ���ģʽǿ�ҽ����������������������룬����״̬���������IO=1->0��>25mA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																FLOATEDINPUT	//�������롾��֧������״̬�������������������Ϊ0A��IO�ڳʸ���̬���������״̬��
 *																DRAIN_OPEN		//��©˫��ڡ�����״̬���������IO=1->0��0A,IO=0->1��>50mA�����״̬�ṩ������֮��
 *	@param	  level_state	��ʼ����		��������ģʽ��Ч��
 *  @warning  �����������ŵ�IO��ģʽ����Ϊǿ����˫���
 *	@Sampleusage:	gpio_group_init(p0, FLOATEDINPUT, 0x66);
 */
void gpio_group_init(px_e px,  port_mode mode,  uint8 level_state)//��ʼ��һ��GPIO�˿�(�ĸ��˿ڣ�ʲôģʽ����ʼ����)
{
	switch(px)
	{
		case 0 :
			//����P0M0��P0M1������IO��ģʽ
			if(BIT_GET(mode,0))P0M0=0xff;else P0M0=0x00;
			if(BIT_GET(mode,1))P0M1=0xff;else P0M1=0x00;
			//�˿��������
			P0=level_state;
			break;
		case 1 :
			if(BIT_GET(mode,0))P1M0=0xff;else P1M0=0x00;
			if(BIT_GET(mode,1))P1M1=0xff;else P1M1=0x00;
			P1=level_state;
			break;
		case 2 :
			if(BIT_GET(mode,0))P2M0=0xff;else P2M0=0x00;
			if(BIT_GET(mode,1))P2M1=0xff;else P2M1=0x00;
			P2=level_state;
			break;
		case 3 :
			if(BIT_GET(mode,0))P3M0=0xff;else P3M0=0x00;
			if(BIT_GET(mode,1))P3M1=0xff;else P3M1=0x00;
			P3=level_state;
			break;
		case 4 :
			if(BIT_GET(mode,0))P4M0=0xff;else P4M0=0x00;
			if(BIT_GET(mode,1))P4M1=0xff;else P4M1=0x00;
			P4=level_state;
			break;
		case 5 :
			if(BIT_GET(mode,0))P5M0=0xff;else P5M0=0x00;
			if(BIT_GET(mode,1))P5M1=0xff;else P5M1=0x00;
			P5=level_state;
			break;
		case 6 :
			if(BIT_GET(mode,0))P6M0=0xff;else P6M0=0x00;
			if(BIT_GET(mode,1))P6M1=0xff;else P6M1=0x00;
			P6=level_state;
			break;
		case 7 :
			if(BIT_GET(mode,0))P7M0=0xff;else P7M0=0x00;
			if(BIT_GET(mode,1))P7M1=0xff;else P7M1=0x00;
			P7=level_state;
			break;
		
		default:
			;//���ԣ����ݶ˿ڲ�����
	}
	
}

/*!
 *	@brief		����gpio�ڹ���ģʽ
 *	@param		pxn				IO��
 *	@param		mode			����ģʽ��
 *																WEAKPULLUP		//������˫��ڡ�����״̬���������IO=1->0��15uA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																STRONGPULLUP	//ǿ����˫��ڡ���ģʽǿ�ҽ����������������������룬����״̬���������IO=1->0��>25mA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																FLOATEDINPUT	//�������롾��֧������״̬�������������������Ϊ0A��IO�ڳʸ���̬���������״̬��
 *																DRAIN_OPEN		//��©˫��ڡ�����״̬���������IO=1->0��0A,IO=0->1��>50mA�����״̬�ṩ������֮��
 *  @warning  �����������ŵ�IO��ģʽ����Ϊǿ����˫���
 *	@Sampleusage:	gpio_mode(p25, FLOATEDINPUT);
 */
void gpio_mode(pxn_e pxn,  port_mode mode)//����GPIO���Ź���ģʽ(�ĸ����ţ�ʲôģʽ)
{
	switch(px(pxn))
	{
		case 0 :
			//����P0M0��P0M1������IO��ģʽ
			if(BIT_GET(mode,0)) BIT_SET(P0M0,pn(pxn));else BIT_CLR(P0M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P0M1,pn(pxn));else BIT_CLR(P0M1,pn(pxn));
			break;
		case 1 :
			if(BIT_GET(mode,0)) BIT_SET(P1M0,pn(pxn));else BIT_CLR(P1M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P1M1,pn(pxn));else BIT_CLR(P1M1,pn(pxn));
			break;
		case 2 :
			if(BIT_GET(mode,0)) BIT_SET(P2M0,pn(pxn));else BIT_CLR(P2M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P2M1,pn(pxn));else BIT_CLR(P2M1,pn(pxn));
			break;
		case 3 :
			if(BIT_GET(mode,0)) BIT_SET(P3M0,pn(pxn));else BIT_CLR(P3M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P3M1,pn(pxn));else BIT_CLR(P3M1,pn(pxn));
			break;
		case 4 :
			if(BIT_GET(mode,0)) BIT_SET(P4M0,pn(pxn));else BIT_CLR(P4M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P4M1,pn(pxn));else BIT_CLR(P4M1,pn(pxn));
			break;
		case 5 :
			if(BIT_GET(mode,0)) BIT_SET(P5M0,pn(pxn));else BIT_CLR(P5M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P5M1,pn(pxn));else BIT_CLR(P5M1,pn(pxn));
			break;
		case 6 :
			if(BIT_GET(mode,0)) BIT_SET(P6M0,pn(pxn));else BIT_CLR(P6M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P6M1,pn(pxn));else BIT_CLR(P6M1,pn(pxn));
			break;
		case 7 :
			if(BIT_GET(mode,0)) BIT_SET(P7M0,pn(pxn));else BIT_CLR(P7M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P7M1,pn(pxn));else BIT_CLR(P7M1,pn(pxn));
			break;
		default:
			;//���ԣ����ݹܽŲ�����
	}
	
}

/*!
 *	@brief		����һ��gpio�˿ڹ���ģʽ
 *	@param		px				�˿�
 *	@param		mode			����ģʽ��
 *																WEAKPULLUP		//������˫��ڡ�����״̬���������IO=1->0��15uA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																STRONGPULLUP	//ǿ����˫��ڡ���ģʽǿ�ҽ����������������������룬����״̬���������IO=1->0��>25mA,IO=0->1��>50mA�����״̬�ṩ������֮��
 *																FLOATEDINPUT	//�������롾��֧������״̬�������������������Ϊ0A��IO�ڳʸ���̬���������״̬��
 *																DRAIN_OPEN		//��©˫��ڡ�����״̬���������IO=1->0��0A,IO=0->1��>50mA�����״̬�ṩ������֮��
 *  @warning  �����������ŵ�IO��ģʽ����Ϊǿ����˫���
 *	@Sampleusage:	gpio_group_mode(p0, FLOATEDINPUT);
 */
void gpio_group_mode(px_e px,  port_mode mode)//����һ��GPIO�˿ڹ���ģʽ(�ĸ��˿ڣ�ʲôģʽ)
{
	switch(px)
	{
		case 0 :
			//����P0M0��P0M1������IO��ģʽ
			if(BIT_GET(mode,0))P0M0=0xff;else P0M0=0x00;
			if(BIT_GET(mode,1))P0M1=0xff;else P0M1=0x00;
			break;
		case 1 :
			if(BIT_GET(mode,0))P1M0=0xff;else P1M0=0x00;
			if(BIT_GET(mode,1))P1M1=0xff;else P1M1=0x00;
			break;
		case 2 :
			if(BIT_GET(mode,0))P2M0=0xff;else P2M0=0x00;
			if(BIT_GET(mode,1))P2M1=0xff;else P2M1=0x00;
			break;
		case 3 :
			if(BIT_GET(mode,0))P3M0=0xff;else P3M0=0x00;
			if(BIT_GET(mode,1))P3M1=0xff;else P3M1=0x00;
			break;
		case 4 :
			if(BIT_GET(mode,0))P4M0=0xff;else P4M0=0x00;
			if(BIT_GET(mode,1))P4M1=0xff;else P4M1=0x00;
			break;
		case 5 :
			if(BIT_GET(mode,0))P5M0=0xff;else P5M0=0x00;
			if(BIT_GET(mode,1))P5M1=0xff;else P5M1=0x00;
			break;
		case 6 :
			if(BIT_GET(mode,0))P6M0=0xff;else P6M0=0x00;
			if(BIT_GET(mode,1))P6M1=0xff;else P6M1=0x00;
			break;
		case 7 :
			if(BIT_GET(mode,0))P7M0=0xff;else P7M0=0x00;
			if(BIT_GET(mode,1))P7M1=0xff;else P7M1=0x00;
			break;
		
		default:
			;//���ԣ����ݶ˿ڲ�����
	}
	
}

/*!
 *@brief	��������״̬
 *@param	pxn					IO��
 *@param	level_state	״̬��0=�͵�ƽ��1=�ߵ�ƽ	��������ģʽ��Ч��
 *@warning  ���Դ����������Ž�����IO��״̬���ã���ô��ڹ��ܿ��ܻ��ܵ�Ӱ�죡
 *@Sampleusage��gpio_set(p00,0);
 */
void gpio_set(pxn_e pxn,  bool level_state)//��������״̬
{
	switch(px(pxn))
	{
		case 0 :
			if(level_state)BIT_SET(P0,pn(pxn));else BIT_CLR(P0,pn(pxn));//��������״̬
			break;
		case 1 :
			if(level_state)BIT_SET(P1,pn(pxn));else BIT_CLR(P1,pn(pxn));
			break;
		case 2 :
			if(level_state)BIT_SET(P2,pn(pxn));else BIT_CLR(P2,pn(pxn));
			break;
		case 3 :
			if(level_state)BIT_SET(P3,pn(pxn));else BIT_CLR(P3,pn(pxn));
			break;
		case 4 :
			if(level_state)BIT_SET(P4,pn(pxn));else BIT_CLR(P4,pn(pxn));
			break;
		case 5 :
			if(level_state)BIT_SET(P5,pn(pxn));else BIT_CLR(P5,pn(pxn));
			break;
		case 6 :
			if(level_state)BIT_SET(P6,pn(pxn));else BIT_CLR(P6,pn(pxn));
			break;
		case 7 :
			if(level_state)BIT_SET(P7,pn(pxn));else BIT_CLR(P7,pn(pxn));
			break;
		
		default:
			;//���ԣ��������Ų�����
	}
}

/*!
 *@brief	��ת����״̬
 *@param	pxn					IO��
 *@warning  ���Դ����������Ž�����IO��״̬���ã���ô��ڹ��ܿ��ܻ��ܵ�Ӱ�죡
 *@Sampleusage: gpio_turn(p22);
 */
void gpio_turn(pxn_e pxn)//��ת����״̬
{
	switch(px(pxn))
	{
		case 0 :
			if(BIT_GET(P0,pn(pxn))) BIT_CLR(P0,pn(pxn));else BIT_SET(P0,pn(pxn));//��������״̬
			break;
		case 1 :
			if(BIT_GET(P1,pn(pxn))) BIT_CLR(P1,pn(pxn));else BIT_SET(P1,pn(pxn));
			break;
		case 2 :
			if(BIT_GET(P2,pn(pxn))) BIT_CLR(P2,pn(pxn));else BIT_SET(P2,pn(pxn));
			break;
		case 3 :
			if(BIT_GET(P3,pn(pxn))) BIT_CLR(P3,pn(pxn));else BIT_SET(P3,pn(pxn));
			break;
		case 4 :
			if(BIT_GET(P4,pn(pxn))) BIT_CLR(P4,pn(pxn));else BIT_SET(P4,pn(pxn));
			break;
		case 5 :
			if(BIT_GET(P5,pn(pxn))) BIT_CLR(P5,pn(pxn));else BIT_SET(P5,pn(pxn));
			break;
		case 6 :
			if(BIT_GET(P6,pn(pxn))) BIT_CLR(P6,pn(pxn));else BIT_SET(P6,pn(pxn));
		case 7 :
			if(BIT_GET(P7,pn(pxn))) BIT_CLR(P7,pn(pxn));else BIT_SET(P7,pn(pxn));
		
		default:
			;//���ԣ��������Ų�����
	}
}

/*!
 *@brief	��ȡ����״̬
 *@param	pxn					IO��
 *@Sampleusage: gpio_get(p22);
 */
bool gpio_get(pxn_e pxn)//��ȡ����״̬
{
	switch(px(pxn))
	{
		case 0 :
			return BIT_GET(P0,pn(pxn));
		case 1 :
			return BIT_GET(P1,pn(pxn));
		case 2 :
			return BIT_GET(P2,pn(pxn));
		case 3 :
			return BIT_GET(P3,pn(pxn));
		case 4 :
			return BIT_GET(P4,pn(pxn));
		case 5 :
			return BIT_GET(P5,pn(pxn));
		case 6 :
			return BIT_GET(P6,pn(pxn));
		case 7 :
			return BIT_GET(P7,pn(pxn));
	}
	return 0;//���ԣ��������Ų�����
}
