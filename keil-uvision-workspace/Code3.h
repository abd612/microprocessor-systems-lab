#define SYSCTL_RCGCGPIO_R	(*(( volatile unsigned long*)0x400FE608))

#define	GPIO_PORTA_DATA_R	(*(( volatile unsigned long*)0x400043FC))
#define GPIO_PORTA_DIR_R	(*(( volatile unsigned long*)0x40004400))
#define GPIO_PORTA_DEN_R	(*(( volatile unsigned long*)0x4000451C))

#define GPIO_PORTB_DATA_R	(*(( volatile unsigned long*)0x400053FC))
#define GPIO_PORTB_DIR_R	(*(( volatile unsigned long*)0x40005400))
#define	GPIO_PORTB_DEN_R	(*(( volatile unsigned long*)0x4000551C))

#define GPIO_PORTC_DATA_R	(*(( volatile unsigned long*)0x400063FC))
#define	GPIO_PORTC_DIR_R	(*(( volatile unsigned long*)0x40006400))
#define	GPIO_PORTC_DEN_R	(*(( volatile unsigned long*)0x4000651C))

#define	GPIO_PORTD_DATA_R		(*((volatile unsigned long *)0x400073FC))
#define	GPIO_PORTD_DIR_R		(*((volatile unsigned long *)0x40007400))
#define	GPIO_PORTD_DEN_R		(*((volatile unsigned long *)0x4000751C))

#define	GPIO_PORTE_DATA_R	(*(( volatile unsigned long *)0x400243FC))
#define	GPIO_PORTE_DIR_R	(*(( volatile unsigned long *)0x40024400))
#define	GPIO_PORTE_DEN_R	(*(( volatile unsigned long *)0x4002451C))

#define	GPIO_PORTF_DATA_R	(*(( volatile unsigned long *)0x400253FC))
#define	GPIO_PORTF_DIR_R	(*(( volatile unsigned long *)0x40025400))
#define	GPIO_PORTF_DEN_R	(*(( volatile unsigned long *)0x4002551C))


#define GPIO_PORTALL_CLK_EN 	0x3F			//port A,B,C,D,E and F enable

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
