#define SYSCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))

#define NVIC_EN0_R				(*((volatile unsigned long *)0xE000E100))
#define NVIC_DIS0_R				(*((volatile unsigned long *)0xE000E000))

#define NVIC_PRI7_R				(*((volatile unsigned long *)0xE000E41C))

#define GPIO_PORTF_DATA_R	(*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R	(*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R	(*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_PUR_R	(*((volatile unsigned long *)0x40025510))

#define GPIO_PORTF_IS_R		(*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_R	(*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_R	(*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_R		(*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_ICR_R	(*((volatile unsigned long *)0x4002541C))

#define NVIC_EN0_INT30	0x40000000
#define	PORTF_CLK_EN		0x20
#define LEDs						0x0E
#define SW1							0x10
#define INT_PF4					0x10

void EnableInterrupts (void);
void DisableInterrupts (void);
void Init_INT_GPIO (void);
void Delay (unsigned long value);
void WaitForInterrupt (void);

volatile unsigned long i = 0;

void EnableInterrupts (void)
{
	GPIO_PORTF_IM_R = 0xFFFFFFFF;
	//NVIC_DIS0_R = 0x0;
	//NVIC_EN0_R = 0x40000000;
}

void DisableInterrupts (void)
{
	GPIO_PORTF_IM_R = 0x00000000;
	//NVIC_DIS0_R = 0x40000000;
}

void WaitForInterrupt (void)
{
	Delay (100);
}

void Init_INT_GPIO (void)
{
	volatile unsigned delay_clk;
	
	SYSCTL_RCGCGPIO_R |= PORTF_CLK_EN;
	delay_clk = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTF_DEN_R |= (SW1 | LEDs);
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_PUR_R |= SW1;
	
	DisableInterrupts ();
	GPIO_PORTF_IS_R &= ~INT_PF4;
	GPIO_PORTF_IBE_R &= ~INT_PF4;
	GPIO_PORTF_IEV_R &= ~INT_PF4;
	GPIO_PORTF_ICR_R |= INT_PF4;
	GPIO_PORTF_IM_R |= INT_PF4;
	
	NVIC_PRI7_R = 0x00A00000;
	NVIC_EN0_R = NVIC_EN0_INT30;
	EnableInterrupts ();
}

void Delay (unsigned long value)
{
	unsigned long i = 0;
	
	for (i = 0; i < value; i++);
}

void GPIOPortF_Hnadler (void)
{
	int j;
	GPIO_PORTF_ICR_R = INT_PF4;
	
	if (i == 3)
		i = 1;
	
	else
		i++;
	
	for (j = 0; i < 2; j++)
	{
		GPIO_PORTF_DATA_R ^= 1 << i;
		Delay (100000);
	}
}

int __main ()
{
	Init_INT_GPIO ();
	
	while (1)
	{
		WaitForInterrupt ();
	}
}