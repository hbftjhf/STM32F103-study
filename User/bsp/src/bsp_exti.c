/**
 * @file bsp_exti.c
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief 外部中断驱动
 * @version 1.0 构建了按键外部中断初始化函数bsp_Init_Key_EXTI，编写中断服务函数实现led翻转
 * @date 2023-08-06
 * 
 * 
 */

#include "bsp.h"

/**
 * @brief EXTI(外部中断)Key初始化
 * 
 */
void bsp_Init_Key_EXTI(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/** 开启AFIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	/** 连接 EXTI Line4 到 PE4 引脚 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	/** EXTI中断源 */
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	/** 中断模式 */
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	/** 上升延触发 */
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	/** 使能 */
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	/** 根据 EXTI_InitStructure 初始化 EXTI */
	EXTI_Init(&EXTI_InitStructure);

	/** 连接 EXTI Line0(外部中断线0) 到 PA0 引脚 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	/** EXTI中断源 */
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	/** 中断模式 */
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	/** 上升延触发 */
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	/** 使能 */
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	/** 根据 EXTI_InitStructure 初始化 EXTI */
	EXTI_Init(&EXTI_InitStructure);

	/**中断优先级分组2*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/**使能指定的IRQ通道*/
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	/**抢占优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
	/**子优先级*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
	/**使能或失能*/
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	/**根据NVIC_InitStructure初始化NVIC*/
	NVIC_Init(&NVIC_InitStructure);

	/**使能指定的IRQ通道*/
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	/**抢占优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
	/**子优先级*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01;
	/**使能或失能*/
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	/**根据NVIC_InitStructure初始化NVIC*/
	NVIC_Init(&NVIC_InitStructure);
}



void EXTI0_IRQHandler(void)
{
	delay_ms(10);
	/**读取按键状态*/
	while(EXTI_GetITStatus(EXTI_Line0)!=RESET){
		bsp_LedToggle(1);
		/**清除中断标志位*/
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	/**读取按键状态*/
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET){
		/**翻转led0*/
		bsp_LedToggle(0);
		/**清除中断标志位*/
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
