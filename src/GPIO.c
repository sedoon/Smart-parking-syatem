#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"




void MGPIO_vMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8mode)
{
	switch (copy_u8port)
	{
	case PORTA:
		GPIOD->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOA->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	case PORTB:
		GPIOB->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOB->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	case PORTC:
		GPIOC->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOC->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	case PORTD:
		GPIOD->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOD->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	case PORTE:
		GPIOE->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOE->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	case PORTH:
		GPIOH->MODER &=	(u32)~(0b11<<(2*copy_u8pin));
		GPIOH->MODER |=	(u32)(copy_u8mode<<(2*copy_u8pin));
		break;
	default : /* ERROR */break;
	}
}

void MGPIO_vSETOUTPUTMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8outputmode)
{
	switch (copy_u8port)
	{
	case PORTA:
		GPIOA->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	case PORTB:
		GPIOB->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	case PORTC:
		GPIOC->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	case PORTD:
		GPIOD->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	case PORTE:
		GPIOE->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	case PORTH:
		GPIOH->	OTYPER 	|=	(u32)(copy_u8outputmode<<(copy_u8pin));
		break;
	default : /* ERROR */break;
	}
}


void MGPIO_vSPEEDMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8speedmode)
{
	switch (copy_u8port)
	{
	case PORTA:
		GPIOA->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	case PORTB:
		GPIOB->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	case PORTC:
		GPIOC->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	case PORTD:
		GPIOD->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	case PORTE:
		GPIOE->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	case PORTH:
		GPIOH->OSPEEDR |=	(u32)(copy_u8speedmode<<(2*copy_u8pin));
		break;
	default : /* ERROR */break;
	}
}

void MGPIO_vPULLMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8pullmode)
{
	switch (copy_u8port)
	{
	case PORTA:
		GPIOA->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	case PORTB:
		GPIOB->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	case PORTC:
		GPIOC->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	case PORTD:
		GPIOD->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	case PORTE:
		GPIOE->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	case PORTH:
		GPIOH->PUPDR |=	(u32)(copy_u8pullmode<<(2*copy_u8pin));
		break;
	default : /* ERROR */break;
	}
}

u8 MGPIO_u8READ_PIN(u8 copy_u8port,u8 copy_u8pin)
{
	u8 L_u8READ =0;
	switch (copy_u8port)
	{
	case PORTA:
		L_u8READ = GET_BIT(GPIOA->IDR,copy_u8pin);
		break;
	case PORTB:
		L_u8READ = GET_BIT(GPIOB->IDR,copy_u8pin);
		break;
	case PORTC:
		L_u8READ = GET_BIT(GPIOC->IDR,copy_u8pin);
		break;
	case PORTD:
		L_u8READ = GET_BIT(GPIOD->IDR,copy_u8pin);
		break;
	case PORTE:
		L_u8READ = GET_BIT(GPIOE->IDR,copy_u8pin);
		break;
	case PORTH:
		L_u8READ = GET_BIT(GPIOH->IDR,copy_u8pin);
		break;
	default : /* ERROR */break;
	}
	return L_u8READ;
}

void MGPIO_vWRITE_PIN(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8STATE)
{
	switch (copy_u8STATE)
	{
	case HIGH :
		switch (copy_u8port)
		{
		case PORTA:
			GPIOA->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		case PORTB:
			GPIOB->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		case PORTC:
			GPIOC->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		case PORTD:
			GPIOD->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		case PORTE:
			GPIOE->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		case PORTH:
			GPIOH->BSRR =	(u32)(1<<(copy_u8pin));
			break;
		default : /* ERROR */break;
		}
		break;
		case LOW :
			copy_u8pin+=16;
			switch (copy_u8port)
			{
			case PORTA:
				GPIOA->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			case PORTB:
				GPIOB->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			case PORTC:
				GPIOC->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			case PORTD:
				GPIOD->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			case PORTE:
				GPIOE->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			case PORTH:
				GPIOH->BSRR =	(u32)(1<<(copy_u8pin));
				break;
			default : /* ERROR */break;
			}
			break;
			default : /* ERROR */break;
	}
}

void MGPIO_vLOCKPIN(u8 copy_u8port,u8 copy_u8pin)
{
	switch (copy_u8port)
	{
	case PORTA:
		GPIOA->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOA->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOA->LCKR,LCK_BIT)==0);
		break;
	case PORTB:
		GPIOB->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOB->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOB->LCKR,LCK_BIT)==0);
		break;
	case PORTC:
		GPIOC->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOC->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOC->LCKR,LCK_BIT)==0);
		break;
	case PORTD:
		GPIOD->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOD->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOD->LCKR,LCK_BIT)==0);
		break;
	case PORTE:
		GPIOE->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOE->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOE->LCKR,LCK_BIT)==0);
		break;
	case PORTH:
		GPIOH->LCKR |=	(u32)(1<<(copy_u8pin));
		GPIOH->LCKR |=	(u32)(1<<(LCK_BIT));
		while (GET_BIT(GPIOH->LCKR,LCK_BIT)==0);
		break;
	default : /* ERROR */break;
	}
}

void MGPIO_vALTFUNC(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8alt_func_num)
{
	if(copy_u8pin<8)
	{
		switch (copy_u8port)
		{
		case PORTA:
			GPIOA->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTB:
			GPIOB->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTC:
			GPIOC->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTD:
			GPIOD->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTE:
			GPIOE->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTH:
			GPIOH->AFRL |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		default : /* ERROR */break;
		}
	}
	else if (copy_u8pin<16)
	{
		copy_u8pin -= 8;
		switch (copy_u8port)
		{
		case PORTA:
			GPIOA->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTB:
			GPIOB->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTC:
			GPIOC->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTD:
			GPIOD->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTE:
			GPIOE->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		case PORTH:
			GPIOH->AFRH |=	(u32)(copy_u8alt_func_num<<(4*copy_u8pin));
			break;
		default : /* ERROR */break;
		}
	}
}



