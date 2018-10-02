#include "common.h"
#include "STC_gpio.h"
#include "STC_soft_IIC.h"

/*!
 *	@brief		IIC��ʼ��
 *	@param		SCL_pxn  SCL����Ӧ������(Сд����)
              SDA_pxn  SDA����Ӧ������(Сд����)
 *	@warning	�˳�ʼ���������Ǳ�Ҫ��ӦΪֻ�Ƕ�IO�ڵĹ���ģʽ�ͳ�ʼ��ƽ���˳�ʼ��������Ƭ���ϵ��Ĭ�ϵ����þ��Ƿ���Ҫ���
              �˺����з���ֵ���Գ�ʼ����������ߵĵ�ƽ���м�⣬������IIC�������ñ�׼���ظ�1������ظ�0
              ���ǵ�IIC�������ģ���ʱ��������Ҫ�ϸߵ�ִ��Ч�ʣ���PORT_cfg.h�ж˿�����Ϊ��д��Pxx�����˺���Ҫ���ö˿ڹ���ģʽ��ʹ��Сд��pxx�˿ڱ�ʾ���ͣ����б�ʾ���Ͳ����ݣ�
							����ʹ�ô˺�����ʼ��IIC�����˿�����PORT_cfg.h�е����ñ���һ�£�������Ķ˿�����ر���˫��һ�£�
							����IIC�豸�ɹ�����һ�������ϣ�����ֻ������1·IICͨ������
							�����ٶ��������·���#if��ɣ��������ϵ��豸���ɽ���1MHz���ϵ�ʱ�ӱ仯��(����ģʽ)����д#if 1 �� �������������#if 0 ������ʵ�����ѡ��systick_delay_us(x)���xֵ(����д0-��ͨģʽ)
							��Ҫע����������ٶ�����������������������豸Ҫ��������
 *	@Sampleusage:	IIC_init(p41 , p42);//P41��ΪSCL�ߡ�P42��ΪSDA��
 */

#if 0
 #define IIC_delay() _nop_()
#else
 #define IIC_delay() systick_delay_us(1)
#endif

bool IIC_init(pxn_e SCL_pxn , pxn_e SDA_pxn)
{
	gpio_init(SCL_pxn, WEAKPULLUP, 1);
	gpio_init(SDA_pxn, WEAKPULLUP, 1);
	_nop_();
	if (IIC_SCL && IIC_SDA) return true;
	else return false;
}

/*!
 *	@brief		IIC�����ź�
 *	@param		
 *	@warning	�������źŷ���ʧ�ܣ�˵���������ڱ���������ռ�ã������ߴ���
              �ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_Start();//�����ź�
 */

bool IIC_Start(void)
{
	IIC_SCL = 1;//SCL = 1
  IIC_SDA = 1;//SDA = 1
  _nop_();
  if (IIC_SCL && IIC_SDA)//��֤�ڷ��������ź�ǰ���ߴ��ڿ���״̬����IIC_SDA��IIC_SCL�����ڸߵ�ƽ״̬
	{
		IIC_SDA = 0;//SDA = 0
		IIC_delay();
		if (IIC_SDA) return false;//������δ������
		else //������������
		{
			IIC_SCL = 0;//SCL = 0
			_nop_();
			if(IIC_SCL) return false;//ʱ����δ������
			else return true; //ʱ���������ͣ���ʼ�źŴ������
		}
	}
  else return false;//����δ���ڿ���״̬
}

/*!
 *	@brief		IICֹͣ�ź�
 *	@param		
 *	@warning	�ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_Stop();//ֹͣ�ź�
 */

void IIC_Stop(void)
{
	IIC_SCL = 0;//SCL = 0
	IIC_SDA = 0;//SDA = 0
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SDA = 1;//SDA = 1
}

/*!
 *	@brief		IIC��������Ӧ���źţ����ߴӻ��㷢�͸���(����)�����������յ�
 *	@param		
 *	@warning	�ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_Ack();
 */

