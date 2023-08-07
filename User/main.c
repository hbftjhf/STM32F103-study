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
	// bsp_Led_On(0);
	bsp_Led_On(1);
	while (1)
	{
		//bsp_LedToggle(0);
		//delay_ms(1000);
	}
	
}

