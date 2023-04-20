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
//����������
#define BUZZ_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)
//�رշ�����
#define BUZZ_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)
//��ת������״̬
#define BUZZ_TURN HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11)
//�������л�����
#define Read_interface HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
//�������ð���
#define Read_alarmOrhumiture_set HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)
//��+����
#define Read_increase HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)
//��-����
#define Read_decrease HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
//���ý��������л�����
#define Set_up_down HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)
//���ý��������л�����
#define Set_left_right HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
//���ñ����������õ�flash��
#define Set_save_flash HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
//���������ģ���ƽ
#define Read_sound HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
//����LED��
#define LED_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
//�ر�LED��
#define LED_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

