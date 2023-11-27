#include "tim.h"
#include "gpio.h"
#include "getdata.h"
#include "stdio.h"
#include "oled.h"
uint16_t speed_left = 500;
uint16_t speed_right = 500;

void go_back()
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,speed_right);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,speed_left);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL0_PIN,GPIO_PIN_SET);  
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL1_PIN,GPIO_PIN_RESET);
//	
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL2_PIN,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL3_PIN,GPIO_PIN_SET);

}

void go_front()
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,speed_right);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,speed_left);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL1_PIN,GPIO_PIN_SET);  
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL0_PIN,GPIO_PIN_RESET);
//	
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL3_PIN,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL2_PIN,GPIO_PIN_SET);
}

void go_right()
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,speed_left);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL1_PIN,GPIO_PIN_RESET);  
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL0_PIN,GPIO_PIN_RESET);
//	
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL3_PIN,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL2_PIN,GPIO_PIN_SET);
}

void go_left()
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,speed_right);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL1_PIN,GPIO_PIN_SET);  
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL0_PIN,GPIO_PIN_RESET);
//	
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL3_PIN,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL2_PIN,GPIO_PIN_RESET);
}

void car_stop()
{
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL1_PIN,GPIO_PIN_RESET);  
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL0_PIN,GPIO_PIN_RESET);
//	
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL3_PIN,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(WHEEL0_3_GPIOx,WHEEL2_PIN,GPIO_PIN_RESET);
}

void follow_road(uint16_t *Data)
{
	while(1)
	{	
		if(HAL_GPIO_ReadPin(HAMPER2_GPIOx,HAMPER2_PIN) == RESET && HAL_GPIO_ReadPin(HAMPER3_GPIOx,HAMPER3_PIN) == SET)
		{
			go_right();
		}
		else if(HAL_GPIO_ReadPin(HAMPER3_GPIOx,HAMPER3_PIN) == RESET && HAL_GPIO_ReadPin(HAMPER2_GPIOx,HAMPER2_PIN) == SET)
		{
			go_left();
		}
		else
		{
			go_front();
		}
		
		if(*Data)
		{
			return;
		}
	}
}

void set_left_speed()
{
	if(__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_3))
	{
		speed_left>100?(speed_left -= 40):(speed_left = 500);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,speed_left);
	}
	else if(__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_4))
	{
		speed_left>100?(speed_left -= 40):(speed_left = 500);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,speed_left);
	}
}

void set_right_speed()
{
	if(__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_1))
	{
		speed_right>100?(speed_right -= 40):(speed_right = 500);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,speed_right);
	}
	else if(__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_2))
	{
		speed_right>100?(speed_right -= 40):(speed_right = 500);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,speed_right);
	}
}

void delay_us(uint32_t us) //����CPUѭ��ʵ�ֵķǾ�׼Ӧ�õ�΢����ʱ����
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us); //ʹ��HAL_RCC_GetHCLKFreq()������ȡ��Ƶֵ�����㷨�õ�1΢���ѭ������
    while (delay--); //ѭ��delay�Σ��ﵽ1΢����ʱ
}

double get_time_SR04(uint16_t *RxBuffer,uint8_t *flag_capture)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
	//���벶��ģʽ����Ϊ�����ش���
	__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
    //������ʱ��
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	double distance = 0;
	double high_time = 0;
	uint32_t cnt= 0xffffff;
	while(cnt--)
	{
		if(*flag_capture == 2)
		{
			high_time = RxBuffer[2]- RxBuffer[1];    //�ߵ�ƽʱ��
			distance = (high_time / 1000000.0) * 340.0 / 2.0 * 100.0;
			if(distance <= 0)
			{
				distance = 0;
			}
			printf("buf[2]:%d buf[1]:%d  %.2f cm\n",RxBuffer[2],RxBuffer[1],distance);
			*flag_capture = 0;
			return distance;
		}
	}
	*flag_capture = 0;
	return 0;
}

//DHT11���
void DHT11_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void DHT11_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin  = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void DHT11_Strat(void)
{
	DHT11_OUT();   //PG9����Ϊ���ģʽ
	DHT11_LOW;     //������������
	HAL_Delay(20); //�ӳٱ������18ms; 
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


void DHT11_test()
{
	DHT11_OUT();   //PG9����Ϊ���ģʽ
	DHT11_LOW;     //������������
	HAL_Delay(20); //�ӳٱ������18ms; 
	DHT11_HIGH;    //�����������ߵȴ�DHT11��Ӧ
	delay_us(30);
	DHT11_IN();
	while(1)
	{
		if(!DHT11_IO_IN)
		{
			PFout(9) ^= 1;
			return ;
		}
	}
}


