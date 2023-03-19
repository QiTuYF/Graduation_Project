#include "dht11.h"

double temperature=0; 
uint32_t humydity=0;
char tempra[4],humydi[3];

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
    HAL_Delay(1000);                              
  
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
            printf("��ǰʪ�ȣ�%d.%d%%  ��ǰ�¶ȣ�%d.%d��C--",data[0],data[1],data[2],data[3]);
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
	Sprintf_temprature_humydity();
//	OLED_ShowString(0,2,(uint8_t *)"Temprature:",16);   //��ʾ�¶�
    OLED_ShowCHinese(0,2,7);   //��ʾ�¶�
	OLED_ShowCHinese(16,2,8);
	OLED_ShowCHinese(32,2,6);
	OLED_ShowString(48,2,(uint8_t *)tempra,16);
	OLED_ShowString(88,2,(uint8_t *)"C",16);
//	OLED_ShowString(0,4,(uint8_t *)"Humydity:",16);   //��ʾʪ��
	OLED_ShowCHinese(0,4,9);   //��ʾʪ��
	OLED_ShowCHinese(16,4,10);
	OLED_ShowCHinese(32,4,6);
	OLED_ShowString(48,4,(uint8_t *)humydi,16);
}
