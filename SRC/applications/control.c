#include "control.h"

void lanya(u8 data)
{
	switch(data)
	{
		case 1:  break;
		case 2:  break;
		case 3:  break;
		case 4:  break;
		case 5:  break;
		case 6:  break;
		case 7:  break;
		case 8:  break;
		case 9:  break;
		case 10: break;
		case 11: break;
		case 12:  break;
		default:       ;
	}
}


void TIM4_IRQHandler(void){
	

	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC1);
}



