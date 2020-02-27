#include <bosdk.h>

#if(BOSDK_ENABLE_BODAL_DRIVER_LED)

#include "fsl_gpio.h"

typedef struct
{
  GPIO_Type *port;
  uint32_t  pin;
  uint8_t   on_state;
  uint8_t   off_state;
} led_tbl_t;


static led_tbl_t led_tbl[BODAL_LED_MAX_CH] =
    {
        {GPIO1, 9, 0, 1},
    };




bool ledInit(void)
{
  for (int i=0; i<BODAL_LED_MAX_CH; i++)
  {
    ledOff(i);
  }

  return true;
}

void ledOn(uint8_t ch)
{
  GPIO_PinWrite(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_state);
}

void ledOff(uint8_t ch)
{
  GPIO_PinWrite(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_state);
}

void ledToggle(uint8_t ch)
{
  GPIO_PortToggle(led_tbl[ch].port, (1<<led_tbl[ch].pin));
}


#endif /* BOSDK_ENABLE_BODAL_DRIVER_LED */

