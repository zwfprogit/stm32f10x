#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//系统中断分组设置化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/10
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************  
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

#define uint unsigned int
#define uchar unsigned char

#define CLOCK 72/8 //??=72M

/*------------------------------------------------------------
                  ??8M,???72M?????
------------------------------------------------------------*/	
void Stm32_Clock_Init(void)
{
	unsigned char temp=0;
	u8 timeout=0;
	RCC_DeInit();
	RCC->CR|=0x00010000;  //????????HSEON

	timeout=0;
	while(!(RCC->CR>>17)&&timeout<200)timeout++;//????????	 

	//0-24M ??0;24-48M ??1;48-72M??2;(????!)	   
	FLASH->ACR|=0x32;//FLASH 2?????

	RCC->CFGR|=0X001D2400;//APB1/2=DIV2;AHB=DIV1;PLL=9*CLK;HSE??PLL???
	RCC->CR|=0x01000000;  //PLLON

	timeout=0;
	while(!(RCC->CR>>25)&&timeout<200)timeout++;//??PLL??

	RCC->CFGR|=0x00000002;//PLL??????
	while(temp!=0x02&&timeout<200)     //??PLL??????????
	{   
		temp=RCC->CFGR>>2;
		timeout++;
		temp&=0x03;
	}  
}
