#include "ds1302.h"
 
uint32_t year=0,month=0,day=0,hour=0,minute=0,second=0,week=0;
char  yea[5],mon[3],dayy[3],hou[3],minu[3],sec[3],wee[2];
static void DS1302_Data_Write_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
static void DS1302_Data_Read_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DS1302_Single_Byte_Write(uint8_t data)
{
	DS1302_Data_Write_Init();
	CLK_L;
	for(int i=0;i<8;i++)
	{
		CLK_L;
		if((data&0x01)==0x01)
			DATA_H;
		else
			DATA_L;
		CLK_H;
		data>>=0x01;
	}
}
void DS1302_Write_Register(uint8_t regAddress,uint8_t regData)
{
	RST_L;
	CLK_L;
	HAL_Delay(1);
	RST_H;
	HAL_Delay(2);
	DS1302_Single_Byte_Write(regAddress);
	DS1302_Single_Byte_Write(regData);	
	RST_L;
	CLK_L;
	HAL_Delay(2);
}
uint8_t DS1302_Read_Register(uint8_t regAddress)
{
	RST_L;
	CLK_L;
	uint8_t regData=0x00;
	HAL_Delay(3);
	RST_H;
	DS1302_Single_Byte_Write(regAddress);
	DS1302_Data_Read_Init();
	for(int i=0;i<8;i++)
	{
		regData>>=0x01;
		CLK_H;
		HAL_Delay(4);
		CLK_L;
		HAL_Delay(14);
		if(DATA_READ==GPIO_PIN_SET)
			regData=regData|0x80;
	}
	HAL_Delay(4);
	RST_L;
	DATA_L;
	return regData;
}

void DS1302_Set_Time(uint8_t year,uint8_t week,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second)
{
	DS1302_Write_Register(W_CONTR,0x00);
	DS1302_Write_Register(W_YEAR,year);
	DS1302_Write_Register(W_WEEK,week);
	DS1302_Write_Register(W_MONTH,month);
	DS1302_Write_Register(W_DAY,day);
	DS1302_Write_Register(W_HOUR,hour);
	DS1302_Write_Register(W_MINUTE,minute);
	DS1302_Write_Register(W_SECOND,second);
	DS1302_Write_Register(W_CONTR,0x80);
}
timeNow_t DS1302_Read_Time(void)
{
	timeNow_t timeNow;
	timeNow.year=DS1302_Read_Register(R_YEAR);
	timeNow.week=DS1302_Read_Register(R_WEEK);
	timeNow.month=DS1302_Read_Register(R_MONTH);
	timeNow.day=DS1302_Read_Register(R_DAY);
	timeNow.hour=DS1302_Read_Register(R_HOUR);
	timeNow.minute=DS1302_Read_Register(R_MINUTE);
	timeNow.second=DS1302_Read_Register(R_SECOND);
	return timeNow;
}

void DS1302_Print_Time(void)
{
	timeNow_t timeNow=DS1302_Read_Time();
//	printf("20%02X-%02X-%02X %02X:%02X:%02X\r\n",timeNow.year,timeNow.month,timeNow.day,timeNow.hour,timeNow.minute,timeNow.second);
	year=2000+timeNow.year/16*10+timeNow.year%16;	
	month=timeNow.month/16*10+timeNow.month%16;
	day=timeNow.day/16*10+timeNow.day%16;
	hour=timeNow.hour/16*10+timeNow.hour%16;
	minute=timeNow.minute/16*10+timeNow.minute%16;
	second=timeNow.second/16*10+timeNow.second%16;
	week=timeNow.week/16*10+timeNow.week%16;
}

void Sprintf_time(void)
{
	printf("%d-%d-%02d %d:%02d:%02d 星期%d\r\n",year,month,day,hour,minute,second,week);
	memset(yea,0,sizeof(sec));
	memset(mon,0,sizeof(sec));
	memset(dayy,0,sizeof(sec));
	memset(hou,0,sizeof(sec));
	memset(minu,0,sizeof(sec));
	memset(sec,0,sizeof(sec));
	memset(wee,0,sizeof(sec));
	sprintf(yea,"%d",year);
	sprintf(mon,"%02d",month);
	sprintf(dayy,"%02d",day);
	sprintf(hou,"%02d",hour);
	sprintf(minu,"%02d",minute);
	sprintf(sec,"%02d",second);
	sprintf(wee,"%d",week);
	
	
}

void Show_time(void)
{
	DS1302_Print_Time();
	Sprintf_time();
	//	OLED_ShowString(0,6,(uint8_t *)"Time:",16);      //显示时间
//	OLED_ShowCHinese(0,6,11);   //显示时间
//	OLED_ShowCHinese(16,6,12);
//	OLED_ShowCHinese(32,6,6);
//	OLED_ShowNum(0,6,year,4,16);
	OLED_ShowString(0,6,(uint8_t *)yea,16);
	OLED_ShowString(40,6,(uint8_t *)mon,16);
	OLED_ShowString(56,6,(uint8_t *)dayy,16);
	OLED_ShowString(72,6,(uint8_t *)hou,16);
	OLED_ShowString(88,6,(uint8_t *)minu,16);
	OLED_ShowString(104,6,(uint8_t *)sec,16);
	OLED_ShowString(120,6,(uint8_t *)wee,16);
	
//	HAL_Delay(50);
	
}


