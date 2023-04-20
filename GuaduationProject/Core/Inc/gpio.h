/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
//开启蜂鸣器
#define BUZZ_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)
//关闭蜂鸣器
#define BUZZ_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)
//翻转蜂鸣器状态
#define BUZZ_TURN HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11)
//读界面切换按键
#define Read_interface HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
//闹钟设置按键
#define Read_alarmOrhumiture_set HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)
//读+按键
#define Read_increase HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)
//读-按键
#define Read_decrease HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
//设置界面上下切换按键
#define Set_up_down HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)
//设置界面左右切换按键
#define Set_left_right HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
//设置保存闹钟设置到flash中
#define Set_save_flash HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
//读声音检测模块电平
#define Read_sound HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
//开启LED灯
#define LED_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
//关闭LED灯
#define LED_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

