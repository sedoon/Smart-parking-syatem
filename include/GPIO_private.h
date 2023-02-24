#ifndef	_GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H



#define GPIOA_BASE_ADDRESS			0x40020000
#define GPIOB_BASE_ADDRESS			0x40020400
#define GPIOC_BASE_ADDRESS			0x40020800
#define GPIOD_BASE_ADDRESS			0x40020C00
#define GPIOE_BASE_ADDRESS			0x40021000
#define GPIOH_BASE_ADDRESS			0x40021C00

typedef struct {
	volatile u32	MODER;
	volatile u32	OTYPER;
	volatile u32	OSPEEDR;
	volatile u32	PUPDR;
	volatile u32	IDR;
	volatile u32	ODR;
	volatile u32	BSRR;
	volatile u32	LCKR;
	volatile u32	AFRL;
	volatile u32	AFRH;
}GPIO_t;


#define GPIOA		((GPIO_t*)(GPIOA_BASE_ADDRESS))
#define GPIOB		((GPIO_t*)(GPIOB_BASE_ADDRESS))
#define GPIOC		((GPIO_t*)(GPIOC_BASE_ADDRESS))
#define GPIOD		((GPIO_t*)(GPIOD_BASE_ADDRESS))
#define GPIOE		((GPIO_t*)(GPIOE_BASE_ADDRESS))
#define GPIOH		((GPIO_t*)(GPIOH_BASE_ADDRESS))



#endif
