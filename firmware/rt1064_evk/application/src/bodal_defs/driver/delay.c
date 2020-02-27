#include <bodal/bodal.h>

#if(BOSDK_ENABLE_BODAL_DRIVER_DELAY)

extern uint32_t get_systick_counter();

void delayInit(void)
{

}

void delay(uint32_t ms)
{
  uint32_t pre_time = get_systick_counter();

  while(get_systick_counter()-pre_time < ms);
}

void delayNs(uint32_t ns)
{

}

void delayUs(uint32_t us)
{

}

#endif /* BOSDK_ENABLE_BODAL_DRIVER_DELAY */
