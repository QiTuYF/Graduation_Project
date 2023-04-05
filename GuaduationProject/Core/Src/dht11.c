#include "dht11.h"

double temperature=0,last_temperature=0; 
uint32_t humydity=0,last_humydity=0;
char tempra[4],humydi[3];

extern uint8_t increase_state;
extern uint8_t decrease_state;
extern uint8_t up_down_state;
extern uint8_t left_right_state; 


uint32_t humiture_threshold_value[humiture_count_max][humiture_parameter_max]=
{
	{0,50,0},
	{20,90,0},
};

extern UART_HandleTypeDef huart1;
/**
  * @brief  ��ʪ�ȴ�����������
  * @param  void
  * @retval None
  */
void DHT11(void)
{
    if(DHT11_READ_DATA() == 1)
    {
        printf("����У��ɹ�!\r\n");
    }
    else
    {
        printf("DHT11û��Ӧ�����鴫����!\r\n");
    }
//    HAL_Delay(1000);
	HAL_Delay(50);     	
  
}
 
/**
  * @brief  ��ʪ�ȴ����������źŷ���
  * @param  void
  * @retval None
  */
void DHT11_START(void)
{
    DHT11_GPIO_MODE_SET(0);                         //  ��������Ϊ���ģʽ
    
    DHT11_PIN_RESET;                                //  �������͵�ƽ
    
    HAL_Delay(20);                                  //  �����ȴ� 18 < ms > 30
    
    DHT11_GPIO_MODE_SET(1);                         //  ��������Ϊ����ģʽ���ȴ�DHT11��Ӧ
}                                                   //  ��Ϊ�������������룬GPIO -> 1
 
/**
  * @brief  ��ȡһλ���� 1bit
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_READ_BIT(void)
{
    while(!DHT11_READ_IO);                          //  �������ݵĵ͵�ƽ 
    
    Coarse_delay_us(40);
 
    if(DHT11_READ_IO)                               //  ��ʱ�����Ϊ�ߵ�ƽ������Ϊ 1
    {
        while(DHT11_READ_IO);                       //  �������ݵĸߵ�ƽ
        return 1;
    }   
    else                                            //  ����ʱΪ����Ϊ 0
    {
        return 0;
    }
}
 
/**
  * @brief  ��ȡһ���ֽ����� 1byte / 8bit
  * @param  void
  * @retval temp
  */
unsigned char DHT11_READ_BYTE(void)
{
    uint8_t i,temp = 0;                             //  ��ʱ�洢����
    
    for(i=0; i<8 ;i++)
    {
        temp <<= 1;                                 
        if(DHT11_READ_BIT())                        //  1byte -> 8bit
        {
            temp |= 1;                              //  0000 0001
        }
    }
    return temp;
}
 
/**
  * @brief  ��ȡ��ʪ�ȴ��������� 5byte / 40bit
  * @param  void
  * @retval 0/1/2
  */
unsigned char DHT11_READ_DATA(void)
{
    uint8_t i;
    uint8_t data[5] = {0};
    
    DHT11_START();                                  //  �������������ź�
    
    if(DHT11_Check())                               //  ���DHT11Ӧ��     
    {  
        while(!DHT11_READ_IO);                      //  ����DHT11���źŵĵ͵�ƽ
        while(DHT11_READ_IO);                       //  ����DHT11���źŵĸߵ�ƽ
        
        for(i=0; i<5; i++)
        {                        
            data[i] = DHT11_READ_BYTE();            //  ��ȡ 5byte
        }
        
        if(data[0] + data[1] + data[2] + data[3] == data[4])
        {
			temperature = data[2]+data[3]*0.1;
			humydity    = data[0];
            printf("��ǰʪ�ȣ�%d.%d%%  ��ǰ�¶ȣ�%d.%d��C\r\n",data[0],data[1],data[2],data[3]);
            return 1;                               //  ����У��ͨ��
        }
        else
        {
            return 0;                               //  ����У��ʧ��
        }
    }
    else                                            //  ���DHT11��Ӧ��
    {
        return 2;
    }
}
 
/**
  * @brief  �����ʪ�ȴ������Ƿ����(���DHT11��Ӧ���ź�)
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_Check(void)
{
 
    Coarse_delay_us(40);
    if(DHT11_READ_IO == 0)                          //  ��⵽DHT11Ӧ��
    {
        return 1;
    }
    else                                            //  ��⵽DHT11��Ӧ��
    {
        return 0;
    }
}
 
/**
  * @brief  ��������ģʽ
  * @param  mode: 0->out, 1->in
  * @retval None
  */
