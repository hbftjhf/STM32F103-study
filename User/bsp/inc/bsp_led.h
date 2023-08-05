/**
 * @file bsp_LED.h
 * @brief LED驱动模块-头文件
 * @version 0.1
 * @date 2023-08-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __BSP_LED_H
#define __BSP_LED_H

void bsp_led_Init(void);
void bsp_Led_On(uint8_t _no);
void bsp_Led_Off(uint8_t _no);

#endif // !__BSP_LED_H
