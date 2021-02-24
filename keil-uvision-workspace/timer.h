	#define SYSCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))
	#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
	#define GPIO_PORTF_DIR_R (*((volatile unsigned long  *)0x40025400))
	#define GPIO_PORTF_DEN_R (*((volatile unsigned long *) 0x4002551C))
	
	#define SYSCTL_RCGCTIMER_R	(*((volatile unsigned long *)0x4002551C))
	
	#define TIMER0_CTL_R	(*((volatile  unsigned long *)0x4003000C))
	#define TIMER0_CFG_R	(*((volatile  unsigned long *)0x40030000))
	#define TIMER0_TAMR_R	(*((volatile  unsigned long *)0x40030004))
	#define TIMER0_TAILR_R	(*((volatile  unsigned long *)0x40030028))
	#define TIMER0_TAPR_R	(*((volatile  unsigned long *)0x40030038))
	#define TIMER0_ICR_R	(*((volatile  unsigned long *)0x40030024))
	#define TIMER0_IMR_R	(*((volatile  unsigned long *)0x40030018))
	
	#define NVIC_EN0_R	(*((volatile  unsigned long *)0xE000E100))
	#define NVIC_PRI4_R	(*((volatile  unsigned long *)0xE000E410))
	
	#define TIM0_CLK_EN	0x01
	#define TIM0_EN			0x01
	#define TIM_16_BIT_EN	0x04
	#define TIM_TAMR_PERIODIC_EN 0x2
	#define TIM_FREQ_10usec	0x9F
	
	#define TIM0_INT_CLR	0x1
	#define EN0_INT19	0x80000
	#define PORTF_CLK_EN	0x20
	#define	TOGGLE_PF1 	0x02
	#define LED_RED	0x02
	
	void GPIO_Init (void);
	void Timer_Init (unsigned long period);
	void DisableInterrupts (void);
	void EnableInterrupts (void);
	void WaitForInterrupt (void);