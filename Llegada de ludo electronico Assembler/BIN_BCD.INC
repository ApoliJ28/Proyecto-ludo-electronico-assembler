	CBLOCK 						; Definida a continuación de la ultima asignada (En las subrutinas no se debe fijar la dirección de la RAM)
	Centenas					; Dirección 0x0C.
	Decenas						; Dirección 0x0D.
	Unidades					; Dirección 0x0E.
	ENDC						; Terminamos de asignar las direcciones.
BIN_a_BCD						; Subrutina para convertir de binario a decimal.
	clrf Centenas				; Pone en cero la registro "Centenas".
	clrf Decenas				; Pone en cero el registro "Decenas".
	movwf Unidades				; Se copia el dato W que es el "Numero a convertir", al registro "Unidades".
Resta_10						; Restamos 10 a las unidades hasta que las unidades sean menor a 10 en decimal.
	movlw d'10'					; Movemos el valor literal al registro W para restar lo con las unidades.
	subwf Unidades,0			; Operación arítmetica, W = Unidades - W.
	btfss STATUS,0				; Si las unidades es mayor a 10 salta, ¿W es positivo?, ¿Si C=1?
	goto FIN_BIN_a_BCD			; Es menor a 10, se acabo. Ir a la etiqueta FIN_BIN_a_BCD.
Incrementa_Decenas				; Incrementa en uno las decenas mientras que las unidades sean mayor a 10.
	movwf Unidades				; Guarda el resultado anterior de la resta.
	incf Decenas,1				; Incrementamos en 1 el registro "Decenas" y lo guardamos en el mismo registro.
	movlw d'10'					; Movemos el valor literal al registro W para restar lo con las decenas.
	subwf Decenas,0				; Operación arítmetica, W = Decenas - W.
	btfss STATUS,2				; Si las decenas son igual a diez salta, ¿C=1?
	goto Resta_10				; No es igual a 10, Vuelve a restar 10 al numero.
Incrementa_Centenas				; Incrementamos en 1 las decenas mientras que las decenas sean igual a 10.
	clrf Decenas				; Ponemos las decenas en cero ya que llego a 10.
	incf Centenas,1				; Incrementamos en 1 el registro "Centenas" y lo guardamos en el mismo.
	goto Resta_10				; Volvemos a restar 10 al numero.
FIN_BIN_a_BCD					; Ya que terminamos en convertir, copiamos los datos de la decenas y unidades al registro W Para poder moverlo a la salida para visualizarlo.
	swapf Decenas,0				; Cambiamos los nibles de alto y bajo, y guardamos el dato en el registro W. Ejemplo: 0x01 -> 0x10
	addwf Unidades,0			; Operación arítmetica, W = W + Unidades.
	return						; Retornamos de la subrutina. Vuelve al programa principal.
