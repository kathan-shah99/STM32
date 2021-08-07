#ifndef	_GPIO_LIB
#define  _GPIO_LIB


#include "stm32f10x.h"

//PORT name
#define PORTA 	GPIOA
#define PORTB 	GPIOB
#define PORTC 		GPIOC

//PIN MODE
#define OUTPUT_MODE 						((uint32_t) 0x01)
#define INPUT_MODE 							((uint32_t) 0x02)

//INPUT MODE CONFIG TYPE
#define INPUT_ANALOG						((uint32_t) 0x00)	//Analog mode
#define INPUT_FLOATING					((uint32_t) 0x01)  	//Default as reset
#define INPUT_PU_PD							((uint32_t) 0x02 )	//Input with Pull up / Pull Down


//OUTPUT MODE CONFIG TYPE
#define OUTPUT_GEN_PURPOSE									((uint32_t) 0x00)	//GP output with Pull up/Pull Down
#define OUTPUT_GEN_PURPOSE_OD					((uint32_t) 0x01)  	//GP output with Open/Drain
#define OUTPUT_ALT_FUNC_PUPL								((uint32_t) 0x02)	//AF output with Pull up/Pull Down
#define OUTPUT_ALT_FUNC_OD									((uint32_t) 0x03)	//AF output with Open/Drain


//OUTPUT MODES Speeds

#define SPEED_10MHZ					((uint32_t) 0x01)	//output mode max clock 10 MHz 
#define SPEED_2MHZ						((uint32_t) 0x02)	//output mode max clock 2 MHz 
#define SPEED_50MHZ					((uint32_t) 0x03)	//output mode max clock 50 MHz 




//Clock Enabling

#define GPIO_CLK_ENABLE_ALT_FUNC					(RCC->APB2ENR |= (1<<0))
#define GPIO_CLK_ENABLE_PORT_A							(RCC->APB2ENR |= (1<<2))
#define GPIO_CLK_ENABLE_PORT_B							(RCC->APB2ENR |= (1<<3))
#define GPIO_CLK_ENABLE_PORT_C							(RCC->APB2ENR |= (1<<4))


//HIGH SET POSTIONS FOR CRH REGISTER CNFY & MODE
#define CNF_POS_BIT1	(PIN_POSITION[pin_number + 2])
#define CNF_POS_BIT2	(PIN_POSITION[pin_number + 3])


//Config Structure

typedef struct
{

	GPIO_TypeDef *port;
	
	uint32_t pin;
	
	uint32_t mode;
	
	uint32_t mode_type;
	
	uint32_t pull;
	
	uint32_t speed;
	
	uint32_t alt_func;

	
}GPIO_TYPE;




//Functions Declaration
//*****************************************************************
static void config_pin(GPIO_TypeDef *PORT , uint32_t pin_number , uint32_t mode_type);


static void config_pin_speed(GPIO_TypeDef *PORT , uint32_t pinnumber , uint32_t speed,  uint32_t mode);

void GPIO_write(GPIO_TypeDef *GPIO , uint32_t pin_number , uint32_t state);

void GPIO_Toggle(GPIO_TypeDef *GPIO , uint32_t pin_number );

void GPIO_setup(GPIO_TYPE gpio_type);

#endif

