#include "../aed2.h"

typedef String hostname;
typedef Nat interfaz; 

struct computadora{
	hostname ip;
	Conj<interfaz> cinterfaces;

	computadora(hostname ipnueva, Conj<interfaz> cji){
		ip = ipnueva;
		cinterfaces = cji;
	}
};

class Red{
	
	private:

		struct Datos{
			Conj<interfaz> interfaces;
			Dicc<interfaz, hostname> conexiones;
			Dicc<hostname, Conj< Lista<hostname> > > alcanzables;

			Datos(Conj<interfaz> is, Dicc<interfaz, hostname> cs, Dicc<hostname, Conj< Lista<hostname> > > as){
				interfaces = is;
				conexiones = cs;
				alcanzables = as;
			}
		};
		
		Dicc<hostname, Datos> red_;

		void ActualizarCaminos(const hostname c1, const hostname c2);
		void ActualizarVecinos(const hostname c1, Conj<hostname>& actualizados);

	public:
		
		Conj<hostname> Computadoras() const;
		bool Conectadas(const hostname c1, const hostname c2) const;
		interfaz InterfazUsada(const hostname c1, const hostname c2) const;
		Red(); //iniciar Red
		Red(const Red& r); //copiar Red
		void AgregarCompu(const computadora compu);
		void Conectar(const hostname c1, interfaz i1, const hostname c2, const interfaz i2);
		Conj<hostname> Vecinos(const hostname) const;
		bool UsaInterfaz(const hostname c, const interfaz i) const;
		Conj< Lista<hostname> > CaminosMinimos(const hostname c1, const hostname c2) const;
		bool HayCamino(const hostname c1, const hostname c2) const;
		bool operator == (const Red redi) const;
		

};


Conj<hostname> Red::Computadoras() const{
	typename  Dicc<hostname, Red::Datos>::const_Iterador it = red_.CrearIt();
	Conj<hostname> conjcompus;
	while(it.HaySiguiente()){
		conjcompus.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	return conjcompus;
}

bool Red::Conectadas(const hostname c1, const hostname c2) const{
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

void Red::Conectar(const hostname c1, interfaz i1, const hostname c2, const interfaz i2){
	//actualizo conexiones de ambas
	red_.Significado(c1).conexiones.DefinirRapido(i1, c2);
	red_.Significado(c2).conexiones.DefinirRapido(i2, c1);
	//actualizo caminos de ambas
	this->ActualizarCaminos(c1, c2);
	this->ActualizarCaminos(c2, c1);
	//creo conjuntos con los actualizados hasta el momento
	Conj<hostname> actualizados = Conj<hostname>();
	actualizados.AgregarRapido(c1);
	actualizados.AgregarRapido(c2);
	//actualizo caminos del resto de la red por recursion
	this->ActualizarVecinos(c1, actualizados);
}

void Red::ActualizarCaminos(const hostname c1, const hostname c2){

	typename Conj< Lista<hostname> >::Iterador itCaminos;
	Conj< Lista<hostname> > caminos;
	Lista<hostname> camino1;
	Lista<hostname> camino2;
	Lista<hostname> nuevoCamino;

	//Actualiza caminos de c1 con los de c2
	//recorro alcanzables de c2
	typename Dicc<hostname, Conj< Lista<hostname> > >::Iterador itAlcanzables2 = red_.Significado(c2).alcanzables.CrearIt();
	while(itAlcanzables2.HaySiguiente()){
		//recorro alcanzables de c1
		typename Dicc<hostname, Conj< Lista<hostname> > >::Iterador itAlcanzables1 = red_.Significado(c1).alcanzables.CrearIt();
		while(itAlcanzables1.HaySiguiente()){
			if(itAlcanzables2.SiguienteClave() == itAlcanzables1.SiguienteClave()){
				//el alcanzable ya estaba, me fijo que caminos son más cortos
				itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
				camino2 = itCaminos.Siguiente();
				itCaminos = itAlcanzables1.SiguienteSignificado().CrearIt();
				camino1 = itCaminos.Siguiente();
				if (camino1.Longitud() > camino2.Longitud()){
					//los caminos nuevos son más cortos, borro los que ya están y copio los nuevos
					red_.Significado(c1).alcanzables.Borrar(itAlcanzables1.SiguienteClave());
					//nuevo alcanzable: me copio los caminos agregando c1 al principio
					itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
					caminos = Conj< Lista<hostname> >(); //vacio
					while (itCaminos.HaySiguiente()){
						nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
						nuevoCamino.AgregarAdelante(c1);
						caminos.AgregarRapido(nuevoCamino);
						itCaminos.Avanzar(); 
					}
					//agrego el nuevo alcanzable con el camino
					red_.Significado(c1).alcanzables.DefinirRapido(itAlcanzables2.SiguienteClave(), caminos);					
				}else{
					if (camino1.Longitud() == camino2.Longitud()){
						//tengo que agregar los nuevos caminos(modificados) al conjunto de caminos actual
						itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
						while(itCaminos.HaySiguiente()){
							nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
							nuevoCamino.AgregarAdelante(c1);
							itAlcanzables1.SiguienteSignificado().Agregar(nuevoCamino);
							itCaminos.Avanzar();
						}
					}
				}
			}else{
				//Nuevo alcanzable: me copio los caminos agregando c1 al principio
				itCaminos = itAlcanzables2.SiguienteSignificado().CrearIt();
				caminos = Conj< Lista<hostname> >(); //vacio
				while(itCaminos.HaySiguiente()){
					nuevoCamino = Lista<hostname>(itCaminos.Siguiente());
					nuevoCamino.AgregarAdelante(c1);
					caminos.AgregarRapido(nuevoCamino);
					itCaminos.Avanzar();
				}
				red_.Significado(c1).alcanzables.DefinirRapido(itAlcanzables2.SiguienteClave(), caminos);
			}
			itAlcanzables1.Avanzar();
		}
		itAlcanzables2.Avanzar();
	}
}


void Red::ActualizarVecinos(const hostname c1, Conj<hostname>& actualizados){
	//Actualiza los caminos de los vecinos de C, y luego hace recursión para los vecinos de los vecinos.
	typename Dicc<interfaz, hostname>::Iterador itVecinos = red_.Significado(c1).conexiones.CrearIt();
	while(itVecinos.HaySiguiente()){
		//Si todavía no fue actualizado, lo actualizo y hago recursión sobre los vecinos
		if ( !actualizados.Pertenece(itVecinos.SiguienteSignificado()) ){
			this->ActualizarCaminos(itVecinos.SiguienteSignificado(), c1);
			actualizados.AgregarRapido(itVecinos.SiguienteSignificado());
			this->ActualizarVecinos(itVecinos.SiguienteSignificado(), actualizados);
		}
		itVecinos.Avanzar();
	}
}

