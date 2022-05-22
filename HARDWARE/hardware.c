//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F100
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hardware.h"
#include "STM32_Init.h"
//#include "rb_mmc_cfg.h"
#include "rb_util.h"
#include "hdadc.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void SystemInit(void)
{
        stm32_Init();
        //PWR_PVDCmd(DISABLE);
}

void SelectInitGPIO(void)
{
      GpioInit_LEDA();
      GpioInit_KEY();
			
			
}



void Init(void)
{
        RCC_GetClocksFreq((void *)&MPU_ClocksStatus);
//        PCLK1=RCC_ClocksStatus.PCLK1_Frequency;// stm32_GetPCLK1();
//        PCLK2=RCC_ClocksStatus.PCLK2_Frequency;// stm32_GetPCLK2();
        PCLK1_NOP=MPU_ClocksStatus.PCLK1_Frequency/1000000;
        TIMER0_PER=stm32_TimerGetReload(0);
        TIMER1_PER=stm32_TimerGetReload(1);
        TIMER2_PER=stm32_TimerGetReload(2);
        TIMER3_PER=stm32_TimerGetReload(3);
        TIMER4_PER=stm32_TimerGetReload(4);

        SelectInitGPIO();
				Setup_ADC();
	
	
/*  
        SPI2_Init();
        SPI2_DMA_Init();
        SPI2_GPIO_ON();
*/
}





//


