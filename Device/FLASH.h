#ifndef __FLASH_H
#define __FLASH_H


#include "stm32f10x.h"

// STM32F103C8T6     һ�����Ǵ������ַ��ʼ 0x0800F000    Ȼ�������

void Write_flsh_byte(uint32_t EEPROM_ADD, uint32_t EEPROM_Data);
uint32_t readFlash(uint32_t EEPROM_ADD);

#endif




