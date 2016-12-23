/**
  ******************************************************************************
  * @file    Examples/1986BE93_EVAL/PORT/Joystick_LEDs/main.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    16/10/2010
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#define         USE_MDR32F9Q1_Rev0

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "_MCU_drv\MDR32F9Qx_it.h"


/** @addtogroup __1986BE9x_StdPeriph_Examples 1986BE9x StdPeriph Examples
  * @{
  */

/** @addtogroup __1986BE93_EVAL 1986BE93 Evaluation Board
  * @{
  */

/** @addtogroup PORT_Joystick_LEDs PORT_Joystick_LEDs
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ALL_PORTS_CLK (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
//                       RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
//                       RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

#define LEDS_PORT MDR_PORTD
#define LEDS_RST_CLK_PCLK_PORT  RST_CLK_PCLK_PORTD

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

//int port;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void Init_All_Ports(void)
{
  /* Enable the RTCHSE clock on all ports */
  RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);

  /* Configure all ports to the state as after reset, i.e. low power consumption */
  PORT_StructInit(&PORT_InitStructure);
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_Init(MDR_PORTB, &PORT_InitStructure);
  PORT_Init(MDR_PORTC, &PORT_InitStructure);
  PORT_Init(MDR_PORTD, &PORT_InitStructure);
  PORT_Init(MDR_PORTE, &PORT_InitStructure);
  PORT_Init(MDR_PORTF, &PORT_InitStructure);

  /* Disable the RTCHSE clock on all ports */
  RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
}

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
  uint32_t tmp_port_pin;
  
  /*!< Usually, reset is done before the program is to be loaded into microcontroller,
       and there is no need to perform any special operations to switch the ports 
       to low power consumption mode explicitly. So, the function Init_All_Ports 
       is used here for demonstration purpose only.     
  */
  Init_All_Ports();
  
  NVIC_EnableIRQ( SVCall_IRQn );

  /* Enables the RTCHSE clock on PORTE and PORTF */
  RST_CLK_PCLKcmd( RST_CLK_PCLK_RST_CLK | LEDS_RST_CLK_PCLK_PORT, ENABLE );

  /* Configure PORTF pins 0,1 for output to switch LEDs on/off */

  PORT_InitStructure.PORT_Pin   = (PORT_Pin_10 | PORT_Pin_11);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(LEDS_PORT, &PORT_InitStructure);

  /* Configure PORTE pins 3, 6 for input to handle joystick events 

  PORT_InitStructure.PORT_Pin   = (PORT_Pin_3 | PORT_Pin_6);
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(PORTF, &PORT_InitStructure);
  */


  /* In this infinite loop, PORTE pin3 and pin6 (joystick) are iteratively scanned and 
     PORTF output pins (LED indicators) are appropriately set/cleared.  
     Note: in this example, the following fact about 1986BE93 eval board is used: the
     joystic input pin numbers exactly match LED output pins, i.e:
         LEFT   => VD2
         RIGHT  => VD3   
  */
  while( 1 )
  {
    PORT_SetBits(LEDS_PORT, PORT_Pin_10);
   
    for(int i = 0; i < 3; i++)
    {
        PORT_SetBits(LEDS_PORT, PORT_Pin_11);
        delay(100000);
        PORT_ResetBits(LEDS_PORT, PORT_Pin_11);
    }
    
    PORT_ResetBits(LEDS_PORT, PORT_Pin_10);
    delay(100000);
  }
}

/**
  * @brief  Reports the source file ID, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file_id: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
  /* User can add his own implementation to report the source file ID and line number.
     Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group PORT_Joystick_LEDs */

/** @} */ /* End of group __1986BE93_EVAL */

/** @} */ /* End of group __1986BE9x_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2010 Milandr *******************
*
* END OF FILE main.c */

