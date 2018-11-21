#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ϵͳ�жϷ������û�		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/10
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
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
