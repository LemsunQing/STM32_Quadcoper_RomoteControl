#ifndef __APPLICANT_H
#define __APPLICANT_H

#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "OLED.h"
#include "Delay.h"
#include "Interf.h"
#include "stdio.h"
#include "Key.h"
#include "MPU6050.h"

void Unit_Init_All(void);
void Key_app_Demo(void);
void ADC_App_Demo(void);
void MPU_6050_DEMO(void);


#endif
