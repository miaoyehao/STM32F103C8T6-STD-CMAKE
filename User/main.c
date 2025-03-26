#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyFLASH.h"
#include "Key.h"
#include "Store.h"

uint8_t KeyNum;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();
	Store_Init();

	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(1, 1, "Data:");

	/*OLED_ShowHexNum(1, 1, Myflash_ReadWord(0x08000000), 8);
	OLED_ShowHexNum(2, 1, Myflash_ReadHalfWord(0x08000000), 8);
	OLED_ShowHexNum(3, 1, Myflash_ReadByte(0x08000000), 8);

	MyFLASH_ErasePage(0x0800FC00);
	MyFLASH_ProgramWord(0x0800FC00, 0x12345678);
	MyFLASH_ProgramHalfWord(0x0800FC10, 0xABCD);*/
	


	while (1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			Store_Data[0] ++;
			Store_Data[1] += 1;
			Store_Data[2] += 2;
			Store_Data[3] += 3;
			Store_Data[4] += 4;
			Store_Save();
			//MyFLASH_EraseALLPages();
		}
		if(KeyNum == 2)
		{
			Store_Clear();
			//MyFLASH_ErasePage(0x08000000);
		}
		OLED_ShowHexNum(1,6,Store_Data[0],4);
		OLED_ShowHexNum(3,1,Store_Data[1],4);
		OLED_ShowHexNum(3,6,Store_Data[2],4);
		OLED_ShowHexNum(4,1,Store_Data[3],4);
		OLED_ShowHexNum(4,6,Store_Data[4],4);
		
	}		
}
