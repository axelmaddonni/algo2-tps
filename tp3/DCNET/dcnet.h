#ifndef dcnet
#define dcnet

#include "../aed2.h"
#include "../Heap/Heap.hpp"
#include "../TRIE/dicc_trie.h"
#include "../AA/diccLog.h"
#include "../Red/Red.h"


	typedef String hostname;

	struct Paquete{
		int idpaquete;
		Nat prioridad;
		String origen;
		String destino;
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
	};
	
	Red red;

	Dicc<hostname, Datos> computadoras;

	DiccString<typename Dicc<hostname, Datos>::Iterador> porHostname;

	typename Dicc<hostname, Datos>::Iterador conMasEnvios;

	Arreglo<Arreglo<Lista<hostname> > > caminos;


public:

	const Red& dameRed() const;

	const Lista<hostname>& caminoRecorrido(Nat idpaquete) const; //devolvemos por referencia

	Nat cantidadEnviados(hostname c); //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER

	Conj<Paquete>& enEspera(hostname c); //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER

	Dcnet(const Red& r); //inicar dcnet

	~Dcnet(); //destructor

	void crearPaquete(const Paquete p);

	void avanzarSegundo() const;

	bool paqueteEnTransito(Nat p) const;

	hostname laQueMasEnvio() const;

	bool operator==(Dcnet& d) const;

};

//Red
const Red& Dcnet::dameRed() const{
	return red;
}

//Camino Recorrido
const Lista<hostname>& Dcnet::caminoRecorrido(Nat idpaquete) const{
	typename Dicc<hostname, Datos>::const_Iterador itCompu = computadoras.CrearIt();
	
	bool yaEncontrado = false;
	Paquete p;

	while (itCompu.HaySiguiente() && !yaEncontrado){
		if  ( (itCompu.SiguienteSignificado().paqPorid).Definido(idpaquete) ){
			p = ((itCompu.SiguienteSignificado()).paqPorid).Significado(idpaquete).Siguiente();
			yaEncontrado = true;
		}else{
			itCompu.Avanzar();
		}
	}
	return caminos[(computadoras.Significado(p.origen)).indice][(itCompu.SiguienteSignificado()).indice];
}

//Paquetes enviados
Nat Dcnet::cantidadEnviados(hostname c) { //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER
	return (porHostname.obtener(c))->SiguienteSignificado().cantEnvios;
}

//En Espera
Conj<Paquete>& Dcnet::enEspera(hostname c) { //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER
	return (porHostname.obtener(c))->SiguienteSignificado().paquetes;
}


