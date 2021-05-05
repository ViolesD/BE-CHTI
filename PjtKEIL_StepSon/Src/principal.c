
#include "DriverJeuLaser.h"

void callback_son(void);
void start_son(void);

int main(void)
{
//test modif
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
	
// configuration du Timer 4 en débordement 91ms 6552
	Timer_1234_Init_ff( TIM4, 6552);
	
	//partie pour pwm
	//fixer la prériode du timer
	Timer_1234_Init_ff( TIM3, 1);
	
	//char GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	//unsigned short int PWM_Init_ff( TIM_TypeDef *Timer, char Voie, u32 Periode_ticks );
	

	/*PWM_Init_ff( TIM1, 4, 250);
	Une fois cette fonction exécutée, le timer 1 va compter modulo 250, c'est à dire que la période de la PWM
	sera égale à T PWM =T Ck·250=
	250
	72·106=3,47µs . Sa résolution est naturellement égale à 250. Le signal 
	PWM sortira sur la voie 4 du Timer 1.*/
	
	PWM_Init_ff( TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	PWM_Set_Value_TIM3_Ch3( (unsigned short int)720);

	/*Elle est adaptée au projet, puisqu'elle ne permet l'usage que du Timer 3, canal 3. 
	void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks);
	Exemple (on suppose que la PWM est configurée avec une résolution de 250)


PWM_Set_Value_TIM3_Ch3( 125);
Le signal PWM aura donc un rapport cyclique de 50%
*/
	
	
// Activation des interruptions issues du Timer 4
// Association de la fonction à exécuter lors de l'interruption : timer_callback
// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
	
//** Placez votre code là ** // 	
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );

//============================================================================	
	
	
while	(1)
	{
		start_son();
		for (int i=0;i<5000000;i++){}
	}
}
