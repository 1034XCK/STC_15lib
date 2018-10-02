#ifndef  __STC_CLOCK_H__
#define  __STC_CLOCK_H__

//��ʱ�ӷ�Ƶ��ϵͳʱ�ӱ���
typedef enum
{
	DIV_1,	//��ʱ��Ƶ��/1������Ƶ
	DIV_2,	//��ʱ��Ƶ��/2
	DIV_4,	//��ʱ��Ƶ��/4
	DIV_8,	//��ʱ��Ƶ��/8
	DIV_16,	//��ʱ��Ƶ��/16
	DIV_32,	//��ʱ��Ƶ��/32
	DIV_64,	//��ʱ��Ƶ��/64
	DIV_128,//��ʱ��Ƶ��/128
	DIV_MAX,
}CLOCK_DIV_e;

//��ʱ�Ӷ����Ƶ���
typedef enum
{
	OUTPUT_NO,	//��ʱ�Ӳ��������ʱ��
	MCKO_1,			//��ʱ�Ӷ������ʱ�ӣ���ʱ��Ƶ�ʲ���Ƶ�����Ƶ��=��ʱ�ӣ�EXTAL_IN��
	MCKO_2,			//��ʱ�Ӷ������2��Ƶʱ�ӣ�Ƶ��=��ʱ��/2
	MCKO_4,			//��ʱ�Ӷ������4��Ƶʱ�ӣ�Ƶ��=��ʱ��/4
	MCKO_MAX,
}MCKO_e;

extern void clockdiv_count(CLOCK_DIV_e div);	//��ʱ�ӷ�Ƶ��ϵͳʱ��
extern void mclock_div_output(MCKO_e mcko);	//��ʱ�Ӷ����Ƶ���

#endif /* __STC_CLOCK_H__  */