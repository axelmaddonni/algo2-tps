#ifndef dcnet
#define dcnet
#include<assert.h>
#include<vector>
#include<map>
#include<algorithm>

#include "aed2.h"

using namespace std;

class Dcnet{
private:

	struct Paquete{
		int idpaquete;
		Nat prioridad;
		String origen;
		String destino;
	};

	typedef String hostname;
	//typedef typename Conj<Paquete>::Iterador itConj;

	struct Datos{
		Nat indice;
		Conj<Paquete> paquetes;
		ColaLog<typename Conj<Paquete>::Iterador> cola;
		DiccLog<Nat,typename Conj<Paquete>::Iterador> paqPorid;
		Nat cantEnvios;
	};

	Red_T red;
	Dicc<hostname, Datos> computadoras;
	DiccString<typename Dicc<hostname, Datos>::Iterador> porHostname;
	typename Dicc<hostname, Datos>::Iterador conMasEnvios;
	Arreglo<Arreglo<Lista<hostname>>> caminos;


public:

	red
	caminoRecorrido
	CantidadEnviados
	EnEspera
	IniciarDcnet
	CrearPaquete
	AvanzarSegundo
	PaqueteEnTransito
	LaQueMasEnvio
	==

const Red_T& Red() const;

const Lista<hostname> caminoRecorrido(Nat idpaquete) const;

Nat cantidadEnviados(hostname c) const;

Conj<Paquete> enEspera(hostname c) const;

Dcnet(const Red r); //inicar dcnet

~Dcnet(); //destructor

void crearPaquete(const paquete p);

void avanzarSegundo() const;

bool paqueteEnTransito(const paquete p) const;

Conj<hostname> laQueMasEnvio() const;

bool operator==(Dcnet d&) const;

};