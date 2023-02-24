/*
 ============================================================================
 Name        : TFT_program.c
 Author      : Sayed ibrahim
 Version     : V.1
 ============================================================================
 */

/************** INCLUDE LIB **************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/************** INCLUDE MCAL**************/
#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"
/************** INCLUDE HCAL**************/
#include "TFT_private.h"
#include "TFT_interface.h"
#include "TFT_config.h"



/******************************************* Start_FUNCTION  *******************************************/
/*	For Init TFT  :

			-	Resat Puls (High 100 micro & Low 1 micro & high 100 micro & low 100 micro & 120 Melay high and stil high )
			-	Sleep Out 0x11
			-	Wait 150 Ms
			-	Color mode And Select The Option(Parameter)From ( 444 (0x03), 365(0x05) , 666(0x06) )  Send Option as Data Not Command 
			-	Display On TFT 0X29

 */

void HTFT_voidInit(void)
{
	/*	Resat Puls  */

	MGPIO_vWRITE_PIN(TFT_RESEAT_PIN, HIGH) ;
	MSTK_vBusyWait(100);
	MGPIO_vWRITE_PIN(TFT_RESEAT_PIN, LOW)  ;
	MSTK_vBusyWait(1);
	MGPIO_vWRITE_PIN(TFT_RESEAT_PIN, HIGH) ;
	MSTK_vBusyWait(100);
	MGPIO_vWRITE_PIN(TFT_RESEAT_PIN, LOW)  ;
	MSTK_vBusyWait(100);
	MGPIO_vWRITE_PIN(TFT_RESEAT_PIN, HIGH) ;
	MSTK_vBusyWait(120000);

	/*		Sleep Out Command		*/
	voidWriteCommand(0x11)						;
	MSTK_vBusyWait(150000)					;

	/*		Color Mode Command		*/
	voidWriteCommand(0x3A)						;
	voidWriteData(0x05)							;

	/*		Display On Command		*/
	voidWriteCommand(0x29)						;
}
/*******************************************  END_ FUNCTION  *******************************************/

/*******************************************************************************************************/

/******************************************* Start_FUNCTION  *******************************************/

void HTFT_voidDrawCar(u8 X_0,u8 X_1,u16 Y_0,u16 Y_1, u16*Copy_Image)
{
	u32 Counter ;
	// u8 Y_0_LEFT  = Y_0 >> 8;
	// u8 Y_0_RIGHT = Y_0 & 0x00ff;
	/*	SET SIZE X,Y  */
	u32 Local_u32Size =( X_1 - X_0 ) * ( Y_1 - Y_0 ) ;
	/*	Set X_ADRESS Start X_0 End X_1*/
	voidWriteCommand(0x2A);
	/* Start = 00*/
	voidWriteData(0);
	voidWriteData(X_0);
	/* End = 239*/
	voidWriteData(0);
	voidWriteData(X_1);


	/*	Set Y_ADRESS Start Y_0 End Y_1 */
	voidWriteCommand(0x2B);
	/* Start = 00*/
	voidWriteData(Y_0 >> 8);
	voidWriteData(Y_0 & 0x00ff);
	/* End = 319*/
	voidWriteData(Y_1 >> 8);
	voidWriteData(Y_1 & 0x00ff);

	/* RAM Write Command Every thing is coming After This Command Display on TFT*/
	voidWriteCommand(0x2C);
	for(Counter = 0 ; Counter < Local_u32Size ; Counter ++)
	{
		/* Write For One Pixel The High Byte Then Low Byte For Each Pixel */
		/* Write The High Byte */
		voidWriteData(Copy_Image[Counter] >> 8);
		/* Write The LOW Byte */
		voidWriteData(Copy_Image[Counter] & 0x00ff);
	}
}


/*******************************************  END_ FUNCTION  *******************************************/

/*******************************************************************************************************/

/******************************************* Start_FUNCTION  *******************************************/

/* static  : Beacuse It Private No One Can Call it Out Of Moduel */
void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp ;			// SPI Resive Data here No Recive So Don't Care

	/* Set A0	Pin to Low	*/
	MGPIO_vWRITE_PIN(TFT_DC_PIN , LOW) ;

	/* Send Command Over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Command ,  &Local_u8Temp );

}
/*******************************************  END_ FUNCTION  *******************************************/

/*******************************************************************************************************/

