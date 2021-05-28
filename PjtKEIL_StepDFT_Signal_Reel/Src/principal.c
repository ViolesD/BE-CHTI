
#include "DriverJeuLaser.h"
#include <stdio.h>

int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal;

void Systick_Period_ff( unsigned int Periode_ticks );
void Systick_Prio_IT( char Prio, void (*Systick_function)(void) );
int var[64];
short int dma_buf[64];
void callbackSystick(void){
	//faire rien pour l'instant
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for(int k=0; k<64 ; k++){
		var[k]=DFT_ModuleAuCarre(dma_buf,k);
	}
}



int main(void)
{

	
Systick_Period_ff(360000);
Systick_Prio_IT(3,callbackSystick);

SysTick_On ;
SysTick_Enable_IT ;


//pour adc
//Init_TimingADC_ActiveADC_ff( ADC_TypeDef * ADC, u32 Duree_Ech_ticks )
Init_TimingADC_ActiveADC_ff( ADC1, 72 );
Single_Channel_ADC( ADC1, 2 );
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
Init_ADC1_DMA1( 0, dma_buf );




// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	



//============================================================================	
	
while	(1)
	{
		
	}
}

