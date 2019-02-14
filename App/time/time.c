#include "time.h"
#include "led.h"
#include "exti.h"
#include "stm32f10x.h"


void TIM4_Init(u16 pre,u16 psc)   //psc��16λ�ģ�������65535
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; //��ʼ����ʱ������
	
	NVIC_InitTypeDef NVIC_InitStructure;  //���ö�ʱ���ж����ȼ�
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period=pre;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE);  //��ʱ��4ʹ�ܣ������˶�ʱ��

}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==1)//����������ն�
	{
		led2=!led2;
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//ִ�����жϺ���������жϱ�־λ
	
}

