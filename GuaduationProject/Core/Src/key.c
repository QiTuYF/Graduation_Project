#include "key.h"

extern uint32_t second;
//extern uint8_t interface_state;
//extern uint8_t key_state;


uint8_t key_state=1; //����״̬
uint8_t interface_state=1;  //ҳ��״̬
uint8_t increase_state=0;
uint8_t decrease_state=0;
uint8_t up_down_state=0;
uint8_t left_right_state=0;

void key_scan(void)
{
//	BUZZ_ON;
//	HAL_Delay(50);
//	BUZZ_OFF;
//	HAL_Delay(50);
	if(0 == Read_interface)   //Read_interfaceΪ�������л�����״̬
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
		HAL_Delay(2);
		if(0 == Read_alarm_set)
		{
			while(0 == Read_alarm_set);
			//
			//
		}
	}
	if(0 == Read_increase)
	{
		HAL_Delay(2);
		if(0 == Read_increase)
		{
			while(0 == Read_increase);
			if(interface_state == 3) //������ҳ���°�������Ч
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
			if(interface_state == 3) //������ҳ���°�������Ч
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
			if(interface_state == 3) //������ҳ���°�������Ч
			{
				up_down_state++;
				if(up_down_state >= alarm_count_max)
				{
					up_down_state=0;
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
			if(interface_state == 3) //������ҳ���°�������Ч
			{
				left_right_state++;
				if(left_right_state >= alarm_parameter_max)
				{
					left_right_state=0;
				}
			}			
		}
	}
	
}


void key_state_response(void)
{
	if(key_state == 1)  
	{
		if(interface_state == 1)   //��OLED����ʾʱ��
		{
			
			
			if(second == 0)   //��ʱ������������Ļ�����ַ�
			{
				OLED_Clear();
				Show_time();
			} 
			Show_time();
		}
		else if(interface_state == 2)   //��OLED����ʾ�¶�ʪ��
		{
			//���ڴ�ӡDHT11�Ƿ�����
			DHT11();
			//��OLED����ʾ�¶�ʪ��
			Show_temprature_humydity();
		}
		else if(interface_state == 3)   //������������
		{
			Set_alarm();//��ʾ������������
		}
	}
}
