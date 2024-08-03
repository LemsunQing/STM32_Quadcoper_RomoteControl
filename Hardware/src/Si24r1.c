#include "Si24r1.h"

/***************首选项为硬件SPI******************/

#if Hard_SPI_Complie_Set		

void GPIO_Init_All(void)
{
    // 使能GPIOA和GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // 配置RF_CSN, RF_SCK, RF_MOSI引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = RF_CSN_PIN | RF_SCK_PIN | RF_MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RF_GPIO_PORT, &GPIO_InitStructure);

    // 配置RF_MISO引脚为浮空输入
    GPIO_InitStructure.GPIO_Pin = RF_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(RF_GPIO_PORT, &GPIO_InitStructure);

    // 配置RF_CE引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = RF_CE_PIN;
    GPIO_Init(RF_CE_PORT, &GPIO_InitStructure);

    // 设置初始状态
    GPIO_SetBits(RF_GPIO_PORT, RF_CSN_PIN | RF_SCK_PIN | RF_MOSI_PIN);
    GPIO_ResetBits(RF_CE_PORT, RF_CE_PIN);
}

uint8_t SPI_Transfer(uint8_t data)
{
    uint8_t receivedData = 0;

    for (int i = 0; i < 8; i++)
    {
        if (data & 0x80)
            GPIO_SetBits(RF_GPIO_PORT, RF_MOSI_PIN);
        else
            GPIO_ResetBits(RF_GPIO_PORT, RF_MOSI_PIN);

        data <<= 1;

        GPIO_SetBits(RF_GPIO_PORT, RF_SCK_PIN);
        Delay_us(1);

        receivedData <<= 1;
        if (GPIO_ReadInputDataBit(RF_GPIO_PORT, RF_MISO_PIN))
            receivedData |= 0x01;

        GPIO_ResetBits(RF_GPIO_PORT, RF_SCK_PIN);
        Delay_us(1);
    }

    return receivedData;
}

void SI24R1_Init(void)
{
    GPIO_ResetBits(RF_CE_PORT, RF_CE_PIN); // 禁用CE
}

void SI24R1_WriteReg(uint8_t reg, uint8_t value)
{
    GPIO_ResetBits(RF_GPIO_PORT, RF_CSN_PIN); // 选中设备
    SPI_Transfer(0x20 | reg); // 发送寄存器地址
    SPI_Transfer(value); // 写入寄存器值
    GPIO_SetBits(RF_GPIO_PORT, RF_CSN_PIN); // 取消选中设备
}

uint8_t SI24R1_ReadReg(uint8_t reg)
{
    uint8_t result;
    GPIO_ResetBits(RF_GPIO_PORT, RF_CSN_PIN); // 选中设备
    SPI_Transfer(reg); // 发送寄存器地址
    result = SPI_Transfer(0xFF); // 读取寄存器值
    GPIO_SetBits(RF_GPIO_PORT, RF_CSN_PIN); // 取消选中设备
    return result;
}


/*************第二个选项为软件SP********************/
#else		

uint8_t T_ADDR[5]={0xF0,0xF0,0xF0,0xF0,0xF0};
uint8_t R_ADDR[5]={0xF0,0xF0,0xF0,0xF0,0xF0};

void W_MOSI(uint8_t Value)
{
	GPIO_WriteBit(MOSI_Port,MOSI_Pin,(BitAction)Value);
}

void W_SCK(uint8_t Value)
{
	GPIO_WriteBit(SCK_Port,SCK_Pin,(BitAction)Value);
}

void W_CSN(uint8_t Value)
{
	GPIO_WriteBit(CSN_Port,CSN_Pin,(BitAction)Value);
}

void W_CE(uint8_t Value)
{
	GPIO_WriteBit(CE_Port,CE_Pin,(BitAction)Value);
}

uint8_t R_IRQ(void)
{
	return GPIO_ReadInputDataBit(IRQ_Port,IRQ_Pin);
}

uint8_t R_MISO(void)
{
	return GPIO_ReadInputDataBit(MISO_Port,MISO_Pin);
}

void NRF24L01_Pin_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//配置成推挽输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=MOSI_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MOSI_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=SCK_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SCK_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=CSN_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(CSN_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=CE_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(CE_Port,&GPIO_InitStructure);
	
	
	//配置成上拉输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=IRQ_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IRQ_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=MISO_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MISO_Port,&GPIO_InitStructure);
	
}

