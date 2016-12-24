/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Sergei Chernykh
  * @version V1.0.0
  * @date    23/12/2016
  * @brief   Main program body.
  ******************************************************************************
  */

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "_MCU_drv\MDR32F9Qx_it.h"
#include "port.h"

;
/**
  * @brief  Delay time function.
  * @param  Delay time
  * @reval  None
  */
void delay( uint32_t time )
{
  for (;time;time--);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
    /* Enables the RTCHSE clock on LED_PORT*/
    RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK | LED_RST_CLK_PCLK, ENABLE);
    
    /* Configure LED_PORT pins LED_PINS for output to switch LEDs on/off */
    PORT_InitTypeDef PORT_InitStructure;
    PORT_InitStructure.PORT_Pin   = LED_PINS;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
    
    //Создаем объект порта
    Port ledPort;
    //Устанавливаем имя, пины
    ledPort.Name = LED_PORT;
    ledPort.Pins = LED_PINS;
    //Сбрасываем порт
    ledPort.DeInit();
    ledPort.InitStruct = &PORT_InitStructure;
    //Инициализируем порт
    ledPort.Init();
    
    while(1)
    {
        //поочередно зажигаем светодиоды
        ledPort.SetBits(LED_1);
        delay(300000);
        ledPort.SetBits(LED_2);
        delay(300000);
        //если в платы больше двух светодиодов
#if defined (USE_1901VC1F) || defined (USE_1986VE91T)
        ledPort.SetBits(LED_3);
        delay(300000);
        ledPort.SetBits(LED_4);
        delay(300000);
        ledPort.SetBits(LED_5);
        delay(300000);
#endif
        //в конце гасим все светодиоды
        ledPort.ResetBits();
        delay(300000);
    }   
}