#ifndef __ds1302_H 
#define __ds1302_H  

#include "main.h"
#include "gpio.h"
#include "stdio.h"
#include "oled.h"
#include "stm32f1xx.h"
#include "string.h"
 
#define W_SECOND 0x80
#define W_MINUTE 0x82
#define W_HOUR   0x84
#define W_DAY    0x86
#define W_MONTH  0x88
#define W_WEEK   0x8A
#define W_YEAR   0x8C
#define W_CONTR  0x8E
 
#define R_SECOND 0x81
#define R_MINUTE 0x83
#define R_HOUR   0x85
#define R_DAY    0x87
#define R_MONTH  0x89
#define R_WEEK   0x8B
#define R_YEAR   0x8D
#define R_CONTR  0x8F

#define alarm_count_max 3 //闹钟最大数
#define alarm_parameter_max 4  //闹钟最大参数：如、时、分、秒、开启或关闭
 
#define RST_L     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define RST_H     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define CLK_L     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
#define CLK_H     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define DATA_L    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define DATA_H    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
 
#define DATA_READ HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)
 
typedef struct {
	uint8_t year;
	uint8_t week;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}timeNow_t;

//static void DS1302_Data_Write_Init(void);
//static void DS1302_Data_Read_Init(void);
void DS1302_Single_Byte_Write(uint8_t data);
void DS1302_Write_Register(uint8_t regAddress,uint8_t regData);
uint8_t DS1302_Read_Register(uint8_t regAddress);
void DS1302_Set_Time(uint8_t year,uint8_t week,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second);
timeNow_t DS1302_Read_Time(void);
void DS1302_Print_Time(void);
void Show_time(void);
void Set_alarm(void);
 
#endif
