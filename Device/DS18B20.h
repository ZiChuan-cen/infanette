#ifndef __DS18B20_H__
#define __DS18B20_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f10x.h"

/***********************   DS18B20 �������Ŷ���  **************************/
#define DS18B20_Dout_GPIO_CLK_ENABLE()              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_Pin_3

/***********************   DS18B20 �����궨��  ****************************/
#define DS18B20_Dout_LOW()						GPIO_ResetBits(DS18B20_Dout_PORT, DS18B20_Dout_PIN)
#define DS18B20_Dout_HIGH()						GPIO_SetBits(DS18B20_Dout_PORT, DS18B20_Dout_PIN)
#define DS18B20_Data_IN()						GPIO_ReadInputDataBit(DS18B20_Dout_PORT,DS18B20_Dout_PIN)



/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
unsigned char DS18B20_Init(void);//��ʼ��DS18B20
short DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��

void DS18B20_Write_Byte(unsigned char dat);//д��һ���ֽ�
unsigned char DS18B20_Read_Byte(void);//����һ���ֽ�
unsigned char DS18B20_Read_Bit(void);//����һ��λ
unsigned char DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20  



#endif /* __DS18B20_H__ */


