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
		void AgregarCompu(const computadora compu);
		void Conectar(const hostname c1, interfaz i1, const hostname c2, const interfaz i2);
		Conj<hostname> Vecinos(const hostname);
		bool UsaInterfaz(const hostname c, const interfaz i);
		Conj< Lista<hostname> > CaminosMinimos(const hostname c1, const hostname c2);
		bool HayCamino(const hostname c1, const hostname c2);
		bool operator == (const Red redi) const;
		//Falta Copiar


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




interfaz InterfazUsada(const hostname c1, const hostname c2);
Red IniciarRed();

void AgregarCompu(Red redi, const computadora compu){

}

void Conectar(Red redi, const hostname c1, interfaz i1, const hostname c2, const interfaz i2);
Conj<hostname> Vecinos(const hostname);
bool UsaInterfaz(const hostname c, const interfaz i);
Conj< Lista<hostname> > CaminosMinimos(const hostname c1, const hostname c2);
bool HayCamino(const hostname c1, const hostname c2);
bool operator == (const Red red1, const Red red2);