//Iniciar Dcnet
Dcnet::Dcnet(const Red& r){

	//Completo computadoras y porHostname:

	//creo un diccionario lineal
	computadoras = Dicc<hostname, Datos>();
	//creo un diccionario universal (trie)
	porHostname =  DiccString<typename Dicc<hostname, Dcnet::Datos>::Iterador>(); 

	//creo una lista vacía donde voy a guardar los hostnames y ordenarlos
	Lista<hostname> listaComp = Lista<hostname>();
	Conj<hostname>::const_Iterador itCompus = r.Computadoras().CrearIt();

	while (itCompus.HaySiguiente()){
		//agrego el hostname a la lista de computadoras
		listaComp.AgregarAtras(itCompus.Siguiente());
		/* LO HICE CUANDO CALCULAMOS LOS INDICES
		//Inicializo DATOS (inicia el indice como cero, mas adelante les pondremos valor)
		Dcnet::Datos X = Datos(0, Conj<Paquete>(), ColaLog<typename Conj<Paquete>::Iterador>(), diccLog<Nat,typename Conj<Paquete>::Iterador>(), 0);
		typename Dicc<hostname, Datos>::Iterador itX = computadoras.DefinirRapido(itCompus.Siguiente(), X);
		porHostname.definir(itCompus.Siguiente(), itX);
		*/
		itCompus.Avanzar();
	}		

	//Hago esto para asignar los indices por orden alfabético
	Nat indice = 0;
	Nat cant = r.Computadoras().Cardinal();
	hostname min;
	Lista<hostname>::Iterador itHostname;
	while (indice < cant ){
		//busco el minimo de la lista de hostnames
		itHostname = listaComp.CrearIt();
		min = itHostname.Siguiente();
		itHostname.Avanzar();
		while (itHostname.HaySiguiente()){
			if (min < itHostname.Siguiente()){
				min = itHostname.Siguiente();
			}
			itHostname.Avanzar();
		}
		//Inicializo DATOS (inicia el indice como cero, mas adelante les pondremos valor)
		Dcnet::Datos X = Datos(0, Conj<Paquete>(), ColaLog<typename Conj<Paquete>::Iterador>(), diccLog<Nat,typename Conj<Paquete>::Iterador>(), indice);
		typename Dicc<hostname, Datos>::Iterador itX = computadoras.DefinirRapido(itHostname.Siguiente(), X);
		porHostname.definir(itHostname.Siguiente(), itX);

		//creo un iterador de la lista para eliminar el minimo que ya use
		itHostname = listaComp.CrearIt();
		bool noElimine = true;
		while (itHostname.HaySiguiente() && noElimine){
			if(itHostname.Siguiente() == min){
				itHostname.EliminarSiguiente();
				noElimine = false;
			}
			itHostname.Avanzar();
		}
		indice = indice + 1;
	}

	//Completo conMasEnvios:
	conMasEnvios = computadoras.CrearIt();

	//Completo caminos:
	Dicc<hostname, Datos>::Iterador itPC = computadoras.CrearIt();
	Dicc<hostname, Datos>::Iterador itPC2 = computadoras.CrearIt();
	Nat n = computadoras.CantClaves();
	Arreglo<Arreglo<Lista<hostname> > > caminos = Arreglo<Arreglo<Lista<hostname> > >(n);
	//voy a crear un arreglo en cada posición de array caminos, el cual va a tener el mínimo camino
	while (itPC.HaySiguiente()){
		Arreglo<Lista<hostname> > arrayDestinos = Arreglo<Lista<hostname> >(n);
		while(itPC2.HaySiguiente()){
			Conj<Lista<hostname> >::Iterador itConj = r.CaminosMinimos(itPC.SiguienteClave(), itPC2.SiguienteClave()).CrearIt();
			//de todos los caminos me quedo con uno
			if (itConj.HaySiguiente()){
				arrayDestinos[itPC2.SiguienteSignificado().indice] = itConj.Siguiente();
			}else{
				//si no hay camino, creo una lista vacia
				arrayDestinos[itPC2.SiguienteSignificado().indice] = Lista<hostname>();
			}
			itPC2.Avanzar();
		}
		caminos[itPC.SiguienteSignificado().indice] = arrayDestinos;
		itPC.Avanzar();
	}

}

//Destructor


//Crear Paquete
void Dcnet::crearPaquete(const Paquete p){
	typename Dicc<hostname, Datos>::Iterador itPC = *(porHostname.obtener(p.origen));
	typename Conj<Paquete>::Iterador itPaq = (itPC.SiguienteSignificado().paquetes).AgregarRapido(p);
	(itPC.SiguienteSignificado().cola).encolar(p.prioridad, itPaq);
	(itPC.SiguienteSignificado().paqPorid).Definir(p.idpaquete, itPaq);
}

//Avanzar segundo


//Paquete en transito
bool Dcnet::paqueteEnTransito(Nat p) const{
	bool res = false;
	typename Dicc<hostname, Dcnet::Datos>::const_Iterador itCompu = computadoras.CrearIt();
	while(itCompu.HaySiguiente() && !res){
		Conj<Paquete>::const_Iterador itPaq = (itCompu.SiguienteSignificado().paquetes).CrearIt();
		while (itPaq.HaySiguiente() && itPaq.Siguiente().idpaquete != p ){
			itPaq.Avanzar();
		}
		if (itPaq.Siguiente().idpaquete == p){
			res = true;
		}
		itCompu.Avanzar();
	}
	return res;
}

//La que más envió
hostname Dcnet::laQueMasEnvio() const{
	return conMasEnvios.SiguienteClave();
}

//operador == (igualdad de dcnet)


#endif