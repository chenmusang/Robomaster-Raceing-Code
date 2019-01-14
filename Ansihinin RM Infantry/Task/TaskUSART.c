#include "TaskUSART.h"

/*任务相关*/
static TaskHandle_t USART1_ReceiverHandler = NULL;/*DR16（USART1）控制句柄*/
static TaskHandle_t UASRTSend_xHandler = NULL;/*USART发送句柄*/
/*队列相关*/
QueueHandle_t xUsart1RxQueue = NULL;
QueueHandle_t xUsart1ToChassis = NULL;
/*USART1接受任务*/
void USART1_ReceiveTask(void *pvParameters);

void USART_TaskCreate(void)
{
    /*队列创建*/
    xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));
    /*任务创建*/
    xTaskCreate(USART1_ReceiveTask,           /* 任务函数  */        
				"USART1_ReceiveTask",         /* 任务名    */      
				128,       			      /* 任务栈大小*/  
				NULL,                 /* 任务参数  */    
			    4,       			        /* 任务优先级*/
				&USART1_ReceiverHandler);   /* 任务句柄  */
	
	
                 
}

void USART1_ReceiveTask(void *pvParameters)
{
   uint8_t usart1RxBuffer[20];
   while(1)
   {
        xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
        DR16_Process(usart1RxBuffer);
				GPIO_ToggleBits(GPIOB,GPIO_Pin_5);
   }
}



