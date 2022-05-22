//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F100
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hdadc.h"
#include "hardware.h"


void Setup_ADC(void)
{
//    GPIO_InitTypeDef  GPIO_InitStructure;
  
    ADC_InitTypeDef ADC_InitStructure;
  
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    ADC_DeInit(ADC1);
  
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; //
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 16;
    ADC_Init(ADC1, &ADC_InitStructure);
  
            // Enable ADC1
            ADC_Cmd(ADC1, ENABLE);
              
            // Enable ADC1 reset calibration register
            ADC_ResetCalibration(ADC1);
            // Check the end of ADC1 reset calibration register
            while (ADC_GetResetCalibrationStatus(ADC1));

            // Start ADC1 calibration
            ADC_StartCalibration(ADC1);
            // Check the end of ADC1 calibration
            while (ADC_GetCalibrationStatus(ADC1));
//GPIO Init            

//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin   = ADCBAT_wp_bit | ADCV5E_wp_bit;
//    GPIO_Init(ADC_port, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
//    GPIO_InitStructure.GPIO_Pin   = ADCINX_wp_bit | ADCINY_wp_bit;
//    GPIO_Init(ADC_port, &GPIO_InitStructure);
//    GpioInit_ADC_D0();
//    GpioInit_ADC_D1();
//    GpioInit_ADC_D2();
//    GpioInit_ADC_D3();
//    GpioInit_ADC_D4();
//    GpioInit_ADC_D5();
//    GpioInit_ADC_D6();
//    GpioInit_ADC_D7();
//    GpioInit_ADC_D8();
//    GpioInit_ADC_D9();
//    GpioInit_ADC_D10();
//    GpioInit_ADC_D11();

		GpioInit_ADC12IN10();
		GpioInit_ADC12IN6();
  
}

u16 Read_ADC_GroupBIT(u32 sel)
{
  u8 channel=0;
  switch (sel)
  {
    case macRead_ADC_GroupNAME(ADC12IN10):  channel=10; break;
    case macRead_ADC_GroupNAME(ADC12IN6):   channel=6; break;
  }
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}




