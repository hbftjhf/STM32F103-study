/**
 * @file bsp.h
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief 底层驱动模块所有的.h文件的汇总文件。
 * 		  应用程序只需要#include "bsp.h"即可，不用一个一个包含.h文件
 * @version 1.0
 * @date 2023-08-02
 * 
 */

#ifndef __BSP_H_
#define __BSP_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//通过添加注释或取消注释控制是否包含底层驱动
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_exti.h"

//bsp.c 函数
void bsp_Init(void);
void bsp_SysTick_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif // !__BSP_H_
