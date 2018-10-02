#ifndef __STC_PORT_H__
#define __STC_PORT_H__

/*枚举管脚编号*/
typedef enum 
{
    /*  p0端口  */ //0~7
    p00,  p01,  p02,  p03,  p04,  p05,  p06,  p07,

    /*  p1端口  */ //8~15
    p10,  p11,  p12,  p13,  p14,  p15,  p16,  p17,

    /*  p2端口  */ //16~23
    p20,  p21,  p22,  p23,  p24,  p25,  p26,  p27,

    /*  p3端口  */ //24~31
    p30,  p31,  p32,  p33,  p34,  p35,  p36,  p37,

    /*  p4端口  */ //32~39
    p40,  p41,  p42,  p43,  p44,  p45,  p46,  p47,
	
		/*  p5端口  */ //40~47
    p50,  p51,  p52,  p53,  p54,  p55,  p56,  p57,
	
		/*  p6端口  */ //48~55
    p60,  p61,  p62,  p63,  p64,  p65,  p66,  p67,
	
		/*  p5端口  */ //56~63
    p70,  p71,  p72,  p73,  p74,  p75,  p76,  p77,
	
} pxn_e;

/*  枚举端口模块  */
typedef enum
{
    p0, p1, p2, p3, p4, p5, p6, p7,

    p_MAX,
	
} px_e;

/*  枚举编号  */
typedef enum
{
    px0, px1, px2, px3, px4, px5, px6, px7,
	
} Pn_e;

//根据以上定义，可以得出：px = pxn / 8 ; pn=pxn & 7
#define px(pxn)			((pxn)>>3)
#define pn(pxn)			((pxn)&0x07)

/*  枚举PORT配置  */
typedef enum port_mode
{
    WEAKPULLUP,		//弱上拉双向口【输入状态所需电流：IO=1->0需15uA,IO=0->1需>50mA；输出状态提供电流反之】
		STRONGPULLUP,	//强上拉双向口【此模式强烈建议仅输出，但可以用来输入，输入状态所需电流：IO=1->0需>25mA,IO=0->1需>50mA；输出状态提供电流反之】
		FLOATEDINPUT,	//浮空输入【仅支持输入状态，且输入所需电流几乎为0A，IO口呈高阻态所以无输出状态】
		DRAIN_OPEN,		//开漏双向口【输入状态所需电流：IO=1->0需0A,IO=0->1需>50mA；输出状态提供电流反之】
} port_mode;

#endif      //__STC_PORT_H__