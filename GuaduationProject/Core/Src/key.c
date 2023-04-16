#include "key.h"

extern uint32_t second;
//extern uint8_t interface_state;
//extern uint8_t key_state;


uint8_t key_state=1; //����״̬
uint8_t interface_state=1;  //ҳ��״̬
uint8_t interface_setalarmOrhumiture_state=0; //���ò���ҳ�棬Ϊ�������û���ʪ����ֵ����
uint8_t increase_state=0;
uint8_t decrease_state=0;
uint8_t up_down_state=0;
uint8_t left_right_state=0;
uint8_t save_flash_state=0,save_flash_times=0;

extern uint32_t alarm_clock[alarm_count_max][alarm_parameter_max];

void key_scan(void)
{
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
	if(0 == Read_alarmOrhumiture_set)  //Read_alarmOrhumiture_setΪ��ʪ�Ȼ���������ҳ���л�����״̬
	{
		HAL_Delay(2);
		if(0 == Read_alarmOrhumiture_set)
		{
			while(0 == Read_alarmOrhumiture_set);
			OLED_Clear();
			if(interface_state == 3) //������ҳ���°�������Ч
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
				if(interface_setalarmOrhumiture_state ==0) //�����Ӳ���
				{
					if(up_down_state >= alarm_count_max)
					{
						up_down_state=0;
					}
				}else if(interface_setalarmOrhumiture_state ==1){  //����ʪ����ֵ����
				
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
			if(interface_state == 3) //������ҳ���°�������Ч
			{
				left_right_state++;
				
				if(interface_setalarmOrhumiture_state ==0) //�����Ӳ���
				{
					if(left_right_state >= alarm_parameter_max)
					{
						left_right_state=0;
					}
				}else if(interface_setalarmOrhumiture_state ==1){  //����ʪ����ֵ����			
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
//			DHT11();
			//��OLED����ʾ�¶�ʪ��
			Show_temprature_humydity();
		}
		else if(interface_state == 3)   //�������ӻ�����ʪ����ֵ����
		{
			if(interface_setalarmOrhumiture_state == 0)
			{	
				if(save_flash_state == 1)
				{
					save_flash_state=0;
					save_flash_times++;
					OLED_ShowNum(104,0,(unsigned int)save_flash_times,3,16);
					STMFLASH_Write(FLASH_SAVE_ADDR,(uint16_t *)alarm_clock,sizeof(alarm_clock));//д
				}
				OLED_ShowNum(104,0,(unsigned int)save_flash_times,3,16);
				Set_alarm();//��ʾ�����������ݲ����ܹ���������
			}
			else if(interface_setalarmOrhumiture_state == 1)
			{
				set_humiture();//��ʾ��ʪ����ֵ���ݲ����ܹ�������ʪ����ֵ
			}
		}
	}
}
