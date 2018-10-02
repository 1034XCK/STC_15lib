#ifndef  __STC_CLOCK_H__
#define  __STC_CLOCK_H__

//主时钟分频至系统时钟倍数
typedef enum
{
	DIV_1,	//主时钟频率/1，不分频
	DIV_2,	//主时钟频率/2
	DIV_4,	//主时钟频率/4
	DIV_8,	//主时钟频率/8
	DIV_16,	//主时钟频率/16
	DIV_32,	//主时钟频率/32
	DIV_64,	//主时钟频率/64
	DIV_128,//主时钟频率/128
	DIV_MAX,
}CLOCK_DIV_e;

//主时钟对外分频输出
typedef enum
{
	OUTPUT_NO,	//主时钟不对外输出时钟
	MCKO_1,			//主时钟对外输出时钟，但时钟频率不分频，输出频率=主时钟（EXTAL_IN）
	MCKO_2,			//主时钟对外输出2分频时钟，频率=主时钟/2
	MCKO_4,			//主时钟对外输出4分频时钟，频率=主时钟/4
	MCKO_MAX,
}MCKO_e;

extern void clockdiv_count(CLOCK_DIV_e div);	//主时钟分频至系统时钟
extern void mclock_div_output(MCKO_e mcko);	//主时钟对外分频输出

#endif /* __STC_CLOCK_H__  */