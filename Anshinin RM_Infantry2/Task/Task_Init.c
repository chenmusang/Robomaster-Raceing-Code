/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ����������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Init.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
  |--Date        : 2019-02-18             
  |--Libsupports : 
  |--Description :                                                     
  |--FunctionList                                                     
  |-------1. ....                                                     
  |          <version>:                                                     
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#include "Task_Init.h" 

/*-----------------------------------file of end------------------------------*/

/*��ʼ������*/
TaskHandle_t StartTaskHandler=NULL;

/**
  * @Data    2019-02-18 20:50
  * @brief   ��ʼ������
  * @param   void *pvParameters
  * @retval  void
  */
void TaskStart(void *pvParameters)
{
     /*�����ж����ȼ�����*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);


    /*�����ٽ���*/
    taskENTER_CRITICAL();
    /* =========================== Init of begin =========================== */
    
    /*�����ʼ��*/
    CAN1_QuickInit();

    /*LED��ʼ��*/
    LED_Init();


    /* =========================== Init of end =========================== */

    /* =========================== Task of begin =========================== */
    
    /*CAN���񴴽�*/
    CAN_TaskCreate();

    /*�������񴴽�*/
    Control_TaskCreate();
    

    

    /* =========================== Task of end =========================== */
    
    
    /*ɾ����ʼ������*/
    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL();
}
 

 