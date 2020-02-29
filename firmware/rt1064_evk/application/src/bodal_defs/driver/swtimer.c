#include <bosdk.h>

#if(BOSDK_ENABLE_BODAL_DRIVER_SWTIMER)

typedef struct
{

  uint8_t  Timer_En;
  uint8_t  Timer_Mode;
  uint32_t Timer_Ctn;
  uint32_t Timer_Init;
  void (*TmrFnct)(void *);
  void *TmrFnctArg;
} swtimer_t;

static volatile uint32_t sw_timer_counter = 0;
static volatile uint16_t sw_timer_handle_index = 0;
static swtimer_t swtimer_tbl[HW_SWTIMER_MAX_CH];

bool swtimerInit(void)
{
  uint8_t i;
  static uint8_t is_init = 0;

  if (is_init == 1){
    return false;
  }

  for(i=0; i<HW_SWTIMER_MAX_CH; i++)
  {
    swtimer_tbl[i].Timer_En   = OFF;
    swtimer_tbl[i].Timer_Ctn  = 0;
    swtimer_tbl[i].Timer_Init = 0;
    swtimer_tbl[i].TmrFnct    = NULL;
  }

  is_init = 1;

  return true;
}

void swtimerISR(void)
{
  uint8_t i;

  sw_timer_counter++;

  for (i=0; i<HW_SWTIMER_MAX_CH && i<sw_timer_handle_index; i++)
  {
    if(swtimer_tbl[i].Timer_En == ON){
      swtimer_tbl[i].Timer_Ctn--;
      if(swtimer_tbl[i].Timer_Ctn == 0){
        if(swtimer_tbl[i].Timer_Mode == ONE_TIME){
          swtimer_tbl[i].Timer_En = OFF;
        }
        swtimer_tbl[i].Timer_Ctn = swtimer_tbl[i].Timer_Init;
        (*swtimer_tbl[i].TmrFnct)(swtimer_tbl[i].TmrFnctArg);
      }
    }
  }

}

void swtimerSet(uint8_t TmrNum, uint32_t TmrData, uint8_t TmrMode, void (*Fnct)(void *),void *arg)
{
  swtimer_tbl[TmrNum].Timer_Mode = TmrMode;
  swtimer_tbl[TmrNum].TmrFnct    = Fnct;
  swtimer_tbl[TmrNum].TmrFnctArg = arg;
  swtimer_tbl[TmrNum].Timer_Ctn  = TmrData;
  swtimer_tbl[TmrNum].Timer_Init = TmrData;
}

void swtimerStart(uint8_t TmrNum)
{
  if(TmrNum < HW_SWTIMER_MAX_CH){
    swtimer_tbl[TmrNum].Timer_Ctn = swtimer_tbl[TmrNum].Timer_Init;
    swtimer_tbl[TmrNum].Timer_En  = ON;
  }
}

void swtimerStop (uint8_t TmrNum)
{
  if(TmrNum < HW_SWTIMER_MAX_CH){
    swtimer_tbl[TmrNum].Timer_En = OFF;
  }
}

void swtimerReset(uint8_t TmrNum)
{
  swtimer_tbl[TmrNum].Timer_En   = OFF;
  swtimer_tbl[TmrNum].Timer_Ctn  = swtimer_tbl[TmrNum].Timer_Init;
}

swtimer_handle_t swtimerGetHandle(void)
{
  swtimer_handle_t TmrIndex = sw_timer_handle_index;

  sw_timer_handle_index++;

  return TmrIndex;
}

uint32_t swtimerGetCounter(void)
{
  return sw_timer_counter;
}

#endif /* BOSDK_ENABLE_BODAL_DRIVER_SWTIMER */

