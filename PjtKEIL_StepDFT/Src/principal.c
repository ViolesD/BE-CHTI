
#include "DriverJeuLaser.h"
#include <stdio.h>

int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal;
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	
int var;
//============================================================================	
	for (int k=1;k<64;k++){
		var=DFT_ModuleAuCarre(&LeSignal,k);
		var++;
		var--;
	}
while	(1)
	{
		
	}
}

