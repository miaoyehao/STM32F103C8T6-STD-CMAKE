#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//GPIO引脚，赋值为第0号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	/*OLED显示*/
	OLED_ShowChar(1, 1, 'A');				//1行1列显示字符A
	
	OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
	
	OLED_ShowNum(2, 1, 12345, 5);			//2行1列显示十进制数字12345，长度为5
	
	OLED_ShowSignedNum(2, 7, -66, 2);		//2行7列显示有符号十进制数字-66，长度为2
	
	OLED_ShowHexNum(3, 1, 0xAA55, 4);		//3行1列显示十六进制数字0xA5A5，长度为4
	
	OLED_ShowBinNum(4, 1, 0xAA55, 16);		//4行1列显示二进制数字0xA5A5，长度为16
											//C语言无法直接写出二进制数字，故需要用十六进制表示
	
	while (1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	//GPIOA的第0号引脚输出低电平
		Delay_ms(500);						//延时500ms
		GPIO_SetBits(GPIOA,GPIO_Pin_0);	//GPIOA的第0号引脚输出高电平
		Delay_ms(500);						//延时500ms
	}
}
