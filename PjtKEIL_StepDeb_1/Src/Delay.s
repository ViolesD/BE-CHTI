	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) : genre malloc
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite

;miste à zero de vartime
VarTime	dcd 0
	EXPORT VarTime;DIRECTIVES DOIVENT ETRE DECALEES!
	
; ===============================================================================================
	
;constantes (équivalent du #define en C)
TimeValue	equ 900000

	EXPORT Delay_100ms ; la fonction Delay_100ms est rendue publique donc utilisable par d'autres modules.

		
;Section ROM code (read only) :		
	area    moncode,code,readonly


; REMARQUE IMPORTANTE 
; Cette manière de créer une temporisation n'est clairement pas la bonne manière de procéder :
; - elle est peu précise
; - la fonction prend tout le temps CPU pour... ne rien faire...
;
; Pour autant, la fonction montre :
; - les boucles en ASM
; - l'accés écr/lec de variable en RAM
; - le mécanisme d'appel / retour sous programme
;
; et donc possède un intérêt pour débuter en ASM pur

;définit le début de la procédure
Delay_100ms proc
	;mets la valeur de vartime dans r0
	    ldr r0,=VarTime  ;ro=vartime		  
	;pareil			  
		ldr r1,=TimeValue;ri=timevalue
	;mets la valeur de r1 dans r0 les 32
		str r1,[r0]
;repère pour boucler
BoucleTempo	
;recherche en mémoire à l'adresse r0 et placé dans r1
		ldr r1,[r0]     				
	;soustraire 1 à r1 et le S est la pour mettre à jour le flag (qui permet de boucler après)
		subs r1,#1
		; mettre ne mémoire
		str  r1,[r0]
		;regarde si le flag Z est à 1 et sinon il boucle 
		bne	 BoucleTempo
		;saute à l'adresse contenue dans lr qui est le retour de la fonction delay_100ms
		bx lr
		
		endp
		
		
	END	