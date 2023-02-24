/*
 ============================================================================
 Name        : Vehicle Smart barking
 Author      : Sayed ibrahim
 Version     : V.1
 ============================================================================
 */

/****************************    LIB INCLUDE    ****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include "Delay_interface.h"

/****************************	MCAL INCLUDE   ****************************/
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "UART_interface.h"


/****************************	APP INCLUDE	  ****************************/
#include "CAR_IMG.h"

/****************************	HAL INCLUDE	  ****************************/
#include "TFT_interface.h"
#include "LCD.h"
#include "motor_interface.h"
#include "sensor_interface.h"


/****************************	STAGES MACROS	****************************/
#define ENTRY_STAGE				1
#define PARKING_STAGE			2
#define RETRIEVING_STAGE		3
#define VERIFYING_STAGE			4

/****************************    GLOBAL VARIABLES INIT    ****************************/
extern u16 car_arr[];										//car img
extern u16 CAR_INDEX_ARR[10][4];							//cars position on tft

u8 G_u8SensorsReadsArr[11]={0};								//sensors flags
u8 G_u8Cars[10]={0};										//car flags
u8 G_u8PasswordsArr[10][4]={0};								//2D array for password of 4 integers
u8 MQTT_RECIEVE[20];										//UART receive


const u8 MOTOR[10]={1,2,3,4,5,6,7,8,9,10};					//motor indexes
const u8 SENSOR[10]={1,2,3,4,5,6,7,8,9,10};					//sensor indexes

