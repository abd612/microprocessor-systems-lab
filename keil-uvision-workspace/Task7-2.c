#define	SYSTCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))
#define	GPIO_PORTF_DATA_R		(*((volatile unsigned long *)0x400253FC))
#define	GPIO_PORTF_DIR_R		(*((volatile unsigned long *)0x40025400))
#define	GPIO_PORTF_DEN_R		(*((volatile unsigned long *)0x4002551C))

#define GPIO_PORTF_CLK_EN		0x20
//#define	GPIO_PORTF_PIN1_EN	0x2
//#define	LED_ON							0x2
//#define	LED_OFF							~(0x2)
#define	DELAY									500000

int __main (void)
{
	int	GPIO_PORTF_PIN1_EN;
	int	LED_ON;
	int	LED_OFF;
	int value;
	int i;
	volatile unsigned long ulLoop;

	SYSTCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;

	ulLoop = SYSTCTL_RCGCGPIO_R;

	for (i = 0; i < 7; i++)
	{
		switch(i)
		{
			case 0: value = 2; break;
			case 1: value = 4; break;
			case 2: value = 8; break;
			case 3: value = 6; break;
			case 4: value = 10; break;
			case 5: value = 12; break;
			case 6: value = 14; break;
			default: break;
		}
		
		GPIO_PORTF_PIN1_EN = value;
		LED_ON = value;
		LED_OFF = ~value;
		
		GPIO_PORTF_DIR_R |= GPIO_PORTF_PIN1_EN;
		GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN1_EN;
		
		GPIO_PORTF_DATA_R |= LED_ON;

		for (ulLoop = 0; ulLoop < DELAY; ulLoop++);
		
		GPIO_PORTF_DATA_R &= LED_OFF;

		for (ulLoop = 0; ulLoop < DELAY; ulLoop++);
	}
}