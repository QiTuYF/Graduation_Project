#include "treatment_tim.h"

uint8_t times=0;

extern uint32_t alarm_clock[alarm_count_max][alarm_parameter_max];
extern uint32_t humiture_threshold_value[humiture_count_max][humiture_parameter_max];
extern uint32_t hour,minute,second;
extern double temperature; 
extern uint32_t humydity;
const uint8_t lamp_min=0,lamp_max=1;

unsigned char lamp[2]={6,20};

void treatment_tim_one(void)
{
	uint8_t i=0,flag_one=0;
	for(i=0; i<alarm_count_max; i++)
	{
		if(alarm_clock[i][alarm_parameter_switch] == 1)
		{
			if(alarm_clock[i][alarm_parameter_hour] == hour)
			{
				if(alarm_clock[i][alarm_parameter_minute] == minute)
				{
					if(alarm_clock[i][alarm_parameter_second] == second)
					{
												
							flag_one=1;						
							break;	
												
					}
				}
			}
		}
	}
	
	if( temperature > humiture_threshold_value[temprature_parameter][humiture_parameter_upper]
	||  temperature < humiture_threshold_value[temprature_parameter][humiture_parameter_lower]		   
	){
		if(humiture_threshold_value[temprature_parameter][humiture_parameter_switch]== 1 )
		{
			flag_one = 1;			
		}
		
	}
	if( humydity > humiture_threshold_value[humidity_parameter][humiture_parameter_upper]
	||  humydity < humiture_threshold_value[humidity_parameter][humiture_parameter_lower]		   
	){
		if(humiture_threshold_value[humidity_parameter][humiture_parameter_switch]== 1 )
		{
			flag_one =1;		
		}
	}
	
	
	if(flag_one == 1)
	{
		BUZZ_ON;
	}else{
		BUZZ_OFF;
	}	
}

void treatment_tim_two(void)
{
		times++;
		if(hour<=lamp[lamp_min] || hour>=lamp[lamp_max])
		{
			if(!Read_sound)
			{
				LED_ON;			
			}else if(Read_sound && times==80){
				LED_OFF;
				times=0;
			}
		}
}

