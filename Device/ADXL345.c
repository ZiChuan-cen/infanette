
/******************************
    ���ܣ�
            ���Ƕ�ģ��Ƕ�
    ʾ����
            Init_ADXL345(); //��ʼ����Ǵ�����
            Angle();                //����ѭ��,ʵʱ�������
            if(Angle_flag)  //�жϵ�ǰ״̬
    ע�⣺
            ����ͷ�ļ���
            �޸�IO��
******************************/


#include "ADXL345.h"
#include "delay.h"

uint8_t Angle_flag0 = 0;        //��ǰ״̬ 0���� 1����
uint8_t BUF[8];                 //������Ǵ����������ԭʼ����
int ADXL345_y = 0, ADXL345_x = 0, ADXL345_z = 0;        //y��ĽǶ�
/***********************
    �жϵ�ǰ״̬
    �Ƕ��ж�
**************************/


void Angle(void)                    //�ж�״̬
{
    Delay_ms(500);

    Multiple_ReadADXL345();                      //�����������ݣ��洢��BUF��
    ADXL345_y = (BUF[3] << 8) + BUF[2];
    ADXL345_x = (BUF[1] << 8) + BUF[0];
    ADXL345_z = (BUF[5] << 8) + BUF[4];
    if (ADXL345_x < 0) ADXL345_x = -ADXL345_x;
    if (ADXL345_y < 0) ADXL345_x = -ADXL345_y;
    if (ADXL345_z < 0) ADXL345_x = -ADXL345_z;

    if (ADXL345_y < 120 || (ADXL345_y > 360))
    {
        Angle_flag0 = 0 ;               //����

    }
    else if ((ADXL345_y > 180))
    {
        Angle_flag0 = 1 ;               //����
    }

}






void ADXL_345_ALL_Int()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    ADXL345_GPIOCLK;

    /*Configure GPIO pin Output Level */
    GPIO_SetBits(ADXL345_GPIO, ADXL345_SDA | ADXL345_SCL);

    //HAL_GPIO_WritePin(ADXL345_GPIO, ADXL345_SDA | ADXL345_SCL, GPIO_PIN_SET);

    /*Configure GPIO pins : PB10 PB11 */
    GPIO_InitStruct.GPIO_Pin = ADXL345_SDA | ADXL345_SCL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);

}

void ADXL345_SDA_Output()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    ADXL345_GPIOCLK;

    GPIO_InitStruct.GPIO_Pin = ADXL345_SDA;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);
}

void ADXL345_SDA_Intput()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    ADXL345_GPIOCLK;
    /*Configure GPIO pins : PB10 PB11 */
    GPIO_InitStruct.GPIO_Pin =  ADXL345_SDA;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(ADXL345_GPIO, &GPIO_InitStruct);
}


///**************************************
//��ʱ5΢��(STC90C52RC@12M)
//��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
//������1T��MCUʱ,���������ʱ����
//**************************************/
//void Delay5us()
//{
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();
//    __nop();

//}

///**************************************
//��ʱ5����(STC90C52RC@12M)
//��ͬ�Ĺ�������,��Ҫ�����˺���
//������1T��MCUʱ,���������ʱ����
//**************************************/
//void Delay5ms()
//{
//    HAL_Delay(3);
//}

/**************************************
��ʼ�ź�
**************************************/
void ADXL345_Start()
{
    SDA_1;                    //����������
    SCL_1;                    //����ʱ����
    Delay_us(5);                 //��ʱ
    SDA_0;                    //�����½���
    Delay_us(5);                 //��ʱ
    SCL_0;                    //����ʱ����

}

