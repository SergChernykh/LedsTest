#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "_MCU_drv\MDR32F9Qx_it.h"

#include "port.h"

;
void delay( uint32_t time )
{
  for (;time;time--);
}

void main(void)
{
    RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK | LED_RST_CLK_PCLK, ENABLE);
    
    PORT_InitTypeDef PORT_InitStructure;
    PORT_InitStructure.PORT_Pin   = LED_PINS;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
    
    Port ledPort;
    
    ledPort.Name = LED_PORT;
    ledPort.Pins = LED_PINS;
    ledPort.DeInit();
    ledPort.InitStruct = &PORT_InitStructure;
    ledPort.Init();
    
    while(1)
    {
        ledPort.SetBits(LED_1);
        delay(300000);
        ledPort.SetBits(LED_2);
        delay(300000);
#if defined (USE_1901VC1F) || defined (USE_1986VE91T)
        ledPort.SetBits(LED_3);
        delay(300000);
        ledPort.SetBits(LED_4);
        delay(300000);
        ledPort.SetBits(LED_5);
        delay(300000);
#endif
        ledPort.ResetBits();
        delay(300000);
    }
    
}