#ifndef __USERCODE_H
#define __USERCODE_H




//================================================================================��־λ
uint8_t UartFlag;//���ڱ�־λ
uint8_t BeepFlag;//��������־λ
uint8_t Dht11Flag;//��ʪ�ȱ�־λ
uint8_t TempFlag;//�¶ȱ�־λ

//================================================================================����
uint8_t SysFace, s0;
uint16_t Temp;//�¶�
uint8_t Humi;//ʪ��
uint8_t Heart, Spo2; //����Ѫ��
uint8_t TempState;//1���¶ȸ�������2:�¶ȵ�������0������
uint8_t HumiState;//1��ʪ�ȸ�������2:ʪ�ȵ�������0������
uint8_t HeartState;//1�����ʸ�������2:���ʵ�������0������
uint8_t Spo2State;//1��Ѫ����������2:Ѫ����������0������
uint8_t VoiceState;
uint8_t BeepKey;//�����رձ���
uint8_t Receive3;//���ڽ�������
uint8_t ReadMAX30102data = 0;

//================================================================================��ֵ
uint8_t Temp_H, Temp_L; //�¶�������
uint8_t Humi_H, Humi_L; //ʪ��������
uint8_t Spo2_H, Spo2_L; //Ѫ��������
uint8_t Heart_H, Heart_L; //����������

//================================================================================��ʱ
uint8_t Time_MS;//��ʱ������
uint8_t BeepTime;//��������ʱ
unsigned int MAX30102Time = 0;      //-- ������ʱ
uint8_t VoiceTime;





#endif

