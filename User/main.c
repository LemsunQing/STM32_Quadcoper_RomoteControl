#include "Applicant.h"
#include "BMP280.h"
#include "Si24r1.h"

int main(void)
{
	Unit_Init_All();
    uint8_t read_value;

    // 假设有一个USART初始化函数
    USART1_Init(); 
    GPIO_Init_All();
    SI24R1_Init();


    while (1)
    {    // 写入CONFIG寄存器
    SI24R1_WriteReg(0x00, 0x34); // 配置寄存器：使能CRC，16位CRC，使能电源

    // 读取CONFIG寄存器
    read_value = SI24R1_ReadReg(CONFIG_REG);

    // 打印读取到的值
    printf("Read CONFIG register: 0x%02X\n", read_value);
		OLED_ShowHexNum(1,1,read_value,2);
        // 主循环
    }
}
