/**
 * @file main.c
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief 主程序
 * @version 1.0
 * @date 2023-08-02
 * 
 * 
 */
#include "bsp.h"

int main()
{
	bsp_Init();
	while (1)
	{
		bsp_Led_On(0);
		bsp_Led_On(1);
		delay_ms(1000);
		bsp_Led_Off(0);
		bsp_Led_Off(1);
		delay_ms(1000);
	}
	
}

