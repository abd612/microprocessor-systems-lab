#include "Code3.h"
void SystemInit()
{}

	
	void clock_enable( void ){
		
		SYSCTL_RCGCGPIO_R |= GPIO_PORTALL_CLK_EN ;
	}
	
	volatile unsigned long delay_clk;
	int i;

/*	
const char led [8][8][8] = {	{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},	
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
															{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},	};
	*/
	

const char row[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x02, 0x04};
const char col[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
const char lay[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

															
	void init_gpio (void)
{
	
	SYSCTL_RCGCGPIO_R |= (GPIO_PORTA_CLK_EN + GPIO_PORTB_CLK_EN + GPIO_PORTC_CLK_EN +
												 GPIO_PORTE_CLK_EN + GPIO_PORTF_CLK_EN);
	
	delay_clk = SYSCTL_RCGCGPIO_R;
	
	///GPIO_PORTA_DEN_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DEN_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DEN_R |= GPIO_PORTC_PINS_EN;
	//GPIO_PORTD_DEN_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DEN_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PINS_EN;
	
	//GPIO_PORTA_DIR_R |= GPIO_PORTA_PINS_EN;
	GPIO_PORTB_DIR_R |= GPIO_PORTB_PINS_EN;
	GPIO_PORTC_DIR_R |= GPIO_PORTC_PINS_EN;
	///GPIO_PORTD_DIR_R |= GPIO_PORTD_PINS_EN;
	GPIO_PORTE_DIR_R |= GPIO_PORTE_PINS_EN;
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PINS_EN;
	
	GPIO_PORTB_DATA_R |= 0xFF;			//Layers->Cathods(0-7)
	
	GPIO_PORTE_DATA_R	&= ~0x1F;			//ROWS	->DATA(0-3)
	GPIO_PORTC_DATA_R &= ~0xF0;			///ROWS	->DATA(4-7)
	
	GPIO_PORTF_DATA_R &= ~0x1E;			//LATCHES	->DECODER+Enable(1-4)
	
//	GPIO_PORTA_DATA_R &= ~0x3C;			
	
}
	void FirstLed(){
		
		int i;
		
		GPIO_PORTB_DATA_R &= ~lay[0];	
		GPIO_PORTE_DATA_R |= row[0];
		//GPIO_PORTF_DATA_R |= col[0];
		
	}
	
void All_on( void ){
	int i,j;
	
	for(i=0;i<8;i++){
	
		GPIO_PORTB_DATA_R &= ~lay[i];
		GPIO_PORTE_DATA_R |= row[i];	
		GPIO_PORTA_DATA_R |= col[i];
		
	}	
		for(j=0;j<2;j++)
		GPIO_PORTF_DATA_R |= row[j+6];

}

	void cube_contracting_animation_no_1(void){
		
		GPIO_PORTB_DATA_R &= ~lay[0];
		GPIO_PORTE_DATA_R |= row[0];
		GPIO_PORTA_DATA_R |= col[0];
	
}

int main()
{
		while(1)
		{
				init_gpio();
				FirstLed();
		}
}