/**
  ******************************************************************************
  * @file    port.h
  * @author  Sergei Chernykh
  * @version V1.0.0
  * @date    23/12/2016
  * @brief   Класс для работы с портом
  ******************************************************************************
  */
      
#ifndef PORT_H
#define PORT_H

#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_config.h"

class Port
{
public:
    //Имя порта
    MDR_PORT_TypeDef*   Name;
    //Рабочие пины
    uint32_t            Pins;
    //Структура инициализации
    PORT_InitTypeDef*   InitStruct;
    
public:
    //Инициализировать порт
    void Init();
    //Деинициализировать порт
    void DeInit();
    //Зажечь все пины Pins
    void SetBits();
    //Зажечь пин pinIndex
    void SetBits(uint32_t pinIndex);
    //Погасить все пины Pins
    void ResetBits(); 
    //Погасить пин pinIndex
    void ResetBits(uint32_t pinIndex);
}
#endif