#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;//设定一个结构体名称

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //引脚：LED0-->PB.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //类型：推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //翻转速度：IO口速度为50MHz

	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.8
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.8 输出高
}
