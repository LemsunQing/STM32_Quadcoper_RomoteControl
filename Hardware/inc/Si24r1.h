#ifndef __SI24R1_H
#define __SI24R1_H

#include "stm32f10x.h"                  // Device header
#include "Interf.h"
#include "Delay.h"


//引脚定义
#define RF_CSN_PIN   GPIO_Pin_4     // Chip Select Not (CSN) - 用于选择设备，低电平使能
#define RF_SCK_PIN   GPIO_Pin_5     //Serial Clock (SCK) - SPI时钟线
#define RF_MISO_PIN  GPIO_Pin_6     //Master In Slave Out (MISO) - SPI主机输入、从机输出
#define RF_MOSI_PIN  GPIO_Pin_7     //Master Out Slave In (MOSI) - SPI主机输出、从机输入
#define RF_CE_PIN    GPIO_Pin_0     //Chip Enable (CE) - 用于控制设备进入发送/接收模式
#define RF_IRQ_PIN   GPIO_Pin_1     // Interrupt Request (IRQ) - 用于接收数据时触发中断

#define RF_GPIO_PORT GPIOA
#define RF_CE_PORT   GPIOB

#define Hard_SPI_Complie_Set 1  //选择编译选项 硬件SPI OR 软件SPI 

#if Hard_SPI_Complie_Set  //首选项为硬件SPI

// 函数声明
void GPIO_Init_All(void);
void SPI_GPIO_Init(void);
uint8_t SPI_Transfer(uint8_t data);
void SI24R1_Init(void);
uint8_t SI24R1_ReadReg(uint8_t reg);
void SI24R1_ReadPayload(uint8_t *data, uint8_t length);

#else           //第二个选项为软件SPI



#endif



#endif
