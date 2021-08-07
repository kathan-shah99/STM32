#include	"_GPIO_LIB.h"
#include "stdint.h"


uint32_t PIN_POSITION[16] = {
	(0X00),		//0th pin - 0th bit start (4 bit offset)
	(0X04),		//1st pin - 4th bit start  (0 + 4 = 4 )
	(0X08),
	(0X0C),
	(0X10),
	(0X14),
	(0X18),		//6th pin - 24th bit start in CRL
	(0X1C),		//7th pin - 28th bit start in CRL
	(0X00),		//8th Pin - 0th bit start in CRH
	(0X04),		//9th pin - 4th bit start in CRH
	(0X08),		
	(0X0C),
	(0X10),
	(0X14),
	(0X18),
	(0X1C)		//15th Pin
};

static void config_pin(GPIO_TypeDef *PORT , uint32_t pin_number , uint32_t mode_type)
{
	
	if(pin_number >= 8)	//Control High Register
	{
		switch(mode_type)
		{
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
								PORT->CRH &=   ~((1<<CNF_POS_BIT1) | (1<<CNF_POS_BIT2));
				break;
		
			case OUTPUT_GEN_PURPOSE_OD | INPUT_FLOATING:
				PORT->CRH &= ~(1<<CNF_POS_BIT2);
				PORT->CRH |= (1<<CNF_POS_BIT1);
				break;
		
			case OUTPUT_ALT_FUNC_PUPL | INPUT_PU_PD:
					//PORT->CRH |= (1<<CNF_POS_BIT1)
					//PORT->CRH &= ~(1<<CNF_POS_BT2)
					PORT->CRH |= (OUTPUT_ALT_FUNC_PUPL<<CNF_POS_BIT1);
				break;
		
			case OUTPUT_ALT_FUNC_OD:
					//PORT->CRH |= (1<<CNF_POS_BIT1)
					//PORT->CRH |= ~(1<<CNF_POS_BT2)
					PORT->CRH |= (OUTPUT_ALT_FUNC_OD<<CNF_POS_BIT1);
					break;
		}
	}
	else
	{
	switch(mode_type)		//Control Low Register
		{
		
		case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
				PORT->CRL &=   ~((1<<CNF_POS_BIT1) | (1<<CNF_POS_BIT2));
				break;
		
		case OUTPUT_GEN_PURPOSE_OD | INPUT_FLOATING:
				PORT->CRL &= ~(1<<CNF_POS_BIT2);
				PORT->CRL |= (1<<CNF_POS_BIT1);
				break;
		
		case OUTPUT_ALT_FUNC_PUPL | INPUT_PU_PD:
				//PORT->CRL |= (1<<CNF_POS_BIT1)
				//PORT->CRL &= ~(1<<CNF_POS_BT2)
				PORT->CRL |= (OUTPUT_ALT_FUNC_PUPL<<CNF_POS_BIT1);
				break;
		
		case OUTPUT_ALT_FUNC_OD:
				//PORT->CRL |= (1<<CNF_POS_BIT1)
				//PORT->CRL |= ~(1<<CNF_POS_BT2)
				PORT->CRL |= (OUTPUT_ALT_FUNC_OD<<CNF_POS_BIT1);
				break;
		}
		}
	}

static void config_pin_speed(GPIO_TypeDef *PORT , uint32_t pin_number , uint32_t pin_speed,  uint32_t pin_mode)
{

	if(pin_number >= 8)		//Control High Register speed Setting
	{
		if(pin_mode == INPUT_MODE)
			PORT->CRH &= ~((1<<PIN_POSITION[pin_number]) | (1<<(PIN_POSITION[pin_number+1])));
		else
			PORT->CRH |= (pin_speed << (PIN_POSITION[pin_number]));
	
	}
	else				//Control Low Register
	{
	if(pin_mode == INPUT_MODE)
		PORT->CRL &= ~((1<<PIN_POSITION[pin_number]) | (1<<(PIN_POSITION[pin_number+1])));
	else
		PORT->CRL |= (pin_speed << (PIN_POSITION[pin_number]));
	}
}
	

void GPIO_write(GPIO_TypeDef *GPIO , uint32_t pin_number , uint32_t state)
{
	if(state)
		GPIO->BSRR  = (1 << pin_number);
	else
		GPIO->BSRR  = (1<< (pin_number+16));
}

void GPIO_Toggle(GPIO_TypeDef *GPIO , uint32_t pin_number )
{
	GPIO->ODR ^= (1<< pin_number);
}


void GPIO_setup(GPIO_TYPE gpio_type)
{
	if (gpio_type.port == PORTA)
	GPIO_CLK_ENABLE_PORT_A;
	
	if (gpio_type.port == PORTB)
	GPIO_CLK_ENABLE_PORT_B;
	
	if (gpio_type.port == PORTC)
	GPIO_CLK_ENABLE_PORT_C;
	
	config_pin(gpio_type.port , gpio_type.pin , gpio_type.mode_type);
	
	config_pin_speed(gpio_type.port, gpio_type.pin , gpio_type.speed , gpio_type.mode);
	
	
}


