#include "treatment_tim.h"
extern uint32_t alarm_clock[3][3];
extern uint32_t hour,minute,second;
void treatment_tim_one(void)
{
	uint8_t i=0,alarm_flag=1;
	for(i=0; i<=4; i++)
	{
		if(alarm_clock[i][0] == hour)
		{
			if(alarm_clock[i][1] == minute)
			{
				if(alarm_clock[i][2] == second)
				{
					BUZZ_ON;
					alarm_flag=0;
				}
			}
		}else{
			if(alarm_flag == 1)
			BUZZ_OFF;
		}
	}
	
}

