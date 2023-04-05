#ifndef __DHT11_H__
#define __DHT11_H__
 
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "stdio.h"
#include "stm32f1xx.h"
#include "oled.h" 
 
/* Private define ------------------------------------------------------------*/
#define DHT11_PIN_SET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)                                            //  ����GPIOΪ��
#define DHT11_PIN_RESET HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)                                          //  ����GPIOΪ��
#define DHT11_READ_IO   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)                                                          //  DHT11 GPIO����

#define humiture_count_max 2 //��ʪ�������������¶Ⱥ�ʪ������
#define humiture_parameter_max 3  //��ʪ����ֵ�����޺�����
#define temprature_parameter 0  //�¶���ֵ����������λ��
#define humidity_parameter 1  //ʪ����ֵ����������λ��
#define humiture_parameter_lower 0  //��ʪ�Ȳ�������������������λ��
#define humiture_parameter_upper 1  //��ʪ�Ȳ�������������������λ��
#define humiture_parameter_switch 2  //��ʪ�Ȳ����п���״̬����������λ�ú궨��
#define oled__humiture_line (2*i+3) //oled�ڲ�������ҳ����ʾ����ʪ����
#define oled__humiture_num_line (3*i+4) //oled�ڲ�������ҳ����ʾ����ʪ��������
#define temprature_threshold_max 50  //ϵͳ�¶��������ֵ
#define temprature_threshold_min 0	//ϵͳ�¶�������Сֵ
#define humidity_threshold_max 90  //ϵͳʪ���������ֵ
#define humidity_threshold_min 20//ϵͳʪ��������Сֵ
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
