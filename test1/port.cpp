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
    PORT_SetBits(Name, Pin);
}

void Port::ResetBits()
{
    PORT_ResetBits(Name, Pin);
}