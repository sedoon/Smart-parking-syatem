/*=======================================================================================
============================   - RCC_program.c				 ============================
============================   - Created: 3/9/2021			 ============================
============================   - Author: sayed ibrahim       ============================
============================   - Version : _1_				 ============================
=========================================================================================*/

/*===========   INCLUDE LIB   ===========*/
		 #include "STD_TYPES.h"
		 #include "BIT_MATH.h"
/*======================================*/	 
/*===========  INCLUDE MCAL  ===========*/
		#include "RCC_private.h"
		#include "RCC_interface.h"
		#include "RCC_config.h"
/*======================================*/	

/*====================================================   Start_FUNCTION   ====================================================*/
 /*
	- Function To Enable Prepheral :
	
							       - BusName_t      :  The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One Detect Which REG To Choice Pripheral From It
							       - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg 
	
*/


void MRCC_vEnableClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	
	switch(BusName)
	{
		case AHB1_BUS:  SET_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  SET_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  SET_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  SET_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /*   ERROR   */          break ;
		
	}
	
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/

 /*
	- Function To Disable Prepheral :
	
							       - BusName_t      :  The Bus Of The Prepheral ( AHB1 , AHB2  , APB1 , APB2 ) Every One Detect Which REG To Choice Pripheral From It
							       - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg 
	
*/

void MRCC_vDisableClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	switch(BusName)
	{
		case AHB1_BUS:  CLR_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  CLR_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  CLR_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  CLR_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /* ERROR */          break ;
		
	}
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/

/*
* Function To Enable Security System
*/

void MRCC_vEnableSecuritySystem(void)
{
	SET_BIT( RCC_CR  , CSSON);
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*
* Function To Disable Security System
*/

void MRCC_vDisableSecuritySystem(void)
{
	CLR_BIT( RCC_CR  , CSSON);
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/* About The Function :
	
				- CLK		: HSE | HSI |PLL	
				- PLLSrc	:PLL_HSE | PLL_HSI
				- HSESrc    :HSE_Crystal ,HSE_RC 
 */

void MRCC_vInitSystemCLK(void)
{
	/********** HSI **********/
#if CLKSRC == HSI 
	/* 1- EN HSI */
	SET_BIT(MRCC->CR , 0U);
	/* 2- CLK SYS --> HSI */
	CLR_BIT(MRCC->CFGR, 0U);
	CLR_BIT(MRCC->CFGR, 1U);
	/********** HSE **********/
#elif CLKSRC == HSE
	
	#if HSE_SRC == CRYSTAL 
	/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Disable BYP */
		CLR_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLR_BIT(MRCC->CFGR, 1U);

	#elif HSE_SRC == RC 
		/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Enable BYP */
		SET_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLR_BIT(MRCC->CFGR, 1U);
	#else 
    /* Error*/
	#endif
	
	/********** PLL **********/
#elif CLKSRC == PLL	

    #if PLL_SRC == _HSE_PLL 
     /*1-Enable HSE */
			SET_BIT(MRCC->CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- EN PLL*/
			SET_BIT(MRCC->,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/* 3- PLL From HSE */
			SET_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
 
    #elif PLL_SRC == _HSI_PLL  
            /*Enable HSI */
		     SET_BIT(MRCC->CR,0U);
			/*2- EN PLL*/
			SET_BIT(MRCC->CR,24U);
			/* 3- PLL From HSI */
			CLR_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
    #else 
            /* Error*/
	#endif
/****************************************************/

#else 
/* Error*/
#endif // The End Of Big IF	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/

void MRCC_vInitClock(CLKSrcName_t Copy_tClkSrc , HSESrc_t Copy_tHSESrc ,PLLSrc_t Copy_tPLLSrc )
{
	switch(Copy_tClkSrc)
	{
		case HSE :
		switch(Copy_tHSESrc)
		{
		  case _HSE_CRYSTAL : 
			/*1-Enable HSE */
			SET_BIT(RCC_CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*Disable BYP*/
			CLR_BIT(RCC_CR,18U);
			/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLR_BIT(RCC_CFGR,1U);
		  break ;
		  /************************************************/
          case _HSE_RC :   
			/*Enable HSE */
			SET_BIT(RCC_CR,16U);
            /*2-Disable BYP*/
			SET_BIT(RCC_CR,18U);
				/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLR_BIT(RCC_CFGR,1U);

		  break ;

		  /*********************************************/
		  default :  break ;
		}
	    break ;
		/*******************/
		case HSI :
		/*Enable HSI */
		SET_BIT(RCC_CR,0U);
		/* Input system Clk*/
		CLR_BIT(RCC_CFGR,0U);
		CLR_BIT(RCC_CFGR,1U);
	    break ;
		/********************/
		case PLL :
		switch(Copy_tPLLSrc)
		{
			case _HSE_PLL: 
			/*1-Enable HSE */
			SET_BIT(RCC_CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- EN PLL*/
			SET_BIT(RCC_CR,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/**/
			SET_BIT(RCC_PLLCFGR, 22U);
			
			CLR_BIT(RCC_CFGR,0U);
			SET_BIT(RCC_CFGR,1U);
			
			break ;
			
			/**************************/
			
			case _HSI_PLL : 
			/*Enable HSI */
		     SET_BIT(RCC_CR,0U);
			/*2- EN PLL*/
			SET_BIT(RCC_CR,24U);
			
			CLR_BIT(RCC_PLLCFGR, 22U);
			
			CLR_BIT(RCC_CFGR,0U);
			SET_BIT(RCC_CFGR,1U);
			
			
			
			break ;
		}

	    break ;
		
	}
	
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
