//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HATIMERS_H
#define __HATIMERS_H


#include "SysType.h"



//////////////////////////////////////////////////////////////////////////////////////


extern u32 isTimerCompareOverflow(u32 valTimerDelay, u32 valTimerCounter );


//#define TMS_StartWait(__npos,__nval)   Timer_1ms_Store[__npos]=Timer_1ms_Counter+(__nval)
//#define TMS_CheckWait(__npos)          Timer_1ms_Store[__npos]<=Timer_1ms_Counter

//#define TMS_1msStartWait(__name,__nval)   __name=Timer_1ms_Counter+(__nval)
//#define TMS_1msCheckWait(__name)          __name<=Timer_1ms_Counter
//#define TMS_1msGetProcessTime(__name)     Timer_1ms_Counter-__name

//#define TMS_StoreStartWait(__num,__nval)   TMS_1msStartWait(Timer_1ms_Store[__num],__nval)
//#define TMS_StoreCheckWait(__num)          TMS_1msCheckWait(Timer_1ms_Store[__num])
//#define TMS_StoreGetProcessTime(__num)     TMS_1msGetProcessTime(Timer_1ms_Store[__num])



typedef u32(timerGetProc_t)(void);


extern u32 Timer_CounterProc(void);
extern vu32 TimerCounterUpdate(void);

extern u32 Timer_1ms_CounterUpdate(void);
#define Timer_1ms_Counter       Timer_1ms_CounterUpdate()     //extern vu32 Timer_1ms_Counter;
extern vu32 Timer_1ms_Store[];
extern u32 Timer_1ms_CounterProc(void);




extern RCC_ClocksTypeDef MPU_ClocksStatus;
//extern vu32 PCLK1;
//extern vu32 PCLK2;
extern vu8  PCLK1_NOP;
extern vu32 TIMER0_PER;
extern vu32 TIMER1_PER;
extern vu32 TIMER2_PER;
extern vu32 TIMER3_PER;
extern vu32 TIMER4_PER;



// Global define
extern void DelayMCS(u32 mcs);
extern void DelayMS(u32 ms);
extern void DelayNOP(u32 co);
extern void DelayNOP_CLK(void);

#define WaitMS_GetTime()    Timer_1ms_Counter
extern void WaitMS_Start(u32 *p, u32 ms);
extern u8 WaitMS_Check(u32 *p);
extern void WaitMS_Wait(u32 *p);

extern void Sleep(u32 ms);

extern void SysTick_Interrupt(u32 sysTimeAdder);

#endif
