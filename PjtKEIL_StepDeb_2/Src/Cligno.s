	PRESERVE8
	THUMB   
		

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





		
		
	END	