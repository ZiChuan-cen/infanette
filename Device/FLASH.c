#include "FLASH.h"


//flash��ַ��ʼ��0x0800 0000��
//������ַ��0x0800 0000 + оƬʵ�ʵ�flash��С
//��ͬ��оƬflash��С��ͬ

//һ�������洢�����һЩ����Ϊconst�����ݣ��ϵ粻��ʧ

void Write_flsh_byte(uint32_t EEPROM_ADD, uint32_t EEPROM_Data)
{
    //1������FLASH
	FLASH_Unlock();
    //2������FLASH
    //��ʼ��FLASH_EraseInitTypeDef
	
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = EEPROM_ADD;
    f.NbPages = 1;
    //����PageError
    uint32_t PageError = 0;
    //���ò�������
    FLASH_ErasePage(&f, &PageError);
    //3����FLASH��д
    FLASH_ProgramWord(FLASH_TYPEPROGRAM_WORD, EEPROM_ADD, EEPROM_Data);
    FLASH_Lock();
}

//FLASH��ȡ���ݲ���
uint32_t readFlash(uint32_t EEPROM_ADD)
{
    uint32_t temp = *(__IO uint32_t *)(EEPROM_ADD);
    return temp;
}







