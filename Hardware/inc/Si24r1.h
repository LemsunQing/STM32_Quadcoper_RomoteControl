#ifndef __SI24R1_H
#define __SI24R1_H

#include "stm32f10x.h"                  // Device header
#include "Interf.h"
#include "Delay.h"
#include "Si24R1_Reg.h"


//引脚定义
#define RF_CSN_PIN   GPIO_Pin_4     // Chip Select Not (CSN) - 用于选择设备，低电平使能
#define RF_SCK_PIN   GPIO_Pin_5     //Serial Clock (SCK) - SPI时钟线
#define RF_MISO_PIN  GPIO_Pin_6     //Master In Slave Out (MISO) - SPI主机输入、从机输出
#define RF_MOSI_PIN  GPIO_Pin_7     //Master Out Slave In (MOSI) - SPI主机输出、从机输入
#define RF_CE_PIN    GPIO_Pin_0     //Chip Enable (CE) - 用于控制设备进入发送/接收模式
#define RF_IRQ_PIN   GPIO_Pin_1     // Interrupt Request (IRQ) - 用于接收数据时触发中断

#define RF_GPIO_PORT GPIOA
#define RF_CE_PORT   GPIOB

// 定义CONFIG寄存器地址
#define CONFIG_REG 0x00

#define Hard_SPI_Complie_Set 1  //选择编译选项 硬件SPI OR 软件SPI 

#if Hard_SPI_Complie_Set  //首选项为硬件SPI

// 函数声明
void GPIO_Init_All(void);
uint8_t SPI_Transfer(uint8_t data);
void SI24R1_Init(void);
void SI24R1_WriteReg(uint8_t reg, uint8_t value);
uint8_t SI24R1_ReadReg(uint8_t reg);

#else           //第二个选项为软件SPI

uint8_t R_IRQ(void);
void W_Reg(uint8_t Reg,uint8_t Value);
uint8_t R_Reg(uint8_t Reg);
void W_Buf(uint8_t Reg , uint8_t* Buf, uint8_t Len);
void R_Buf(uint8_t Reg , uint8_t* Buf, uint8_t Len);
void NRF24L01_Init(void);
void Receive(uint8_t* Buf);
uint8_t Send(uint8_t* Buf);

#endif



#endif
