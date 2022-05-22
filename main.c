//super CODE TEST
#include "SysType.h"
#include "hardware.h"




void LED(int val)
{
	LEDA(val);
}
	
//volatile u32 AdcSuperValue = 0;
//volatile u32 AdcVoltage = 0;	//1000 = 1.0 v

vu32 HumadityAdcValue = 0;
vu32 HumadityAdcVoltage = 0;
vu32 HumadityAdcPowerValue = 0;
vu32 HumadityAdcPowerVoltage = 0;



void MeasueHumadity(void)
{
		HumadityAdcValue = HumadityReadADC();	
		HumadityAdcVoltage = (HumadityAdcValue * 3300) / 4096;
	
		HumadityAdcPowerValue = Read_ADC12IN10();	
		HumadityAdcPowerVoltage = (HumadityAdcPowerValue * 3300) / 4096;
	
}


int main(void)\
{
	Init();
	
	bool ButtonValue = 0;
	int TimerMax = 10000;
	int ButtonTimer = TimerMax;
	bool flag = 0;
	
  while(1)
  {
		if(flag==1) ButtonTimer += 1;
//		LED(1);
//		DelayMS(500);
//		LED(0);
//		DelayMS(500);
//3.3 = 0x0FFF = 4095 = ADC
// voltague = ADC / 4095 * 3.3		
//
		
		
		MeasueHumadity();
//OFF
		if ((KEY()!=0)&&(ButtonValue==1)&&(ButtonTimer>=TimerMax))
		{
			ButtonValue = 0;
			ButtonTimer = 0;
			flag = 1;
		} else{
			if((KEY()!=0)&&(ButtonValue==0)&&(ButtonTimer>=TimerMax))
			{
				ButtonValue = 1;
				ButtonTimer = 0;
				flag = 1;
			}
		}
		
		if(ButtonTimer>TimerMax) flag=0;

		if (ButtonValue==1)
		{
			HumadityPower(1);
		} else {
			HumadityPower(0);
		}
	
  }	
}





