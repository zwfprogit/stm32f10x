#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;//�趨һ���ṹ������

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PBʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //���ţ�LED0-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //���ͣ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //��ת�ٶȣ�IO���ٶ�Ϊ50MHz

	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.8
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.8 �����
}
