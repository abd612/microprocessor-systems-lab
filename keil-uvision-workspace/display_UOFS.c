#include "gpio.h"

const char lut_uofs [4] = {0xC1, 0xC0, 0x8E, 0x92};

const char lut_helo [4] = {0x89, 0x86, 0xC7, 0xC0};

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

void display_uofs (void)
{
	GPIO_PORTA_DATA_R	= SEG_OFF;
	GPIO_PORTB_DATA_R	= lut_uofs [3-0];
	GPIO_PORTA_DATA_R	 = SEG_1;
	delay (10000);
	
	GPIO_PORTA_DATA_R	= SEG_OFF;
	GPIO_PORTB_DATA_R	= lut_uofs [3-1];
	GPIO_PORTA_DATA_R	 = SEG_2;
	delay (10000);
	
	GPIO_PORTA_DATA_R	= SEG_OFF;
	GPIO_PORTB_DATA_R	= lut_uofs [3-2];
	GPIO_PORTA_DATA_R	 = SEG_3;
	delay (10000);
	
	GPIO_PORTA_DATA_R	= SEG_OFF;
	GPIO_PORTB_DATA_R	= lut_uofs [3-3];
	GPIO_PORTA_DATA_R	 = SEG_4;
	delay (10000);
}

void display_helo (void)
{
	int i;
	
	for (i = 0; i < 5; i++)
	{
		GPIO_PORTA_DATA_R	= SEG_OFF;
		GPIO_PORTB_DATA_R	= lut_helo[i];
		GPIO_PORTA_DATA_R	= seg_select[3-i];
		delay (10000);
	}
}

void delay (unsigned long value)
{
	unsigned long i;
	
	for (i = 0; i < value; i++);
}

int __main (void)
{
	init_gpio ();
	
	while (1)
		display_uofs ();
}