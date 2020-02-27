#include "bsp.h"

#include "config/board/clock_config.h"
#include "config/board/pin_mux.h"
#include "config/board/peripherals.h"

void bsp_init()
{
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

  SysTick_Config(SystemCoreClock/1000U);
}


static volatile uint32_t systick_counter = 0;

void SysTick_Handler(void)
{
  systick_counter++;
}

uint32_t get_systick_counter()
{
  return systick_counter;
}
