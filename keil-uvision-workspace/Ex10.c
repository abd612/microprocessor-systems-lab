void SystemInit(){}

// GPIO registers
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long*)0x400FE608))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long*)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long*)0x40025400))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long*)0x4002551C))

// Timer registers
#define SYSCTL_RCGCTIMER_R (*((volatile unsigned long*)0x400FE604))
#define TIMER0_CTL_R (*((volatile unsigned long*)0x4003000C))
#define TIMER0_CFG_R (*((volatile unsigned long*)0x40030000))
#define TIMER0_TAMR_R (*((volatile unsigned long*)0x40030004))
#define TIMER0_TAILR_R (*((volatile unsigned long*)0x40030028))
#define TIMER0_TAPR_R (*((volatile unsigned long*)0x40030038))
#define TIMER0_ICR_R (*((volatile unsigned long *)0x40030024))
#define TIMER0_IMR_R (*((volatile unsigned long*)0x40030018))
	
// NVIC registers
#define NVIC_EN0_R (*((volatile unsigned long*)0xE000E100))
#define NVIC_PRI4_R (*((volatile unsigned long*)0xE000E410))
	
// constant values
#define TIM0_CLK_EN 0x01 //enable clock for Timer0
#define TIM0_EN 0x01 // disable Timer0 before setup
#define TIM_16_BIT_EN 0x04 //configure 16- bit timer mode
#define TIM_TAMR_PERIODIC_EN 0x02 // configure periodic mode
#define TIM_FREQ_10usec 159 // select prescaler for
														
// desired frequency 100kHz
#define TIM0_INT_CLR 0x01 // clear timeout interrupt
#define EN0_INT19 0x00080000 //enable interrupt 19
#define PORTF_CLK_EN 0x20 // enable clock for portF
#define TOGGLE_PF1 0x02 // toggle red led (PF1)
#define LED_RED 0x02 //configured red led (PF1)

// function headers
void GPIO_Init(void);
void Timer_Init ( unsigned long period);
void DisableInterrupts(void);
void EnableInterrupts (void);
void WaitForInterrupt (void);

void Timer_Init (unsigned long period){

		SYSCTL_RCGCTIMER_R |= TIM0_CLK_EN;//enable clock for Timer0
		TIMER0_CTL_R &= ~(TIM0_EN); //disable Timer0 before setup
		TIMER0_CFG_R |= TIM_16_BIT_EN;//configure 16-bit timer mode
		TIMER0_TAMR_R |= TIM_TAMR_PERIODIC_EN;//configure periodic mode
		TIMER0_TAILR_R = period; //set initial load value
		TIMER0_TAPR_R = TIM_FREQ_10usec; //set prescalaer for desired frequency 100 kHz
		TIMER0_ICR_R = TIM0_INT_CLR;//clear time out interrupt
		TIMER0_IMR_R |= TIM0_EN; //enable interrupt mask for Timer_0A

		DisableInterrupts();
		//Set priority for interrupt
		NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0x40000000;
		NVIC_EN0_R |= EN0_INT19; //enable interrupt 19
		TIMER0_CTL_R |= TIM0_EN; //enable Timer_0A

		EnableInterrupts();
}

void GPIO_Init(){

		SYSCTL_RCGCGPIO_R |= PORTF_CLK_EN ;
		GPIO_PORTF_DIR_R |= LED_RED ;
		GPIO_PORTF_DEN_R |= LED_RED ;
}
 
void Timer0A_Handler(void){

		TIMER0_ICR_R = TIM0_INT_CLR ;
		GPIO_PORTF_DATA_R ^= TOGGLE_PF1 ;
}

int main(void){

		Timer_Init(500000) ; //generate a square wave for2Hz
		GPIO_Init(); //initialize PF1 as digital output
		while(1);

}