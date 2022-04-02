#include "config.h"
	
void data_config()
{


}

void init_config(void)
{  
	SysTick_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Scheduler_Setup();
	uart_init(500000);
	PS2_Init();
	pwm_servo_init();
	TIM_INIT();
	uart_init(500000); 
}

