#include "gpio.h"
#include "delay.h"
#include "oled.h"
#include "getdata.h"

//DHT11���
void DHT11_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DHT11_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin  = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DHT11_Strat(void)
{
	DHT11_OUT();   //PG9����Ϊ���ģʽ
	DHT11_LOW;     //������������
	//HAL_Delay(20); //�ӳٱ������18ms; 
	delay_us(20000);
	DHT11_HIGH;    //�����������ߵȴ�DHT11��Ӧ
	delay_us(30);   
}

/**
  * @brief  DHT11������Ӧ�ź�
  * @param  ��
  * @retval ����ֵ0/1  0����Ӧ�ɹ� 1����Ӧʧ��
  */
uint8_t DHT11_Check(void)
{
	uint16_t retry = 0;
	DHT11_IN();
	//����whileѭ���ķ�ʽ�����Ӧ�ź�
	while(DHT11_IO_IN && retry <100) // DHT11������ 40us ~80us
	{
		retry++;
		delay_us(1);//1us
	}
	if(retry>=100) //�жϵ�DHT11�ӳٳ���80usʱreturn 1 �� ˵����Ӧʧ��
	{return  1;}
	else retry =  0;
		
	while(!DHT11_IO_IN && retry<100)// // DHT11����֮������� 40us ~80us
	{
		retry++;
		delay_us(1);//1us
	}
		
	if(retry>=100)
	{return 1;}
	return 0 ;
}

/**
  * @brief  DHT11��ȡһλ����
  * @param  ��
  * @retval ����ֵ0/1  1����ȡ�ɹ� 0����ȡʧ��
  */
uint8_t DHT11_Read_Bit(void)
{
	uint8_t retry = 0 ;
	while(DHT11_IO_IN && retry <100)//ͬ�ϲ���whileѭ���ķ�ʽȥ�ɼ�����
	{
		retry++;
		delay_us(1);
	}
	retry = 0 ;
	while(!DHT11_IO_IN && retry<100)
	{
		retry++;
		delay_us(1);
	}
 
	delay_us(40);              //�����źţ���ʱ40us 
	if(DHT11_IO_IN) return 1;  //�����źź����߻ᱻ���� �򷵻�1��ʾ��ȡ�ɹ�
	else 
	return 0 ;
}

/**
  * @brief  DHT11��ȡһ���ֽ�����
  * @param  ��
  * @retval ����ֵ��dat ���ɼ�����һ���ֽڵ����ݷ���
  */
uint8_t DHT11_Read_Byte(void)
{
	uint8_t i , dat ;
	dat = 0 ;
	for(i=0; i<8; i++)
	{
		dat <<= 1; //ͨ�����ƴ洢����
		dat |= DHT11_Read_Bit();
	}
	return dat ; 
}

/**
  * @brief  DHT11��ȡ����
  * @param  temp���¶�ֵ humi ��ʪ��ֵ
  * @retval ����ֵ0/1 0����ȡ���ݳɹ� 1����ȡ����ʧ��
  */
uint8_t DHT11_Read_Data(uint8_t* temp , uint8_t* humi)
{
	uint8_t buf[5];        //������λ����
    uint8_t i;    
	DHT11_Strat();         //��ʼ�ź�
	if(DHT11_Check() == 0) //��Ӧ�ź�
    {
		for(i=0; i<5; i++)
		{
			buf[i] = DHT11_Read_Byte();
		}
		if(buf[0]+buf[1]+buf[2]+buf[3] == buf[4]) //У������
		{
		    *humi = buf[0]; // ʪ��
			*temp = buf[2]; // �¶�
		}
	}else return 1;
	
   return 0 ;
}


