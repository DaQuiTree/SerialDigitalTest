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
void LED4_Display (void);			// LED显示
void LED_OUT(u8 X);				// LED单字节串行移位函数

unsigned char LED_0F[];		// LED字模表

#define RCLK_UP GPIOE->BSRR = GPIO_Pin_9; //拉高
#define SCLK_UP GPIOE->BSRR = GPIO_Pin_10;
#define DIO_UP GPIOE->BSRR = GPIO_Pin_11;
 
#define RCLK_DOWN GPIOE->BRR = GPIO_Pin_9;//拉低
#define SCLK_DOWN GPIOE->BRR = GPIO_Pin_10;
#define DIO_DOWN GPIOE->BRR = GPIO_Pin_11;
 
u8 LED[8];	//用于LED的8位显示缓存

int main (void) 
{

    RCC_Configuration();	//系统时钟初始化
    GPIO_Configuration();//端口初始化
    
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
	unsigned char *led_table;          // 查表指针
	u8 i;
	//显示第1位
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK_DOWN;
	RCLK_UP;
	//显示第2位
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK_DOWN;
	RCLK_UP;
	//显示第3位
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK_DOWN;
	RCLK_UP;
	//显示第4位
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




