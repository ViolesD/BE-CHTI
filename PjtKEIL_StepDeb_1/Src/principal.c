#include "DriverJeuLaser.h"

extern void Delay_100ms(void);


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers

CLOCK_Configure();

// configuration de PortB.1 (PB1) en sortie push-pull
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	
	
	

//============================================================================	
	
	
while	(1)
	{
		//mets la valeur de PB1 è à après 100 ms 
		Delay_100ms();
		GPIOB_Set(1);
		//mets la valeur de PB1 à 0 après 100 ms 
		Delay_100ms();
		GPIOB_Clear(1);
	}
}