static void DHT11_GPIO_MODE_SET(uint8_t mode)
{
    if(mode)
    {
        /*  ����  */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = GPIO_PIN_9;                   //  9������
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;             //  ����ģʽ
        GPIO_InitStruct.Pull = GPIO_PULLUP;                 //  ��������
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else 
    {
        /*  ���  */
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin = GPIO_PIN_9;                //  9������
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;      //  Push Pull �������ģʽ
        GPIO_InitStructure.Pull = GPIO_PULLUP;              //  �������
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    //  ����
        HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
    }
}
 
/**
  * @brief  ������ʱ us , ������ 72M ��Ƶ��ʹ��
  * @param  us: <= 4294967295
  * @retval None
  */
void Coarse_delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
} 


/**
  * @brief  ����ʪ��ת��Ϊ�ַ���
  * @param  void
  * @retval 0/1
  */
void Sprintf_temprature_humydity(void)
{
	sprintf(tempra,"%.1f",temperature);
//	printf("%s\r\n",tempra);
	sprintf(humydi,"%d",humydity);
	sprintf(humydi,"%s%%",humydi);
//	printf("%s\r\n",humydi);	
}  


/**
  * @brief  ��OLED����ʾ�¶�ʪ��
  * @param  void
  * @retval 0/1
  */
void Show_temprature_humydity(void)
{
	//���ڴ�ӡDHT11�Ƿ�����
//	DHT11();
	if( last_temperature-temperature >= 0.1 
	 || temperature-last_temperature>=0.1
	 || last_humydity-humydity>1
	 || humydity-last_humydity>1 )
	{
			OLED_Clear();
	}
	last_temperature = temperature;
  	last_humydity = humydity;
	Sprintf_temprature_humydity();
//	OLED_ShowString(0,2,(uint8_t *)"Temprature:",16);   //��ʾ�¶�
	OLED_ShowCHinese(0,2,13);  //��
	OLED_ShowCHinese(16,2,14);  //ǰ
	OLED_ShowCHinese(32,2,7);  //��
	OLED_ShowCHinese(48,2,10);  //��
	OLED_ShowCHinese(64,2,6);  //��
	OLED_ShowString(80,2,(uint8_t *)tempra,16);
	OLED_ShowString(120,2,(uint8_t *)"C",16);
    
//	OLED_ShowString(0,4,(uint8_t *)"Humydity:",16);   //��ʾʪ��
	OLED_ShowCHinese(0,5,13);  //��
	OLED_ShowCHinese(16,5,14);  //ǰ
	OLED_ShowCHinese(32,5,9);  //ʪ
	OLED_ShowCHinese(48,5,10);  //��
	OLED_ShowCHinese(64,5,6);  //��
	OLED_ShowString(80,5,(uint8_t *)humydi,16);
	
	
}

void set_humiture(void)
{
	uint8_t i=0;

	OLED_ShowNum(0,0,(unsigned int)up_down_state+1,1,16);  //��ǰ���õ�����x��
	OLED_ShowNum(16,0,(unsigned int)left_right_state+1,1,16);  //��ǰ���õ�����y��
	OLED_ShowCHinese(32,0,13); //��
	OLED_ShowCHinese(48,0,14); //ǰ
	OLED_ShowCHinese(64,0,28); //��
	OLED_ShowCHinese(80,0,29); //ֵ
	
	for(i=0; i<humiture_count_max; i++)
	{
		OLED_ShowNum(0,oled__humiture_line,(unsigned int)i+1,1,16); //���
//		OLED_ShowCHinese(48,oled__humiture_line,28); //��
//		OLED_ShowCHinese(64,oled__humiture_line,29); //ֵ
		if(i == 0) //�¶�
		{
			OLED_ShowCHinese(16,oled__humiture_line,7); //��
			OLED_ShowCHinese(32,oled__humiture_line,8); //��
			OLED_ShowNum(48,oled__humiture_line,humiture_threshold_value[i][0],2,16); //�¶�����
//			OLED_ShowString(56,oled__humiture_line,(uint8_t *)"C",16);
			OLED_ShowString(64,oled__humiture_line,(uint8_t *)"-",16);
			OLED_ShowNum(72,oled__humiture_line,humiture_threshold_value[i][1],2,16); //�¶�����	
			OLED_ShowString(88,oled__humiture_line,(uint8_t *)"C",16);
		}else if(i==1){ //ʪ��
			OLED_ShowCHinese(16,oled__humiture_line,9); //ʪ
			OLED_ShowCHinese(32,oled__humiture_line,10); //��
			OLED_ShowNum(48,oled__humiture_line,humiture_threshold_value[i][0],2,16); //ʪ������
//			OLED_ShowString(56,oled__humiture_line,(uint8_t *)"%",16);
			OLED_ShowString(64,oled__humiture_line,(uint8_t *)"-",16);
			OLED_ShowNum(72,oled__humiture_line,humiture_threshold_value[i][1],2,16); //ʪ������				
			OLED_ShowString(88,oled__humiture_line,(uint8_t *)"%",16);
		}
		if(humiture_threshold_value[i][humiture_parameter_switch] == 0)  //������ر�
		{
			OLED_ShowCHinese(96,oled__humiture_line,26);
			OLED_ShowCHinese(112,oled__humiture_line,27);
		}else if(humiture_threshold_value[i][humiture_parameter_switch] == 1){
			OLED_ShowCHinese(96,oled__humiture_line,24);
			OLED_ShowCHinese(112,oled__humiture_line,25);
		}
	}
	set_humiture_threshold_value();
}

