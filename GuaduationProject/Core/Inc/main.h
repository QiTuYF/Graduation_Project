/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DATA_DS1302_Pin GPIO_PIN_1
#define DATA_DS1302_GPIO_Port GPIOA
#define RST_DS1302_Pin GPIO_PIN_2
#define RST_DS1302_GPIO_Port GPIOA
#define CLK_DS1302_Pin GPIO_PIN_3
#define CLK_DS1302_GPIO_Port GPIOA
#define buzzer_io_Pin GPIO_PIN_11
#define buzzer_io_GPIO_Port GPIOB
#define key_interface_Pin GPIO_PIN_12
#define key_interface_GPIO_Port GPIOB
#define key_parameter_set_Pin GPIO_PIN_13
#define key_parameter_set_GPIO_Port GPIOB
#define key_increase_Pin GPIO_PIN_14
#define key_increase_GPIO_Port GPIOB
#define key_decrease_Pin GPIO_PIN_15
#define key_decrease_GPIO_Port GPIOB
#define key_up_down_Pin GPIO_PIN_3
#define key_up_down_GPIO_Port GPIOB
#define key_left_right_Pin GPIO_PIN_4
#define key_left_right_GPIO_Port GPIOB
#define key_save_flash_Pin GPIO_PIN_5
#define key_save_flash_GPIO_Port GPIOB
#define DATA_DHT11_Pin GPIO_PIN_9
#define DATA_DHT11_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