/******************************************* Start_FUNCTION  *******************************************/

/* static  : Beacuse It Private No One Can Call it Out Of Moduel */
void voidWriteData(u8 Copy_u8Data)
{

	u8 Local_u8Temp ;			// SPI Resive Data here No Recive So Don't Care
	/* Set A0	Pin to High	*/
	MGPIO_vWRITE_PIN(TFT_DC_PIN , HIGH) ;

	/* Send DATA Over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Data , &Local_u8Temp );

}
/*******************************************  END_ FUNCTION  *******************************************/
/*******************************************************************************************************/
/******************************************* Start_FUNCTION  *******************************************/

void HTFT_voidFillColor( u16 Copy_u16Color)
{
	u16 Counter ;
	/*	SET SIZE X,Y  */

	/*	Set X_ADRESS Start 0 End 127*/
	voidWriteCommand(0x2A);
	/* Start = 00*/
	voidWriteData(0);
	voidWriteData(0);
	/* Start = 127*/
	voidWriteData(0);
	voidWriteData(127);


	/*	Set Y_ADRESS Start 0 End 159*/
	voidWriteCommand(0x2B);
	/* Start = 00*/
	voidWriteData(0);
	voidWriteData(0);
	/* Start = 127*/
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write Command Every thing is comming After This Command Display on TFT*/
	voidWriteCommand(0x2C);
	for(Counter = 0 ; Counter < 20480 ; Counter ++)
	{
		/*	Writ For One Pixel The High Byte Then Low Byte For Each Pixel */
		/*Write The High Byte */
		voidWriteData(Copy_u16Color >> 8);
		//voidWriteData(Data);
		/*Write The LOW Byte */
		voidWriteData(Copy_u16Color &0x00ff);
	}
}


/*******************************************  END_ FUNCTION  *******************************************/
/*******************************************************************************************************/
/******************************************* Start_FUNCTION  *******************************************/

void HTFT_voidDrawRect( u8 X_0,u8 X_1,u16 Y_0,u16 Y_1,u16 Copy_u16Color)	 //SIZE = FROM X_0 TO X_1 & FROM Y_0 TO Y_1 & COLOR
{
	u32 Counter ;
	// u8 Y_0_LEFT  = Y_0 >> 8;
	// u8 Y_0_RIGHT = Y_0 & 0x00ff;
	/*	SET SIZE X,Y  */
	u32 Local_u32Size =( X_1 - X_0 ) * ( Y_1 - Y_0 ) ;
	/*	Set X_ADRESS Start X_0 End X_1*/
	voidWriteCommand(0x2A);
	/* Start = 00*/
	voidWriteData(0);
	voidWriteData(X_0);
	/* End = 239*/
	voidWriteData(0);
	voidWriteData(X_1);


	/*	Set Y_ADRESS Start Y_0 End Y_1 */
	voidWriteCommand(0x2B);
	/* Start = 00*/
	voidWriteData(Y_0>>8);
	voidWriteData(Y_0 & 0x00ff);
	/* End = 319*/
	voidWriteData(Y_1>>8);
	voidWriteData(Y_1 & 0x00ff);

	/* RAM Write Command Every thing is coming After This Command Display on TFT*/
	voidWriteCommand(0x2C);
	for(Counter = 0 ; Counter < Local_u32Size+5 ; Counter ++)
	{
		/* Write For One Pixel The High Byte Then Low Byte For Each Pixel */
		/* Write The High Byte */
		voidWriteData(Copy_u16Color >> 8);
		/* Write The LOW Byte */
		voidWriteData(Copy_u16Color &0x00ff);
	}
}


/*******************************************  END_ FUNCTION  *******************************************/
void HTFT_StartPanel(void)
{
	HTFT_voidDrawRect(90,95,0,385,0);
	HTFT_voidDrawRect(145,150,0,385,0);

	HTFT_voidDrawRect(0,90,60,65,0);
	HTFT_voidDrawRect(0,90,125,130,0);
	HTFT_voidDrawRect(0,90,190,195,0);
	HTFT_voidDrawRect(0,90,255,260,0);

	HTFT_voidDrawRect(150,239,60,65,0);
	HTFT_voidDrawRect(150,239,125,130,0);
	HTFT_voidDrawRect(150,239,190,195,0);
	HTFT_voidDrawRect(150,239,255,260,0);
}
