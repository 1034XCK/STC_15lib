#ifndef _PORT_CFG_H_
#define _PORT_CFG_H_

#include "STC_port.h"

/******************************************   UART   ******************************************/

//        模块通道      端口          可选范围                  注意      			          建议
#define UART0_RX_PIN    p30         //p30、p36、p16						只 例						就					p30
#define UART0_TX_PIN    p31         //p31、p37、p17		        能 如       		必				  p31
                                    //                        一 ：           需
#define UART1_RX_PIN    p46         //p10、p46								列 若						选				  p46
#define UART1_TX_PIN    p47         //p11、p47								整 UARTn_TX_PIN	择					p47
                                    //                        体 选           P31
#define UART2_RX_PIN    p00         //p00、p50								选 择						!			      p00
#define UART2_TX_PIN    p01         //p01、p51								择 了						!				    p01
                                    //                        !  P30,         !
#define UART3_RX_PIN    p02         //p02、p52								!	 则						!			      p02
#define UART3_TX_PIN    p03         //p03、p53								!	 UARTn_RX_PIN	!						p03

/*******************************************   CCP  *******************************************/

//        模块通道      端口          可选范围                  注意      			          建议
#define			ECI					p24 				//p34、p24、p12				只整 如：ECI   选p24								p12
#define			CCP_0				p25					//p35、p25、p11				能体 则CCP0只能选p25								p11
#define			CCP_1				p26					//p36、p26、p10				一选 且CCP1只能选p26								p10
#define			CCP_2				p27					//p37、p27、p37				列择 且CCP2只能选p27								p37

/*******************************************   I2C  *******************************************/

//        模块通道      端口          可选范围                  注意      			          建议
#define   IIC_SCL       P41
#define   IIC_SDA       P42
/*******************************************   SPI  *******************************************/

//        模块通道      端口          可选范围                  注意      			          建议
#define   SPI_SS				p60				  //p12、p24、p54			 主模式下可任意引脚								p12
#define   SPI_MOSI			p23				  //p13、p23、p40																				p13
#define   SPI_MISO			p22				  //p14、p22、p41																				p14
#define   SPI_SCLK			p21				  //p15、p21、p43																				p15

/*******************************************   CAN  *******************************************/

//        模块通道      端口          可选范围                  注意      			          建议

/**************************************   主时钟分频输出  *************************************/

//        模块通道      端口          可选范围                  注意      			          建议
#define MCLK_OUTPUT_PIN p54					//p16,p34,p54         STC15的8pin系列在p34						p34
																		//										STC15的16pin及以上系列在p54  	  p54
																		//										STC15W4K系列可在p54和p16				p54

#endif  //_PORT_CFG_H_