/**
  ******************************************************************************
  * @file    port.cpp
  * @author  Sergei Chernykh
  * @version V1.0.0
  * @date    23/12/2016
  * @brief   Класс для работы с портом
  ******************************************************************************
  */

#include "port.h"
;
void Port::Init()
{
    PORT_Init(Name, InitStruct);
}

void Port::DeInit()
{
    PORT_DeInit(Name);
}

void Port::SetBits()
{
    PORT_SetBits(Name, Pins);
}

void Port::SetBits(uint32_t pinIndex)
{
    PORT_SetBits(Name, pinIndex);
}

void Port::ResetBits()
{
    PORT_ResetBits(Name, Pins);
}

void Port::ResetBits(uint32_t pinIndex)
{
    PORT_ResetBits(Name, pinIndex);
}