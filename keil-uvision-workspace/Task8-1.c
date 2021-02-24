#define	SYSCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))

#define	GPIO_PORTB_DATA_R		(*((volatile unsigned long *)0x400053FC))
#define	GPIO_PORTB_DIR_R		(*((volatile unsigned long *)0x40005400))
#define	GPIO_PORTB_DEN_R		(*((volatile unsigned long *)0x4000551C))

#define	GPIO_PORTA_DATA_R		(*((volatile unsigned long *)0x400043FC))
#define	GPIO_PORTA_DIR_R		(*((volatile unsigned long *)0x40004400))
#define	GPIO_PORTA_DEN_R		(*((volatile unsigned long *)0x4000451C))

#define	SEG_1		0XFB
#define	SEG_2		0xF7
#define	SEG_3		0xEF
#define	SEG_4		0xDF
#define	SEG_OFF	0xFF

const char lut_hey [4] = {0x89, 0x86, 0x91, 0xFF};

const char lut_hi [4] = {0x89, 0xF9, 0xFF, 0xFF};

const char lut_abd [4] = {0x88, 0x83, 0xA1, 0xFF};

const char lut_612 [4] = {0x82, 0xF9, 0xA4, 0xFF};

const char seg_select [4] = {0xFB, 0xF7, 0xEF, 0xDF};

void init_gpio (void)
{
	volatile unsigned long delay_clk;
	
	SYSCTL_RCGCGPIO_R |= 0x03;
	delay_clk = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTA_DIR_R |= 0x3C;
	GPIO_PORTA_DEN_R |= 0x3C;
}

void delay (unsigned long value)
{
	unsigned long i;
	
	for (i = 0; i < value; i++);
}

void display_hey (void)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		GPIO_PORTA_DATA_R	= SEG_OFF;
		GPIO_PORTB_DATA_R	= lut_hey[i];
		GPIO_PORTA_DATA_R	= seg_select[3-i];
		delay (10000);
	}
}

void display_hi (void)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		GPIO_PORTA_DATA_R	= SEG_OFF;
		GPIO_PORTB_DATA_R	= lut_hi[i];
		GPIO_PORTA_DATA_R	= seg_select[3-i];
		delay (10000);
	}
}

void display_abd (void)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		GPIO_PORTA_DATA_R	= SEG_OFF;
		GPIO_PORTB_DATA_R	= lut_abd[i];
		GPIO_PORTA_DATA_R	= seg_select[3-i];
		delay (10000);
	}
}

void display_612 (void)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		GPIO_PORTA_DATA_R	= SEG_OFF;
		GPIO_PORTB_DATA_R	= lut_612[i];
		GPIO_PORTA_DATA_R	= seg_select[3-i];
		delay (10000);
	}
}

int __main (void)
{
	init_gpio ();
	
	while (1)
	{
		int i;
		
		for (i = 0; i < 100; i++)
			display_hey ();
		
		for (i = 0; i < 100; i++)
			display_hi ();
	}
}