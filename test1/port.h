/**
  ******************************************************************************
  * @file    port.h
  * @author  Sergei Chernykh
  * @version V1.0.0
  * @date    23/12/2016
  * @brief   ����� ��� ������ � ������
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
    //��� �����
    MDR_PORT_TypeDef*   Name;
    //������� ����
    uint32_t            Pins;
    //��������� �������������
    PORT_InitTypeDef*   InitStruct;
    
public:
    //���������������� ����
    void Init();
    //������������������ ����
    void DeInit();
    //������ ��� ���� Pins
    void SetBits();
    //������ ��� pinIndex
    void SetBits(uint32_t pinIndex);
    //�������� ��� ���� Pins
    void ResetBits(); 
    //�������� ��� pinIndex
    void ResetBits(uint32_t pinIndex);
}
#endif