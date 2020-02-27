#include <bosdk.h>
#include "led_blinky.h"

void ap_led_blinky()
{
  static uint32_t pre_time;

  if (millis()-pre_time >= 500){
    pre_time = millis();
    ledToggle(0);
  }
}

