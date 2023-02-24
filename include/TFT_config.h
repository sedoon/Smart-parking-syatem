
#ifndef TFT_CONFIG_H
#define TFT_CONFIG_H

/*	Write Pin In Pair Port , Pin  */
#define  TFT_DC_PIN			PORTB,PIN9
/*
	SPI_Config_TFT :
			config of SPI 
			MSPI1_t-> CR1 = 0x0347 ;
			Clock Ideal High `	   -------	Clock Polarity = 1
			With full Master Write -------	Clock Phase    = 1
			Need Mosst Significant -------  LSB Frist      = 0
			BR		---------------------------------	   = 000


*/
#define TFT_RESEAT_PIN		PORTB,PIN1


#endif //TFT_CONFIG_H
