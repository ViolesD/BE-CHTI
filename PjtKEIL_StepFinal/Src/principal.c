
#include "DriverJeuLaser.h"
#include <stdio.h>
#include "Affichage_Valise.h"
#include "GestionSon.h"

int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal;

void Systick_Period_ff( unsigned int Periode_ticks );
void Systick_Prio_IT( char Prio, void (*Systick_function)(void) );
int var[64];
short int dma_buf[64];
int points[4];
int compteur_100ms=21;
int tab_occurence[4];
int critere;

void maj_points(void){
	// 85   95 	100 120
	// 17   19  20  24
	compteur_100ms++;
	
	if(var[17]>critere) {
		if (compteur_100ms-tab_occurence[0]>20) {
			tab_occurence[0] = compteur_100ms;
			points[0]++;
			start_son();
			Prepare_Afficheur(1, points[0]);
			Mise_A_Jour_Afficheurs_LED();
		}
	}
	if(var[19]>critere) {
		if (compteur_100ms-tab_occurence[1]>20) {
			tab_occurence[1] = compteur_100ms;
			points[1]++;
			start_son();
			Prepare_Afficheur(2, points[1]);
			Mise_A_Jour_Afficheurs_LED();
		}
	}
	if(var[20]>critere) {
		if (compteur_100ms-tab_occurence[2]>20) {
			tab_occurence[2] = compteur_100ms;
			points[2]++;
			start_son();
			Prepare_Afficheur(3, points[2]);
			Mise_A_Jour_Afficheurs_LED();
		}
	}
	if(var[24]>critere) {
		if (compteur_100ms-tab_occurence[3]>20) {
			tab_occurence[3] = compteur_100ms;
			points[3]++;
			start_son();
			Prepare_Afficheur(4, points[3]);
			Mise_A_Jour_Afficheurs_LED();
		}
	}
	
	if (compteur_100ms>10000) {
		compteur_100ms -= 10000;
		for(int i=0;i<4;i++){
			if(tab_occurence[i]>0){
				tab_occurence[i]-=10000;
			}
		}
	}
}
void callbackSystick(void){
	//faire rien pour l'instant
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for(int k=0; k<64 ; k++){
		var[k]=DFT_ModuleAuCarre(dma_buf,k);
	}
	maj_points();
}


/*
char Aff; //c'est le numéro d'afficheur double
char Valeur; // la valeur à afficher de 0 à 99
char LED ;//la LED à allumer ou éteindre, les valeurs possibles sont LED_LCD_R, LED_LCD_V,
void Init_Affichage(void)
void Choix_Capteur(char Capteur)

void Prepare_Afficheur(char Aff, char Valeur);
void Prepare_Set_Point_Unite(char Aff);
void Prepare_Clear_Point_Unite(char Aff);
void Prepare_Set_LED(char LED);
void Prepare_Clear_LED(char LED);

LED_Cible_4, LED_Cible_3, LED_Cible_2, LED_Cible_1.
La fonction qui actualise l'afficheur est :
void Mise_A_Jour_Afficheurs_LED(void
	
	*/




int main(void)
{
	CLOCK_Configure();
	// configuration du Timer 4 en débordement 91ms 6552
	Timer_1234_Init_ff( TIM4, 6552);
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );
	PWM_Init_ff( TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	PWM_Set_Value_TIM3_Ch3( (unsigned short int)720);
	
	critere=0x68db9;
	//critere=critere*critere*64^2/4;
	
	Init_Affichage();
	for(int i=0;i<4;i++){
		points[i]=0;
	}
	
Systick_Period_ff(360000);
Systick_Prio_IT(9,callbackSystick);

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

