#include "Applicant.h"
#include "BMP280.h"
#include "Si24r1.h"

int main(void)
{	
	uint16_t ID;
	Unit_Init_All();
	
	
 uint8_t data = 0;

	USART1_Init(); 
	GPIO_Init_All();
	SI24R1_Init();
	while (1)
	{
		if (GPIO_ReadInputDataBit(RF_GPIO_PORT, RF_IRQ_PIN) == 0)
		{
			SI24R1_ReadPayload(&data, 1); // 读取数据
			printf("Received data: %d\n", data);
			OLED_ShowNum(1,1,data,5);
			// 清除中断标志
			SI24R1_WriteReg(0x07, 0x40);
		}
			Delay_ms(100); // 每100ms检查一次
	}
	
}
