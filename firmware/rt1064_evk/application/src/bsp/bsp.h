/*
 * bsp.h
 *
 *  Created on: 2020. 2. 17.
 *      Author: Baram
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"


#define logPrintf(...)    printf(__VA_ARGS__)


void bspInit(void);
void bspDeInit(void);

extern void delay(uint32_t delay_ms);
extern uint32_t millis(void);
extern uint32_t micros(void);


#ifdef __cplusplus
}
#endif

#endif /* SRC_BSP_BSP_H_ */
