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
  * @brief  温湿度传感器主函数
  * @param  void
  * @retval None
  */
void DHT11(void)
{
    if(DHT11_READ_DATA() == 1)
    {
        printf("数据校验成功!\r\n");
    }
    else
    {
        printf("DHT11没有应答，请检查传感器!\r\n");
    }
//    HAL_Delay(1000);
	HAL_Delay(50);     	
  
}
 
/**
  * @brief  温湿度传感器启动信号发送
  * @param  void
  * @retval None
  */
void DHT11_START(void)
{
    DHT11_GPIO_MODE_SET(0);                         //  主机设置为输出模式
    
    DHT11_PIN_RESET;                                //  主机拉低电平
    
    HAL_Delay(20);                                  //  主机等待 18 < ms > 30
    
    DHT11_GPIO_MODE_SET(1);                         //  主机设置为输入模式，等待DHT11答应
}                                                   //  因为设置了上拉输入，GPIO -> 1
 
/**
  * @brief  读取一位数据 1bit
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_READ_BIT(void)
{
    while(!DHT11_READ_IO);                          //  过度数据的低电平 
    
    Coarse_delay_us(40);
 
    if(DHT11_READ_IO)                               //  此时如果还为高电平则数据为 1
    {
        while(DHT11_READ_IO);                       //  过度数据的高电平
        return 1;
    }   
    else                                            //  若此时为低则为 0
    {
        return 0;
    }
}
 
/**
  * @brief  读取一个字节数据 1byte / 8bit
  * @param  void
  * @retval temp
  */
