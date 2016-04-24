
//Implementation of Digital Relay on TM4C123GXL
//Current is converted into Voltage using Current sensor
//AC Voltage is convertd in to DC voltage
//DC voltage is sampled using ADC
//Algorithm is applied for circuit breaker decison
// input signal connected to PE2/AIN1

#include "ADCSWTrigger.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "math.h"
#include "SysTick.h"
#include "Nokia5110.h"
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

volatile unsigned long ADCvalue,time,rms,ADCvalue0;

// The digital number ADCvalue is a representation of the voltage  
//1 bit=.001465A
// Current in Amps  ADCvalue
// 0.00                0
// 0.825            1024
// 1.65             2048
// 2.5              3072
// 3.3              4095

// Intilizing for Breaker Signal
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
float voltage=0;
float Vrms;

//Dealy using instructions dealys
void Delay1(void)
	{
		unsigned long volatile time1;
    time1 = 145448;  // 0.1sec
    while(time1){
		          time1--;
                       }
}
	

//Main Loop for implemetation of whole relay
int main(void){
	unsigned long volatile delay,i;
	
  PLL_Init();                           // 80 MHz
  ADC0_InitSWTriggerSeq3_Ch1();         // ADC initialization PE2/AIN1
	Nokia5110_Init();             // initialize Nokia5110 LCD
	SysTick_Init();
  PortF_Init();

	
	while(1){
		Nokia5110_SetCursor(0, 0);
		voltage=0;
		
    // 1)Sampling of Current 
    ADCvalue0 = ADC0_InSeq3();
		voltage=((ADCvalue0*1000)/4095)*3.3;
		// RMS value Calculation
		
		//Vrms=voltage/1.414;
		Vrms=voltage;
		Nokia5110_OutString("Current");
		Nokia5110_OutUDec(Vrms);

		//Calculation of time
		time=13500/(((Vrms*1000)/1500)-1000);
		Nokia5110_OutString("Time  ");
		Nokia5110_OutUDec(time);
		
		
		//Logic for Brekaer
		if (Vrms>1500){
			Nokia5110_SetCursor(0, 6);
			Nokia5110_OutString("  Fault=1  ");
      SysTick_Wait1ms(time);
			ADCvalue0 = ADC0_InSeq3();
		  Vrms=((ADCvalue0*1000)/4095)*3;
		 
			if(Vrms>1500){
         GPIO_PORTF_DATA_R = 0x02;
		     Nokia5110_SetCursor(0, 20);
         Nokia5110_OutString("CB Trip=1");	}
      	
    }
		
	  else if (Vrms<=1500){
			Nokia5110_SetCursor(0, 6);
			Nokia5110_OutString("  Fault=0  ");
			Nokia5110_SetCursor(0, 30);
			Nokia5110_OutString("CB Trip=0");	
			GPIO_PORTF_DATA_R =0x00; }
}
}
