#include "../aed2.h"



typedef String hostname;
typedef Nat interfaz; 
class Red{
	
	private:

		struct Datos{
			Conj<interfaz> interfaces;
			Dicc<interfaz, hostname> conexiones;
			Dicc<hostname, Conj<Lista(hostname)> > alcanzables;

			Datos(Conj<interfaz> is, Dicc<interfaz, hostname> cs, Dicc<hostname, Conj<Lista(hostname)> > as){
				interfaces = is;
				conexiones = cs;
				alcanzables = as;
			}
		};
		
		Dicc<hostname, Datos> red_;

	public:
		

		Conj<hostname> Computadoras(const Red redi);
		bool Conectadas(const Red redi, const hostname c1, const hostname c2);
		interfaz InterfazUsada(const Red redi, const hostname c1, const hostname c2);
		Red IniciarRed();
		void AgregarCompu(Red redi, const );
		Conectar(Red redi, const hostname c1, int i1, const hostname c2, const int i2);
		Conj<hostname> Vecinos(const Red redi, const hostname);
		bool UsaInterfaz(const Red redi, const hostname c, const interfaz i);
		Conj< Lista<hostname> > CaminosMinimos(const Red redi, const hostname c1, const hostname c2);
		bool HayCamino(const Red redi, const hostname c1, const hostname c2);
		bool operator == (const Red redi) const;
		Copiar


};


Conj<hostname> Computadoras(const Red redi){
	typename  Red::const_Iterador it = redi.CrearIt();
	Conj<hostname> conjcompus;
	while(it.HaySiguiente()){
		conjcompus.AgregarRapido(it.Siguiente());
		it.Avanzar();
	}
	return conjcompus;
}

