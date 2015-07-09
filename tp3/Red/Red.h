#ifndef RED_H_
#define RED_H_

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

			Datos(const Conj<interfaz>& is, const Dicc<interfaz, hostname>& cs, const Dicc<hostname, Conj< Lista<hostname> > >& as){
				//copia las estructuras usando constructores por copia definidos
				interfaces = is;
				conexiones = cs;
				alcanzables = as;
			}

			bool operator==(const Datos& otrosDatos) const{
				return (interfaces == otrosDatos.interfaces) and (conexiones == otrosDatos.conexiones) and (alcanzables == otrosDatos.alcanzables);
				}
		};
		
		Dicc<hostname, Datos> red_;

		void ActualizarCaminos(const hostname& c1, const hostname& c2);
		void ActualizarVecinos(const hostname& c1, Conj<hostname>& actualizados);

	public:
		

		Conj<hostname> Computadoras() const;
		bool Conectadas(const hostname& c1, const hostname& c2) const;
		interfaz InterfazUsada(const hostname& c1, const hostname& c2) const;
		Red(); //iniciar Red
		Red(const Red& r); //copiar Red
		//~Red(); //uso destructor por defecto
		void AgregarCompu(const computadora& compu);
		void Conectar(const hostname& c1, interfaz i1, const hostname& c2, interfaz i2);
		Conj<hostname> Vecinos(const hostname& compu) const;
		bool UsaInterfaz(const hostname& c, interfaz i) const;
		Conj< Lista<hostname> > CaminosMinimos(const hostname& c1, const hostname& c2) const;
		bool HayCamino(const hostname& c1, const hostname& c2) const;
		bool operator == (const Red& otrared) const;

		Conj<interfaz> Interfaces(const hostname& c) const;

		//IMPRIMIR RED (para testear)
		std::ostream& ImprimirRed(std::ostream& os) const;
};

#endif