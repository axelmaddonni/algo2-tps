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

	public:
		

		Conj<hostname> Computadoras();
		bool Conectadas(const hostname c1, const hostname c2);
		interfaz InterfazUsada(const hostname c1, const hostname c2);
		Red IniciarRed();
		void AgregarCompu(const computadora& compu);
		void Conectar(const hostname c1, interfaz i1, const hostname c2, const interfaz i2);
		Conj<hostname> Vecinos(const hostname compu);
		bool UsaInterfaz(const hostname c, const interfaz i);
		Conj< Lista<hostname> > CaminosMinimos(const hostname c1, const hostname c2);
		bool HayCamino(const hostname c1, const hostname c2);
		bool operator == (const Red& otrared) const;
		//++falta copiar++


};


Conj<hostname> Red::Computadoras(){
	typename  Dicc<hostname, Red::Datos>::const_Iterador it = red_.CrearIt();
	Conj<hostname> conjcompus;
	while(it.HaySiguiente()){
		conjcompus.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	return conjcompus;
}

bool Red::Conectadas(const hostname c1, const hostname c2){
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


interfaz Red::InterfazUsada(const hostname c1, const hostname c2){
	typename Dicc<interfaz, hostname>::const_Iterador it = red_.Significado(c1).conexiones.CrearIt();
	while(it.HaySiguiente()){
		if(it.SiguienteSignificado() == c2){
			return it.SiguienteClave();
		}
		it.Avanzar();
	}
}


///++++  IniciarRed deberia ser un constructor?++++

Red IniciarRed(){}

void Red::AgregarCompu(const computadora& compu){
	Conj<interfaz> copycinterfaces( compu.cinterfaces );
	Dicc<interfaz, hostname> pcconexiones;
	Dicc<hostname, Conj< Lista<hostname> > > cjalcanzables;
	//la ip(string) se copia sola?
	Datos datospc( copycinterfaces, pcconexiones, cjalcanzables );
	red_.DefinirRapido(compu.ip, datospc);
}

/*++++++++++++++++++ la hizo axel+++++++++++++++++++
void Conectar(Red redi, const hostname c1, interfaz i1, const hostname c2, const interfaz i2);
*/

Conj<hostname> Red::Vecinos(const hostname compu){
	typename Dicc<interfaz, hostname>::const_Iterador it = red_.Significado(compu).conexiones.CrearIt();
	Conj<hostname> res;
	while(it.HaySiguiente()){
		res.AgregarRapido(it.SiguienteSignificado());
		it.Avanzar();
	}
	return res;
}


bool Red::UsaInterfaz(const hostname c, const interfaz i){
	return red_.Significado(c).conexiones.Definido(i);
}	

Conj< Lista<hostname> > Red::CaminosMinimos(const hostname c1, const hostname c2){
	typename Conj< Lista<hostname> >::const_Iterador itCaminos = red_.Significado(c1).alcanzables.Significado(c2).CrearIt();
	Conj< Lista<hostname> > res;
	while(itCaminos.HaySiguiente()){
		res.AgregarRapido(itCaminos.Siguiente());
		itCaminos.Avanzar();
	}
	return res;
}


bool Red::HayCamino(const hostname c1, const hostname c2){
	return red_.Significado(c1).alcanzables.Definido(c2);
}

bool Red::operator == (const Red& otrared) const{
		//+++ COMPLETAR +++
}

