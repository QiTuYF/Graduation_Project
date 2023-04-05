#include "treatment_tim.h"
extern uint32_t alarm_clock[alarm_count_max][alarm_parameter_max];
extern uint32_t humiture_threshold_value[humiture_count_max][humiture_parameter_max];
extern uint32_t hour,minute,second;
extern double temperature; 
extern uint32_t humydity;
void treatment_tim_one(void)
{
	uint8_t i=0,alarm_flag=1;
	for(i=0; i<=alarm_count_max; i++)
	{
		if(alarm_clock[i][alarm_parameter_hour] == hour)
		{
			if(alarm_clock[i][alarm_parameter_minute] == minute)
			{
				if(alarm_clock[i][alarm_parameter_second] == second)
				{
					if(alarm_clock[i][alarm_parameter_switch] == 1)
					{
						BUZZ_ON;
						alarm_flag=0;					
					}
					
				}
			}
		}else{
			if(alarm_flag == 1)
			BUZZ_OFF;
		}
	}
	
}

void treatment_tim_two(void)
{
	uint8_t alarm_flag=1;
	if( temperature > humiture_threshold_value[temprature_parameter][humiture_parameter_upper]
	||  temperature < humiture_threshold_value[temprature_parameter][humiture_parameter_lower]		   
	){
		if(humiture_threshold_value[temprature_parameter][humiture_parameter_switch]== 1 )
		{
			BUZZ_ON;
			alarm_flag=0;
		}
		
	}else if( humydity > humiture_threshold_value[humidity_parameter][humiture_parameter_upper]
	      ||  humydity < humiture_threshold_value[humidity_parameter][humiture_parameter_lower]		   
	){
		if(humiture_threshold_value[humidity_parameter][humiture_parameter_switch]== 1 )
		{
			BUZZ_ON;
			alarm_flag=0;
		}
	}else{
		if(alarm_flag == 1)
		BUZZ_OFF;
	}
}

