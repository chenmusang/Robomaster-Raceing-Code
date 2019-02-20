/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���ޣ�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ����������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : PID.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-19               
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
#ifndef __PID_H 
#define __PID_H 

#include "stm32f4xx.h"
#include "BSP_MATH.h"

/* =========================== INC_PID of begin =========================== */
typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}incrementalpid_t;
/* =========================== INC_PID of end =========================== */

/* =========================== POS_PID of begin =========================== */
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float Kp,Ki,Kd;
	float PWM;

	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}positionpid_t;
/* =========================== POS_PID of end =========================== */

/* =========================== INCFUZ_PID of begin =========================== */
typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
    float ec_error; /*���仯��*/ 
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}INCfuzzationpid_t;
/* =========================== INCFUZ_PID of end =========================== */


/* =========================== POSFUZ_PID of begin =========================== */
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
    float Add_error;
	float ec_error; /*���仯��*/ 
	float Kp,Ki,Kd;
	float PWM;

	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}POSfuzzationpid_t;
/* =========================== POSFUZ_PID of end =========================== */

/*����ʽPID��ʼ��*/
void IncrementalPID_Init(incrementalpid_t *pid, float kp, float ki, float kd, \
uint32_t MaxOutput, uint32_t IntegralLimit);

/*λ��ʽPID��ʼ��*/
void PositionPID_Init(positionpid_t *pid, float kp, float ki, float kd, \
uint32_t MaxOutput, uint32_t IntegralLimit);

/*ģ������ʽPID��ʼ��*/
void INCFuzzationPID_Init(INCfuzzationpid_t *pid, float kp, float ki, float kd,\
uint32_t MaxOutput, uint32_t IntegralLimit);

/*ģ��λ��ʽPID��ʼ��*/
void POSFuzzationPID_Init(POSfuzzationpid_t *pid, float kp, float ki, float kd,\
uint32_t MaxOutput, uint32_t IntegralLimit);

/*����ʽPID����*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured);

/*λ��ʽPID����*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured);

/*ģ������ʽPID����*/
int FuzzyPID_INCCalculation(INCfuzzationpid_t *pid,float target, float measured);

/*ģ��λ��ʽPID����*/
int FuzzationPID_POSCalculation(POSfuzzationpid_t * pid, float target, float measured);




/* =========================== FUZZYCAL of begin =========================== */
/*kpģ��ֵ�Ƶ�*/
float fuzzy_kp(float e, float ec);

/*kiģ��ֵ�Ƶ�*/
float fuzzy_ki(float e, float ec);

/*Kdģ��ֵ�Ƶ�*/
float fuzzy_kd(float e, float ec);

/* =========================== FUZZYCAL of end =========================== */





#endif	// __PID_H
/*-----------------------------------file of end------------------------------*/

