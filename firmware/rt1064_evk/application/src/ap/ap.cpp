#include "ap.h"
#include "bsp.h"

#include "bosdk.h"

void apInit(void)
{
  bsp_init();

  //Software Timer
  swtimerInit();

  //CMDIF using UART
  uartInit();
  cmdifInit();
  cmdifOpen(0, 115200);

  //LED
  ledInit();

  //Button
  buttonInit();
}

void apMain(void)
{
  static uint32_t pre_time;

  while(1)
  {
    cmdifMain();

    if (millis()-pre_time >= 500){
      pre_time = millis();
      ledToggle(0);
    }
  }
}
