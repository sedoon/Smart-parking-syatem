/****************************************************************
 ************  - SPI_config.h			       ******************
 ***********					   		       ******************
 ***********   -Created: 3/15/2021			   ******************
 ***********   -Author:sayed ibrahim     ******************
 ***********   -Version : _1_				   ******************
 ***********								   ******************
 ****************************************************************/ 

/****************************************************************
***********  guard of file will call on time in .c  *************
****************************************************************/

/***************************************************************
****  What Is The Configration Parameter Which User Need    ****

			1 - Clock Phase			2 - Clock Polarity 
			3 - Frequancy			4 - Data Size 
			5 - Data Order			6 -	Mode 
	
**************************************************************/
		
		
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

	

	#define  BUSY_FLAG					7
	
	#define MSP1_STATUS          MSPI_ENABLE

	#define MSPI1_CLOCK_MODE     MSPI_MODE3

	#define MSPI1_MASTER_SLAVE   MSPI_MASTER



	#define MSPI1_DATA_ORDER     MSPI_MSB_FIRST

	#define MSPI1_SS_MANAGE      HW_SLAVE_MANAGEMENT

	#define MSPI1_DATA_SIZE      MSPI_8BIT_DATA

	#define MSPI1_INT_STATUS     MSPI_INT_DISABLE




#endif //SPI_CONFIG_H
