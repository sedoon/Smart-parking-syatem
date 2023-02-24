/*
 * LCD.c
 *
 * Created: 13-Feb-22 10:09:44 AM
 *  Author: sayed ibrahim
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "Delay_interface.h"
#include "LCD.h"
#include "LCD_CFG.h"

void LCD_WRIDE_CMD(u8 command);

void LCD_INIT()
{
	MGPIO_vMODE(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	MGPIO_vMODE(LCD_CONTROL_PORT,LCD_EN_PIN,OUTPUT);
	MGPIO_vSETOUTPUTMODE(LCD_CONTROL_PORT, 0, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(LCD_CONTROL_PORT, 1, PUSH_PULL);
#if LCD_MODE == _8_BIT_MODE




	MGPIO_vMODE(LCD_DATA_PORT,0,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,1,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,2,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,3,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,4,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,5,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,6,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,7,OUTPUT);

	MGPIO_vSETOUTPUTMODE(GPIOA, 0, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 1, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 2, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 3, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 4, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 5, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 6, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(GPIOA, 7, PUSH_PULL);


	Delay_vMsIn16MHz(100);
	LCD_WRIDE_CMD(0x38);	//use 8 bit mode

#elif LCD_MODE == _4_BIT_MODE

	MGPIO_vMODE(LCD_DATA_PORT,4,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,5,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,6,OUTPUT);
	MGPIO_vMODE(LCD_DATA_PORT,7,OUTPUT);
	MGPIO_vSETOUTPUTMODE(LCD_DATA_PORT, 4, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(LCD_DATA_PORT, 5, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(LCD_DATA_PORT, 6, PUSH_PULL);
	MGPIO_vSETOUTPUTMODE(LCD_DATA_PORT, 7, PUSH_PULL);
	Delay_vMsIn16MHz(100);
	LCD_WRIDE_CMD(0x32);	//use 4 bit mode
	LCD_WRIDE_CMD(0x28);
#endif
	LCD_WRIDE_CMD(0x0C);	//LCD ON
	LCD_WRIDE_CMD(0x02);	//Return home
	LCD_WRIDE_CMD(0x01);	//clear
	LCD_WRIDE_CMD(0x06);	//from left to write

}
void LCD_WRIDE_CMD(u8 command)
{
#if LCD_MODE == _8_BIT_MODE

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	//PORT_WRITE(LCD_DATA_PORT,command);


	MGPIO_vWRITE_PIN(LCD_DATA_PORT,0,((command>>0)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,1,((command>>1)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,2,((command>>2)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,3,((command>>3)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((command>>4)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((command>>5)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((command>>6)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((command>>7)&1));



	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);
	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	Delay_vMsIn16MHz(5);

#elif LCD_MODE == _4_BIT_MODE

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_RS_PIN,LOW);
	/*to send the lift half byte*/
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((command>>4)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((command>>5)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((command>>6)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((command>>7)&1));

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	/*to send the right half byte*/
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((command>>0)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((command>>1)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((command>>2)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((command>>3)&1));

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);
	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	Delay_vMsIn16MHz(5);

#endif
}
void LCD_WRIDE_CHR(u8 character)
{
#if LCD_MODE == _8_BIT_MODE

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
	//PORT_WRITE(LCD_DATA_PORT,character);
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,0,((character>>0)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,1,((character>>1)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,2,((character>>2)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,3,((character>>3)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((character>>4)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((character>>5)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((character>>6)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((character>>7)&1));

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);
	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	Delay_vMsIn16MHz(5);

#elif LCD_MODE == _4_BIT_MODE

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);
	/*to send the lift half byte*/
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((character>>4)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((character>>5)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((character>>6)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((character>>7)&1));

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	/*to send the right half byte*/
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,4,((character>>0)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,5,((character>>1)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,6,((character>>2)&1));
	MGPIO_vWRITE_PIN(LCD_DATA_PORT,7,((character>>3)&1));

	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,HIGH);
	Delay_vMsIn16MHz(1);
	MGPIO_vWRITE_PIN(LCD_CONTROL_PORT,LCD_EN_PIN,LOW);
	Delay_vMsIn16MHz(5);
#endif
}
void LCD_WRIDE_STRING(const unsigned char * str_ptr)
{
	while((*str_ptr) != '\0')
		{
		LCD_WRIDE_CHR(*str_ptr);
		str_ptr++;
		}
}
void LCD_WRIDE_NUM(u32 number)
{
	if (number == 0)
	{
		LCD_WRIDE_CHR('0');

	}
	else
	{
		s8 i=0;
		u8 arr[10]={0};
		while(number !=0)
		{
			arr[i++] = number % 10;
			number/=10;
		}
		i--;
		while(i>=0)
		{
			LCD_WRIDE_CHR(arr[i--]+48);
		}
	}
}
void LCD_CLR()
{
	LCD_WRIDE_CMD(0x01);
}
void LCD_GOTO(u8 row,u8 col)
{
	u8 arr[2] = {0x80,0xC0};

	LCD_WRIDE_CMD(arr[row]+col);


}
void LCD_WRITE_NEGATIVE(s32 number)
{
	if (number == 0)
	{
		LCD_WRIDE_CHR('0');

	}
	else if (number>0)
	{
		LCD_WRIDE_NUM(number);
	}
	else if (number<0)
	{
		LCD_WRIDE_CHR('-');
		number*=-1;
		LCD_WRIDE_NUM(number);
	}
}
void LCD_WRITE_FLOAT(f64 number)
{
	s8 i=0,j=0;
	u32 x=number;
	u8 base_NUM[10]={0};
	f64 y=0;
	if (number<0)
	{
		number*=-1;
		x=number;
		LCD_WRIDE_CHR('-');
	}
	y=(((number+1.0)-x)*10000000);
	while(x !=0)
	{
		base_NUM[i++] = x % 10;
		x/=10;
	}
	u8 k=i--;
	while(i>=0)
	{
		LCD_WRIDE_CHR(base_NUM[i--]+48);
	}
	LCD_WRIDE_CHR('.');
	u8 F_NUM[10]={0};
	i=0;
	u32 z=y;
	while(z !=0)
	{
		F_NUM[i++] = z % 10;
		z/=10;
	}
	i-=2;
	for(j=0;j<10;j++)
	{
		if(F_NUM[j]==0)
		{
			F_NUM[j]='k';
		}
		else
		{
			break;
		}
	}
	while(F_NUM[i]!='k'&& k!=7)
	{
		LCD_WRIDE_CHR(F_NUM[i--]+48);
		k++;
	}


}
