iConectar (inout r: estr_red, in c1: hostname, in i1: interfaz, in c2:hostname, in i2:interfaz) 

	//Actualizo conexiones de ambas
	DefinirRapido(Significado(r,c1).conexiones, i1, c2)
	DefinirRapido(Significado(r,c2).conexiones, i2, c1)

	//Actualizo caminos de ambas
	ActualizarCaminos(r, c1, c2)
	ActualizarCaminos(r, c2, c1)

	//Creo conjunto con los actualizados hasta el momento
	actualizados <- Vacio() //conjunto
	AgregarRapido (actualizados, c1)
	AgregarRapido (actualizados, c2)

	//Actualizo resto de la Red
	ActualizarVecinos(r, c1, actualizados)

end fuction


iActualizarCaminos(r, c1, c2)
// Actualiza los caminos de c1 con los de c2.

	// Recorro los alcanzables de c2
	itAlcanzables2 <- crearIt(Significado(r,c2).alcanzables)

	while (HaySiguiente(itAlcanzables2))
		// Recorro alcanzables de c1
		itAlcanzables1 <- crearIt(Significado(r,c1).alcanzables)

		while (HaySiguiente(itAlcanzables1))

			if (SiguienteClave(itAlcanzables2) == SiguienteClave(itAlcanzables1))

				// El alcanzable ya estaba, me fijo que caminos son más cortos
				itCaminos <- crearIt (SiguienteSignificado(itAlcanzables2)) 
				camino2 <- Siguiente(itCaminos) //camino minimo del c2
				itCaminos <- crearIt (SiguienteSignificado(itAlcanzables1)) 
				camino1 <- Siguiente(itCaminos) //camino minimo del c1

				if (longitud(camino1) > longitud(camino2))
					// Los caminos nuevos son mas cortos, borro los que están y copio los nuevos
					Borrar (Significado(r,c1).alcanzables, SiguienteClave(itAlcanzables1))
					// Nuevo alcanzable : me copio los caminos agregando c1 al principio
					itCaminos <- crearIt (SiguienteSignificado(itAlcanzables2)) 
					caminos <- Vacio () //conjunto donde voy a guardar los caminos modificados
					while (HaySiguiente(itCaminos))
						nuevoCamino <- copy(Siguiente(itCaminos)) //copio el camino que voy a modificar
						AgregarAdelante(nuevoCamino, c1) 
						AgregarRapido (caminos, nuevoCamino)
						avanzar (itCaminos)
					end while
					// agrego el nuevo alcanzable con el camino
					DefinirRapido(Significado(r,c1).alcanzables, SiguienteClave(itAlcanzables2), caminos)

				else

					if longitud(camino1) == longitud (camino2)
						//Tengo que agregar los nuevos caminos (modificados) al conjunto de caminos actual
						itCaminos <- crearIt (SiguienteSignificado(itAlcanzables2)) 
						while (HaySiguiente(itCaminos))
							nuevoCamino <- copy(Siguiente(itCaminos)) //copio el camino que voy a modificar
							AgregarAdelante(nuevoCamino, c1) 
							Agregar(SiguienteSignificado(itAlcanzables1), nuevoCamino)
							avanzar (itCaminos)
						end while
					end if

				end if

			else
				// Nuevo alcanzable : me copio los caminos agregando c1 al principio
				itCaminos <- crearIt (SiguienteSignificado(itAlcanzables2)) 
				caminos <- Vacio () //conjunto donde voy a guardar los caminos modificados
				while (HaySiguiente(itCaminos))
					nuevoCamino <- copy(Siguiente(itCaminos)) //copio el camino que voy a modificar
					AgregarAdelante(nuevoCamino, c1) 
					AgregarRapido (caminos, nuevoCamino)
					avanzar (itCaminos)
				end while
				// agrego el nuevo alcanzable con el camino
				DefinirRapido(Significado(r,c1).alcanzables, SiguienteClave(itAlcanzables2), caminos)

			end if

			avanzar (itAlcanzables1) 

		end while

		avanzar (itAlcanzables2)

	end while	

end fuction


iActualizarVecinos(r, c, actualizados)
	// Actualiza los caminos de los vecinos de C, y luego hace recursion para los vecinos de los vecinos
	
	itVecinos <- crearIt (Significado(r, c).conexiones)

	while ( HaySiguiente(itVecinos) )
		// Si todavía no fue actualizado, lo actualizo y hago recursión sobre los vecinos
		if ( SiguienteClave(itVecinos) \notin actualizados)
			ActualizarCaminos(r, SiguienteClave(itVecinos), c )
			AgregarRapido (actualizados, SiguienteClave(itVecinos))
			ActualizarVecinos(r, SiguienteClave(itVecinos), actualizados)
		end if 
	avanzar (itVecinos)
	end while

end fuction




