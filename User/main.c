#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t MyTaskhandle;

void MyTask(void *pvParameters)
{
	while (1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set Pin 13 low
		vTaskDelay(500); // Delay for 500 ms
		GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set Pin 13 high
		vTaskDelay(500); // Delay for 500 ms
	}
}
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable GPIOC clock
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // Pin 13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 
	GPIO_Init(GPIOC, &GPIO_InitStructure); // Initialize GPIOC
	xTaskCreate(MyTaskhandle,"MyTask", 128, NULL, 2, &MyTaskhandle);
	vTaskStartScheduler();
	while (1)
	{
		
	}
}
