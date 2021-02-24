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
#define	DELAY								50000

volatile unsigned long delay_clk;
int i, j;

const char row[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x02, 0x04};
const char col[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
const char layer[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const char lat[8] = {0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E};
const char lay[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void CubeOff ();
void CubeOn ();
void CubeBlink ();
void LayerTraverseDown ();
void LayerTraverseUp ();
void LayerTraverseUpDown ();
void CubeFillDown ();
void CubeFillUp ();
void LayersHalf ();
void ROWW();
void A();
void Convergence();
void CubeFillEmpty ();

void	init_gpio (void)
{
	SYSTCTL_RCGCGPIO_R |= (GPIO_PORTB_CLK_EN + GPIO_PORTC_CLK_EN +
												 GPIO_PORTE_CLK_EN + GPIO_PORTF_CLK_EN);
	
	delay_clk = SYSTCTL_RCGCGPIO_R;
	
//	GPIO_PORTA_DEN_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DEN_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DEN_R |= GPIO_PORTC_PINS_EN;
//	GPIO_PORTD_DEN_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DEN_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PINS_EN;
	
//	GPIO_PORTA_DIR_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DIR_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DIR_R |= GPIO_PORTC_PINS_EN;
//	GPIO_PORTD_DIR_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DIR_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PINS_EN;
}

int main (void)
{
	init_gpio ();
	
	while (1)
	{
		int i,j;
		
		//GPIO_PORTB_DATA_R |= 0xFF;		// 0-7 Layers (Cathodes)
		GPIO_PORTE_DATA_R |= 0x0F;		// 0-3 Rows (Anodes)
		GPIO_PORTC_DATA_R |= 0xF0;		// 4-7 Rows (Anodes)
		GPIO_PORTF_DATA_R &= ~0x10;		// Latch Enable (Active Low)
		for(i=0;i<8;i++)
		{
			GPIO_PORTF_DATA_R = lat[i];
			for(j=0;j<1000;j++);
		}
	//GPIO_PORTF_DATA_R |= (0x2 * i);		// 0-7 Columns (Latch Address)
		/*
		for (i = 0; i < 8; i++)
		{
			GPIO_PORTF_DATA_R |= 0x10;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			GPIO_PORTF_DATA_R &= ~0x10;
			for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
		}
		*/
		
		CubeOn();
		//CubeBlink();
		//LayerTraverseDown ();
		//LayerTraverseUp ();
		//LayerTraverseUpDown ();
		//Convergence();
		//CubeFillDown ();
		//CubeFillUp ();
		//CubeFillEmpty ();
		//LayersHalf ();
	}
}

void CubeOff ()
{
			GPIO_PORTF_DATA_R |= 0x10;
			for (delay_clk = 0; delay_clk < 5*DELAY; delay_clk++);
}

void CubeOn ()
{
			GPIO_PORTB_DATA_R |= 0xFF;
			GPIO_PORTF_DATA_R &= ~0x10;
			for (delay_clk = 0; delay_clk < 5*DELAY; delay_clk++);
}

void CubeBlink ()
{
	GPIO_PORTB_DATA_R |= 0xFF;
	
	for (i = 0; i < 10; i++)
		{
			CubeOff();
			CubeOn();
		}
}

void LayerTraverseDown ()
{
	GPIO_PORTB_DATA_R &= ~0xFF;
	
	for (j = 0; j < 20; j++)
		{
			for (i = 0; i < 8; i++)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
				GPIO_PORTB_DATA_R &= ~layer[i];
			}
		}
}

void LayerTraverseUp ()
{
	for (j = 0; j < 20; j++)
		{
			for (i = 7; i > -1; i--)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
				GPIO_PORTB_DATA_R &= ~layer[i];
			}
		}
}

void LayerTraverseUpDown ()
{
	for (j = 0; j < 20; j++)
		{
			for (i = 0; i < 8; i++)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
				GPIO_PORTB_DATA_R &= ~layer[i];
			}
			
			for (i = 7; i > -1; i--)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
				GPIO_PORTB_DATA_R &= ~layer[i];
			}
		}
}

void CubeFillDown ()
{
	GPIO_PORTB_DATA_R &= ~0xFF;
	
	for (j = 0; j < 10; j++)
		{
			for (i = 0; i < 8; i++)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < 3*DELAY; delay_clk++);
			}
			
			GPIO_PORTB_DATA_R &= ~0xFF;
		}
}

