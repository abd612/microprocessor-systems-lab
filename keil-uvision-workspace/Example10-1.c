// R e g i s t e r d e f i n i t i o n s f o r c l o c k enable
 #define SYSCTL_RCGCGPIO_R ( * ( ( volatile unsigned long *) 0x400FE608 ) )
 #define SYSCTL_RCGCADC_R ( * ( ( volatile unsigned long *) 0x400FE638 ) )

// R e g i s t e r d e f i n i t i o n s f o r GPIO port A
 #define GPIO_PORTA_DATA_R ( * ( ( volatile unsigned long *) 0x400043FC ) )
 #define GPIO_PORTA_DIR_R ( * ( ( volatile unsigned long *) 0x40004400 ) )
 #define GPIO_PORTA_DEN_R ( * ( ( volatile unsigned long *) 0x4000451C ) )

 // R e g i s t e r d e f i n i t i o n s f o r GPIO port B
 #define GPIO_PORTB_DATA_R ( * ( ( volatile unsigned long *) 0x400053FC ) )
 #define GPIO_PORTB_DIR_R ( * ( ( volatile unsigned long *) 0x40005400 ) )
 #define GPIO_PORTB_DEN_R ( * ( ( volatile unsigned long *) 0x4000551C ) )

 // R e g i s t e r d e f i n i t i o n s f o r GPIO port F
 #define GPIO_PORTF_DATA_R ( * ( ( volatile unsigned long *) 0x400253FC ) )
 #define GPIO_PORTF_DIR_R ( * ( ( volatile unsigned long *) 0x40025400 ) )
 #define GPIO_PORTF_DEN_R ( * ( ( volatile unsigned long *) 0x4002551C ) )

 // R e g i s t e r d e f i n i t i o n s f o r ADC0 and Sample Sequencer 3
 #define ADC0_PC_R ( * ( ( volatile unsigned long *) 0x40038FC4 ) )
 #define ADC0_SSPRI_R ( * ( ( volatile unsigned long *) 0x40038020 ) )
 #define ADC0_ACTSS_R ( * ( ( volatile unsigned long *) 0x40038000 ) )
 #define ADC0_IM_R ( * ( ( volatile unsigned long *) 0x40038008 ) )
 #define ADC0_RIS_R ( * ( ( volatile unsigned long *) 0x40038004 ) )
 #define ADC0_ISC_R ( * ( ( volatile unsigned long *) 0x4003800C ) )
 #define ADC0_SAC_R ( * ( ( volatile unsigned long *) 0x40038030 ) )
 #define ADC0_PSSI_R ( * ( ( volatile unsigned long *) 0x40038028 ) )
 #define ADC0_SSCTL3_R ( * ( ( volatile unsigned long *) 0x400380A4 ) )
 #define ADC0_SSFIFO3_R ( * ( ( volatile unsigned long *) 0x400380A8 ) )

 unsigned char Lookup_7Seg_Disp [ 12 ] = {0xC0 , 0xF9 , 0xA4 , 0xB0 , 0x99 ,
 0x92 , 0x82 , 0xF8 , 0x80 , 0x90 , 0xC6 } ;
 unsigned char Temperature_Value [ 3 ] = {0 , 0 , 0xA} ;
 unsigned char i , value =0;
 unsigned int ADC_value = 0 , temperature = 0 ;

 void ADC_Init ( ) {

 volatile unsigned long delay ;

 // Enable c l o c k

 // Enable c l o c k f o r GPIO port A,B and F [ pg . 314]
 SYSCTL_RCGCGPIO_R |= 0x23 ;
 // Enable c l o c k f o r ADC0 [ pg . 326]
 SYSCTL_RCGCADC_R |= 0x01 ;
 // Delay f o r c l o c k s i g n a l to s e t t l e down
 delay = SYSCTL_RCGCADC_R;

 //GPIO A, B, F enable

 // Set the l a t c h enable pins o f 7 segment as output [ pg . 622]
 GPIO_PORTA_DIR_R |= 0x38 ;
 // Set the d i g i t a l o p e r a t i o n f o r GPIO port A [ pg . 641]
 GPIO_PORTA_DEN_R |= 0x38 ;

 GPIO_PORTB_DIR_R |= 0xFF ;
 GPIO_PORTB_DEN_R |= 0xFF ;
 GPIO_PORTB_DATA_R |= 0xFF ;

 GPIO_PORTF_DIR_R |= 0x08 ;
 GPIO_PORTF_DEN_R |= 0x08 ;

 GPIO_PORTF_DATA_R |= 0x08 ;

 //ADC0 c o n f i g u r e

 // Clear the sample r a t e [ pg . 847]
 ADC0_PC_R &= 0x00 ;
 // Set sample r a t e equal to 125 ksps
 ADC0_PC_R |= 0x01 ;
 // Set the p r i o r i t y o f sample s e q u e n c e r s .
 // Sample sequence 0 has h i g h e s t and SS3 has lowest p r i o r i t y [ pg . 798]
 ADC0_SSPRI_R |= 0x3210 ;
 // Disable sample sequence 3 b e f o r c o n f i g u r a t i o n [ pg . 780]
 ADC0_ACTSS_R &= ~0x08;
 //ADC0_ACTSS_R &= ˜0x08 ;
 // Enable TS0 , IE0 and END0 b i t s [ pg . 833]
 ADC0_SSCTL3_R |= 0x0E ;
 // Enable 16x hardware oversampling [ pg . 804]
 ADC0_SAC_R |= 0x4 ;
 // Disable I n t e r r u p t by w r i t i n g 0 to corresponding b i t [ pg . 784]
ADC0_IM_R &= ~0x08;
//ADC0_IM_R &= ˜     ~0x08
 // Activate sample sequencer
 ADC0_ACTSS_R |= 0x08 ;

 }

 void ADC_Temperature ( void ) {

 // Software t r i g g e r [ pg . 802]
 ADC0_PSSI_R |= 0x08 ;

 // P o l l the s t a t u s o f corresponding RIS b i t to wait
 // f o r the end o f c o n v e r s i o n [ pg . 782]
 while ( ( ADC0_RIS_R & 0x08 )==0) ;
 // After c o n v e r s i o n f e t c h the data from the FIFO [ pg . 817]
 ADC_value = (ADC0_SSFIFO3_R & 0xFFF) ;
 // C a l c u l a t e the value o f temperature [ pg . 771]
 temperature = ( unsigned char ) ( 147.5 - ( ADC_value * 3.3* 75 ) /4096) ;

 Temperature_Value [ 1 ] = temperature %10;
 Temperature_Value [ 0 ] = temperature /10;

 // Clear RIS to s t a r t c o v e r s i o n again [ pg . 787]
 ADC0_ISC_R |= 0x08 ;
 }

 // Function to i n t r o d u c e delay
 void Delay ( unsigned long count ) {
 int i ;
 for ( i = 0 ; i < count ; i++)
 { }
 }

 int main ( ) {

 // I n i t i a l i z e ADC and GPIO p o r t s f o r seven segment d i s p l a y
 ADC_Init ( ) ;

 while ( 1 )
 {
 for ( i = 0 ; i <= 2 ; i++)
 {
 value = Temperature_Value [2- i ] ;
 GPIO_PORTB_DATA_R = Lookup_7Seg_Disp [ value ] ;

 // S e l e c t the d i g i t on Port A
 GPIO_PORTA_DATA_R = (0x38 - (1 << ( i +3) ) ) ;
 Delay (1000) ;
 }
 ADC_Temperature ( ) ;
 }
 }