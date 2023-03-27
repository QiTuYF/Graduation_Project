#include "stmflash.h"
#include "stdio.h"
const u8 TEXT_Buffer_1[]={"STM32 FLASH TEST_1"};//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer_2[]={"STM32 FLASH TEST_2"};//要写入到STM32 FLASH的字符串数组
#define SIZE sizeof(TEXT_Buffer_1)	 	//数组长度
 
 
int main(void)
{
 
u8 datatemp[SIZE];  //Flash读取缓存数组
u8 *p=datatemp;	    //数组指针   
  
    HAL_Init();
  
    SystemClock_Config();
  
    MX_GPIO_Init();
    MX_USART1_UART_Init();
 
printf("串口打印正常!\r\n");
   
STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_1,SIZE);//第一次写读
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
printf("%s\r\n",p);
HAL_Delay(50);
STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_2,SIZE);//第二次写读    
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
printf("%s\r\n",p);
 
  while (1){
  }
 
}