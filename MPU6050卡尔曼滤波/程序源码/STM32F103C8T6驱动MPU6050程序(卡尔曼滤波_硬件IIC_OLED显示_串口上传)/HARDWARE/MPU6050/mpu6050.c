#include "mpu6050.h"

//PB10 SCL
//PB11 SDA
static void I2C_GPIO_Config(void) //I2C2配置
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB,ENABLE ); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

static void I2C_Mode_Config(void) //工作模式配置
{ 
	I2C_InitTypeDef I2C_InitStructure; 
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ;  
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_InitStructure.I2C_ClockSpeed = 50000; 
	I2C_Init(I2C2, &I2C_InitStructure);	   
	I2C_Cmd  (I2C2,ENABLE);
	I2C_AcknowledgeConfig(I2C2, ENABLE);   
}

void I2C_MPU6050_Init(void) //MPU6050初始化
{	   
 	I2C_GPIO_Config();
	I2C_Mode_Config();
}  
	
void I2C_ByteWrite(uint8_t REG_Address,uint8_t REG_data) //写一个字节到I2C设备寄存器中
{
	I2C_GenerateSTART(I2C2,ENABLE);	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));	
	I2C_Send7bitAddress(I2C2,SlaveAddress,I2C_Direction_Transmitter);	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	
	I2C_SendData(I2C2,REG_Address);	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	I2C_SendData(I2C2,REG_data);	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t I2C_ByteRead(uint8_t REG_Address) //从IIC设备寄存器中读取一个字节
{
	uint8_t REG_data;	
	while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));	
	I2C_GenerateSTART(I2C2,ENABLE);//起始信号	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));	
	I2C_Send7bitAddress(I2C2,SlaveAddress,I2C_Direction_Transmitter);//发送设备地址+写信号	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//	
	I2C_Cmd(I2C2,ENABLE);	
	I2C_SendData(I2C2,REG_Address);//发送存储单元地址，从0开始	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	I2C_GenerateSTART(I2C2,ENABLE);//起始信号	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));	
	I2C_Send7bitAddress(I2C2,SlaveAddress,I2C_Direction_Receiver);//发送设备地址+读信号	
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));	
	I2C_AcknowledgeConfig(I2C2,DISABLE);	
	I2C_GenerateSTOP(I2C2,ENABLE);	
	while(!(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED)));	
	REG_data=I2C_ReceiveData(I2C2);//读出寄存器数据	
	return REG_data;
}

void MPU_Init(void) //初始化Mpu6050
{
	I2C_MPU6050_Init();
	I2C_ByteWrite(PWR_MGMT_1,0x00);//解除休眠状态
	I2C_ByteWrite(SMPLRT_DIV,0x07);
	I2C_ByteWrite(CONFIG,0x06);
	I2C_ByteWrite(GYRO_CONFIG,0x18);
	I2C_ByteWrite(ACCEL_CONFIG,0x01);
}

unsigned int GetData(unsigned char REG_Address) //获得16位数据
{
	char H,L;
	H=I2C_ByteRead(REG_Address);
	L=I2C_ByteRead(REG_Address+1);
	return (H<<8)+L;   //合成数据
}
