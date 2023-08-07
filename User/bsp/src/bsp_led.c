/**
 * @file bsp_LED.c
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief led驱动模块
 * @version v1.1 新增了led翻转函数bsp_LedToggle。
 * @date 2023-08-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "bsp.h"

/* led所有端口时钟 */
#define RCC_ALL_LED (RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE)

#define GPIO_PORT_LED0 	GPIOB
#define GPIO_PIN_LED0	GPIO_Pin_5

#define GPIO_PORT_LED1	GPIOE
#define GPIO_PIN_LED1	GPIO_Pin_5

/**
 * @brief led初始化函数
 * 
 */
void bsp_led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 打开GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_ALL_LED,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		/* 设置输出模式 */
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		/* 设置输出速率 */
	GPIO_InitStructure.GPIO_Pin=GPIO_PIN_LED0;			/* 选择引脚 */
	GPIO_Init(GPIO_PORT_LED0,&GPIO_InitStructure);		/* 初始化*/
	GPIO_SetBits(GPIO_PORT_LED0,GPIO_PIN_LED0);

	GPIO_InitStructure.GPIO_Pin=GPIO_PIN_LED1;
	GPIO_Init(GPIO_PORT_LED1,&GPIO_InitStructure);
	GPIO_SetBits(GPIO_PORT_LED1,GPIO_PIN_LED1);
}

/**
 * @brief 点亮指定的led
 * 
 * @param _no led灯序号（0~1)
 */
void bsp_Led_On(uint8_t _no)
{
	if (_no==0)
	{
		GPIO_ResetBits(GPIO_PORT_LED0,GPIO_PIN_LED0);
	}else if (_no==1)
	{
		GPIO_ResetBits(GPIO_PORT_LED1,GPIO_PIN_LED1);
	}
	
}

/**
 * @brief 熄灭指定的led
 * 
 * @param _no led灯序号（0~1)
 */
void bsp_Led_Off(uint8_t _no)
{
	if (_no==0)
	{
		GPIO_SetBits(GPIO_PORT_LED0,GPIO_PIN_LED0);
	}else if (_no==1)
	{
		GPIO_SetBits(GPIO_PORT_LED1,GPIO_PIN_LED1);
	}
}

/**
 * @brief 翻转led
 * 
 * @param _no led灯序号
 */
void bsp_LedToggle(uint8_t _no)
{
	if(_no==0){
		GPIO_PORT_LED0->ODR^=GPIO_PIN_LED0;
	}else if (_no==1){
		GPIO_WriteBit(GPIO_PORT_LED1,GPIO_PIN_LED1,(BitAction)!(GPIO_ReadOutputDataBit(GPIO_PORT_LED1,GPIO_PIN_LED1)));
	}
}
