#ifndef __KEY_H
#define __KEY_H

#define Key_Log 1 //是否打印信息
#define ADC_Log 1

#include "stm32f10x.h"                  // Device header
#include "Interf.h"
#include "stdbool.h"
#include "Delay.h"

#define Key_Port4 GPIOB
#define Key_Pin_A GPIO_Pin_12
#define Key_Pin_B GPIO_Pin_13
#define Key_Pin_C GPIO_Pin_14
#define Key_Pin_D GPIO_Pin_15

#define Key_Port2 GPIOA
#define Key_PortIn GPIOA

#define Key_Pin_ML GPIO_Pin_12
#define Key_Pin_MR GPIO_Pin_15
#define Key_Pin_Y GPIO_Pin_11
#define Key_Pin_X GPIO_Pin_8

#define Joystick_Port GPIOA             /*摇杆端口*/
#define Joys_Pin_L_X GPIO_Pin_0         /*摇杆的左右两组，XY轴的ADC*/
#define Joys_Pin_L_Y GPIO_Pin_1
#define Joys_Pin_R_Y GPIO_Pin_2
#define Joys_Pin_R_X GPIO_Pin_3

void Keys_GPIO_Init(void);
void Joys_ADC_Init(void);
uint16_t Joystick_Read(uint8_t channel);
char Key_Read(void);

#endif
