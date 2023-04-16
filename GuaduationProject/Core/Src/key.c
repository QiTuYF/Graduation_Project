#include "key.h"

extern uint32_t second;
//extern uint8_t interface_state;
//extern uint8_t key_state;


uint8_t key_state=1; //按键状态
uint8_t interface_state=1;  //页面状态
uint8_t interface_setalarmOrhumiture_state=0; //设置参数页面，为闹钟设置或温湿度阈值设置
uint8_t increase_state=0;
uint8_t decrease_state=0;
uint8_t up_down_state=0;
uint8_t left_right_state=0;
uint8_t save_flash_state=0,save_flash_times=0;

extern uint32_t alarm_clock[alarm_count_max][alarm_parameter_max];

void key_scan(void)
{
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
	if(0 == Read_alarmOrhumiture_set)  //Read_alarmOrhumiture_set为温湿度或闹钟设置页面切换按键状态
	{
		HAL_Delay(2);
		if(0 == Read_alarmOrhumiture_set)
		{
			while(0 == Read_alarmOrhumiture_set);
			OLED_Clear();
			if(interface_state == 3) //在设置页面下按键才有效
			{
				up_down_state=0;
				left_right_state=0;
				interface_setalarmOrhumiture_state++;
				if(interface_setalarmOrhumiture_state>=2)
				{
					interface_setalarmOrhumiture_state=0;
				}
			}
			
		}
	}
	if(0 == Read_increase)
	{
		HAL_Delay(2);
		if(0 == Read_increase)
		{
			while(0 == Read_increase);
			if(interface_state == 3) //在设置页面下按键才有效
			{
				increase_state=1;
			}
			
		}
	}
	if(0 == Read_decrease)
	{
		HAL_Delay(2);
		if(0 == Read_decrease)
		{
			while(0 == Read_decrease);
			if(interface_state == 3) //在设置页面下按键才有效
			{
				decrease_state=1;
			}
			
		}
	}
	if(0 == Set_up_down)
	{
		HAL_Delay(2);
		if(0 == Set_up_down)
		{
			while(0 == Set_up_down);
			if(interface_state == 3) //在设置页面下按键才有效
			{
				up_down_state++;
				if(interface_setalarmOrhumiture_state ==0) //对闹钟操作
				{
					if(up_down_state >= alarm_count_max)
					{
						up_down_state=0;
					}
				}else if(interface_setalarmOrhumiture_state ==1){  //对温湿度阈值操作
				
					if(up_down_state >= humiture_count_max)
					{
						up_down_state=0;
					}
				}
								
			}
			
		}
	}
	if(0 == Set_left_right)
	{
		HAL_Delay(2);
		if(0 == Set_left_right)
		{
			while(0 == Set_left_right);
			if(interface_state == 3) //在设置页面下按键才有效
			{
				left_right_state++;
				
				if(interface_setalarmOrhumiture_state ==0) //对闹钟操作
				{
					if(left_right_state >= alarm_parameter_max)
					{
						left_right_state=0;
					}
				}else if(interface_setalarmOrhumiture_state ==1){  //对温湿度阈值操作			
					if(left_right_state >= humiture_parameter_max)
					{
						left_right_state=0;
					}
				}												
			}			
		}
	}
	if(0 == Set_save_flash)
	{
		HAL_Delay(2);
		if(0 == Set_save_flash)
		{
			while(0 == Set_save_flash);
			save_flash_state=1;
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
//			DHT11();
			//在OLED上显示温度湿度
			Show_temprature_humydity();
		}
		else if(interface_state == 3)   //设置闹钟或者温湿度阈值数据
		{
			if(interface_setalarmOrhumiture_state == 0)
			{	
				if(save_flash_state == 1)
				{
					save_flash_state=0;
					save_flash_times++;
					OLED_ShowNum(104,0,(unsigned int)save_flash_times,3,16);
					STMFLASH_Write(FLASH_SAVE_ADDR,(uint16_t *)alarm_clock,sizeof(alarm_clock));//写
				}
				OLED_ShowNum(104,0,(unsigned int)save_flash_times,3,16);
				Set_alarm();//显示所有闹钟数据并且能够设置闹钟
			}
			else if(interface_setalarmOrhumiture_state == 1)
			{
				set_humiture();//显示温湿度阈值数据并且能够设置温湿度阈值
			}
		}
	}
}