/**************************************
ֹͣ�ź�
**************************************/
void ADXL345_Stop()
{

    SDA_0;                    //����������
    SCL_1;                    //����ʱ����
    Delay_us(5);                 //��ʱ
    SDA_1;                    //����������
    Delay_us(5);                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{
    if (ack == 1) SDA_1;
    else       SDA_0;
//  SDA = ack;                  //дӦ���ź�
    SCL_1;                    //����ʱ����
    Delay_us(5);                 //��ʱ
    SCL_0;                    //����ʱ����
    Delay_us(5);                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
unsigned char ADXL345_RecvACK()
{

    unsigned char CY_Dat = 0;
    SCL_1;                    //����ʱ����
    Delay_us(5);                 //��ʱ
    if (ADXL345SDA == 1) CY_Dat = 1;
    else   CY_Dat = 0;
//    CY_Dat = SDA;                   //��Ӧ���ź�

    SCL_0;                    //����ʱ����
    Delay_us(5);                 //��ʱ
    ADXL345_SDA_Output();
    return CY_Dat;

}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void ADXL345_Sendbyte(unsigned char dat)
{
    unsigned char i;
    ADXL345_SDA_Output();
    for (i = 0; i < 8; i++)     //8λ������
    {
        if ((dat & 0x80) == 0x80) SDA_1;
        else                               SDA_0;
        dat <<= 1;              //�Ƴ����ݵ����λ
        //    SDA = CY;               //�����ݿ�
        SCL_1;                //����ʱ����
        Delay_us(5);             //��ʱ
        SCL_0;                //����ʱ����
        Delay_us(5);             //��ʱ
    }
    ADXL345_SDA_Intput();
    ADXL345_RecvACK();
    ADXL345_SDA_Output();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
unsigned char ADXL345_Recvbyte()
{
    unsigned char i;
    unsigned char dat = 0;
    SDA_1;                    //ʹ���ڲ�����,׼����ȡ����,
    ADXL345_SDA_Intput();
    for (i = 0; i < 8; i++)     //8λ������
    {
        dat <<= 1;
        SCL_1;                //����ʱ����
        Delay_us(5);             //��ʱ
        if (ADXL345SDA == 1) dat |= 0x01;  //������
        else              dat |= 0x00;
        SCL_0;                //����ʱ����
        Delay_us(5);             //��ʱ
    }
    ADXL345_SDA_Output();
    return dat;

}

//******���ֽ�д��*******************************************

void Single_Write_ADXL345(unsigned char REG_Address, unsigned char REG_data)
{
    ADXL345_Start();                  //��ʼ�ź�
    ADXL345_Sendbyte(SlaveAddress);   //�����豸��ַ+д�ź�
    ADXL345_Sendbyte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
    ADXL345_Sendbyte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
    ADXL345_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
unsigned char Single_Read_ADXL345(unsigned char REG_Address)
{
    unsigned char REG_data;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Sendbyte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_Sendbyte(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Sendbyte(SlaveAddress + 1);       //�����豸��ַ+���ź�
    REG_data = ADXL345_Recvbyte();            //�����Ĵ�������
    ADXL345_SendACK(1);
    ADXL345_Stop();                           //ֹͣ�ź�
    return REG_data;
}
//*********************************************************
//
//��������ADXL345�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
//
//*********************************************************
void Multiple_ReadADXL345(void)
{
    unsigned char i;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Sendbyte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_Sendbyte(0x32);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Sendbyte(SlaveAddress + 1);       //�����豸��ַ+���ź�
    for (i = 0; i < 6; i++)                  //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = ADXL345_Recvbyte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
            ADXL345_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
            ADXL345_SendACK(0);                //��ӦACK
        }
    }
    ADXL345_Stop();                          //ֹͣ�ź�
    Delay_ms(5);
}

//*****************************************************************

//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�************************
void Init_ADXL345()
{

    ADXL_345_ALL_Int();
    Delay_ms(500);
    Single_Write_ADXL345(0x31, 0x0B);  //������Χ,����16g��13λģʽ
    Single_Write_ADXL345(0x2C, 0x08);  //�����趨Ϊ12.5 �ο�pdf13ҳ
    Single_Write_ADXL345(0x2D, 0x08);  //ѡ���Դģʽ   �ο�pdf24ҳ
    Single_Write_ADXL345(0x2E, 0x80);  //ʹ�� DATA_READY �ж�
    Single_Write_ADXL345(0x1E, 0x00);  //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    Single_Write_ADXL345(0x1F, 0x00);  //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
    Single_Write_ADXL345(0x20, 0x00);  //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}






























