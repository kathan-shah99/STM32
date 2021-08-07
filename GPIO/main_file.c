#include "stm32f10x.h"
#include	"_GPIO_LIB.h"


int main() {
/*
	//initialize clock for GPIO-B
	RCC ->APB2ENR  |= (1<<3);
	
	//Configure pin3 on GPIOB
	
	GPIOB -> CRL |= (  (0<<4) | (1<<5)  );  	//OUTPUT 500MHz
	
	GPIOB -> CRL  &=  ~(   (1<<6) | (1<<7)  );  //General purpose OUTPUT (Push-Pull)
	
	*/
	
	
	GPIO_TYPE  myPin;
	
	myPin.port = PORTB;
	myPin.pin = 1;
	myPin.mode_type = OUTPUT_GEN_PURPOSE;
	myPin.mode  = OUTPUT_MODE;
	myPin.speed = SPEED_2MHZ;
	
	GPIO_setup(myPin);
	
	while(1)	
	{
	
		GPIO_write(myPin.port , myPin.pin , 1);
		for(int i = 0; i<500000 ; i++);						//delay
		
		GPIO_Toggle(myPin.port , myPin.pin);
		for(int i = 0; i<500000 ; i++);						//delay
	}
	return 0;
}

