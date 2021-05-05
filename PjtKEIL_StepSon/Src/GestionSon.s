	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
			
;short SortieSon;
SortieSon	dcw 0
	EXPORT SortieSon;DIRECTIVES DOIVENT ETRE DECALEES!
;int index_son=0;
index		dcd 0
	EXPORT index

	
; ===============================================================================================
;short SortieSon;
;int index_son=0;
;void callback_son(void){
;	if(index==LongueurSon)
;		index=0;
;	SortieSon=((son[index_son]+32768)*719)/(32768*2);
;	index_son++;
;	PWM(SortieSon);
;}


;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


		
	import Son
	import LongueurSon
	import PWM_Set_Value_TIM3_Ch3

	export start_son
start_son proc
	ldr r2,=index
	mov r1,#0
	str r1,[r2]
	bx lr
	endp

;void callback_son(void){
	EXPORT callback_son
callback_son proc

	push {lr}
	push{r5}
	push{r4}
;récupère les adresses des variables
	ldr r0,=Son
	ldr r1,=SortieSon
	ldr r2,=index
	
;	SortieSon=((son[index_son]+32768)*719)/(32768*2);
;if(index==LongueurSon)
	ldr r3,[r2]
	ldr r4,=LongueurSon
	ldr r4,[r4]
	cmp r3,r4
; index=0;
	beq SUITE
	
	;réucpère son[index_son]
	lsl r5,r3,#1
	
	; signé taille limité
	ldrsh r4,[r0,r5]
; reformatage des valeurs
	ldr r5,=32768
	add r4,r5
	mov r5,#719
	mul r4,r5
	;décalage pour diviser
	asr r4,#16
; stockage en memoire
	str r4,[r1]
	
;	index_son++;	
	add r3,#1
	str r3,[r2]

;	PWM(SortieSon);
	mov r0,r4
	bl PWM_Set_Value_TIM3_Ch3

;}
SUITE
	pop{r4}
	pop{r5}
	pop {lr}
	bx	lr
	endp


	END	