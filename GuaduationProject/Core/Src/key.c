#include "key.h"

extern uint32_t second;
//extern uint8_t interface_state;
//extern uint8_t key_state;

uint8_t key_state=1; //按键状态
uint8_t interface_state=1;  //页面状态

void key_scan(void)
{
//	BUZZ_ON;
//	HAL_Delay(50);
//	BUZZ_OFF;
//	HAL_Delay(50);
	if(0 == Read_interface)   //Read_interface为读界面切换按键状态
	{
		HAL_Delay(2);
		if(0 == Read_interface)
		{
			while(0 == Read_interface);
			OLED_Clear();
			key_state = 1;
			interface_state++;
			if(interface_state > interface_state_max)  interface_state=1;
			//
			//
		}
	}
	if(0 == Read_alarm_set)
	{
		HAL_Delay(20);
		if(0 == Read_alarm_set)
		{
			while(0 == Read_alarm_set);
			//
			//
		}
	}
	if(0 == Read_increase)
	{
		HAL_Delay(20);
		if(0 == Read_increase)
		{
			while(0 == Read_increase);
			//
			//
		}
	}
	if(0 == Read_decrease)
	{
		HAL_Delay(20);
		if(0 == Read_decrease)
		{
			while(0 == Read_decrease);
			//
			//
		}
	}
	
}


void key_state_response(void)
{
	if(key_state == 1)  
	{
		if(interface_state == 1)   //在OLED上显示时间
		{
			
			
			if(second == 0)   //定时清屏，以免屏幕残留字符
			{
				OLED_Clear();
				Show_time();
			} 
			Show_time();
		}
		else if(interface_state == 2)   //在OLED上显示温度湿度
		{
			//串口打印DHT11是否正常
			DHT11();
			//在OLED上显示温度湿度
			Show_temprature_humydity();
		}
		else if(interface_state == 3)   //设置闹钟数据
		{
			Set_alarm();//显示所有闹钟数据
		}
	}
}
