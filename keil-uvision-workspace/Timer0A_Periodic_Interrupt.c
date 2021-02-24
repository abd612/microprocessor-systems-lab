#include "timer.h"

void SystemInit()
{
}
	
void Timer_Init(unsigned long period)
{	
	SYSCTL_RCGCTIMER_R |= TIM0_CLK_EN;
	TIMER0_CTL_R &= ~(TIM0_EN);
	TIMER0_CFG_R |= TIM_16_BIT_EN;
	TIMER0_TAMR_R |= TIM_TAMR_PERIODIC_EN;
	TIMER0_TAILR_R = period;
	TIMER0_TAPR_R = TIM_FREQ_10usec;
	
	TIMER0_ICR_R = TIM0_INT_CLR;
	TIMER0_IMR_R |= TIM0_EN;
	
	DisableInterrupts();
	
	NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF)|0x40000000;
	NVIC_EN0_R |= EN0_INT19;
	
	TIMER0_CTL_R |= TIM0_EN;
	
	EnableInterrupts();
}

void GPIO_Init()
{	
	SYSCTL_RCGCGPIO_R |= PORTF_CLK_EN;
	GPIO_PORTF_DIR_R |= LED_RED;
	GPIO_PORTF_DEN_R |= LED_RED;
}

void Timer0A_Handler(void)
{
	TIMER0_ICR_R = TIM0_INT_CLR;
	GPIO_PORTF_DATA_R ^= TOGGLE_PF1;
}

int main (void)
{	
	Timer_Init(50000);
	GPIO_Init();
	while(1);
}