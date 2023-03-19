#include "dht11.h"

double temperature=0; 
uint32_t humydity=0;
char tempra[4],humydi[3];

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
    HAL_Delay(1000);                              
  
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
            printf("当前湿度：%d.%d%%  当前温度：%d.%d°C--",data[0],data[1],data[2],data[3]);
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
	Sprintf_temprature_humydity();
//	OLED_ShowString(0,2,(uint8_t *)"Temprature:",16);   //显示温度
    OLED_ShowCHinese(0,2,7);   //显示温度
	OLED_ShowCHinese(16,2,8);
	OLED_ShowCHinese(32,2,6);
	OLED_ShowString(48,2,(uint8_t *)tempra,16);
	OLED_ShowString(88,2,(uint8_t *)"C",16);
//	OLED_ShowString(0,4,(uint8_t *)"Humydity:",16);   //显示湿度
	OLED_ShowCHinese(0,4,9);   //显示湿度
	OLED_ShowCHinese(16,4,10);
	OLED_ShowCHinese(32,4,6);
	OLED_ShowString(48,4,(uint8_t *)humydi,16);
}
