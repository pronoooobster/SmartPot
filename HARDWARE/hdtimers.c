//////////////////////////////////////////////////////////////////////////////////////
// 
// Low Level Timers For Project
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////
#include "SysType.h"
#include "cortex_rb_sys.h"
#include "cortex_rb_dwt.h"          

#include "hdtimers.h"
#if (CoCOS_EN==1)
#include "coocox.h"
#endif


//vu32 PCLK1;
//vu32 PCLK2;
vu8  PCLK1_NOP;
vu32 TIMER0_PER;
vu32 TIMER1_PER;
vu32 TIMER2_PER;
vu32 TIMER3_PER;
vu32 TIMER4_PER;

RCC_ClocksTypeDef MPU_ClocksStatus;


///////////////////////////
// Timer Procedures
///////////////////////////

#define CortexTimerDeltaProcedure(_timer, _systicks)      \
    static vu32 ccnt=0;                                   \
    const vu32 systick = _systicks;                       \
    const vu32 delt=(vu32)(DWT->CYCCNT - ccnt);           \
    DWT->CTRL |= (vu32)1;                                 \
    CoreDebug->DEMCR |= (vu32)0x01000000;                 \
    if (delt >= (systick))                                \
    {                                                     \
      const vu32 dtime=delt / (vu32)(systick);            \
      ccnt += (vu32)dtime * (vu32)(systick);              \
      _timer += (vu32)dtime;                              \
    }

//#define isTimerCompareOverflow(_valTimerDelay, _valTimerCounter)    ( ((((u32)(_valTimerDelay)) - ((u32)(_valTimerCounter))) >>29) )

vu32 Timer_CounterX=0;
u32 Timer_CounterProc(void)
{
    return TimerCounterUpdate();//Timer_Counter;
}

vu32 TimerCounterUpdate(void)
{/*
    static vu32 ccnt=0;
    const vu32 delt=(u32)(DWT->CYCCNT - ccnt);
    DWT->CTRL |= 1;
    CoreDebug->DEMCR |= 0x01000000;     // enable trace
    //0x01000000
    if (delt >= PCLK1_NOP)
    {
      const vu32 dtime=delt / PCLK1_NOP;
      ccnt += dtime * PCLK1_NOP;
      Timer_CounterX += dtime;
    }*/
    CortexTimerDeltaProcedure(Timer_CounterX, PCLK1_NOP)
    return Timer_CounterX;
}



u32 isTimerCompareOverflow(vu32 valTimerDelay, vu32 valTimerCounter)
{
  vu32 st=1;
  if (valTimerDelay) st = ((((vu32)(valTimerDelay)) - ((vu32)(valTimerCounter))) >>30);
  //if (st) st=1;
  return st;
}



void SysTick_Interrupt(u32 sysTimeAdder)
{
}

/*
void SysTick_Interrupt(u32 sysTimeAdder)
{
        //////Timer_Counter+=sysTimeAdder;//TIMER0_PER;
//        Timer_Counter+=TIMER0_PER;
        //ExtBuf6Vns_Interrupt();
}

//#ifndef CoCOS_EN
//#endif
//#define CoCOS_EN  0

#if (CoCOS_EN!=1)
void SysTick_Handler(void) __irq
{
      SysTick_Interrupt(TIMER0_PER);
}
#endif
*/
void DelayMCS(u32 mcs)
{
        u32 w_timc = /*Timer_Counter*/TimerCounterUpdate() + mcs;
        while (!isTimerCompareOverflow(w_timc, /*Timer_Counter*/TimerCounterUpdate()));//while (w_timc>Timer_Counter) __nop();
    
}
void DelayMS(u32 ms)
{
        while (ms--) DelayMCS(1000);
}

void DelayNOP(u32 co)
{
        while (co--) __nop();
}

void DelayNOP_CLK(void)
{
        DelayNOP(PCLK1_NOP);
}
//Timer 1 ms
vu32 Timer_1ms_CounterX=0;
vu32 Timer_1ms_Store[8];


u32 Timer_1ms_CounterUpdate(void)
{
    #if UseTimerRTC==1
      RtcTimerDeltaProcedure(Timer_1ms_CounterX,SystemLFXOClockGet()/1000);
    #else
      CortexTimerDeltaProcedure(Timer_1ms_CounterX, PCLK1_NOP*1000)
    #endif
    return Timer_1ms_CounterX;
  
}




/*
//void TIM1_UP_TIM16_IRQHandler(void) __irq
void TIM1_UP_IRQHandler(void) __irq
{
      //Code HERE
//        Timer_1ms_Counter++;
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}

*/

void TIM2_IRQHandler(void) __irq
{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        //Timer_1ms_Counter++;
}


void TIM3_IRQHandler(void) __irq
{

      //Code HERE
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//        ExtBuf6Vns_Interrupt();
}

void TIM4_IRQHandler(void) __irq
{
      //Code HERE
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}



void WaitMS_Start(u32 *p, u32 ms)
{
    p[0]=Timer_1ms_Counter+ms;
}

//return 1 if timer overflow started value
u8 WaitMS_Check(u32 *p)
{
    return isTimerCompareOverflow(p[0], Timer_1ms_Counter);//return p[0]<Timer_1ms_Counter;
}

void WaitMS_Wait(u32 *p)
{
   while (!WaitMS_Check(p));
}


void Sleep(u32 ms)
{
  if (ms)
  {
    u32 p;
    WaitMS_Start(&p, ms);
    while (!WaitMS_Check(&p))
    {
#if (CoCOS_EN==1)
      CoTickDelay(1);
#endif
    }
  } else {
#if (CoCOS_EN==1)
      CoTickDelay(1);
#endif
  }
  
}





