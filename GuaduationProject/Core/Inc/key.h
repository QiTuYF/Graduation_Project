#ifndef __KEY_H__
#define __KEY_H__

/* Private includes ----------------------------------------------------------*/
#include "gpio.h"
#include "main.h"
#include "stdio.h"
#include "stm32f1xx.h" 
#include "oled.h"
#include "ds1302.h"
#include "dht11.h"
/* Private function prototypes -----------------------------------------------*/
void key_scan(void);
void key_state_response(void);
#endif