unsigned char DHT11_READ_BYTE(void)
{
    uint8_t i,temp = 0;                             //  暂时存储数据
    
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
  * @brief  读取温湿度传感器数据 5byte / 40bit
  * @param  void
  * @retval 0/1/2
  */
unsigned char DHT11_READ_DATA(void)
{
    uint8_t i;
    uint8_t data[5] = {0};
    
    DHT11_START();                                  //  主机发送启动信号
    
    if(DHT11_Check())                               //  如果DHT11应答     
    {  
        while(!DHT11_READ_IO);                      //  过度DHT11答复信号的低电平
        while(DHT11_READ_IO);                       //  过度DHT11答复信号的高电平
        
        for(i=0; i<5; i++)
        {                        
            data[i] = DHT11_READ_BYTE();            //  读取 5byte
        }
        
        if(data[0] + data[1] + data[2] + data[3] == data[4])
        {
			temperature = data[2]+data[3]*0.1;
			humydity    = data[0];
            printf("当前湿度：%d.%d%%  当前温度：%d.%d°C\r\n",data[0],data[1],data[2],data[3]);
            return 1;                               //  数据校验通过
        }
        else
        {
            return 0;                               //  数据校验失败
        }
    }
    else                                            //  如果DHT11不应答
    {
        return 2;
    }
}
 
/**
  * @brief  检测温湿度传感器是否存在(检测DHT11的应答信号)
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_Check(void)
{
 
    Coarse_delay_us(40);
    if(DHT11_READ_IO == 0)                          //  检测到DHT11应答
    {
        return 1;
    }
    else                                            //  检测到DHT11不应答
    {
        return 0;
    }
}
 
/**
  * @brief  设置引脚模式
  * @param  mode: 0->out, 1->in
  * @retval None
  */
static void DHT11_GPIO_MODE_SET(uint8_t mode)
{
    if(mode)
    {
        /*  输入  */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = GPIO_PIN_9;                   //  9号引脚
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;             //  输入模式
        GPIO_InitStruct.Pull = GPIO_PULLUP;                 //  上拉输入
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else 
    {
        /*  输出  */
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin = GPIO_PIN_9;                //  9号引脚
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;      //  Push Pull 推挽输出模式
        GPIO_InitStructure.Pull = GPIO_PULLUP;              //  上拉输出
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    //  高速
        HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
    }
}
 
/**
  * @brief  程序延时 us , 必须在 72M 主频下使用
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
  * @brief  将温湿度转换为字符串
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
  * @brief  在OLED上显示温度湿度
  * @param  void
  * @retval 0/1
  */
void Show_temprature_humydity(void)
{
	//串口打印DHT11是否正常
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
//	OLED_ShowString(0,2,(uint8_t *)"Temprature:",16);   //显示温度
	OLED_ShowCHinese(0,2,13);  //当
	OLED_ShowCHinese(16,2,14);  //前
	OLED_ShowCHinese(32,2,7);  //温
	OLED_ShowCHinese(48,2,10);  //度
	OLED_ShowCHinese(64,2,6);  //：
	OLED_ShowString(80,2,(uint8_t *)tempra,16);
	OLED_ShowString(120,2,(uint8_t *)"C",16);
    
//	OLED_ShowString(0,4,(uint8_t *)"Humydity:",16);   //显示湿度
	OLED_ShowCHinese(0,5,13);  //当
	OLED_ShowCHinese(16,5,14);  //前
	OLED_ShowCHinese(32,5,9);  //湿
	OLED_ShowCHinese(48,5,10);  //度
	OLED_ShowCHinese(64,5,6);  //：
	OLED_ShowString(80,5,(uint8_t *)humydi,16);
	
	
}

void set_humiture(void)
{
	uint8_t i=0;

	OLED_ShowNum(0,0,(unsigned int)up_down_state+1,1,16);  //当前设置的坐标x轴
	OLED_ShowNum(16,0,(unsigned int)left_right_state+1,1,16);  //当前设置的坐标y轴
	OLED_ShowCHinese(32,0,13); //当
	OLED_ShowCHinese(48,0,14); //前
	OLED_ShowCHinese(64,0,28); //阈
	OLED_ShowCHinese(80,0,29); //值
	
	for(i=0; i<humiture_count_max; i++)
	{
		OLED_ShowNum(0,oled__humiture_line,(unsigned int)i+1,1,16); //序号
//		OLED_ShowCHinese(48,oled__humiture_line,28); //阈
//		OLED_ShowCHinese(64,oled__humiture_line,29); //值
		if(i == 0) //温度
		{
			OLED_ShowCHinese(16,oled__humiture_line,7); //温
			OLED_ShowCHinese(32,oled__humiture_line,8); //度
			OLED_ShowNum(48,oled__humiture_line,humiture_threshold_value[i][0],2,16); //温度下限
//			OLED_ShowString(56,oled__humiture_line,(uint8_t *)"C",16);
			OLED_ShowString(64,oled__humiture_line,(uint8_t *)"-",16);
			OLED_ShowNum(72,oled__humiture_line,humiture_threshold_value[i][1],2,16); //温度上限	
			OLED_ShowString(88,oled__humiture_line,(uint8_t *)"C",16);
		}else if(i==1){ //湿度
			OLED_ShowCHinese(16,oled__humiture_line,9); //湿
			OLED_ShowCHinese(32,oled__humiture_line,10); //度
			OLED_ShowNum(48,oled__humiture_line,humiture_threshold_value[i][0],2,16); //湿度下限
//			OLED_ShowString(56,oled__humiture_line,(uint8_t *)"%",16);
			OLED_ShowString(64,oled__humiture_line,(uint8_t *)"-",16);
			OLED_ShowNum(72,oled__humiture_line,humiture_threshold_value[i][1],2,16); //湿度上限				
			OLED_ShowString(88,oled__humiture_line,(uint8_t *)"%",16);
		}
		if(humiture_threshold_value[i][humiture_parameter_switch] == 0)  //开启或关闭
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
		if(up_down_state == temprature_parameter) //当鼠标指针指向温度阈值设置时
		{
			humiture_threshold_value[up_down_state][left_right_state]++;
			if(left_right_state == humiture_parameter_lower)  //温度下限设置
			{
				if(humiture_threshold_value[up_down_state][left_right_state]+2 >= humiture_threshold_value[temprature_parameter][humiture_parameter_upper])
				{
					//当温度下限大于当前温度上限，重置温度下限为最小值
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_min;
				}
			}else if(left_right_state == humiture_parameter_upper){  //温度上限设置	
				if(humiture_threshold_value[up_down_state][left_right_state] > temprature_threshold_max)
				{
					//当温度上限大于系统温度上限(50°C)，重置温度上限为系统最大值
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_max;
				}
			}else if(left_right_state == humiture_parameter_switch)  //开关状态设置
			{
				if(humiture_threshold_value[up_down_state][left_right_state] >= 2)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 0;
				}
			}
		}else if(up_down_state == humidity_parameter){ //当鼠标指针指向湿度阈值设置时
			humiture_threshold_value[up_down_state][left_right_state]+=2;
			if(left_right_state == humiture_parameter_lower)  //湿度下限设置
			{
				if(humiture_threshold_value[up_down_state][left_right_state]+4 >= humiture_threshold_value[humidity_parameter][humiture_parameter_upper])
				{
					//当湿度下限大于当前湿度上限，重置湿度下限为最小值
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_min;
				}
			}else if(left_right_state == humiture_parameter_upper){  //湿度上限设置	
				if(humiture_threshold_value[up_down_state][left_right_state] > humidity_threshold_max)
				{
					//当湿度上限大于系统湿度上限(90%)，重置湿度上限为系统最大值
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_max;
				}
			}else if(left_right_state == humiture_parameter_switch)  //开关状态设置
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
		if(up_down_state == temprature_parameter) //当鼠标指针指向温度阈值设置时
		{		
			if(left_right_state == humiture_parameter_lower) //温度下限设置
			{
				if(humiture_threshold_value[up_down_state][left_right_state] == temprature_threshold_min) //当前温度下限等于系统温度下限
				{
					humiture_threshold_value[up_down_state][left_right_state] = humiture_threshold_value[temprature_parameter][humiture_parameter_upper]-2;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}else if(left_right_state == humiture_parameter_upper){ //温度上限设置
				if(humiture_threshold_value[up_down_state][left_right_state] == humiture_threshold_value[temprature_parameter][humiture_parameter_lower]+2) //当前温度上限等于当前温度下限+2
				{
					humiture_threshold_value[up_down_state][left_right_state] = temprature_threshold_max;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}else if(left_right_state == humiture_parameter_switch){ //温度开关设置
				if(humiture_threshold_value[up_down_state][left_right_state] == 0)
				{
					humiture_threshold_value[up_down_state][left_right_state] = 1;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]--;
				}
			}
		}else if(up_down_state == humidity_parameter){ //当鼠标指针指向湿度阈值设置时				
			if(left_right_state == humiture_parameter_lower) //湿度下限设置
			{
				if(humiture_threshold_value[up_down_state][left_right_state] == humidity_threshold_min) //当前湿度下限等于系统湿度下限
				{
					humiture_threshold_value[up_down_state][left_right_state] = humiture_threshold_value[humidity_parameter][humiture_parameter_upper]-4;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]-=2;
				}
			}else if(left_right_state == humiture_parameter_upper){ //湿度上限设置
				if(humiture_threshold_value[up_down_state][left_right_state] == humiture_threshold_value[humidity_parameter][humiture_parameter_lower]+4) //当前湿度上限等于当前湿度下限+4
				{
					humiture_threshold_value[up_down_state][left_right_state] = humidity_threshold_max;
				}else{
					humiture_threshold_value[up_down_state][left_right_state]-=2;
				}
			}else if(left_right_state == humiture_parameter_switch){ //湿度开关设置
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
