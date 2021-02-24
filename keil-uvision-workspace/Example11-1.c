// Register definitions for Clock Enable
#define SYSCTL_RCGCUART_R 					( *((volatile unsigned long *) 0x400FE618))
#define SYSCTL_RCGCGPIO_R 					( *((volatile unsigned long *) 0x400FE608))
// Register definitions for GPIO PortD
#define GPIO_PORTD_AFSEL_R 					( *((volatile unsigned long *) 0x40007420))
#define GPIO_PORTD_PCTL_R 					( *((volatile unsigned long *) 0x4000752C))
#define GPIO_PORTD_DEN_R 						( *((volatile unsigned long *) 0x4000751C))
#define GPIO_PORTD_DIR_R 						( *((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_LOCK_R 					( *((volatile unsigned long *) 0x40007520))
#define GPIO_PORTD_CR_R 						( *((volatile unsigned long *)0x40007524))
	
//Register definitions for UART2 module
#define UART2_CTL_R 								(*((volatile unsigned long *)0x4000E030))
#define UART2_IBRD_R 								(*((volatile unsigned long *)0x4000E024))
#define UART2_FBRD_R 								(*((volatile unsigned long *)0x4000E028))
#define UART2_LCRH_R 								(*((volatile unsigned long *)0x4000E02C))
#define UART2_CC_R 									(*((volatile unsigned long *)0x4000EFC8))
#define UART2_FR_R 									(*((volatile unsigned long *)0x4000E018))
#define UART2_DR_R 									(*((volatile unsigned long *)0x4000E000))

//Macros for initialization and configuration of UART2
#define UART2_CLK_EN            0x00000004        //EnableclockforUART2
#define GPIO_PORTD_CLK_EN   		0x00000008    		//EnableclockforGPIOPORTD

#define GPIO_PORTD_UART2_CFG    0x000000C0				//Digitalenable
																									//Activate alternate function for PD6 and PD7
#define GPIO_PCTL_PD6_U2RX      0x01000000				//ConfigurePD6asU2RX
#define GPIO_PCTL_PD7_U2TX      0x10000000				//ConfigurePD7asU2TX
#define GPIO_PORTD_UNLOCK_CR    0x4C4F434B				//UnlockCommitregister
#define GPIO_PORTD_CR_EN        0x000000FF				//Disablewriteprotection

#define UART_CS_SysClk					0x00000000				//UsesystemasUARTclock
#define UART_CS_PIOSC						0x00000005				//UsePIOSCasUARTclock
#define UART_LCRH_WLEN_8				0x00000060				//8bitwordlength
#define UART_LCRH_FEN						0x00000010				//EnableUARTFIFOs
#define UART_FR_TXFF						0x00000020				//UARTTransmitFIFOFull
#define UART_FR_RXFE						0x00000010				//UARTReceiveFIFOEmpty
#define UART_CTL_UARTEN					0x00000001				//EnableUART
#define UART_LB_EN							0x00000080				//UseUARTinLoopbackmode

// Function definitions
unsigned char UART_Rx( void ) ;
void UART_Tx( unsigned char data ) ;
void UART_Tx_String ( char *pt ) ;
void UART_Rx_String ( char *bufPt , unsigned short max) ;

//Intialize and configure UART
void UART_Init ( void ) {

	// Enable clock for UART2 and GPIO Port D
	SYSCTL_RCGCUART_R |= UART2_CLK_EN; 								// Activate UART2
	SYSCTL_RCGCGPIO_R |= GPIO_PORTD_CLK_EN; 					// Activate Port D

	// Configuration to use PD6 and PD7 as UART
	GPIO_PORTD_LOCK_R = GPIO_PORTD_UNLOCK_CR; 				// Unlock commit register
	GPIO_PORTD_CR_R |= GPIO_PORTD_CR_EN; 							// Enable U2Tx on PD7
		
	GPIO_PORTD_DEN_R |= GPIO_PORTD_UART2_CFG; 				// Enable digital I /O on PD6-7
	GPIO_PORTD_AFSEL_R |= GPIO_PORTD_UART2_CFG;    		// Enable alt . func . on PD6??7
	GPIO_PORTD_PCTL_R |= (GPIO_PCTL_PD6_U2RX | GPIO_PCTL_PD7_U2TX) ;

	// Configuration of UART2 module
	UART2_CTL_R &= ~UART_CTL_UARTEN; 									// Disable UART
	// IBRD = int (16,000,000/(16*115,200))=int(8.6805)
	UART2_IBRD_R = 8 ;
	// FBRD=int(0.6805*64+0.5)=44
	UART2_FBRD_R = 44 ;
	// 8-bit word length , no parity bit , one stop bit , FIFOs enable
	UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN) ;
	UART2_CC_R = UART_CS_SysClk ; 										// Use system clock as UART clock
	//UART2_CTL_R |= UART_LB_EN; 											// Enable loopback mode
	UART2_CTL_R |= UART_CTL_UARTEN; 									// Enable UART2
}

// Wait for input and returns its ASCII value
unsigned char UART_Rx( void ) {
	while ( (UART2_FR_R & UART_FR_RXFE) != 0) ;
	return ( ( unsigned char ) (UART2_DR_R & 0xFF) ) ;
}

/* Accepts ASCII characters from the serial port and
adds them to a string . It echoes each character as it
is inputted . */
void UART_Rx_String ( char *pt , unsigned short max) {
	int length=0;
	char character ;

	character = UART_Rx( ) ;
	if ( length < max) {
		*pt = character ;
		pt++;
		length++;
		UART_Tx( character +4 ) ;
	}
	*pt = 0 ;
}

// Output 8-bit to serial port
void UART_Tx( unsigned char data ) {
	while ( (UART2_FR_R & UART_FR_TXFF) != 0) ;
	UART2_DR_R = data ;
}

// Output a character string to serial port
void UART_Tx_String ( char *pt ) {
	while (*pt ) {
		UART_Tx(*pt ) ;
		pt++;
	}
}

int main ( void ) {
	char string [ 17 ] ;
	UART_Init ( ) ;
	// The input given using keyboard is displayed on hyperterminal
	// .i.e. , data is echoed
	UART_Tx_String ("Hey, I just met you, an this is crazy!") ;

	while ( 1 ) {
		UART_Rx_String ( string , 16);
	}
}