void IIC_Ack(void)
{
	IIC_SDA = 0;//SDA = 0
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC�������ջظ���Ӧ���źţ����ߴӻ��㷢�͸���(����)��������û�յ�
 *	@param		
 *	@warning	�ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_NoAck();
 */

void IIC_NoAck(void)
{
	IIC_SDA = 1;//SDA = 1
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC��������Ӧ���ź�
 *	@param		
 *	@warning	�ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_GetAck();
 */

bool IIC_GetAck(void)
{
	IIC_SDA = 1;//SDA = 1
	IIC_delay();
	IIC_SCL = 1;//SCL = 1
	IIC_delay();
	if(IIC_SDA)//�ӻ��ظ���Ӧ���ź�
	{
		IIC_SCL = 0;//SCL = 0
		IIC_SDA = 0;//SDA = 0
		return false;//�ӻ����մ�֡����ʧ��
	}
	else //�ӻ��ظ�Ӧ���ź�
	{
		IIC_SDA = 0;//SDA = 0
		IIC_SCL = 0;//SCL = 0
		return true;//�ӻ����մ�֡���ݳɹ�
	}
}

/*!
 *	@brief		IIC��������8λ����
 *	@param		
 *	@warning	��IICЭ���ڲ���ĳ8���ź�����
              �ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_SendByte(0x88)
 */

void IIC_SendByte(uint8 x)
{
	uint8 n=8;
	while(n--)
	{
		IIC_SCL = 0;//SCL = 0
		IIC_SDA = x & 0x80;//׼������һ��λ������
		x <<= 1;
		IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	}
	IIC_SCL = 0;//SCL = 0
}

/*!
 *	@brief		IIC��������8λ����
 *	@param		
 *	@warning	��IICЭ���ڲ���ĳ8���ź�����
              �ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_ReceiveByte();
 */

uint8 IIC_ReceiveByte(void)
{
	uint8 n=8 , byte=0;
	IIC_SDA = 1;//SDA = 1
	while(n--)
	{
		byte <<= 1;
		IIC_SCL = 0;//SCL = 0
	  IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	  byte |= IIC_SDA;
	}
	IIC_SCL = 0;//SCL = 0
	return byte;
}

/*!
 *	@brief		IIC�����ȴ��ӻ�׼�������ݣ������մӻ���������8λ����
 *	@param		
 *	@warning	��IICЭ���ڲ���ĳ8���ź�����
              �ú���ΪIICЭ��㣬���ɸĶ�(���Ż���ȷ����ȫ�ȶ���ǰ���´�����򻯡�ռ��CPUʱ����С��)�������ⲿ����
 *	@Sampleusage:	IIC_Wait_ReceiveByte();
 */

uint8 IIC_Wait_ReceiveByte(void)
{
	uint8 n=7 , byte=0;
	IIC_SDA = 1;//SDA = 1
	IIC_SCL = 0;//SCL = 0
	IIC_delay();
  IIC_SCL = 1;//SCL = 1
	while(!IIC_SCL);//�ȴ��ӻ�׼����Ҫ���͵�����(����Ϊ���ӻ��ͷ�SCL��)
	IIC_delay();
	byte |= IIC_SDA;
	while(n--)
	{
		byte <<= 1;
		IIC_SCL = 0;//SCL = 0
	  IIC_delay();
		IIC_SCL = 1;//SCL = 1
	  IIC_delay();
	  byte |= IIC_SDA;
	}
	IIC_SCL = 0;//SCL = 0
	return byte;
}

/*!
 *	@brief		��IIC�ӻ�����д�Ĵ�������ָ��
 *	@param		addr  �ӻ���ַ
              reg   ��Ҫ�����ļĴ�����ַ
              Data  ��Ҫд��ӻ�������
 *	@warning	addrΪ���豸��7bit��ַ��ʮ�����Ʊ�ʾ
              �ú���ֻ��дһ���ֽڵ����ݣ�������ᷢ��IIC�����źţ��ʲ��ܷ��Ͷ��ֽ�����
              �ú����з���ֵ���ж�д1���ֽڲ����Ƿ�ɹ���0-ʧ�ܡ�1-�ɹ�
 *	@Sampleusage:	IIC_Write_Reg(0x1e , 0x00 , 0x10);
 */

bool IIC_Write_Reg(uint8 addr , uint8 reg , uint8 Data)
{
	if (!IIC_Start()) return false;
  IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
  if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_SendByte(reg);
  if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_SendByte(Data);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
  IIC_Stop();
  return true;
}

/*!
 *	@brief		��IIC�ӻ���Ҫ�Ĵ�������ָ��
 *	@param		addr  �ӻ���ַ
              reg   ��Ҫ�����ļĴ�����ַ
 *	@warning	addrΪ���豸��7bit��ַ��ʮ�����Ʊ�ʾ
              �ú���ֻ�ܶ�һ���ֽڵ����ݣ�������ᷢ��IIC�����źţ��ʲ��ܽ��ն��ֽ�����
              ע�⣺�ú���û�о����������ʲ��ܵ�֪���������������Ƿ���ȷ���������߲������ڿ����������������ɴ��������ȡ�ٶ�
 *	@Sampleusage:	IIC_Read_Reg(0x1e , 0x00);
 */

uint8 IIC_Read_Reg(uint8 addr , uint8 reg)
{
	uint8 Data=0;
	IIC_Start();
  IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
  IIC_GetAck();
  IIC_SendByte(reg);
  IIC_GetAck();
	IIC_Stop();
  IIC_Start();
  IIC_SendByte(addr << 1 | IIC_Direction_Receiver);
  IIC_GetAck();
  Data = IIC_Wait_ReceiveByte();
  IIC_NoAck();
  IIC_Stop();
  return Data;
}

/*!
 *	@brief		��ĳ��IIC������ĳ���Ĵ�����ʼ(�Ĵ�����ַ���֧��32λ��)����һ������(�������������֧��255�ֽ�)
 *	@param		addr     IIC���������ַ
              reg_wide �Ĵ�����ַλ��(��ѡλ��: bit_wide_8 , bit_wide_16 , bit_wide_32)
              reg      ��Ӧλ��ļĴ�����ַ
              len      Ҫ���͵�����������(��λ:�ֽ�)
              *Data    �����������׵�ַ(��ȡ��ַ����&���뺯��)
 *	@warning	���Ĵ���λ��������ļĴ�����ַ�������������õ�λ��ȡ��λ�෢�ͣ���ʱIIC��������������
              ע�����������������������鳤�ȵ�ƥ�䣬��Ҫʱ��ʹ��sizeof()������⴫��
 *	@Sampleusage:	IIC_Write(0x44 , bit_wide_8 , 0x20 , 1 , &Data);
 */

bool IIC_Write(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *Data)
{
	if (!IIC_Start()) return false;
	IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
	while(reg_wide--)
	{
		IIC_SendByte(reg >> (8*reg_wide) & 0xff);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	while(len--)
	{
		IIC_SendByte(*Data++);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	IIC_Stop();
  return true;
}

/*!
 *	@brief		��ĳ��IIC������ĳ���Ĵ�����ʼ(�Ĵ�����ַ���֧��32λ��)����һ������(�������������֧��255�ֽ�)
 *	@param		addr     IIC���������ַ
              reg_wide �Ĵ�����ַλ��(��ѡλ��: bit_wide_8 , bit_wide_16 , bit_wide_32)
              reg      ��Ӧλ��ļĴ�����ַ
              len      Ҫ���յ�����������(��λ:�ֽ�)
              *Data    �����������׵�ַ(��ȡ��ַ����&���뺯��)
              ����ʵ���һ��nΪ�ӻ��ظ�NoAck���Դ�����û�г�������������У���Ϊ���������ã����ɸ���������Ӧ�ٶ��뱾����������ѭ����������ʱ����е���
 *	@warning	���Ĵ���λ��������ļĴ�����ַ�������������õ�λ��ȡ��λ�෢�ͣ���ʱIIC��������������
              ע�����������������������鳤�ȵ�ƥ�䣬���峤��Ӧ�鿴IIC�����ֲᣡ
 *	@Sampleusage:	IIC_Read(0x44 , bit_wide_16 , 0x2c06 , 6 , &BUF);
 */

bool IIC_Read(uint8 addr , bit_wide reg_wide , uint32 reg , uint8 len , uint8 *buf)
{
	uint8 n=10;//�ӻ��ظ�NoAck���Դ���
	if (!IIC_Start()) return false;
	IIC_SendByte(addr << 1 | IIC_Direction_Transmitter);
	if (!IIC_GetAck())
	{
    IIC_Stop();
    return false;
  }
	while(reg_wide--)
	{
		IIC_SendByte(reg >> (8*reg_wide) & 0xff);
		if (!IIC_GetAck())
		{
			IIC_Stop();
			return false;
		}
	}
	IIC_Stop();
	while(n--)
	{
		if (!IIC_Start()) return false;
		IIC_SendByte(addr << 1 | IIC_Direction_Receiver);
		if (IIC_GetAck()) break;
		else IIC_Stop();
	}
	if(n==0) return false;
	*buf++ = IIC_Wait_ReceiveByte();
	len--;
	while(len--)
	{
		IIC_Ack();
		*buf++ = IIC_ReceiveByte();
	}
	IIC_NoAck();
  IIC_Stop();
	return true;
}
