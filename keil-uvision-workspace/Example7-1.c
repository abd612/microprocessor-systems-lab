#define	SYSTCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))
#define	GPIO_PORTF_DATA_R		(*((volatile unsigned long *)0x400253FC))
#define	GPIO_PORTF_DIR_R		(*((volatile unsigned long *)0x40025400))
#define	GPIO_PORTF_DEN_R		(*((volatile unsigned long *)0x4002551C))

#define GPIO_PORTF_CLK_EN		0x20
#define	GPIO_PORTF_PIN1_EN	0x8
#define	LED_ON							0x8
#define	LED_OFF							~(0x8)
#define	DELAY								20000000

int __main (void)
{
	volatile unsigned long ulLoop;

	SYSTCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;

	ulLoop = SYSTCTL_RCGCGPIO_R;

	GPIO_PORTF_DIR_R |= GPIO_PORTF_PIN1_EN;
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN1_EN;

	while (1)
	{
		
		GPIO_PORTF_DATA_R |= LED_ON;

		for (ulLoop = 0; ulLoop < DELAY; ulLoop++);
		
		GPIO_PORTF_DATA_R &= LED_OFF;

		for (ulLoop = 0; ulLoop < DELAY; ulLoop++);
	}
}