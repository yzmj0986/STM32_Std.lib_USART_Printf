#include "stm32f10x.h"
#include "led.h"
#include "system.h"
#include "SysTick.h"
#include "USART.h"


int main()
{
	u8 i=0;
	u16 data=1234;
	float fdata=12.34;
	char str[]="Hello World!";
		
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�ж����ȼ�����
	LED_Init();
	USART1_Init(9600);
	
	
	
	
	while(1)
	{
		i++;
		if(i%20==0)
		{
			led1=!led1;
			
			printf("���������data=%d\r\n",data);
			printf("���������fdata=%.2f\r\n",fdata);
			printf("����ַ���str=%s\r\n",str);
			printf("����˽�����data=%o\r\n",data);
			printf("���ʮ��������data=%X\r\n",data);
		}
		delay_ms(20);
	}
	
}

