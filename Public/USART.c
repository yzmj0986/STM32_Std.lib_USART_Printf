#include "USART.h"


int fputc(int ch,FILE *p)     //Printf�ض���
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


void USART1_Init(u32 btl)
	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     //PA9�Ǵ���1�ķ�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;     //PA10�Ǵ���1�Ľ������ţ�����ģʽ ����Ҫ�����ٶȡ�
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=btl;                 //���ڲ��������ã������ʡ��ֳ���ֹͣλ����żУ�顢Ӳ������ģʽ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);   //ʹ��USART1λ
	
	USART_ClearFlag(USART1,USART_FLAG_TC);  //�����־λ
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);   //���ô����ж����Ͳ�ʹ��
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;    //�ж����ȼ����� ��ռʽ����Ӧʽ��Ϊ��͵�1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART1_IRQHandler(void)
{
	u8 r;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		r=USART_ReceiveData(USART1);
		USART_SendData(USART1,r);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
	USART_ClearFlag(USART1,USART_FLAG_TC);
}

