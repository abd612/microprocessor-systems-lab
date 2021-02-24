void SystemInit ()
{
	
}

#define	SYSTCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))
#define	SYSTCTL_RCGC2_R			(*((volatile unsigned long *)0x400FE108))

#define	GPIO_PORTA_DATA_R		(*((volatile unsigned long *)0x400043FC))
#define	GPIO_PORTA_DIR_R		(*((volatile unsigned long *)0x40004400))
#define	GPIO_PORTA_DEN_R		(*((volatile unsigned long *)0x4000451C))

#define	GPIO_PORTB_DATA_R		(*((volatile unsigned long *)0x400053FC))
#define	GPIO_PORTB_DIR_R		(*((volatile unsigned long *)0x40005400))
#define	GPIO_PORTB_DEN_R		(*((volatile unsigned long *)0x4000551C))

#define	GPIO_PORTC_DATA_R		(*((volatile unsigned long *)0x400063FC))
#define	GPIO_PORTC_DIR_R		(*((volatile unsigned long *)0x40006400))
#define	GPIO_PORTC_DEN_R		(*((volatile unsigned long *)0x4000651C))

#define	GPIO_PORTD_DATA_R		(*((volatile unsigned long *)0x400073FC))
#define	GPIO_PORTD_DIR_R		(*((volatile unsigned long *)0x40007400))
#define	GPIO_PORTD_DEN_R		(*((volatile unsigned long *)0x4000751C))

#define	GPIO_PORTE_DATA_R		(*((volatile unsigned long *)0x400243FC))
#define	GPIO_PORTE_DIR_R		(*((volatile unsigned long *)0x40024400))
#define	GPIO_PORTE_DEN_R		(*((volatile unsigned long *)0x4002451C))

#define	GPIO_PORTF_DATA_R		(*((volatile unsigned long *)0x400253FC))
#define	GPIO_PORTF_DIR_R		(*((volatile unsigned long *)0x40025400))
#define	GPIO_PORTF_DEN_R		(*((volatile unsigned long *)0x4002551C))

#define	GPIO_PORTF_DATA_RD	(*((volatile unsigned long *)0x40025040))
#define	GPIO_PORTF_DATA_WR	(*((volatile unsigned long *)0x40025020))

#define GPIO_PORTA_CLK_EN		0x01
#define GPIO_PORTB_CLK_EN		0x02
#define GPIO_PORTC_CLK_EN		0x04
#define GPIO_PORTD_CLK_EN		0x08
#define GPIO_PORTE_CLK_EN		0x10
#define GPIO_PORTF_CLK_EN		0x20

#define	GPIO_PORTA_PINS_EN	0xFC
#define	GPIO_PORTB_PINS_EN	0xFF
#define	GPIO_PORTC_PINS_EN	0xF0
#define	GPIO_PORTD_PINS_EN	0xCF
#define	GPIO_PORTE_PINS_EN	0x3F
#define	GPIO_PORTF_PINS_EN	0x1F

#define	LED_ON							0x8
#define	LED_OFF							~(0x8)
#define	DELAY								20000

volatile unsigned long delay_clk;
int i;

const char led [8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; 

void	init_gpio (void)
{
	SYSTCTL_RCGCGPIO_R |= (GPIO_PORTA_CLK_EN + GPIO_PORTB_CLK_EN + GPIO_PORTC_CLK_EN +
												 GPIO_PORTE_CLK_EN + GPIO_PORTF_CLK_EN);
	
	delay_clk = SYSTCTL_RCGCGPIO_R;
	
	GPIO_PORTA_DEN_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DEN_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DEN_R |= GPIO_PORTC_PINS_EN;
//	GPIO_PORTD_DEN_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DEN_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PINS_EN;
	
	GPIO_PORTA_DIR_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DIR_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DIR_R |= GPIO_PORTC_PINS_EN;
//	GPIO_PORTD_DIR_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DIR_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PINS_EN;
}

int __main (void)
{
	init_gpio ();
	
	while (1)
	{
		for (i = 0; i < 8; i++)
		{
			GPIO_PORTB_DATA_R |= led [i];
			GPIO_PORTF_DATA_R &= ~0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			GPIO_PORTF_DATA_R |= 0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
		}
		
		for (i = 0; i < 8; i++)
		{
			GPIO_PORTB_DATA_R &= ~led [i];
			GPIO_PORTF_DATA_R &= ~0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			GPIO_PORTF_DATA_R |= 0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
		}
		
		for (i = 7; i > -1; i--)
		{
			GPIO_PORTB_DATA_R |= led [i];
			GPIO_PORTF_DATA_R &= ~0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			GPIO_PORTF_DATA_R |= 0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
		}
		
		for (i = 7; i > -1; i--)
		{
			GPIO_PORTB_DATA_R &= ~led [i];
			GPIO_PORTF_DATA_R &= ~0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			GPIO_PORTF_DATA_R |= 0x08;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
		}

		
//		GPIO_PORTA_DATA_R |= GPIO_PORTA_PINS_EN;
//		GPIO_PORTB_DATA_R |= GPIO_PORTB_PINS_EN;
//		GPIO_PORTC_DATA_R |= GPIO_PORTC_PINS_EN;
//		GPIO_PORTD_DATA_R |= GPIO_PORTD_PINS_EN;
//		GPIO_PORTE_DATA_R |= GPIO_PORTE_PINS_EN;
//		GPIO_PORTF_DATA_R |= GPIO_PORTF_PINS_EN;
/*		
		GPIO_PORTF_DATA_R |= 0x08;
		
		GPIO_PORTB_DATA_R |= led [0] + led [2] + led [4];
		GPIO_PORTB_DATA_R &= ~led [1] + ~led [3];
		
		for (delay_clk = 0; delay_clk < 1000000; delay_clk++);
		
		GPIO_PORTF_DATA_R &= ~0x08;
		
		GPIO_PORTB_DATA_R = led [1] + led [3];
		GPIO_PORTB_DATA_R &= ~led [0] + ~led [2] + ~led [4];
		
		for (delay_clk = 0; delay_clk < 1000000; delay_clk++);
*/
	}
}