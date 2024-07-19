#include "Key.h"

void Keys_GPIO_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = Key_Pin_A | Key_Pin_B | Key_Pin_C | Key_Pin_D;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(Key_Port4,&GPIO_InitStruct);

    /*初始化摇杆中建以及左侧XY键*/
    GPIO_InitStruct.GPIO_Pin = Key_Pin_ML | Key_Pin_MR | Key_Pin_Y | Key_Pin_X;
    GPIO_Init(Key_Port2,&GPIO_InitStruct);
}
    /*初始化摇杆ADC*/
void Joys_ADC_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStruct;

    // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /*初始化摇杆ADC引脚*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = Joys_Pin_L_X | Joys_Pin_L_Y | Joys_Pin_R_Y | Joys_Pin_R_X;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Joystick_Port,&GPIO_InitStruct);

    // ADC配置
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // 使能ADC1
    ADC_Cmd(ADC1, ENABLE);

    // 重置校准寄存器
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));

    // 开始校准
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));  

}

// 读取摇杆位置
uint16_t Joystick_Read(uint8_t channel)
{
		uint16_t ADC_Value = 0;
    // 配置ADC通道
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);

    // 开始转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // 等待转换完成
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		// 读取ADC值
		ADC_Value = ADC_GetConversionValue(ADC1);
	
		#if ADC_Log
		printf("[ADC]:chan%d:%d\r\n",(uint16_t)channel,ADC_Value);
		#endif
	
    return ADC_Value;
}

/// @brief 读取按键的值返回，没有使用延时函数和中断处理 MD代码又臭又长
/// @param  
/// @return 
char Keys_Read(void)
{   
    char Keys_Value = '0';
	
    if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_A) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_A) == 0?
        'A':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'A');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_A) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_B) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_B) == 0?
        'B':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'B');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_B) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0?
        'C':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'C');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0?
        'D':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'D');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0)
        {;}
    }
	if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0?
        'C':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'C');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_C) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0?
        'D':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'D');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port4,Key_Pin_D) == 0)
        {;}
    }
		
	if(GPIO_ReadInputDataBit(Key_Port2,Key_Pin_Y) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port2,Key_Pin_Y) == 0?
        'Y':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'Y');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port2,Key_Pin_Y) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_Port2,Key_Pin_X) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_Port2,Key_Pin_X) == 0?
        'X':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'X');
        #endif
        while(GPIO_ReadInputDataBit(Key_Port2,Key_Pin_X) == 0)
        {;}
    }
	if(GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_ML) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_ML) == 0?
        'L':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'L');
        #endif
        while(GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_ML) == 0)
        {;}
    }
		
    if(GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_MR) == 0)
    {
        Keys_Value =
        GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_MR) == 0?
        'R':'0';
        #if Key_Log
        printf("[Key]:Key %c push\r\n",'R');
        #endif
        while(GPIO_ReadInputDataBit(Key_PortIn,Key_Pin_MR) == 0)
        {;}
    }


    return Keys_Value;
}


