#include "Red.h"

Conj<interfaz> Red::Interfaces(const hostname& c) const{

	return red_.Significado(c).interfaces;

}

Conj<hostname> Red::Computadoras() const{
	typename  Dicc<hostname, Red::Datos>::const_Iterador it = red_.CrearIt();
	Conj<hostname> conjcompus;
	while(it.HaySiguiente()){
		conjcompus.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	return conjcompus;
}

bool Red::Conectadas(const hostname& c1, const hostname& c2) const{
	typename Dicc<interfaz, hostname>::const_Iterador it = red_.Significado(c1).conexiones.CrearIt();
	bool res = false;
	while(it.HaySiguiente() && (!res)){
		if(it.SiguienteSignificado() == c2){
			res = true;
		}
		it.Avanzar();
	}
	return res;
}


interfaz Red::InterfazUsada(const hostname& c1, const hostname& c2) const{
	typename Dicc<interfaz, hostname>::const_Iterador it = red_.Significado(c1).conexiones.CrearIt();
	while(it.HaySiguiente()){
		if(it.SiguienteSignificado() == c2){
			return it.SiguienteClave();
		}
		it.Avanzar();
	}
	return 0;
}

//Constructores

//Iniciar Red
Red::Red(){
	red_ = Dicc<hostname, Datos>();
}

//Copiar Red
Red::Red(const Red& r){
	red_ = Dicc<hostname, Datos>();
	//Creo una red vacía.
	typename Dicc<hostname, Datos>::const_Iterador itRed = r.red_.CrearIt();
	while (itRed.HaySiguiente()){
		String copiaHostname = String(itRed.SiguienteClave());
		Datos data = Datos(itRed.SiguienteSignificado().interfaces, itRed.SiguienteSignificado().conexiones, itRed.SiguienteSignificado().alcanzables);
		red_.DefinirRapido(copiaHostname, data);
		itRed.Avanzar();
	}
}


void Red::AgregarCompu(const computadora& compu){
	Datos datospc = Datos(compu.cinterfaces, Dicc<interfaz, hostname>(), Dicc<hostname, Conj< Lista<hostname> > >());
	String copiaID = String(compu.ip);
	red_.Definir(copiaID, datospc);
}

void Red::Conectar(const hostname& c1, interfaz i1, const hostname& c2, interfaz i2){
	//actualizo conexiones de ambas
	red_.Significado(c1).conexiones.DefinirRapido(i1, c2);
	red_.Significado(c2).conexiones.DefinirRapido(i2, c1);
	//actualizo el camino de c1 a c2
	Conj< Lista<hostname> > nc1 = Conj< Lista<hostname> >();
	Lista<hostname> nl1 = Lista<hostname>();
	nl1.AgregarAtras(c2);
	nc1.AgregarRapido(nl1);
	red_.Significado(c1).alcanzables.Definir(c2, nc1);
	//actualizo el camino de c2 a c1
	Conj< Lista<hostname> > nc2 = Conj< Lista<hostname> >();
	Lista<hostname> nl2 = Lista<hostname>();
	nl2.AgregarAtras(c1);
	nc2.AgregarRapido(nl2);
	red_.Significado(c2).alcanzables.Definir(c1, nc2);
	//actualizo otros caminos de ambas 
	this->ActualizarCaminos(c1, c2);
	this->ActualizarCaminos(c2, c1);

	//actualizo los caminos del resto la red
	Conj<hostname> actualizados = Conj<hostname>();
	this->ActualizarVecinos(c1, actualizados);

/*	-----------------------------------------------------------------------

	usando un while con iteradores de la red :

	typename Dicc<hostname, Datos>::const_Iterador itRed = red_.CrearIt();
	
	while ( actualizados.Cardinal() != red_.CantClaves() ){
		if (!actualizados.Pertenece(itRed.SiguienteClave()) ){
			actualizados.AgregarRapido(itRed.SiguienteClave());
			ActualizarVecinos(itRed.SiguienteClave(), actualizados);
		}
		itRed.Avanzar();
	}

	------------------------------------------------------------------------

	usando recursion: (version 1)

	//creo conjuntos con los actualizados hasta el momento
	Conj<hostname> actualizados = Conj<hostname>();
	actualizados.AgregarRapido(c1);
	actualizados.AgregarRapido(c2);
	Conj<hostname> vecinosActualizados = Conj<hostname>();
	vecinosActualizados.AgregarRapido(c2);
	//actualizo caminos del resto de la red por recursion
	this->ActualizarVecinos(c1, actualizadosGlobal, vecinosActualizados);

*/

}

//funcion private
void Red::ActualizarVecinos(const hostname& c1, Conj<hostname>& actualizados){
	
	typename Dicc<interfaz, hostname>::Iterador itVecinos = red_.Significado(c1).conexiones.CrearIt();
	while(itVecinos.HaySiguiente()){
		//Si todavía no fue actualizado, lo actualizo
		if ( !actualizados.Pertenece(itVecinos.SiguienteSignificado()) ){
			this->ActualizarCaminos(c1, itVecinos.SiguienteSignificado());
			this->ActualizarCaminos(itVecinos.SiguienteSignificado(), c1);
		}
		itVecinos.Avanzar();
	}
	actualizados.Agregar(c1);

	itVecinos = red_.Significado(c1).conexiones.CrearIt();
	while(itVecinos.HaySiguiente()){
		//recursion sobre los vecinos que no habian sido actualizados
		if ( !actualizados.Pertenece(itVecinos.SiguienteSignificado()) ){
			this->ActualizarVecinos(itVecinos.SiguienteSignificado(), actualizados);
		}
		itVecinos.Avanzar();
	}
}

/*
//funcion private
void Red::ActualizarVecinos(const hostname c1, Conj<hostname>& actualizadosGlobal, Conj<hostname>& vecinosActualizados){
	//Actualiza los caminos de los vecinos de C, y luego hace recursión para los vecinos de los vecinos.
	typename Dicc<interfaz, hostname>::Iterador itVecinos = red_.Significado(c1).conexiones.CrearIt();
	actualizadosGlobal.Agregar(c1);
	while(itVecinos.HaySiguiente()){
		//Si todavía no fue actualizado, lo actualizo y hago recursión sobre los vecinos
		if ( !actualizadosGlobal.Pertenece(itVecinos.SiguienteSignificado()) && 
			 !vecinosActualizados.Pertenece(itVecinos.SiguienteSignificado()) ){
			this->ActualizarCaminos(c1, itVecinos.SiguienteSignificado());
			this->ActualizarCaminos(itVecinos.SiguienteSignificado(), c1);
			vecinosActualizados.AgregarRapido(itVecinos.SiguienteSignificado());
			Conj<hostname> vecinosNuevos = Conj<hostname>();
			this->ActualizarVecinos(itVecinos.SiguienteSignificado(), actualizadosGlobal, vecinosNuevos);
		}
		itVecinos.Avanzar();
	}
	
}
*/

//funcion private
void Red::ActualizarCaminos(const hostname& c1, const hostname& c2){

	typename Conj< Lista<hostname> >::Iterador itCaminos;
	Conj< Lista<hostname> > caminos;
	Lista<hostname> camino1;
	Lista<hostname> camino2;
	Lista<hostname> nuevoCamino;

	bool ready = false;

	//Actualiza caminos de c1 con los de c2
	//recorro alcanzables de c2
	typename Dicc<hostname, Conj< Lista<hostname> > >::Iterador itAlcanzables2 = red_.Significado(c2).alcanzables.CrearIt();
	while(itAlcanzables2.HaySiguiente()){
		//recorro alcanzables de c1
		typename Dicc<hostname, Conj< Lista<hostname> > >::Iterador itAlcanzables1 = red_.Significado(c1).alcanzables.CrearIt();
		while(itAlcanzables1.HaySiguiente() && !ready){
			if(itAlcanzables2.SiguienteClave() == itAlcanzables1.SiguienteClave()){
				//el alcanzable ya estaba, me fijo que caminos son más cortos
				ready = true;
				itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
				camino2 = itCaminos.Siguiente();
				itCaminos = itAlcanzables1.SiguienteSignificado().CrearIt();
				camino1 = itCaminos.Siguiente();
				if (camino1.Longitud() > camino2.Longitud() + 1){
					//los caminos nuevos son más cortos, borro los que ya están y copio los nuevos
					//red_.Significado(c1).alcanzables.Borrar(itAlcanzables1.SiguienteClave());
					//nuevo alcanzable: me copio los caminos agregando c1 al principio
					itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
					caminos = Conj< Lista<hostname> >(); //vacio
					while (itCaminos.HaySiguiente()){
						nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
						nuevoCamino.AgregarAdelante(c2);
						caminos.AgregarRapido(nuevoCamino);
						itCaminos.Avanzar(); 
					}
					//agrego el nuevo alcanzable con el camino
					red_.Significado(c1).alcanzables.Definir(itAlcanzables2.SiguienteClave(), caminos);			
				}else{
					if (camino1.Longitud() == camino2.Longitud() + 1){
						//tengo que agregar los nuevos caminos(modificados) al conjunto de caminos actual
						itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
						while(itCaminos.HaySiguiente()){
							nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
							nuevoCamino.AgregarAdelante(c2);
							itAlcanzables1.SiguienteSignificado().Agregar(nuevoCamino);
							itCaminos.Avanzar();
						}
					}
				}
			}
			itAlcanzables1.Avanzar();
		}
			if (!ready && itAlcanzables2.SiguienteClave() != c1){
				//Nuevo alcanzable: me copio los caminos agregando c2 al principio
				itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
				caminos = Conj< Lista<hostname> >(); //vacio
				while(itCaminos.HaySiguiente()){
					nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
					nuevoCamino.AgregarAdelante(c2);
					caminos.AgregarRapido(nuevoCamino);
					itCaminos.Avanzar();
				}
				red_.Significado(c1).alcanzables.DefinirRapido(itAlcanzables2.SiguienteClave(), caminos);
			}
		ready = false;	
		itAlcanzables2.Avanzar();
	}
}



Conj<hostname> Red::Vecinos(const hostname& compu) const{
	typename Dicc<interfaz, hostname>::const_Iterador it = red_.Significado(compu).conexiones.CrearIt();
	Conj<hostname> res = Conj<hostname>();
	while(it.HaySiguiente()){
		res.AgregarRapido(it.SiguienteSignificado());
		it.Avanzar();
	}
	return res;
}


bool Red::UsaInterfaz(const hostname& c, interfaz i) const{
	return red_.Significado(c).conexiones.Definido(i);
}	

Conj< Lista<hostname> > Red::CaminosMinimos(const hostname& c1, const hostname& c2) const{
	typename Conj< Lista<hostname> >::const_Iterador itCaminos = red_.Significado(c1).alcanzables.Significado(c2).CrearIt();
	Conj< Lista<hostname> > res = Conj< Lista<hostname> >();
	while(itCaminos.HaySiguiente()){
		res.AgregarRapido(itCaminos.Siguiente());
		itCaminos.Avanzar();
	}
	return res;
}


bool Red::HayCamino(const hostname& c1, const hostname& c2) const{
	return red_.Significado(c1).alcanzables.Definido(c2);
}

bool Red::operator == (const Red& otrared) const{
		return red_ == otrared.red_;
}

std::ostream& Red::ImprimirRed(std::ostream& os) const{
	typename Dicc<hostname, Datos>::const_Iterador itRed = red_.CrearIt();
	os << "Información de la Red:" << std::endl;
	while (itRed.HaySiguiente()){
		
		os << "Hostname: " << itRed.SiguienteClave() << std::endl;
		
		os << "Interfaces: ";
		Mostrar(os, itRed.SiguienteSignificado().interfaces, '[', ']');
		os << std::endl;
		
		os << "Conexiones: ";
		typename Dicc<interfaz, hostname>::const_Iterador itConex = itRed.SiguienteSignificado().conexiones.CrearIt();
		while (itConex.HaySiguiente()){
			os << '(' << itConex.SiguienteClave() << ',' << itConex.SiguienteSignificado() << ") ";	
			itConex.Avanzar();		
		}	
		os << std::endl;

		os << "Alcanzables: " << std::endl;
		typename Dicc<hostname, Conj< Lista<hostname> > >::const_Iterador itAlcanz = itRed.SiguienteSignificado().alcanzables.CrearIt();
		while (itAlcanz.HaySiguiente()){
			os << itAlcanz.SiguienteClave() << ": " ;
			Mostrar(os, itAlcanz.SiguienteSignificado(), '{', '}');
			os << std::endl;
			itAlcanz.Avanzar();
		}
		os << std::endl << std::endl;
		itRed.Avanzar();
	}
	return os;
}