/****************************	MAIN START	****************************/
int main(void)
{
	MRCC_vEnableClock(AHB1_BUS,_PERIPHERAL_EN_GPIOA );						//enable GPIOA for first 5 motors
	MRCC_vEnableClock(AHB1_BUS,_PERIPHERAL_EN_GPIOC );						//enable GPIOC sensors and UART

	MRCC_vEnableClock(AHB1_BUS,_PERIPHERAL_EN_GPIOE );						//enable GPIOE for remaining 5 motors
	MRCC_vEnableClock(AHB1_BUS,_PERIPHERAL_EN_GPIOB );						//enable GPIOB for LCD and SPI (tft)

	MRCC_vEnableClock(AHB1_BUS,_PERIPHERAL_EN_GPIOD );						//

	MRCC_vEnableClock(APB1_BUS, PERIPHERAL_EN_SPI2);						//Enable SPI peripheral
	MRCC_vEnableClock(APB2_BUS, PERIPHERAL_EN_USART6);						//Enable UART peripheral


	//init motors pins as output
	MGPIO_vMODE(PORTA, PIN0 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN1 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN2 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN3 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN4 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN5 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN6 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN7 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN8 , OUTPUT);
	MGPIO_vMODE(PORTA, PIN9 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN0 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN1 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN2 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN3 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN4 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN5 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN6 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN7 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN8 , OUTPUT);
	MGPIO_vMODE(PORTE, PIN9 , OUTPUT);

	//init sensors pins as input
	MGPIO_vMODE(PORTC, PIN0 , INPUT);
	MGPIO_vMODE(PORTC, PIN1 , INPUT);
	MGPIO_vMODE(PORTC, PIN2 , INPUT);
	MGPIO_vMODE(PORTC, PIN3 , INPUT);
	MGPIO_vMODE(PORTC, PIN4 , INPUT);
	MGPIO_vMODE(PORTC, PIN5 , INPUT);
	MGPIO_vMODE(PORTC, PIN8 , INPUT);
	MGPIO_vMODE(PORTC, PIN9 , INPUT);
	MGPIO_vMODE(PORTC, PIN10 , INPUT);
	MGPIO_vMODE(PORTC, PIN11 , INPUT);
	MGPIO_vMODE(PORTC, PIN12 , INPUT);

	//PULL Down res for sensors (active high)
	MGPIO_vPULLMODE(PORTC,PIN0 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN1 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN2 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN3 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN4 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN5 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN11 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN12 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN8 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN9 ,PULL_DOWN);
	MGPIO_vPULLMODE(PORTC,PIN10,PULL_DOWN);


	MGPIO_vMODE(PORTC, PIN6 , ALT);			//Tx UART6 enable ALT
	MGPIO_vMODE(PORTC, PIN7 , ALT);			//Rx UART6 enable ALT

	MGPIO_vALTFUNC(PORTC, PIN6 , AF8);      //Tx setting UART6 ALT func
	MGPIO_vALTFUNC(PORTC, PIN7 , AF8);      //Rx setting UART6 ALT func

	MGPIO_vMODE(PORTB, PIN10 , ALT);        //SPI CLK
	MGPIO_vMODE(PORTB, PIN15 , ALT);        //SPI MOSI

	MGPIO_vMODE(PORTB, PIN1 , OUTPUT);        //Reset for TFT
	MGPIO_vMODE(PORTB, PIN9 , OUTPUT);        //Data/Command select for tft

	MGPIO_vALTFUNC(PORTB, PIN10 , AF5);      //Setting ALT func SPI CLK
	MGPIO_vALTFUNC(PORTB, PIN15 , AF5);      //Setting ALT func SPI MOSI

	MSPI_VidInit();						//SPI INIT

	HTFT_voidInit();                    //TFT INIT

	HTFT_StartPanel();                  //TFT START LAYOUT

	MUSART_VidInit();                   //UART INIT

	LCD_INIT();                         //LCD INIT

	u8 L_u8Iterator=0;					//iterator
	u8 L_u8NumOfCars=0;					//car counter
	u8 L_u8Action=0;					//action flag
	u8 L_u8ChosedPos=0;					//position flag
	u8 L_u8ChosedPos1=0;				//position flag
	u8 L_u8ChosedPos2=0;				//position flag
	u8 L_u8PassIsOk=0;					//password flag


	while (1)
	{
		LCD_GOTO(0, 0);
		LCD_WRIDE_STRING("Press 1 to park");
		LCD_GOTO(1, 0);
		LCD_WRIDE_STRING("or 2 to retrieve");
		L_u8Action =0 ;
		while(ENTRY_STAGE)
		{
			if(HSENSOR_u8SensorStatus(ENTRY_SENSOR)==THERE_IS_A_CAR)		//checking if car at entrance
			{
				G_u8SensorsReadsArr[0]=1;									//flag
			}
			else
			{
				G_u8SensorsReadsArr[0]=0;
			}

			//MQTT SEND (get a car or park a car)
			MUSART1_PtrReadStringSynch(MQTT_RECIEVE);
			LCD_CLR();
			LCD_WRIDE_STRING(MQTT_RECIEVE);

			if(strcmp(MQTT_RECIEVE,"2")==0)							 //"GET A CAR"
			{
				if(L_u8NumOfCars != 0)
				{
					L_u8Action = 2;							//ENTER RETRIEVE STAGE
					break;
				}
				else{
					LCD_CLR();
					LCD_WRIDE_STRING("INVALID OPTION");
					LCD_GOTO(1, 0);
					LCD_WRIDE_STRING("GARAGE IS EMPTY");
					Delay_vMsIn16MHz(500);
		 			break;												// GO BACK TO MENU
				}

			}
			else if(strcmp(MQTT_RECIEVE,"1")==0)					//"if PARK A CAR"
			{
				if(HSENSOR_u8SensorStatus(ENTRY_SENSOR)==THERE_IS_NO_CAR)			//IF THERE'S NO CAR AT ENTRY
				{
					LCD_CLR();
					LCD_WRIDE_STRING("NO CAR AT ENTRY");
					Delay_vMsIn16MHz(650);
					break;
				}
				if(L_u8NumOfCars<10)												//CHECK ON CARS COUNTER
				{
					if(HSENSOR_u8SensorStatus(ENTRY_SENSOR)==THERE_IS_A_CAR)		//IF THERE'S A CAR AT ENTRY
					{
						G_u8SensorsReadsArr[0]=1;									//ENTRY SENSOR ON
						L_u8Action = 1;												//ENTER PARKING STAGE
						break;
					}
					else
					{
						G_u8SensorsReadsArr[0]=0;									//ENTRY SENSOR OFF GO BACK TO MENU
						//error no car at entry
						LCD_CLR();
						LCD_WRIDE_STRING("NO ENTRY CAR");
						Delay_vMsIn16MHz(500);
					}
				}
				else
				{
					LCD_CLR();
					LCD_WRIDE_STRING("GARAGE IS FULL");
					Delay_vMsIn16MHz(500);
				}
			}
		}
		switch(L_u8Action)													//TO SWITCH ON PARKING OR RETRIEVING STAGE
		{
		case 1:
			while(PARKING_STAGE)
			{
				LCD_CLR();
				LCD_WRIDE_STRING("Enter empty pos");
				L_u8ChosedPos1 = MUSART1_u8RecCharSynch();					//POSITION FIRST DIGIT

				if(L_u8ChosedPos1 == 'q')									//IF q = BACK TO MAIN MENU
				{
					LCD_CLR();
					LCD_WRIDE_STRING("BACK TO MENU");
					Delay_vMsIn16MHz(500);
					break;
				}
				else
				{
					//MISRA
				}

				L_u8ChosedPos2 = MUSART1_u8RecCharSynch();					//POSITION SECOND DIGIT
				LCD_CLR();
				LCD_WRIDE_STRING("Entered pos : ");
				LCD_WRIDE_CHR(L_u8ChosedPos1);                              //DISPLAY POSITION ON LCD
				LCD_WRIDE_CHR(L_u8ChosedPos2);                              //DISPLAY POSITION ON LCD
				Delay_vMsIn16MHz(500);

				L_u8ChosedPos1 -=48;                                        //CONVERTING FROM ASCII
				L_u8ChosedPos2 -=48;                                        //CONVERTING FROM ASCII
				L_u8ChosedPos = (L_u8ChosedPos1 * 10) + L_u8ChosedPos2 ;    //CREATING POSITION DIGITS

				if(L_u8ChosedPos >= 1 && L_u8ChosedPos <= 10)				//VALIDATING POSITION
				{
					if(G_u8SensorsReadsArr[L_u8ChosedPos]==THERE_IS_A_CAR)	//CHECKING IF POSITION IS AVAILABLE USING SESORS ARRAY
					{
						//error chosen position is not empty
						LCD_CLR();
						LCD_WRIDE_STRING("POS IS FULL");
						Delay_vMsIn16MHz(500);
					}
					else
					{
						break;												//POS IS VALID
					}
				}
				else
				{
					//error wrong number range
					LCD_CLR();
					LCD_WRIDE_STRING("INVALID POSITION");
					Delay_vMsIn16MHz(500);
				}
			}
			if(L_u8ChosedPos1 == 'q')										//BREAKING AND BACK TO MENU
			{
				break;
			}
			//MQTT input PASSWORD
			LCD_CLR();
			LCD_WRIDE_STRING("ENTER PASSWORD");
			MUSART1_PtrReadStringSynch(MQTT_RECIEVE);						//PASSWORD INPUT
			//Save PASSWORD
			LCD_CLR();
			LCD_WRIDE_STRING("PASS: ");
			LCD_WRIDE_STRING(MQTT_RECIEVE);									//DISPLAYING PASSWORD ON LCD
			Delay_vMsIn16MHz(700);

			for(L_u8Iterator=0;L_u8Iterator<4;L_u8Iterator++)				//STORING PASSWORD
			{
				G_u8PasswordsArr[L_u8ChosedPos-1][L_u8Iterator]=MQTT_RECIEVE[L_u8Iterator];
			}

			LCD_GOTO(1, 0);
			LCD_WRIDE_STRING("PARKING :) ");

			HMotor_voidMotor_start(MOTOR[L_u8ChosedPos-1], ENTER);							//MOTOR START

			while(HSENSOR_u8SensorStatus(SENSOR[L_u8ChosedPos-1])==THERE_IS_NO_CAR)			//WAITING FOR POSITION SENSOR
			{
				if(HSENSOR_u8SensorStatus(ENTRY_SENSOR)==THERE_IS_NO_CAR)					//CHECKING ON ENTRY SENSOR
				{
					G_u8SensorsReadsArr[ENTRY_SENSOR]=0;
				}
			}

			LCD_CLR();
			LCD_WRIDE_STRING("Car reached pos");
			Delay_vMsIn16MHz(700);

			G_u8SensorsReadsArr[L_u8ChosedPos]=1;											//POSITION SENSOR FLAG

			HMotor_voidMotor_stop(MOTOR[L_u8ChosedPos-1]);									//MOTOR STOP

			/*DRAWING CAR IMG ON TFT IN POSITION*/
			HTFT_voidDrawCar(CAR_INDEX_ARR[L_u8ChosedPos-1][0], CAR_INDEX_ARR[L_u8ChosedPos-1][1], CAR_INDEX_ARR[L_u8ChosedPos-1][2], CAR_INDEX_ARR[L_u8ChosedPos-1][3], car_arr);

			L_u8NumOfCars++;																//CAR COUNTER

			break;

		case 2: 																			//get a car
			while(RETRIEVING_STAGE)
			{
				LCD_CLR();
				LCD_WRIDE_STRING("Enter car pos");
				L_u8ChosedPos1 = MUSART1_u8RecCharSynch();									//POSITION FIRST DIGIT
				if(L_u8ChosedPos1 == 'q')                                                   //IF q = BACK TO MAIN MENU
				{
					LCD_CLR();
					LCD_WRIDE_STRING("BACK TO MENU");
					Delay_vMsIn16MHz(500);
					break;
				}
				else
				{
					//MISRA
				}
				L_u8ChosedPos2 = MUSART1_u8RecCharSynch();                                  //POSITION SECOND DIGIT

				LCD_CLR();
				LCD_WRIDE_STRING("Entered pos : ");
				LCD_WRIDE_CHR(L_u8ChosedPos1);                                              //DISPLAY POSITION ON LCD
				LCD_WRIDE_CHR(L_u8ChosedPos2);                                              //DISPLAY POSITION ON LCD
				Delay_vMsIn16MHz(500);


				L_u8ChosedPos1 -=48;                                                        //CONVERTING FROM ASCII
				L_u8ChosedPos2 -=48;                                                        //CONVERTING FROM ASCII

				L_u8ChosedPos = (L_u8ChosedPos1 * 10) + L_u8ChosedPos2 ;                    //CREATING POSITION DIGITS

				if (G_u8SensorsReadsArr[ENTRY_SENSOR]==1)									//CHECKING ON ENTRY SENSOR
				{
					//EMPTY POS
					LCD_CLR();
					LCD_WRIDE_STRING("CAR AT ENTRY");
					LCD_GOTO(1, 0);
					LCD_WRIDE_STRING("PLEASE WAIT");
					Delay_vMsIn16MHz(500);
				}
				else
				{
					if(L_u8ChosedPos>=1 && L_u8ChosedPos<=10 )								//VALIDATING POSITION
					{
						if(G_u8SensorsReadsArr[L_u8ChosedPos]==THERE_IS_A_CAR)				//CHECKING IF THERE'S A CAR IN POSITION
						{
							break;															//VALID POS
						}
						else
						{
																							//EMPTY POS ASK AGAIN FOR VALID POSITION
							LCD_CLR();
							LCD_WRIDE_STRING("EMPTY POS");
							Delay_vMsIn16MHz(500);
						}
					}
					else
					{
						LCD_CLR();
						LCD_WRIDE_STRING("INVALID NUM");
						Delay_vMsIn16MHz(500);
					}
				}

			}
			if(L_u8ChosedPos1 == 'q')														//BACK TO MENU
			{
				break;
			}
			while(VERIFYING_STAGE)															//VERIFYING PASSWORD STAGE
			{
				LCD_CLR();
				LCD_WRIDE_STRING("Enter password : ");
				MUSART1_PtrReadStringSynch(MQTT_RECIEVE);									//PASSWORD INPUT
				LCD_GOTO(1, 0);
				LCD_WRIDE_STRING("PASS :");
				LCD_WRIDE_STRING(MQTT_RECIEVE);

				for(L_u8Iterator=0;L_u8Iterator<4;L_u8Iterator++)							//COMPAIR PASSWORD
				{
					if(G_u8PasswordsArr[L_u8ChosedPos-1][L_u8Iterator] == MQTT_RECIEVE[L_u8Iterator])
					{
						L_u8PassIsOk=1;														//CORRECT PASSWORD FLAG
					}
					else
					{
						L_u8PassIsOk=0;														//CORRECT PASSWORD FLAG
						break;
					}
				}
				if(L_u8PassIsOk==1)															//CHECK ON PASSWORD FLAG
				{
					LCD_CLR();
					LCD_WRIDE_STRING("CORRECT PASS");
					LCD_GOTO(1, 0);
					LCD_WRIDE_STRING("RETRIEVING");
					Delay_vMsIn16MHz(500);
					break;
				}
				else
				{
					LCD_CLR();
					LCD_WRIDE_STRING("WRONG PASS");
					Delay_vMsIn16MHz(500);
				}
			}

			HMotor_voidMotor_start(MOTOR[L_u8ChosedPos-1], LEAVE);										//MOTOR START

			while(HSENSOR_u8SensorStatus(ENTRY_SENSOR)==THERE_IS_NO_CAR)								//CHECKING IF CAR IN ENTRY
			{
				if(HSENSOR_u8SensorStatus(SENSOR[L_u8ChosedPos-1])==THERE_IS_NO_CAR)					//CHECK ON POSITION SENSOR
				{
					G_u8SensorsReadsArr[L_u8ChosedPos]=0;												//CLEARING THE SENSOR FLAG
				}
			}

			G_u8SensorsReadsArr[0]=1;																	//SETTING ENTRY SENSOR

			HMotor_voidMotor_stop(MOTOR[L_u8ChosedPos-1]);												//MOTOR STOP
			/*	CLEARING POSITION ON TFT	*/
			HTFT_voidDrawRect(CAR_INDEX_ARR[L_u8ChosedPos-1][0], CAR_INDEX_ARR[L_u8ChosedPos-1][1], CAR_INDEX_ARR[L_u8ChosedPos-1][2], CAR_INDEX_ARR[L_u8ChosedPos-1][3], OFF);

			L_u8NumOfCars--;																			//UPDATING CAR COUNTER

			break;

		default:
			//MISRA
			break;
		}
	}
}



