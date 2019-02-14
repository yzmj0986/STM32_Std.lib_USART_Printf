#include "pwm.h"

void TIM3_CH1_PWM_Init(u16 pre,u16 psc)	
{
	GPIO_InitTypeDef GPIO_InitStructure;     //GPIO�˿ڳ�ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  //��ʱ����ʼ��
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;            //GPIOC_6�˿ڣ�ģʽ�Ǹ�������������ٶ�50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ�ܶ�ʱ��3��ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //ʹ��GPIOC��ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   //ʹ��AFIO��ʱ�� 
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);   //ʹ�ܶ�ʱ��3��ӳ�书��
		
	TIM_TimeBaseInitStructure.TIM_Period=pre;              //���ö�ʱ��3�������Զ���װֵpre����Ƶϵ��psc��������ʽ��
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;            //���ö�ʱ��3��PWM����Ĳ�����PWM1ģʽ��������ԡ�ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);    //ʹ��CCRx�ϵ�Ԥװ�ض�ʱ��
	TIM_ARRPreloadConfig(TIM3,ENABLE);                  //ʹ��ARR�ϵ�Ԥװ�ض�ʱ��
	TIM_Cmd(TIM3,ENABLE);   //������ʱ��3
	
}


