#ifndef	_GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H






void MGPIO_vMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8mode);
void MGPIO_vSETOUTPUTMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8outputmode);
void MGPIO_vSPEEDMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8speedmode);
void MGPIO_vPULLMODE(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8pullmode);
void MGPIO_vWRITE_PIN(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8STATE);
u8   MGPIO_u8READ_PIN(u8 copy_u8port,u8 copy_u8pin);
void MGPIO_vLOCKPIN(u8 copy_u8port,u8 copy_u8pin);
void MGPIO_vALTFUNC(u8 copy_u8port,u8 copy_u8pin,u8 copy_u8alt_func_num);




#define		PORTA			0
#define		PORTB			1
#define		PORTC			2
#define		PORTD			3
#define		PORTE			4
#define		PORTH			5

#define		PIN0			0
#define		PIN1			1
#define		PIN2			2
#define		PIN3			3
#define		PIN4			4
#define		PIN5			5
#define		PIN6			6
#define		PIN7			7
#define		PIN8			8
#define		PIN9			9
#define		PIN10			10
#define		PIN11			11
#define		PIN12			12
#define		PIN13			13
#define		PIN14			14
#define		PIN15			15



#define		INPUT			0
#define		OUTPUT			1
#define		ALT				2
#define		ANALOG			3

#define		PUSH_PULL		0
#define 	OPEN_DRAIN		1

#define		LOW_SPEED		0
#define		MED_SPEED		1
#define		HIGH_SPEED		2
#define		VHIGH_SPEED		3

#define		NO_PULL			0
#define		PULL_DOWN		2
#define		PULL_UP			1

#define 	HIGH			1
#define		LOW				0

#define 	LCK_BIT			16

#define 	AF0				0
#define     AF1             1
#define     AF2             2
#define     AF3             3
#define     AF4             4
#define     AF5             5
#define     AF6             6
#define     AF7             7
#define 	AF8				8
#define     AF9             9
#define     AF10            10
#define     AF11            11
#define     AF12            12
#define     AF13            13
#define     AF14            14
#define     AF15            15


#endif
