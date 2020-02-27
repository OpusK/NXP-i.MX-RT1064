#include "ap.h"
#include "bsp.h"

#include "led_blinky/led_blinky.h"

void apInit(void)
{
  bsp_init();
}

void apMain(void)
{
  while(1)
  {
    ap_led_blinky();
  }
}
