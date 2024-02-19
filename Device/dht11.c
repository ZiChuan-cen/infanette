/**
  ******************************************************************************
  * @file    dht11.c
  * @author  fire
  * @date    2023-06-08
  * @brief   ��ʪ�ȴ���������
  ******************************************************************************
  * @attention
  *
  * ƽ̨:Ұ��  STM32 f103 RCt6 ������
  *
  ******************************************************************************
  */

#include "dht11.h"
#include "delay.h"



/**
    * @brief  ����GPIO DHT11�������ģʽת��
    * @param  ��
    * @retval ��
    */
void Change_Dht11_Mode(DHT11Mode_TypeDef mode)
{
    RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin   = DHT11_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == DHT11Mode_IN)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == DHT11Mode_OUT)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }

    GPIO_Init(DHT11_IO, &GPIO_InitStructure);
}


/**
    * @brief  ������ȡ��У�� DHT11 ����
    * @param  ��
    * @retval data
    */
u8 Dht11_ReadData(DHT11_Data_TypeDef *data)
{
    u8 Data[5] = {0};

    /************************************��ʼ�ź�--���*******************************************************/
    Change_Dht11_Mode(DHT11Mode_OUT);
    DHT11_HIGHT();
    DHT11_LOW();
    Delay_ms(20);
    DHT11_HIGHT();  //���ߵȴ�
    Delay_us(30);
    /************************************Ӧ���ź�--����*******************************************************/
    Change_Dht11_Mode(DHT11Mode_IN);
    while (DHT11_ReadPin() == Bit_SET) //�ȴ���Ϊ�͵�ƽ
    {}
    while (DHT11_ReadPin() == Bit_RESET) //�ȴ���Ϊ�ߵ�ƽ
    {}

    /**************************************���ݵķ���**********************************************************/
    for (u8 i = 0; i < 40; i++)
    {
        while (DHT11_ReadPin() == Bit_SET) //����54us
        {}
        while (DHT11_ReadPin() == Bit_RESET) //���ߵȴ��ж�
        {}

        /***********************************�ж����ݡ�1�����ݡ�0��**************************************************/

        Delay_us(40);
        if (DHT11_ReadPin() == Bit_SET) //���Ϊ�ߵ�ƽ��1
        {
            Data[i / 8] |= (1 << (7 - i % 8));
        }
        else//0
        {
            Data[i / 8] &= ~(1 << (7 - i % 8));
        }
    }

    /********************************************У��********************************************************/
    if (Data[4] == Data[0] + Data[1] + Data[2] + Data[3])
    {
        data->Hum = Data[0];
        data->Tem = Data[2];
        return 1;
    }
    else
    {
        return 0;
    }
}



/**
    * @brief  ���DHT11����Ӧ�ź�
    * @param  ��
    * @retval ��⵽��Ӧ-->����1������0��data error
    */
u8 DHT11_Check(void)
{
    u8 retry = 0;
    Change_Dht11_Mode(DHT11Mode_IN);            //����Ϊ����ģʽ

    while (!GPIO_ReadInputDataBit(DHT11_IO, DHT11_Pin) && retry < 100) //DHT11������40~50us
    {
        retry++;
        Delay_us(1);
    }
    if (retry >= 100)   //��ʱδ��Ӧ/δ�յ���ʼ�źţ��˳����
    {
        //printf("1 data error \r\n");
        return 0;
    }
    else
    {
        retry = 0;
    }
    while (GPIO_ReadInputDataBit(DHT11_IO, DHT11_Pin) && retry < 100) //DHT11���ͺ���ٴ�����40~50us
    {
        retry++;
        Delay_us(1);
    }
    if (retry >= 100)   //��ʱ��DHT11���������˳����
    {
        //printf("2 data error \r\n");
        return 0;
    }
    return 1;                   //�豸������Ӧ��������������
}


