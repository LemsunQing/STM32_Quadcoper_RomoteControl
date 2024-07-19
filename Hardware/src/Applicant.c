#include "Applicant.h"

char Key_Infor_Current = '1';
char Key_Infor_Old = '1';

uint16_t joy_L_X = 0;		//ADC_channel 0
uint16_t joy_L_Y = 0;		//ADC_channel 1
uint16_t joy_R_X = 0;		//ADC_channel 2
uint16_t joy_R_Y = 0;		//ADC_channel 3

uint8_t ID;								//定义用于存放ID号的变量
int16_t AX, AY, AZ, GX, GY, GZ;			//定义用于存放各个数据的变量

void Unit_Init_All(void)
{
    LED_GPIO_Init();
	OLED_Init();
	USART1_Init();
	Keys_GPIO_Init();
	Joys_ADC_Init();
	MPU6050_Init();	
}

/// @brief 测试使用按键，在更新老值里能完成对参数的变化，方便调整
/// @param  
void Key_app_Demo(void)
{
	   Key_Infor_Current = Keys_Read();

    // 检测到按键按下时，立即更新老值
    if (Key_Infor_Current != '0')
    {
        Key_Infor_Old = Key_Infor_Current;
        printf("[key]old%c\r\n", Key_Infor_Old);

        // 在OLED上显示当前按键值
        OLED_ShowChar(1, 1, Key_Infor_Current);
    }
    else
    {
        OLED_ShowChar(1, 1, '0');
    }

    // 在OLED上显示老值
    OLED_ShowChar(1, 2, Key_Infor_Old);
}

/// @brief 读取ADC的值显示在串口和OLED上,还有问题未处理
/// @param  
void ADC_App_Demo(void)
{
    joy_L_X = Joystick_Read(0);
	printf("[ADC]LX%d\r\n",joy_L_X);
	OLED_ShowSignedNum(1,1,(uint32_t)joy_L_X,4);//RY
	joy_L_Y = Joystick_Read(1);
	printf("[ADC]LY%d\r\n",joy_L_Y);
	OLED_ShowSignedNum(2,1,(uint32_t)joy_L_Y,4);//真正的LX
	joy_R_Y = Joystick_Read(2);
	printf("[ADC]RY%d\r\n",joy_R_Y);
	OLED_ShowSignedNum(3,1,(uint32_t)joy_R_Y,4);//LY
	joy_R_X = Joystick_Read(3);
	printf("[ADC]RX%d\r\n",joy_R_X);
	OLED_ShowSignedNum(4,1,(uint32_t)joy_R_X,4);//RX
}

/// @brief 
/// @param  
void MPU_6050_DEMO(void)
{
    MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);		//获取MPU6050的数据
    OLED_ShowSignedNum(2, 1, AX, 5);					//OLED显示数据
    OLED_ShowSignedNum(3, 1, AY, 5);
    OLED_ShowSignedNum(4, 1, AZ, 5);
    OLED_ShowSignedNum(2, 8, GX, 5);
    OLED_ShowSignedNum(3, 8, GY, 5);
    OLED_ShowSignedNum(4, 8, GZ, 5);
}
	