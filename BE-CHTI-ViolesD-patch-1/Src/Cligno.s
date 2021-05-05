	PRESERVE8
	THUMB   
	include Driver/DriverJeuLaser.inc

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		

; ===============================================================================================
	
; inclure DriverJeuLaser.inc

		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

;*char FlagCligno
;void timer _callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
;}


;*char FlagCligno => on utilise juste un registre pas besoin de variable?
;miste à zero de FlagCligno
FlagCligno	dcd 0
	EXPORT FlagCligno;DIRECTIVES DOIVENT ETRE DECALEES!
		
;void timer _callback(void)
	EXPORT timer_callback
timer_callback proc
	push {lr}	
;{
;	if (FlagCligno==1)
	LDR	r0,=FlagCligno
	LDR r1,[r0]
	cmp r1,#1
	bne SINON
;	{
;alors
;		FlagCligno=0;
	mov r2,#0
	STR r2,[r0]
;		GPIOB_Set(1);
	mov r0,#1
	BL GPIOB_Set
	B FINSI
	
;	}
;	else
;	{
;		FlagCligno=1;
SINON
	mov r2,#1
	STR r2,[r0]
;		GPIOB_Clear(1);
	mov r0,#1
	BL GPIOB_Set
	B FINSI
;	}	
FINSI
	pop {lr}
	bx	lr
	;ou pop pc;
;}
	endp


		
		
	END	