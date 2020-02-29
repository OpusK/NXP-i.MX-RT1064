#include <bosdk.h>
#include "button_cmdif.h"

void ap_button_cmdif_init()
{
  swtimerInit();

  uartInit();
  cmdifInit();
  cmdifOpen(0, 115200);

  buttonInit();
}

void ap_button_cmdif_loop()
{
  cmdifMain();
}

