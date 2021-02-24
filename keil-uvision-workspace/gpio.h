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

void	init_gpio	(void);
void	display_uofs (void);
void	display_hello (void);
void	delay (unsigned long value);