void set_humiture_threshold_value(void)
{
	if(increase_state == 1)
	{
		if(up_down_state == temprature_parameter) //�����ָ��ָ���¶���ֵ����ʱ
		{
			humiture_threshold_value[up_down_state][left_right_state]++;
			if(left_right_state == humiture_parameter_lower)  //�¶���������
			{
				if(humiture_threshold_value[up_down_state][left_right_state]+2 >= humiture_threshold_value[temprature_parameter][humiture_parameter_upper])
				{
					//���¶����޴��ڵ�ǰ�¶����ޣ������¶�����Ϊ��Сֵ
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_min;
				}
			}else if(left_right_state == humiture_parameter_upper){  //�¶���������	
				if(humiture_threshold_value[up_down_state][left_right_state] > temprature_threshold_max)
				{
					//���¶����޴���ϵͳ�¶�����(50��C)�������¶�����Ϊϵͳ���ֵ
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_max;
				}
			}else if(left_right_state == humiture_parameter_switch)  //����״̬����
			{
				if(humiture_threshold_value[up_down_state][left_right_state] >= 2)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 0;
				}
			}
		}else if(up_down_state == humidity_parameter){ //�����ָ��ָ��ʪ����ֵ����ʱ
			humiture_threshold_value[up_down_state][left_right_state]+=2;
			if(left_right_state == humiture_parameter_lower)  //ʪ����������
			{
				if(humiture_threshold_value[up_down_state][left_right_state]+4 >= humiture_threshold_value[humidity_parameter][humiture_parameter_upper])
				{
					//��ʪ�����޴��ڵ�ǰʪ�����ޣ�����ʪ������Ϊ��Сֵ
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_min;
				}
			}else if(left_right_state == humiture_parameter_upper){  //ʪ����������	
				if(humiture_threshold_value[up_down_state][left_right_state] > humidity_threshold_max)
				{
					//��ʪ�����޴���ϵͳʪ������(90%)������ʪ������Ϊϵͳ���ֵ
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_max;
				}
			}else if(left_right_state == humiture_parameter_switch)  //����״̬����
			{
				humiture_threshold_value[up_down_state][left_right_state]--;
				if(humiture_threshold_value[up_down_state][left_right_state] >= 2)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 0;
				}
			}
		}	
		increase_state=0;
	}
	
	if(decrease_state == 1)
	{
		if(up_down_state == temprature_parameter) //�����ָ��ָ���¶���ֵ����ʱ
		{		
			if(left_right_state == humiture_parameter_lower) //�¶���������
			{
				if(humiture_threshold_value[up_down_state][left_right_state] == temprature_threshold_min) //��ǰ�¶����޵���ϵͳ�¶�����
				{
					humiture_threshold_value[up_down_state][left_right_state] = humiture_threshold_value[temprature_parameter][humiture_parameter_upper]-2;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}else if(left_right_state == humiture_parameter_upper){ //�¶���������
				if(humiture_threshold_value[up_down_state][left_right_state] == humiture_threshold_value[temprature_parameter][humiture_parameter_lower]+2) //��ǰ�¶����޵��ڵ�ǰ�¶�����+2
				{
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_max;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}else if(left_right_state == humiture_parameter_switch){ //�¶ȿ�������
				if(humiture_threshold_value[up_down_state][left_right_state] == 0)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 1;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}
		}else if(up_down_state == humidity_parameter){ //�����ָ��ָ��ʪ����ֵ����ʱ				
			if(left_right_state == humiture_parameter_lower) //ʪ����������
			{
				if(humiture_threshold_value[up_down_state][left_right_state] == humidity_threshold_min) //��ǰʪ�����޵���ϵͳʪ������
				{
					humiture_threshold_value[up_down_state][left_right_state] = humiture_threshold_value[humidity_parameter][humiture_parameter_upper]-4;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]-=2;
				}
			}else if(left_right_state == humiture_parameter_upper){ //ʪ����������
				if(humiture_threshold_value[up_down_state][left_right_state] == humiture_threshold_value[humidity_parameter][humiture_parameter_lower]+4) //��ǰʪ�����޵��ڵ�ǰʪ������+4
				{
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_max;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]-=2;
				}
			}else if(left_right_state == humiture_parameter_switch){ //ʪ�ȿ�������
				if(humiture_threshold_value[up_down_state][left_right_state] == 0)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 1;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}		
		}
		decrease_state=0;
	}
}
