/*
 * 包含头文件
 */
#include "common.h"
#include "STC_gpio.h"

/*!
 *	@brief		初始化单个gpio口
 *	@param		pxn				IO口
 *	@param		mode			工作模式：
 *																WEAKPULLUP		//弱上拉双向口【输入状态所需电流：IO=1->0需15uA,IO=0->1需>50mA；输出状态提供电流反之】
 *																STRONGPULLUP	//强上拉双向口【此模式强烈建议仅输出，但可以用来输入，输入状态所需电流：IO=1->0需>25mA,IO=0->1需>50mA；输出状态提供电流反之】
 *																FLOATEDINPUT	//浮空输入【仅支持输入状态，且输入所需电流几乎为0A，IO口呈高阻态所以无输出状态】
 *																DRAIN_OPEN		//开漏双向口【输入状态所需电流：IO=1->0需0A,IO=0->1需>50mA；输出状态提供电流反之】
 *	@param	  level_state	初始电平，0=低电平，1=高电平	（对输入模式无效）
 *  @warning  串口所在引脚的IO口模式不能为强上拉双向口
 *	@Sampleusage:	gpio_init(p25, STRONGPULLUP, 0);
 */
void gpio_init(pxn_e pxn,  port_mode mode,  uint8 level_state)//初始化GPIO引脚(哪个引脚，什么模式，初始电平)
{
	switch(px(pxn))
	{
		case 0 :
			//设置P0M0与P0M1来控制IO口模式
			if(BIT_GET(mode,0)) BIT_SET(P0M0,pn(pxn));else BIT_CLR(P0M0,pn(pxn));
			if(BIT_GET(mode,1)) BIT_SET(P0M1,pn(pxn));else BIT_CLR(P0M1,pn(pxn));
			//IO口输出数据
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
			;//断言，传递管脚不存在
	}
	
}

/*!
 *	@brief		初始化一组gpio端口
 *	@param		px				端口
 *	@param		mode			工作模式：
 *																WEAKPULLUP		//弱上拉双向口【输入状态所需电流：IO=1->0需15uA,IO=0->1需>50mA；输出状态提供电流反之】
 *																STRONGPULLUP	//强上拉双向口【此模式强烈建议仅输出，但可以用来输入，输入状态所需电流：IO=1->0需>25mA,IO=0->1需>50mA；输出状态提供电流反之】
 *																FLOATEDINPUT	//浮空输入【仅支持输入状态，且输入所需电流几乎为0A，IO口呈高阻态所以无输出状态】
 *																DRAIN_OPEN		//开漏双向口【输入状态所需电流：IO=1->0需0A,IO=0->1需>50mA；输出状态提供电流反之】
 *	@param	  level_state	初始数据		（对输入模式无效）
 *  @warning  串口所在引脚的IO口模式不能为强上拉双向口
 *	@Sampleusage:	gpio_group_init(p0, FLOATEDINPUT, 0x66);
 */
void gpio_group_init(px_e px,  port_mode mode,  uint8 level_state)//初始化一组GPIO端口(哪个端口，什么模式，初始数据)
{
	switch(px)
	{
		case 0 :
			//设置P0M0与P0M1来控制IO口模式
			if(BIT_GET(mode,0))P0M0=0xff;else P0M0=0x00;
			if(BIT_GET(mode,1))P0M1=0xff;else P0M1=0x00;
			//端口输出数据
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
			;//断言，传递端口不存在
	}
	
}

/*!
 *	@brief		更改gpio口工作模式
 *	@param		pxn				IO口
 *	@param		mode			工作模式：
 *																WEAKPULLUP		//弱上拉双向口【输入状态所需电流：IO=1->0需15uA,IO=0->1需>50mA；输出状态提供电流反之】
 *																STRONGPULLUP	//强上拉双向口【此模式强烈建议仅输出，但可以用来输入，输入状态所需电流：IO=1->0需>25mA,IO=0->1需>50mA；输出状态提供电流反之】
 *																FLOATEDINPUT	//浮空输入【仅支持输入状态，且输入所需电流几乎为0A，IO口呈高阻态所以无输出状态】
 *																DRAIN_OPEN		//开漏双向口【输入状态所需电流：IO=1->0需0A,IO=0->1需>50mA；输出状态提供电流反之】
 *  @warning  串口所在引脚的IO口模式不能为强上拉双向口
 *	@Sampleusage:	gpio_mode(p25, FLOATEDINPUT);
 */
void gpio_mode(pxn_e pxn,  port_mode mode)//设置GPIO引脚工作模式(哪个引脚，什么模式)
{
	switch(px(pxn))
	{
		case 0 :
			//设置P0M0与P0M1来控制IO口模式
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
			;//断言，传递管脚不存在
	}
	
}

/*!
 *	@brief		更改一组gpio端口工作模式
 *	@param		px				端口
 *	@param		mode			工作模式：
 *																WEAKPULLUP		//弱上拉双向口【输入状态所需电流：IO=1->0需15uA,IO=0->1需>50mA；输出状态提供电流反之】
 *																STRONGPULLUP	//强上拉双向口【此模式强烈建议仅输出，但可以用来输入，输入状态所需电流：IO=1->0需>25mA,IO=0->1需>50mA；输出状态提供电流反之】
 *																FLOATEDINPUT	//浮空输入【仅支持输入状态，且输入所需电流几乎为0A，IO口呈高阻态所以无输出状态】
 *																DRAIN_OPEN		//开漏双向口【输入状态所需电流：IO=1->0需0A,IO=0->1需>50mA；输出状态提供电流反之】
 *  @warning  串口所在引脚的IO口模式不能为强上拉双向口
 *	@Sampleusage:	gpio_group_mode(p0, FLOATEDINPUT);
 */
void gpio_group_mode(px_e px,  port_mode mode)//设置一组GPIO端口工作模式(哪个端口，什么模式)
{
	switch(px)
	{
		case 0 :
			//设置P0M0与P0M1来控制IO口模式
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
			;//断言，传递端口不存在
	}
	
}

/*!
 *@brief	设置引脚状态
 *@param	pxn					IO口
 *@param	level_state	状态，0=低电平，1=高电平	（对输入模式无效）
 *@warning  若对串口所在引脚进行了IO口状态设置，则该串口功能可能会受到影响！
 *@Sampleusage：gpio_set(p00,0);
 */
void gpio_set(pxn_e pxn,  bool level_state)//设置引脚状态
{
	switch(px(pxn))
	{
		case 0 :
			if(level_state)BIT_SET(P0,pn(pxn));else BIT_CLR(P0,pn(pxn));//设置引脚状态
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
			;//断言，传递引脚不存在
	}
}

/*!
 *@brief	反转引脚状态
 *@param	pxn					IO口
 *@warning  若对串口所在引脚进行了IO口状态设置，则该串口功能可能会受到影响！
 *@Sampleusage: gpio_turn(p22);
 */
void gpio_turn(pxn_e pxn)//反转引脚状态
{
	switch(px(pxn))
	{
		case 0 :
			if(BIT_GET(P0,pn(pxn))) BIT_CLR(P0,pn(pxn));else BIT_SET(P0,pn(pxn));//设置引脚状态
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
			;//断言，传递引脚不存在
	}
}

/*!
 *@brief	读取引脚状态
 *@param	pxn					IO口
 *@Sampleusage: gpio_get(p22);
 */
bool gpio_get(pxn_e pxn)//读取引脚状态
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
	return 0;//断言，传递引脚不存在
}
