
#include "STM32F10x_TYPE.h"

#include "CLanguage.h"

void DelayTest(void)
{
	int a;
	for(a=0; a<10000; a++)
	{
		__nop();
	}
}

int TestNumber1(void)
{
	//int a;
	// char      =  8 bit
	// short int = 16 bit
	// int       = 16 bit
	// long      = 32 bit
	// long long = 64 bit
//	u32 g;
//	signed char t;
	short int d=3;
	signed int a=(d+1); //
//	long b;
//	long long c;	
	
	a=-1;
	
	
	// true != 0
	// false == 0
	//true==false
	//!=
	//<
	//>
	//!
	//u16 a=1==1;
	if (3432465)
	{
	} else {
	}
	
	while(123)
	{
		a=a+1;
	}
/*	
	do{
		__nop();
	}while(a!=0);
	*/
/*	for(a=-1; a>1; a=a+10)
	{
		__nop();
	}
	*/
}


