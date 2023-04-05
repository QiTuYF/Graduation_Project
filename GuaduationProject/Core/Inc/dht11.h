#ifndef __DHT11_H__
#define __DHT11_H__
 
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "stdio.h"
#include "stm32f1xx.h"
#include "oled.h" 
 
/* Private define ------------------------------------------------------------*/
#define DHT11_PIN_SET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)                                            //  设置GPIO为高
#define DHT11_PIN_RESET HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)                                          //  设置GPIO为低
#define DHT11_READ_IO   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)                                                          //  DHT11 GPIO定义

#define humiture_count_max 2 //温湿度种类数：就温度和湿度两种
#define humiture_parameter_max 3  //温湿度阈值：上限和下限
#define temprature_parameter 0  //温度阈值参数所在行位置
#define humidity_parameter 1  //湿度阈值参数所在行位置
#define humiture_parameter_lower 0  //温湿度参数中下限所在数组列位置
#define humiture_parameter_upper 1  //温湿度参数中上限所在数组列位置
#define humiture_parameter_switch 2  //温湿度参数中开关状态所在数组列位置宏定义
#define oled__humiture_line (2*i+3) //oled在参数设置页面显示的温湿度行
#define oled__humiture_num_line (3*i+4) //oled在参数设置页面显示的温湿度数字行
#define temprature_threshold_max 50  //系统温度上限最大值
#define temprature_threshold_min 0	//系统温度下限最小值
#define humidity_threshold_max 90  //系统湿度上限最大值
#define humidity_threshold_min 20//系统湿度下限最小值
/* Private function prototypes -----------------------------------------------*/
void DHT11(void);
void DHT11_START(void);
unsigned char DHT11_READ_BIT(void);
unsigned char DHT11_READ_BYTE(void);
unsigned char DHT11_READ_DATA(void);
unsigned char DHT11_Check(void);
static void DHT11_GPIO_MODE_SET(uint8_t mode);
 
void Coarse_delay_us(uint32_t us);

void Sprintf_temprature_humydity(void);
void Show_temprature_humydity(void);
void set_humiture(void);
void set_humiture_threshold_value(void);  
  
#endif
