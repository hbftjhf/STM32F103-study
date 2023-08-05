/**
 * @file bsp.c
 * @author hbftjhf (hbftjhf@outlook.com)
 * @brief 硬件底层驱动程序的主文件，每个.c文件可以#include "bsp.h"来包含所有外设驱动模块。
 * 		  bsp = Borad surport packet 板级支持包。
 * @version 1.1
 * 			2023-08-04	1.1
 * 			新增了SysTick_Init、delay_us、delay_ms 函数。
 * 			能使用系统滴答定时器延时。
 * @date 2023-08-02
 * 
 */
#include "bsp.h"

static uint8_t 	fac_us=0;		//延时微秒的频率
static uint16_t fac_ms=0;		//延时毫秒的频率

/**
 * @brief 初始化所有硬件设备，配置cpu和外设的寄存器，并初始化一些全局变量。
 * 
 */
void bsp_Init(void)
{
	bsp_led_Init();
	bsp_key_Init();
	bsp_SysTick_Init();
}



/**
 * @brief 初始化SysTick 系统滴答定时器
 * 
 */
void bsp_SysTick_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟，将 72MHz 的频率 8 分频，得到 9 M
	fac_us=SystemCoreClock/8000000;							//为系统时钟的1/8，72/8 延时1微秒9个时钟周期
	fac_ms=(u16)fac_us*1000;								//代表每个ms需要的systick时钟数，即延时1毫秒9000个 SysTick 时钟周期   
}

/**
 * @brief 微秒延时函数
 * 
 * @param nus 延时多少微秒
 */
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us;		//设置重载值:n(us)*延时1us需要多少个SysTick时钟周期
	SysTick->VAL=0x00;				// VAL初始化为0,即清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;		//使能 SysTick 定时器，开始开始倒数
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待计数时间到达（位16）
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;							//重置VAL，即清空计数器
}

/**
 * @brief 毫秒延时函数
 * 
 * @param nms nms>=1864
 */
void delay_ms(uint16_t nms)
{
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	
}
