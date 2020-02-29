#include <bosdk.h>

#if(BOSDK_ENABLE_BODAL_DRIVER_BUTTON)

#include "fsl_gpio.h"

typedef struct
{
  GPIO_Type    *port;
  uint32_t      pin;
  uint8_t       on_state;
  uint8_t       off_state;
} button_tbl_t;

button_tbl_t btn_tbl[BODAL_BUTTON_MAX_CH] =
{
  {GPIO5, 0, LOW, HIGH},
};


typedef struct
{
  bool        pressed;
  bool        pressed_event;
  uint16_t    pressed_cnt;
  uint32_t    pressed_start_time;
  uint32_t    pressed_end_time;

  bool        released;
  bool        released_event;
  uint32_t    released_start_time;
  uint32_t    released_end_time;

} button_t;


static button_t button_tbl[BODAL_BUTTON_MAX_CH];


#if(BOSDK_ENABLE_UTIL_CMDIF)
void buttonCmdifInit(void);
void buttonCmdif(void);
#endif

static bool is_enable = true;
static bool buttonGetPin(uint8_t ch);

void button_isr(void *arg)
{
  uint8_t i;

  for (i=0; i<BODAL_BUTTON_MAX_CH; i++)
  {
    if(buttonGetPin(i)){
      if(button_tbl[i].pressed == false){
        button_tbl[i].pressed_event = true;
        button_tbl[i].pressed_start_time = millis();
      }
      button_tbl[i].pressed = true;
      button_tbl[i].pressed_cnt++;
      button_tbl[i].pressed_end_time = millis();
      button_tbl[i].released = false;
    }else{
      if(button_tbl[i].pressed == true){
        button_tbl[i].released_event = true;
        button_tbl[i].released_start_time = millis();
      }
      button_tbl[i].pressed  = false;
      button_tbl[i].released = true;
      button_tbl[i].released_end_time = millis();
    }
  }
}



bool buttonInit(void)
{
  uint32_t i;
  swtimer_handle_t h_button_timer;


  for (i=0; i<BODAL_BUTTON_MAX_CH; i++)
  {
    if (btn_tbl[i].port != NULL){
      //
    }
  }

  for (i=0; i<BODAL_BUTTON_MAX_CH; i++)
  {
    button_tbl[i].pressed_cnt    = 0;
    button_tbl[i].pressed        = 0;
    button_tbl[i].released       = 0;
    button_tbl[i].released_event = 0;
  }

  h_button_timer = swtimerGetHandle();
  swtimerSet(h_button_timer, 1, LOOP_TIME, button_isr, NULL );
  swtimerStart(h_button_timer);

#if(BOSDK_ENABLE_UTIL_CMDIF)
  buttonCmdifInit();
#endif


  return true;
}

void buttonResetTime(uint8_t ch)
{
  button_tbl[ch].pressed_start_time    = 0;
  button_tbl[ch].pressed_end_time      = 0;
  button_tbl[ch].released_start_time   = 0;
  button_tbl[ch].released_end_time     = 0;

  button_tbl[ch].pressed_event = false;
  button_tbl[ch].released_event = false;
}

bool buttonGetPin(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH || btn_tbl[ch].port == NULL){
    return false;
  }

  return GPIO_PinRead(btn_tbl[ch].port, btn_tbl[ch].pin) == btn_tbl[ch].on_state;
}

void buttonEnable(bool enable)
{
  is_enable = enable;
}

bool buttonGetPressed(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false){
    return false;
  }

  return button_tbl[ch].pressed;
}

bool buttonOsdGetPressed(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH){
    return false;
  }

  return button_tbl[ch].pressed;
}

bool buttonGetPressedEvent(uint8_t ch)
{
  bool ret;

  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false)
    return false;

  ret = button_tbl[ch].pressed_event;

  button_tbl[ch].pressed_event = 0;

  return ret;
}

uint32_t buttonGetPressedTime(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false)
    return 0;

  return button_tbl[ch].pressed_end_time - button_tbl[ch].pressed_start_time;
}


bool buttonGetReleased(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false)
    return false;

  return button_tbl[ch].released;
}

bool buttonGetReleasedEvent(uint8_t ch)
{
  bool ret;

  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false)
    return false;

  ret = button_tbl[ch].released_event;

  button_tbl[ch].released_event = 0;

  return ret;
}

uint32_t buttonGetReleasedTime(uint8_t ch)
{
  if (ch >= BODAL_BUTTON_MAX_CH || is_enable == false)
    return 0;

  return button_tbl[ch].released_end_time - button_tbl[ch].released_start_time;
}



#if(BOSDK_ENABLE_UTIL_CMDIF)
void buttonCmdifInit(void)
{
  cmdifAdd("button", buttonCmdif);
}

void buttonCmdif(void)
{
  bool ret = true;
  uint8_t ch;
  uint32_t i;

  if (cmdifGetParamCnt() == 1){
    if(cmdifHasString("show", 0) == true){
      while(cmdifRxAvailable() == 0)
      {
        for (i=0; i<BODAL_BUTTON_MAX_CH; i++)
        {
          cmdifPrintf("%d ", buttonGetPressed(i));
        }
        cmdifPrintf("\r");
        delay(50);
      }
    }else{
      ret = false;
    }
  }else if (cmdifGetParamCnt() == 2){
    ch = (uint8_t)cmdifGetParam(1);

    if (ch > 0){
      ch--;
    }

    if (cmdifHasString("time", 0) == true){
      while(cmdifRxAvailable() == 0)
      {
        if(buttonGetPressed(ch)){
          cmdifPrintf("BUTTON%d, Time : %d ms\n", ch+1, buttonGetPressedTime(ch));
        }
      }
    }else if(cmdifHasString("show", 0) == true){
      while(cmdifRxAvailable() == 0)
      {
        cmdifPrintf("BUTTON%d: %d\r\n", ch+1, buttonGetPressed(ch));
        delay(50);
      }
    }else{
      ret = false;
    }
  }else{
    ret = false;
  }

  if(ret == false){
    cmdifPrintf( "button [show/time] channel(1~%d) ...\n", BODAL_BUTTON_MAX_CH);
  }
}
#endif /* BOSDK_ENABLE_UTIL_CMDIF */

#endif /* BOSDK_ENABLE_BODAL_DRIVER_BUTTON */