void CubeFillUp ()
{
	GPIO_PORTB_DATA_R &= ~0xFF;
	
	for (j = 0; j < 10; j++)
		{
			for (i = 7; i > -1; i--)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < 3*DELAY; delay_clk++);
			}
			
			GPIO_PORTB_DATA_R &= ~0xFF;
		}
}

void CubeFillEmpty ()
{
	GPIO_PORTB_DATA_R &= ~0xFF;
	
	for (j = 0; j < 10; j++)
		{
			for (i = 0; i < 8; i++)
			{
				GPIO_PORTB_DATA_R |= layer[i];
				for (delay_clk = 0; delay_clk < 3*DELAY; delay_clk++);
			}
			
			for (i = 7; i > -1; i--)
			{
				GPIO_PORTB_DATA_R &= ~layer[i];
				for (delay_clk = 0; delay_clk < 3*DELAY; delay_clk++);
			}
			
			GPIO_PORTB_DATA_R &= ~0xFF;
		}
}

void LayersHalf ()
{
	for (j = 0; j < 20; j++)
		{
			GPIO_PORTB_DATA_R |= 0x0F;
			GPIO_PORTB_DATA_R &= ~0xF0;
			for (delay_clk = 0; delay_clk < 5*DELAY; delay_clk++);
			GPIO_PORTB_DATA_R |= 0xF0;
			GPIO_PORTB_DATA_R &= ~0x0F;
			for (delay_clk = 0; delay_clk < 5*DELAY; delay_clk++);
		}
}

void ROWW()
{
		int i,j,k;
		GPIO_PORTE_DATA_R |= 0x0F;
		GPIO_PORTC_DATA_R	|= 0xF0;
		
		GPIO_PORTB_DATA_R &= ~0xFF;
		for(i=0;i<8;i++){
		
			GPIO_PORTF_DATA_R |= ~(lat[i]);
			
			for(j=0;j<8;j++){
						
			GPIO_PORTB_DATA_R |= layer[j];
			GPIO_PORTE_DATA_R &=	~(layer[0] + layer[2]);
			GPIO_PORTC_DATA_R	&=	~(layer[4] + layer[6]); 
			for(k=0;k<1000;k++);
			
		}
			GPIO_PORTF_DATA_R |= lat[i];
			
	}

}
	void A()
{
	int i,j,k;
	
	GPIO_PORTE_DATA_R	&= ~0x1F;			
	GPIO_PORTC_DATA_R &= ~0xF0;			
	
	for(j=7;j>=0;j++)
	{
		
		GPIO_PORTB_DATA_R &= ~lay[0];
		GPIO_PORTF_DATA_R  = col[j];
		GPIO_PORTE_DATA_R |= (row[2] + row[3]);
		GPIO_PORTC_DATA_R |= (row[4] + row[5]);
		
		for(i=0;i<3;i++){
		GPIO_PORTB_DATA_R &= ~lay[i+1];
		GPIO_PORTE_DATA_R &= ~(row[3]); 
		GPIO_PORTF_DATA_R &= ~(row[4]);
		}
				
		GPIO_PORTB_DATA_R &= ~lay[4];
		GPIO_PORTE_DATA_R |= (row[2] + row[3]);
		GPIO_PORTC_DATA_R |= (row[4] + row[5]);
		
		for(i=0;i<3;i++){
		GPIO_PORTB_DATA_R &= ~lay[i+5];
		GPIO_PORTE_DATA_R &= ~(row[3]); 
		GPIO_PORTF_DATA_R &= ~(row[4]);
		}
		for(k=0;k<100;k++);
	}
}
void Convergence()
{
	GPIO_PORTB_DATA_R &= ~0xFF;
	
	for (j = 0; j < 20; j++)
		{
			for (i = 0; i < 4; i++)
			{
				GPIO_PORTB_DATA_R = layer[i] + layer[7-i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			}
				for (i = 3; i > -1; i--)
			{
				GPIO_PORTB_DATA_R = layer[i] + layer[7-i];
				for (delay_clk = 0; delay_clk < DELAY; delay_clk++);
			}
			
			GPIO_PORTB_DATA_R &= ~0xFF;
		}
}
