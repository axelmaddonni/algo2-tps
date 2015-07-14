#ifndef DCNET_H_
#define DCNET_H_

#include "../aed2.h"
#include "../Heap/Heap.hpp"
#include "../TRIE/dicc_trie.h"
#include "../AA/diccLog.h"
#include "../Red/Red.h"

	typedef String hostname;

	struct Paquete{
		Nat idpaquete;
		Nat prioridad;
		String origen;
		String destino;

		Paquete(Nat id, Nat p, String o, String d){
			idpaquete = id;
			prioridad = p;
			origen = o;
			destino = d;
		}

		Paquete() {
			idpaquete = 0;
			prioridad = 0;
			origen = "";
			destino = "";
		}

		Paquete(const Paquete& otro){
			idpaquete = otro.idpaquete;
			prioridad = otro.prioridad;
			origen = String(otro.origen);
			destino = String(otro.destino);
		}

		void operator=(const Paquete& otro){
			idpaquete = otro.idpaquete;
			prioridad = otro.prioridad;
			origen.assign(otro.origen);
			destino.assign(otro.destino);
		}

		bool operator==(const Paquete& otro) const{
			return (idpaquete == otro.idpaquete) and (prioridad==otro.prioridad) and (origen==otro.origen) and (destino==otro.destino);
		}

		std::ostream& ImprimirPaquete(std::ostream& os) const{
			os << "Paquete " << idpaquete << ", prioridad " << prioridad ;
			os << ", Origen: " << origen << ", Destino: " << destino;
			return os;
		}

	};


class Dcnet{
private:

	struct Datos{
		Nat indice;
		Conj<Paquete> paquetes;
		ColaLog<typename Conj<Paquete>::Iterador> cola; 
		diccLog<Nat,typename Conj<Paquete>::Iterador> paqPorid;
		Nat cantEnvios;

		Datos(Nat i, Conj<Paquete> p, ColaLog<typename Conj<Paquete>::Iterador> c, diccLog<Nat,typename Conj<Paquete>::Iterador> pxid, Nat ce) {
				indice = i;
				paquetes = p;
				cola = c;
				paqPorid = pxid;
				cantEnvios = ce;
			}
			
		void sumarEnvio(){
			cantEnvios++;
		}

	};
	
	Red red;

	Dicc<hostname, Datos> computadoras;

	DiccString<typename Dicc<hostname, Datos>::Iterador> porHostname;

	typename Dicc<hostname, Datos>::Iterador conMasEnvios;

	Arreglo<Arreglo<Lista<hostname> > > caminos;

	struct TuplaDestinos{
		Paquete paquete;
		hostname destino;

		TuplaDestinos(Paquete& p, hostname s){
			paquete = p;
			destino = s;
		}
	};


public:

	const Red& DameRed() const;

	const Lista<hostname>& CaminoRecorrido(Nat idpaquete) const; //devolvemos por referencia

	Nat CantidadEnviados(hostname c) const ; 

	Conj<Paquete>& EnEspera(hostname c) const ; 

	Dcnet();

	//Dcnet(const Red& r); //iniciar dcnet
	
	void IniciarDcnet(const Red& r); //iniciar dcnet


	//~Dcnet(); //destructor

	void CrearPaquete(const Paquete& p);

	void AvanzarSegundo();

	bool PaqueteEnTransito(Nat p) const;

	const hostname& LaQueMasEnvio() const;

	bool operator==(Dcnet& d) const; 

	std::ostream& ImprimirDcnet(std::ostream& os) const;

	const Paquete& damePaquete(Nat idpaquete) const;

};

#endif