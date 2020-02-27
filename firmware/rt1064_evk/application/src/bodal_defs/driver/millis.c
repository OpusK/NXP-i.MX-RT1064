#include <bodal/bodal.h>

#if(BOSDK_ENABLE_BODAL_DRIVER_MILLIS)

extern uint32_t get_systick_counter();

bool millisInit(void)
{
  return true;
}

uint32_t millis(void)
{
  return get_systick_counter();
}

#endif /* BOSDK_ENABLE_BODAL_DRIVER_MILLIS */
