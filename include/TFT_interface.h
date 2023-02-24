/*
 ============================================================================
 Name        : TFT_program.h
 Author      : Sayed ibrahim
 Version     : V.1
 ============================================================================
 */
/****************************************************************
***********  guard of file will call on time in .c  *************
******************************************************************/ 


#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void HTFT_voidInit(void);
void voidWriteCommand(u8 Copy_u8Command);
void voidWriteData(u8 Copy_u8Data);
void HTFT_voidDisplayImage(const u16*Copy_Image);				// Must Constant To go to Flash Not RAM & u16  1pixel = 2byte(2*8)  
void HTFT_voidFillColor( u16 Copy_u16Color);
void HTFT_voidDrawRect( u8 X_0,u8 X_1,u16 Y_0,u16 Y_1,u16 Copy_u16Color);
void HTFT_voidDrawCar(u8 X_0,u8 X_1,u16 Y_0,u16 Y_1, u16*Copy_Image);
void HTFT_StartPanel(void);
void HTFT_voidDrawCar(u8 X_0,u8 X_1,u16 Y_0,u16 Y_1, u16*Copy_Image);

#endif //TFT_INTERFACE_H