//SPI交换一个字节
uint8_t SPI_SwapByte(uint8_t Byte)
{
	uint8_t i,ByteReceive=0x00;
	for(i=0;i<8;i++)
	{
		W_MOSI(Byte&(0x80>>i));
		W_SCK(1);
		if(R_MISO()==1)
		{
			ByteReceive=ByteReceive|(0x80>>i);
		}
		W_SCK(0);
	}
	return ByteReceive;
}

void W_Reg(uint8_t Reg,uint8_t Value)
{
	W_CSN(0);//表示选中NRF24L01
	SPI_SwapByte(Reg);//交换的第一个字节就是指令
	SPI_SwapByte(Value);//交换的第二个字节就是交换的数据
	W_CSN(1);//停止选中NRF24L01
}

uint8_t R_Reg(uint8_t Reg)
{
	uint8_t Value;
	W_CSN(0);//表示选中NRF24L01
	SPI_SwapByte(Reg);//交换的第一个字节就是指令
	Value=SPI_SwapByte(NOP);//交换的第二个字节就是交换的数据
	W_CSN(1);//停止选中NRF24L01
	return Value;
}

void W_Buf(uint8_t Reg , uint8_t* Buf, uint8_t Len)
{
	uint8_t i;
	W_CSN(0);//选中NRF24L01
	SPI_SwapByte(Reg);
	for(i=0;i<Len;i++)
	{
		SPI_SwapByte(Buf[i]);
	}
	W_CSN(1);//停止选中NRF24L01
}

void R_Buf(uint8_t Reg , uint8_t* Buf, uint8_t Len)
{
	uint8_t i;
	W_CSN(0);//选中NRF24L01
	SPI_SwapByte(Reg);
	for(i=0;i<Len;i++)
	{
		Buf[i]=SPI_SwapByte(NOP);
	}
	W_CSN(1);//停止选中NRF24L01
}


void NRF24L01_Init(void)
{
	NRF24L01_Pin_Init();
	
	W_CE(0);
	
	W_Buf(W_REGISTER+TX_ADDR, T_ADDR, 5);//配置发送地址
	W_Buf(W_REGISTER+RX_ADDR_P0, R_ADDR, 5);//配置接收通道0
	W_Reg(W_REGISTER+CONFIG,0x0F);//配置成接收模式
	W_Reg(W_REGISTER+EN_AA,0x01);//通道0开启自动应答
	W_Reg(W_REGISTER+RF_CH,0x00);//配置通信频率2.4G
	W_Reg(W_REGISTER+RX_PW_P0,32);//配置接收通道0接收的数据宽度32字节
	W_Reg(W_REGISTER+EN_RXADDR,0x01);//接收通道0使能
	W_Reg(W_REGISTER+SETUP_RETR,0x1A);//配置580us重发时间间隔,重发10次
	W_Reg(FLUSH_RX,NOP);
	
	W_CE(1);
}

void Receive(uint8_t* Buf)
{
	uint8_t Status;
	Status =R_Reg(R_REGISTER+STATUS);
	if(Status & RX_OK)
	{
		R_Buf(R_RX_PAYLOAD, Buf, 32);
		W_Reg(FLUSH_RX,NOP);
		W_Reg(W_REGISTER+STATUS, Status);
		Delay_us(150);
	}
}

uint8_t Send(uint8_t* Buf)
{
	uint8_t Status;
	W_Buf(W_TX_PAYLOAD, Buf, 32);//在发送数据缓存器发送要发送的数据
	
	W_CE(0);
	W_Reg(W_REGISTER+CONFIG,0x0E);
	W_CE(1);

	while(R_IRQ()==1);//等待中断
	Status= R_Reg(R_REGISTER+STATUS);
	
	if(Status & MAX_TX)//如果发送达到最大次数
	{
		W_Reg(FLUSH_TX,NOP);//清除发送数据缓存器
		W_Reg(W_REGISTER+STATUS,Status);//中断位写1清除中断
		return MAX_TX;
	}
	if(Status & TX_OK)//如果发送成功,接收到应答信号
	{
		W_Reg(W_REGISTER+STATUS,Status);//清除中断
		return TX_OK;
	}
}

#endif
