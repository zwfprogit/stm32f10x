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

//test list
#define list_task_prio 3
#define  list_task_size 128
TaskHandle_t ListTask_handle;//任务句柄
void list_task(void*pvParameters);


int main(void)
{
	Stm32_Clock_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//设置系统中断优先级分组4	 
	delay_init();
	LED_Init();	
	uart_init(115200);
		  										//初始化LED
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
#if 0
	xTaskCreate(led_task,             
		"led_task",           
		led_size,        
		NULL,                  
		led_prio,        
		&led_handle);
#endif
#if 0
	xTaskCreate(time_task,
		"time_task",
		time_size,
		NULL,
		time_prio,
		&time_handle);
#endif
#if 1
	xTaskCreate(list_task,
		"list_task",
		list_task_size,
		NULL,
		list_task_prio,
		&ListTask_handle);
#endif
	vTaskDelete(start_handle); //删除开始任务
	taskEXIT_CRITICAL();            //退出临界区
}
//呼吸灯
void led_task(void * pvParameters)
{
	while(1)
	{
		LED=1;
		delay_ms(500);
		//vTaskDelay(2000);
		LED=0;
		delay_ms(500);
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
List_t  TestList;
ListItem_t  ListItem1;
ListItem_t  ListItem2;
ListItem_t  ListItem3;
void list_task(void*pvParameters)
{
	// 1:初始化列表和列表项
	vListInitialise(&TestList);
	vListInitialiseItem(&ListItem1);
	vListInitialiseItem(&ListItem2);
	vListInitialiseItem(&ListItem3);
	ListItem1.xItemValue=40;
	ListItem1.xItemValue=60;
	ListItem1.xItemValue=50;
	// 2:打印列表和其他列表项地址
	printf("/******printf list and listItem addr start********/\r\n");
	printf("ListItem                		address          \r\n");
	printf("TestList                 		%#x          \r\n",(int)&TestList);
	printf("TestList->pxIndex        		%#x          \r\n",(int)TestList.pxIndex);
	printf("TestList->xListEnd       		%#x          \r\n",(int)&TestList.xListEnd);
	printf("ListItem1			       				%#x          \r\n",(int)&ListItem1);
	printf("ListItem2			       				%#x          \r\n",(int)&ListItem2);
	printf("ListItem3			       				%#x          \r\n",(int)&ListItem3);
	printf("/******printf list and listItem addr end********/\r\n\r\n");
	// 3:向列表中添加ListItem1，并通过串口打印所有列表项中的成员pxNext和pxPrevious的值
	//通过这两个值观擦列表项在列表中的情况
	vListInsert(&TestList,&ListItem1);
	printf("/******add listItem ListItem1 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("/******add listItem ListItem1 end********/\r\n\r\n");
	// 4:向列表中添加ListItem2，并通过串口打印所有列表项中的成员pxNext和pxPrevious的值
	//通过这两个值观擦列表项在列表中的情况
	vListInsert(&TestList,&ListItem2);
	printf("/******add listItem ListItem2 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("ListItem2->pxNext        				%#x          \r\n",(int)ListItem2.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("ListItem2->pxPrevious			      %#x          \r\n",(int)ListItem2.pxPrevious);
	printf("/******add listItem ListItem2 end********/\r\n\r\n");
	// 5:向列表中添加ListItem3，并通过串口打印所有列表项中的成员pxNext和pxPrevious的值
	//通过这两个值观擦列表项在列表中的情况
	vListInsert(&TestList,&ListItem3);
	printf("/******add listItem ListItem3 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("ListItem2->pxNext        				%#x          \r\n",(int)ListItem2.pxNext);
	printf("ListItem3->pxNext        				%#x          \r\n",(int)ListItem3.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("ListItem2->pxPrevious			      %#x          \r\n",(int)ListItem2.pxPrevious);
	printf("ListItem3->pxPrevious			      %#x          \r\n",(int)ListItem3.pxPrevious);
	printf("/******add listItem ListItem2 end********/\r\n\r\n");

	// 6:删除ListItem2，并通过串口打印所有列表项中的成员pxNext和pxPrevious的值
	//通过这两个值观擦列表项在列表中的情况
	uxListRemove(&ListItem2);
	printf("/******remove listItem ListItem3 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("ListItem3->pxNext        				%#x          \r\n",(int)ListItem3.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("ListItem3->pxPrevious			      %#x          \r\n",(int)ListItem3.pxPrevious);
	printf("/******remove listItem ListItem2 end********/\r\n\r\n");
	// 7:向列表中添加ListItem3，并通过串口打印所有列表项中的成员pxNext和pxPrevious的值
	//通过这两个值观擦列表项在列表中的情况
	vListInsertEnd(&TestList,&ListItem2);
	printf("/******add listItem ListItem2 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem2->pxNext        				%#x          \r\n",(int)ListItem2.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("ListItem3->pxNext        				%#x          \r\n",(int)ListItem3.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem2->pxPrevious			      %#x          \r\n",(int)ListItem2.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("ListItem3->pxPrevious			      %#x          \r\n",(int)ListItem3.pxPrevious);
	printf("/******add listItem ListItem2 end********/\r\n");

#if 0//测试结果
/******printf list and listItem addr start********/
ListItem                					address
TestList                 					0x200000a4
TestList->pxIndex        			0x200000ac
TestList->xListEnd       			0x200000ac
ListItem1			       			0x200000b8
ListItem2			       			0x200000cc
ListItem3			       			0x200000e0
/******printf list and listItem addr end********/

/******add listItem ListItem1 start********/
ListItem                					address
TestList->xListEnd->pxNext  		0x200000b8
ListItem1->pxNext        			0x200000ac
TestList->xListEnd->pxPrevious  	0x200000b8
ListItem1->pxPrevious			0x200000ac
/******add listItem ListItem1 end********/

/******add listItem ListItem2 start********/
ListItem                					address
TestList->xListEnd->pxNext  		0x200000cc
ListItem1->pxNext        			0x200000ac
ListItem2->pxNext        			0x200000b8
TestList->xListEnd->pxPrevious  	0x200000b8
ListItem1->pxPrevious			0x200000cc
ListItem2->pxPrevious			0x200000ac
/******add listItem ListItem2 end********/

/******add listItem ListItem3 start********/
ListItem                					address
TestList->xListEnd->pxNext  		0x200000cc
ListItem1->pxNext        			0x200000ac
ListItem2->pxNext        			0x200000e0
ListItem3->pxNext        			0x200000b8
TestList->xListEnd->pxPrevious  	0x200000b8
ListItem1->pxPrevious			0x200000e0
ListItem2->pxPrevious			0x200000ac
ListItem3->pxPrevious			0x200000cc
/******add listItem ListItem2 end********/

/******remove listItem ListItem3 start********/
ListItem                					address
TestList->xListEnd->pxNext  		0x200000e0
ListItem1->pxNext        			0x200000ac
ListItem3->pxNext        			0x200000b8
TestList->xListEnd->pxPrevious  	0x200000b8
ListItem1->pxPrevious			0x200000e0
ListItem3->pxPrevious			0x200000ac
/******remove listItem ListItem2 end********/

/******add listItem ListItem2 start********/
ListItem                					address
TestList->xListEnd->pxNext  		0x200000e0
ListItem2->pxNext        			0x200000ac
ListItem1->pxNext        			0x200000cc
ListItem3->pxNext        			0x200000b8
TestList->xListEnd->pxPrevious  	0x200000cc
ListItem2->pxPrevious			0x200000b8
ListItem1->pxPrevious			0x200000e0
ListItem3->pxPrevious			0x200000ac
/******add listItem ListItem2 end********/
#endif

	while(1)
	{
		LED=!LED;
		vTaskDelay(1000);
	}
}

