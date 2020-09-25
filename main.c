/*
 * IIA Final Implementation.c
 *
 * ENG. AHMED TALAL
* MASTER DEGREE THESIS
* BIOMEDICAL ENGINEERING
* ISTANBUL UNIVERSITY, FACULTY OF ENGINNEERING
*
*			FINAL IMPLEMENTATION CODE
*/

#include <avr/io.h>			/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/
#define F_CPU 8000000		/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/
#include <util/delay.h>		/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/
#include <stdio.h>
#include <stdlib.h>			/*Includes stdlib.h header file which defines different standard library functions.*/
#include <avr/interrupt.h>

#define degree_sysmbol 0x00, 0x05, 0x03, 0x00, 0x00
#define DHT11_PIN 2

extern const unsigned char Logo[];
extern const unsigned char IIA[];
extern const unsigned char face[];

void adc_init(void);								/*ADC Function Declarations*/
int read_adc(unsigned char channel);
uint8_t Receive_data();
uint8_t c=0,I_RH,A_RH,I_Temp,A_Temp,CheckSum,celsius,dB;

	char adcResult[4];
	



int main(void)
{
//	adc_init();									/*ADC initialization*/
	GLCD_Init();								/*LCD Initialization*/
	

	
	GLCD_Imig(Logo);
	_delay_ms(2000);
	
	GLCD_ClearAll();
	GLCD_Imig(IIA);
	_delay_ms(3000);
	
	GLCD_ClearAll();
	GLCD_String(3," READING PARAMETERS!");
	GLCD_String(4," .");
	_delay_ms(500);
	GLCD_String(4," ..");
	_delay_ms(500);
	GLCD_String(4," ...");
	_delay_ms(500);
	GLCD_String(4," ....");
	_delay_ms(500);
	GLCD_String(4," .....");
	_delay_ms(500);
	GLCD_String(4," ......");
	_delay_ms(500);
	GLCD_String(4," .......");
	_delay_ms(500);
	GLCD_String(4," ........");
	_delay_ms(500);
	GLCD_String(4," .........");
	_delay_ms(500);
	GLCD_String(4," ..........");
	_delay_ms(500);
	GLCD_String(4," ............");
	_delay_ms(500);
	GLCD_String(4," .............");
	_delay_ms(500);
	GLCD_String(4," ..............");
	_delay_ms(500);
	GLCD_String(4," ...............");
	_delay_ms(500);
	GLCD_String(4," ................");
	_delay_ms(500);
	GLCD_String(4," .................");
	_delay_ms(500);
	GLCD_String(4," ..................");
	_delay_ms(500);
	GLCD_String(4," ...................");
	_delay_ms(500);
	GLCD_String(4," ....................");
	_delay_ms(500);
	
	GLCD_ClearAll();
	
	GLCD_String(3," READING PARAMETERS!");
	GLCD_String(4," .");
	_delay_ms(500);
	GLCD_String(4," ..");
	_delay_ms(500);
	GLCD_String(4," ...");
	_delay_ms(500);
	GLCD_String(4," ....");
	_delay_ms(500);
	GLCD_String(4," .....");
	_delay_ms(500);
	GLCD_String(4," ......");
	_delay_ms(500);
	GLCD_String(4," .......");
	_delay_ms(500);
	GLCD_String(4," ........");
	_delay_ms(500);
	GLCD_String(4," .........");
	_delay_ms(500);
	GLCD_String(4," ..........");
	_delay_ms(500);
	GLCD_String(4," ............");
	_delay_ms(500);
	GLCD_String(4," .............");
	_delay_ms(500);
	GLCD_String(4," ..............");
	_delay_ms(500);
	GLCD_String(4," ...............");
	_delay_ms(500);
	GLCD_String(4," ................");
	_delay_ms(500);
	GLCD_String(4," .................");
	_delay_ms(500);
	GLCD_String(4," ..................");
	_delay_ms(500);
	GLCD_String(4," ...................");
	_delay_ms(500);
	GLCD_String(4," ....................");
	_delay_ms(500);
		
	GLCD_ClearAll();
	GLCD_Imig(face);
	
	
		 
	GLCD_String(0,"  AHMEDTALAL  Ist.Uni");
	GLCD_String(2,"          Temp1 ");
	GLCD_String(3,"          Temp2 ");
	GLCD_String(4,"          R.H ");
	GLCD_String(5,"          S.Noise");
	_delay_ms(500);

	
	DDRA = 0x00;							        /* Make ADC port as input */
	ADCSRA = 0x87;									/* Enable ADC, with freq/128  */
	ADMUX = 0x40;									/* Vref: Avcc, ADC channel: 0 */
	ADCSRA |= 1<<ADPS2;
	//ADMUX |= 1<<ADLAR;
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	sei();
	ADCSRA |= 1<<ADSC;

/*Start of infinite loop*/
while(1)
{
	
}
return 0;
}
/*End of Program*/

void Request()							/* Microcontroller send start pulse/request */
{
	DDRA |= (1<<DHT11_PIN);
	PORTA &= ~(1<<DHT11_PIN);			/* set to low pin */
	_delay_ms(20);						/* wait for 20ms */
	PORTA |= (1<<DHT11_PIN);			/* set to high pin */
}

void Response()							/* receive response from DHT11 */
{
	DDRA &= ~(1<<DHT11_PIN);
	while(PINA & (1<<DHT11_PIN));
	while((PINA & (1<<DHT11_PIN))==0);
	while(PINA & (1<<DHT11_PIN));
}

uint8_t Receive_data()			/* receive data */
{
	for (int q=0; q<8; q++)
	{
		while((PINA & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(PINA & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PINA & (1<<DHT11_PIN));
	}
	return c;
}


int read_adc(unsigned char channel)
{
	ADMUX = 0x40 | (channel & 0x07);				/* set input channel to read */
	ADCSRA |= (1<<ADSC);							/* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));					/* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);							/* Clear interrupt flag */
	_delay_ms(1);									/* Wait a little bit */
	return ADCW;									/* Return ADC word */
}

ISR(ADC_vect)
{
	uint8_t theLOW = ADCL;
	uint16_t tenBitValue = ADCH << 8 | theLOW;
	
	char data[5];
	char Temperature[10];
	float celsius;
	
	Request();		/* send start pulse */
	Response();		/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	A_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	A_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data(); /* store next eight bit in CheckSum */
	celsius = (read_adc(1)*4.88);
	celsius = (celsius/10.00);
	sprintf(Temperature,"%d%c`C  ", (int)celsius,0);               /* convert integer value to ASCII string */
	GLCD_String(2,"    `C");
	GLCD_Command(0x40);
	GLCD_String(2,Temperature);                /* send string data for printing */
	memset(Temperature,0,10);
	_delay_ms(1000);
	
	itoa(I_RH,data,10);
	GLCD_Command(0x40);
	GLCD_String(4,data);
	GLCD_Command(0x4C);
	GLCD_String(4,".");
	
	itoa(A_RH,data,10);
	GLCD_Command(0x51);
	GLCD_String(4,data);
	GLCD_Command(0x5A);
	GLCD_String(4,"%");

	itoa(I_Temp,data,10);
	GLCD_Command(0x40);
	GLCD_String(3,data);
	
	GLCD_String(3,data);
	GLCD_Command(0x4F);
	GLCD_String(3," `C");
	
	
	GLCD_String(5,"    dB");
	itoa(tenBitValue/2.744681,adcResult, 10);
	GLCD_Command(0x40);
	GLCD_String(5,adcResult);
	
	
	ADCSRA |= 1<<ADSC;
	

}
