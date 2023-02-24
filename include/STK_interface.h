

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


#define     MSTK_SRC_AHB           0U
#define     MSTK_SRC_AHB_8         1U

#define     MSTK_SINGLE_INTERVAL    0U
#define     MSTK_PERIOD_INTERVAL    1U


/* Func : */
void MSTK_vInit(void);
/* Func : */
void MSTK_vBusyWait(u32 Copy_u32Tick);
/* Func : */
u32 MSTK_u32ElapedTime(void);
/* Func : */
u32 MSTK_u32RemaningTime(void);
/* Func : */
void MSTK_vIntervalSingle(u32 Copy_u32Tick  , void (*Copy_vPtr)(void));
/* Func : */
void MSTK_vIntervalPeriodic(u32 Copy_u32Tick, void (*Copy_vPtr)(void));
/* Func : */
void MSTK_voidStopInterval(void) ;









#endif      // STK_INTERFACE_H
 
