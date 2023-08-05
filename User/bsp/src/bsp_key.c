/**
 * @file bsp_key.c
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief Key按键驱动模块
 * @version 1.0 构建了bsp_key_Init、bsp_key_scand函数，bsp_key_scand实现的按下按键翻转对应的led
 * @date 2023-08-05
 * 
 * 
 */

#include "bsp.h"

#define RCC_ALL_KEY		(RCC_APB2Periph_GPIOE,RCC_APB2Periph_GPIOA)

#define GPIO_PORT_KEY0	GPIOE
#define GPIO_PIN_KEY0	GPIO_Pin_4

#define GPIO_PORT_KEY1	GPIOA
#define GPIO_PIN_KEY1	GPIO_Pin_0

/**
 * @brief 按键初始化函数
 * 
 */
void bsp_key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		/* 设置下拉输入 */
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		/* 设置速率 */
	GPIO_InitStructure.GPIO_Pin=GPIO_PIN_KEY0;		/* 选择引脚 */
	GPIO_Init(GPIO_PORT_KEY0,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_PIN_KEY1;		/* 选择引脚 */
	GPIO_Init(GPIO_PORT_KEY1,&GPIO_InitStructure);
	
}

/**
 * @brief 简单的按键扫描函数
 * 
 */
void bsp_key_scand(void)
{
	if(GPIO_ReadInputDataBit(GPIO_PORT_KEY0,GPIO_PIN_KEY0)==1){
		delay_ms(15);
		while(GPIO_ReadInputDataBit(GPIO_PORT_KEY0,GPIO_PIN_KEY0)==1){
			bsp_LedToggle(0);			
		}
	}
	if(GPIO_ReadInputDataBit(GPIO_PORT_KEY1,GPIO_PIN_KEY1)==1){
		delay_ms(15);
		while (GPIO_ReadInputDataBit(GPIO_PORT_KEY1,GPIO_PIN_KEY1)==1){
			bsp_LedToggle(1);
		}
	}
}
