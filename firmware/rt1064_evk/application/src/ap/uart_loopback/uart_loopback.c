#include <bosdk.h>
#include "uart_loopback.h"

void ap_uart_loopback_init()
{
  uartInit();
  uartOpen(0, 115200);
}

void ap_uart_loopback_loop()
{
  while(uartAvailable(0) > 0)
  {
    uartPutch(0, uartGetch(0));
  }
}

