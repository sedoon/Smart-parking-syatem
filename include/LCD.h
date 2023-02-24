/*
 * LCD.h
 *
 * Created: 13-Feb-22 10:09:59 AM
 *  Author: sayed ibrahim
 */ 


#ifndef LCD_H_
#define LCD_H_



void LCD_INIT();
void LCD_WRIDE_CMD(u8);
void LCD_WRIDE_CHR(u8);
void LCD_WRIDE_STRING(  const unsigned char * str_ptr);
void LCD_WRIDE_CHR(u8);
void LCD_CLR();
void LCD_WRIDE_NUM(u32);
void LCD_GOTO(u8,u8);
void LCD_WRITE_FLOAT(f64);
void LCD_WRITE_NEGATIVE(s32);
#define _8_BIT_MODE		8
#define _4_BIT_MODE		4



#endif /* LCD_H_ */
