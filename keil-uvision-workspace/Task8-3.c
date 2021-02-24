#define	SYSCTL_RCGCGPIO_R	(*((volatile unsigned long *)0x400FE608))

#define	GPIO_PORTB_DATA_R		(*((volatile unsigned long *)0x400053FC))
#define	GPIO_PORTB_DIR_R		(*((volatile unsigned long *)0x40005400))
#define	GPIO_PORTB_DEN_R		(*((volatile unsigned long *)0x4000551C))

#define	GPIO_PORTA_DATA_R		(*((volatile unsigned long *)0x400043FC))
#define	GPIO_PORTA_DIR_R		(*((volatile unsigned long *)0x40004400))
#define	GPIO_PORTA_DEN_R		(*((volatile unsigned long *)0x4000451C))

#define	SEG_1		0XDF
#define	SEG_2		0xEF
#define	SEG_3		0xF7
#define	SEG_4		0xFB
#define	SEG_OFF	0xFF

const char lut_2015ee166 [19] = {0xFF, 0xFF, 0xFF, 0xFF, 0xA4, 0xC0, 0xF9, 0x92, 0xBF, 0x86, 0x86, 0xBF, 0xF9, 0x82, 0x82, 0xFF, 0xFF, 0xFF, 0xFF};

const char seg_select [4] = {0xDF, 0xEF, 0xF7, 0xFB};

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

int main (void)
{
	init_gpio ();
	
	while (1)
	{
		int i, j, k;
		
		for (i = 0; i < 15; i++)
		{
			for (j = 0; j < 20; j++)
			{
				for (k = 0; k < 4; k++)
				{
					GPIO_PORTA_DATA_R	= SEG_OFF;
					GPIO_PORTB_DATA_R	= lut_2015ee166[i+k];
					GPIO_PORTA_DATA_R	= seg_select[k];
					delay (10000);
				}
			}
		}
	}
}	