/*
 ============================================================================
 Name        :  Macros
 Author      : Sayed ibrahim
 Version     : V.1
 ============================================================================
 */


 #ifndef BIT_MATH_H_
 #define BIT_MATH_H_


 #define SET_BIT(REG,BITNUM)   REG = REG | (1<<BITNUM)
 #define CLR_BIT(REG , BITNUM) REG &= ~(1<<BITNUM)
 #define TOG_BIT(REG , BITNUM) REG ^= 1<<BITNUM
 #define GET_BIT(REG , BITNUM) ( (REG >> BITNUM) & 1 )



 #endif /* BIT_MATH_H_ */
