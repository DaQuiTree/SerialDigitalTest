#include "pbdata.h"

 u8 fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
 u8 segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
 u8 disbuf[4]={0,0,0,0};
 u8 LED_0F[] = 
 {// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
 };

void RCC_Configuration(void);
void GPIO_Configuration(void);
void LED4_Display (void);			// LED��ʾ
void LED_OUT(u8 X);				// LED���ֽڴ�����λ����

unsigned char LED_0F[];		// LED��ģ��

#define RCLK_UP GPIOE->BSRR = GPIO_Pin_9; //����
#define SCLK_UP GPIOE->BSRR = GPIO_Pin_10;
#define DIO_UP GPIOE->BSRR = GPIO_Pin_11;
 
#define RCLK_DOWN GPIOE->BRR = GPIO_Pin_9;//����
#define SCLK_DOWN GPIOE->BRR = GPIO_Pin_10;
#define DIO_DOWN GPIOE->BRR = GPIO_Pin_11;
 
u8 LED[8];	//����LED��8λ��ʾ����

int main (void) 
{

    RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
    GPIO_Configuration();//�˿ڳ�ʼ��
    
	LED[0]=5;
	LED[1]=6;
	LED[2]=7;
	LED[3]=8;
    
	while(1)
	{
		LED4_Display ();
	} 
} 

void LED4_Display (void)
{
	unsigned char *led_table;          // ���ָ��
	u8 i;
	//��ʾ��1λ
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK_DOWN;
	RCLK_UP;
	//��ʾ��2λ
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK_DOWN;
	RCLK_UP;
	//��ʾ��3λ
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK_DOWN;
	RCLK_UP;
	//��ʾ��4λ
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLK_DOWN;
	RCLK_UP;
}

void LED_OUT(u8 X)
{
	u8 i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80){ 
            DIO_UP;
        }else{ 
            DIO_DOWN;
        }
		X<<=1;
		SCLK_DOWN;
		SCLK_UP;
	}
}

void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);      
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
}




