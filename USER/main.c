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

//test list
#define list_task_prio 3
#define  list_task_size 128
TaskHandle_t ListTask_handle;//������
void list_task(void*pvParameters);


int main(void)
{
	Stm32_Clock_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//����ϵͳ�ж����ȼ�����4	 
	delay_init();
	LED_Init();	
	uart_init(115200);
		  										//��ʼ��LED
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
	vTaskDelete(start_handle); //ɾ����ʼ����
	taskEXIT_CRITICAL();            //�˳��ٽ���
}
//������
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
List_t  TestList;
ListItem_t  ListItem1;
ListItem_t  ListItem2;
ListItem_t  ListItem3;
void list_task(void*pvParameters)
{
	// 1:��ʼ���б���б���
	vListInitialise(&TestList);
	vListInitialiseItem(&ListItem1);
	vListInitialiseItem(&ListItem2);
	vListInitialiseItem(&ListItem3);
	ListItem1.xItemValue=40;
	ListItem1.xItemValue=60;
	ListItem1.xItemValue=50;
	// 2:��ӡ�б�������б����ַ
	printf("/******printf list and listItem addr start********/\r\n");
	printf("ListItem                		address          \r\n");
	printf("TestList                 		%#x          \r\n",(int)&TestList);
	printf("TestList->pxIndex        		%#x          \r\n",(int)TestList.pxIndex);
	printf("TestList->xListEnd       		%#x          \r\n",(int)&TestList.xListEnd);
	printf("ListItem1			       				%#x          \r\n",(int)&ListItem1);
	printf("ListItem2			       				%#x          \r\n",(int)&ListItem2);
	printf("ListItem3			       				%#x          \r\n",(int)&ListItem3);
	printf("/******printf list and listItem addr end********/\r\n\r\n");
	// 3:���б������ListItem1����ͨ�����ڴ�ӡ�����б����еĳ�ԱpxNext��pxPrevious��ֵ
	//ͨ��������ֵ�۲��б������б��е����
	vListInsert(&TestList,&ListItem1);
	printf("/******add listItem ListItem1 start********/\r\n");
	printf("ListItem                				address          \r\n");
	printf("TestList->xListEnd->pxNext  		%#x          \r\n",(int)TestList.xListEnd.pxNext);
	printf("ListItem1->pxNext        				%#x          \r\n",(int)ListItem1.pxNext);
	printf("TestList->xListEnd->pxPrevious  %#x          \r\n",(int)TestList.xListEnd.pxPrevious);
	printf("ListItem1->pxPrevious			      %#x          \r\n",(int)ListItem1.pxPrevious);
	printf("/******add listItem ListItem1 end********/\r\n\r\n");
	// 4:���б������ListItem2����ͨ�����ڴ�ӡ�����б����еĳ�ԱpxNext��pxPrevious��ֵ
	//ͨ��������ֵ�۲��б������б��е����
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
	// 5:���б������ListItem3����ͨ�����ڴ�ӡ�����б����еĳ�ԱpxNext��pxPrevious��ֵ
	//ͨ��������ֵ�۲��б������б��е����
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

	// 6:ɾ��ListItem2����ͨ�����ڴ�ӡ�����б����еĳ�ԱpxNext��pxPrevious��ֵ
	//ͨ��������ֵ�۲��б������б��е����
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
	// 7:���б������ListItem3����ͨ�����ڴ�ӡ�����б����еĳ�ԱpxNext��pxPrevious��ֵ
	//ͨ��������ֵ�۲��б������б��е����
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

#if 0//���Խ��
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

