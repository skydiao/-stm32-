#include "main.h"
#include "delay.h"
//�ڴ˺����м����ʼ��sysytick��ʱ������
//��������ԭ�����̽����޸�
//void delay_us(uint32_t us) {
//    TIM1->CR1 &= ~TIM_CR1_CEN; // �رն�ʱ��
//    TIM1->PSC = 84 - 1; // ����Ԥ��ƵΪ84
//    TIM1->ARR = us; // �����Զ���װ�ؼĴ���Ϊ�������ʱ
//    TIM1->EGR |= TIM_EGR_UG; // ���������¼��Ը���Ԥ��Ƶ���Զ���װ�ؼĴ���
//    TIM1->SR &= ~TIM_SR_UIF; // ��������жϱ�־
//    TIM1->CR1 |= TIM_CR1_CEN; // ���ö�ʱ��

//    while (!(TIM1->SR & TIM_SR_UIF)) {} // �ȴ������жϱ�־������
//}
void delay_us(uint32_t us) //����CPUѭ��ʵ�ֵķǾ�׼Ӧ�õ�΢����ʱ����
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us); //ʹ��HAL_RCC_GetHCLKFreq()������ȡ��Ƶֵ�����㷨�õ�1΢���ѭ������
    while (delay--); //ѭ��delay�Σ��ﵽ1΢����ʱ
}
//void delay_us(u32 nus)
//{
//       u32 ticks;
//       u32 told,tnow,reload,tcnt=0;
//       //if((0x0001&(SysTick->CTRL)) ==0)    //��ʱ��δ����
//              //vPortSetupTimerInterrupt();  //��ʼ����ʱ��
// 
//       reload = SysTick->LOAD;                     //��ȡ��װ�ؼĴ���ֵ
//       ticks = nus * (SystemCoreClock / 1000000);  //����ʱ��ֵ
//       told=SysTick->VAL;                          //��ȡ��ǰ��ֵ�Ĵ���ֵ����ʼʱ��ֵ��
// 
//       while(1)
//       {
//              tnow=SysTick->VAL;          //��ȡ��ǰ��ֵ�Ĵ���ֵ
//              if(tnow!=told)              //��ǰֵ�����ڿ�ʼֵ˵�����ڼ���
//              {         
// 
//                     if(tnow<told)             //��ǰֵС�ڿ�ʼ��ֵ��˵��δ�Ƶ�0
//                          tcnt+=told-tnow;     //����ֵ=��ʼֵ-��ǰֵ
// 
//                     else                  //��ǰֵ���ڿ�ʼ��ֵ��˵���ѼƵ�0�����¼���
//                            tcnt+=reload-tnow+told;   //����ֵ=��װ��ֵ-��ǰֵ+��ʼֵ  ����
//                                                      //�ӿ�ʼֵ�Ƶ�0�� 
// 
//                     told=tnow;                //���¿�ʼֵ
//                     if(tcnt>=ticks)break;     //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
//              } 
//       }     
//}
 
//SystemCoreClockΪϵͳʱ��(system_stmf4xx.c��)��ͨ��ѡ���ʱ����Ϊ
//systick��ʱ��ʱ�ӣ����ݾ����������

