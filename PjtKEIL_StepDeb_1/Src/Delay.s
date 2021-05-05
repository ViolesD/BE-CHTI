	PRESERVE8
	THUMB   
		

; ====================== zone de r�servation de donn�es,  ======================================
;Section RAM (read only) : genre malloc
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite

;miste � zero de vartime
VarTime	dcd 0
	EXPORT VarTime;DIRECTIVES DOIVENT ETRE DECALEES!
	
; ===============================================================================================
	
;constantes (�quivalent du #define en C)
TimeValue	equ 900000

	EXPORT Delay_100ms ; la fonction Delay_100ms est rendue publique donc utilisable par d'autres modules.

		
;Section ROM code (read only) :		
	area    moncode,code,readonly


; REMARQUE IMPORTANTE 
; Cette mani�re de cr�er une temporisation n'est clairement pas la bonne mani�re de proc�der :
; - elle est peu pr�cise
; - la fonction prend tout le temps CPU pour... ne rien faire...
;
; Pour autant, la fonction montre :
; - les boucles en ASM
; - l'acc�s �cr/lec de variable en RAM
; - le m�canisme d'appel / retour sous programme
;
; et donc poss�de un int�r�t pour d�buter en ASM pur

;d�finit le d�but de la proc�dure
Delay_100ms proc
	;mets la valeur de vartime dans r0
	    ldr r0,=VarTime  ;ro=vartime		  
	;pareil			  
		ldr r1,=TimeValue;ri=timevalue
	;mets la valeur de r1 dans r0 les 32
		str r1,[r0]
;rep�re pour boucler
BoucleTempo	
;recherche en m�moire � l'adresse r0 et plac� dans r1
		ldr r1,[r0]     				
	;soustraire 1 � r1 et le S est la pour mettre � jour le flag (qui permet de boucler apr�s)
		subs r1,#1
		; mettre ne m�moire
		str  r1,[r0]
		;regarde si le flag Z est � 1 et sinon il boucle 
		bne	 BoucleTempo
		;saute � l'adresse contenue dans lr qui est le retour de la fonction delay_100ms
		bx lr
		
		endp
		
		
	END	