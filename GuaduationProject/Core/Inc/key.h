#ifndef __KEY_H__
#define __KEY_H__

/* Private includes ----------------------------------------------------------*/
#include "gpio.h"
#include "main.h"
#include "stdio.h"
#include "stm32f1xx.h" 
#include "usart.h"
#include "oled.h"
#include "ds1302.h"
#include "dht11.h"
#include "stmflash.h"
#include "string.h"
#include "tim.h"
/* Private function prototypes -----------------------------------------------*/

#define interface_state_max 3 //最大页面数

void key_scan(void);
void key_state_response(void);
#endif
