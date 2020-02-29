#include "ap.h"
#include "bsp.h"

#include "bosdk.h"

void apInit(void)
{
  bsp_init();

  //LED
  ledInit();

  //UART
  uartInit();
  uartOpen(0, 115200);
}

void apMain(void)
{
  static uint32_t pre_time;

  while(1)
  {
    while(uartAvailable(0) > 0)
    {
      uartPutch(0, uartGetch(0));
    }

    if (millis()-pre_time >= 500){
      pre_time = millis();
      ledToggle(0);
    }
  }
}
