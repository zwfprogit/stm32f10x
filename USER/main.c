#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

/*FreeRTOS头文件*/
#include "FreeRTOS.h"
#include "task.h"

#define start_prio 1										//任务优先级
#define start_size 128										//任务堆栈
TaskHandle_t start_handle;									//任务句柄
void start_task(void *pvParameters);						//任务申明

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//设置系统中断优先级分组4	 
	delay_init();
	uart_init(115200);
	LED_Init();		  										//初始化LED
	//创建任务
    xTaskCreate(start_task,     							//任务函数
                "start_task",   							//任务名称
				start_size, 								//堆栈大小（字）
                NULL,										//传递给任务函数的参数
                start_prio,									//任务优先级
                &start_handle);   							//任务句柄

    vTaskStartScheduler();          //开启任务调度
}
//开始任务
void start_task(void * pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
    //创建任务
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
    vTaskDelete(start_handle); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
//呼吸灯
void led_task(void * pvParameters)
{
	while(1)
	{
		LED=!LED;
		vTaskDelay(200);
	}
}
//开机时间
void time_task(void * pvParameters)
{
	u16 x=0;
	while(1)
	{
		vTaskDelay(1000);
		printf("运行时间: %ds\n",x);
	}
}

