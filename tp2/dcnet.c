iPaqueteEnTransito? (in d:estr_dcnet, in p:IDpaquete) -> res : bool
	res <- false 															O(1)
	itCompu <- crearIt(d.computadoras)										O(1)
	int i = 0;																O(1)
	while (HaySiguiente(itCompu) && !res)								O(n) x
		itpaq <- crearIt(siguienteSignificado(itCompu).paquetes)			O(1)
		while (haySiguiente(itpaq) && siguiente(itpaq).id != p) 			O(1)
			avanzar(itpaq)													O(1)
		end while
		if (siguiente(itpaq) == p ) res <- true end if 						O(1)
		avanzar(itCompu)																O(1)
	end while


iLaQueMasEnvio (in d:estr_dcnet) -> res : hostname
	res <- siguienteClave(d.conMasEnvios) 										O(1)


iAvanzarSegundo(in d:estr_dcnet)

	//Inicializo arreglo auxiliar donde voy a guardar los paquetes desencolados
	arreglo <- crearArreglo[#claves(d.computadoras)] 
			   de tupla(usado: bool, paquete: paquete, destino: string)
			   donde paquete es tupla (IDpaquete: nat, prioridad: nat, origen: string, destino: string)
	int i
	for ( i=0, i < #Claves(d.computadoras), i++ ) 							  O(n) x
		arreglo[i].usado = false					O(1)
	end for 

	//Inicializo variables
	nat origen
	nat destino
	string proxDest
	paquete paqueteDesencolado
	nat IDpaq
	
	//Inicializo iterador
	itCompu <- crearIt(d.computadoras) 											O(1)
	i <- 0

	//CICLO 1: Desencolo y guardo en vector
	while (HaySiguiente(itCompu))										O(n) x

		if ( !(vacio?(siguienteSignificado(itCompu).paquetes)) )

			//Borro el de mayor prioridad del heap
			itpaquete <- desencolar(siguienteSignificado(itCompu).cola) 					O(log k)

			//Lo elimino del dicc AVL
			borrar (siguienteSignificado(itcompu).paquetesPorID, siguiente(itpaquete).IDpaquete )
																							O(log k)
			//Guardo el paquete en una variable
			paqueteDesencolado <- siguiente(itpaquete)																				

			//Lo elimino del conjunto lineal paquetes
			eliminarSiguiente(itpaquete)

			//Calculo proximo destino fijandome en la matriz

			// El origen lo tengo en O(1) en el significado del iterador de computadoras
			origen <- (siguienteSignificado(itCompu)).indice 		 						 O(1)
			// El destino lo obtengo en O(L) buscando por hostname el destino del paquete, 
			// y luego guardo el indice
			itdestino <- significado(d.porHostname, paqueteDesencolado.destino)   			 O(L)
			destino <- (siguienteSignificado(itdestino)).indice								 O(1)
			proxDest <- d.caminos[origen][destino][1] 								 	     O(1)

			//Lo inserto en el arreglo junto con el destino sólo si el destino no era el final
			if (proxDest != paqueteDesencolado.destino)
				arreglo[i] <- <true, paqueteDesencolado , proxDest> 												  O(1)
			end if 

			//Aumento cantidad de envíos
			siguienteSignificado(itCompu).cantEnvios ++ 								    O(1)

			//Actualizo ConMásEnvíos
			if ( siguienteSignificado(itCompu).cantEnvios > siguienteSignificado(d.conMasEnvios).cantEnvios )
				d.conMasEnvios <- itCompu 											  		O(1)

		end if 

		//Avanzo de computadora
		avanzar(itCompu) 									    O(1)
	
	i ++

	end while

	//CICLO 2: Encolo los paquetes del vector a sus destinos correspondientes
	i <- 0
	while (HaySiguiente(itCompu))										O(n) x									   O(n) x

		if (arreglo[i].usado)

			//Busco el proxDestino guardado en el vector por hostname
			itdestino <- significado(d.porHostname, arreglo[i].destino) 	   		 		O(L)
			
			//Agrego el paquete al conjunto de paquetes del prox destino
			itpaquete <- agregarRapido(siguienteSignificado(itdestino).paquetes, arreglo[i].paquete)

			//Encolo en el heap del destino
			prioridad <- (arreglo[i].paquete).prioridad
			encolar(siguienteSignificado(itdestino).cola, prioridad, itpaquete)   		  O(logk)

			//Lo agrego en el dicc AVL
			IDpaq <= (arreglo[i].paquete).IDpaquete 										O(1)
			definir (siguienteSignificado(itdestino).paquetesPorID, IDpaq, itpaquete )
																						  O(log k)
		end if 

	i++
	avanzar(itCompu)

	end while 



iIgualdadObs (in d1: estr_dcnet, in d2: estr_dcnet) -> res: bool

	//Comparo redes usando = de red
	res = (d1.red == d2.red) 														O(??)

	if (res)

		itCompu <- crearIt(d1.computadoras) 										O(1)
		string host 																O(1)

		//Recorro las computadoras
		while ( HaySiguiente(itCompu) && 	res)							   O(n) x

			host <- siguienteClave(itCompu)											O(1)

			//comparo enEspera usando = de conjunto lineal y cantEnviados 
			res = (enEspera(d1, host) == enEspera(d2, host)							O(?)
					&& cantidadEnviados(d1, host) == cantidadEnviados(d1, host) )   O(?)

			
			itpaq <- crearIt(siguienteSignificado(itCompu).paquetes)				O(1)
			int j <- 0																O(1)
			nat id 																	O(1) 					

			//Recorro paquetes de cada computadora
			while ( HaySiguiente(itpaq) && res )  								 O(k) x

				id <- siguiente(itpaq).IDpaquete 									O(1)

				//comparo caminosrecorridos usando = de listas enlazadas
				res = (caminoRecorrido(d1, id) == caminoRecorrido(d2, id)) 			O(?)

																					
				avanzar (itpaq)														O(1)

			end while 

																					
			avanzar(itCompu)														O(1)
			
		end while

	end if 




















