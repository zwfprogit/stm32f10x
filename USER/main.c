#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

/*FreeRTOSͷ�ļ�*/
#include "FreeRTOS.h"
#include "task.h"

#define start_prio 1										//�������ȼ�
#define start_size 128										//�����ջ
TaskHandle_t start_handle;									//������
void start_task(void *pvParameters);						//��������

#define led_prio 2
#define led_size 50
TaskHandle_t led_handle;
void led_task(void * pvParameters);

#define time_prio 3	
#define time_size 50
TaskHandle_t time_handle;
void time_task(void * pvParameters);


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//����ϵͳ�ж����ȼ�����4	 
	delay_init();
	uart_init(115200);
	LED_Init();		  										//��ʼ��LED
	//��������
    xTaskCreate(start_task,     							//������
                "start_task",   							//��������
				start_size, 								//��ջ��С���֣�
                NULL,										//���ݸ��������Ĳ���
                start_prio,									//�������ȼ�
                &start_handle);   							//������

    vTaskStartScheduler();          //�����������
}
//��ʼ����
void start_task(void * pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
    //��������
    xTaskCreate(led_task,             
                "led_task",           
                led_size,        
                NULL,                  
                led_prio,        
                &led_handle);   
	xTaskCreate(time_task,
				"time_task",
				time_size,
				NULL,
				time_prio,
				&time_handle);
    vTaskDelete(start_handle); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}
//������
void led_task(void * pvParameters)
{
	while(1)
	{
		LED=!LED;
		vTaskDelay(200);
	}
}
//����ʱ��
void time_task(void * pvParameters)
{
	u16 x=0;
	while(1)
	{
		vTaskDelay(1000);
		printf("����ʱ��: %ds\n",x);
	}
}

