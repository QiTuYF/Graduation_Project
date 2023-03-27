#include "stmflash.h"
#include "stdio.h"
const u8 TEXT_Buffer_1[]={"STM32 FLASH TEST_1"};//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer_2[]={"STM32 FLASH TEST_2"};//Ҫд�뵽STM32 FLASH���ַ�������
#define SIZE sizeof(TEXT_Buffer_1)	 	//���鳤��
 
 
int main(void)
{
 
u8 datatemp[SIZE];  //Flash��ȡ��������
u8 *p=datatemp;	    //����ָ��   
  
    HAL_Init();
  
    SystemClock_Config();
  
    MX_GPIO_Init();
    MX_USART1_UART_Init();
 
printf("���ڴ�ӡ����!\r\n");
   
STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_1,SIZE);//��һ��д��
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
printf("%s\r\n",p);
HAL_Delay(50);
STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer_2,SIZE);//�ڶ���д��    
STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
printf("%s\r\n",p);
 
  while (1){
  }
 
}