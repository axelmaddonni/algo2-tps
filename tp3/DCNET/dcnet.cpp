#include "dcnet.h"

const Paquete& Dcnet::damePaquete(Nat idpaquete) const{

typename Dicc<hostname, Datos>::const_Iterador itCompu = computadoras.CrearIt();
	
	while (itCompu.HaySiguiente()){
		if  ( (itCompu.SiguienteSignificado().paqPorid).Definido(idpaquete) ){
			break;
		}else{
			itCompu.Avanzar();
		}
	}
	return ((itCompu.SiguienteSignificado()).paqPorid).Significado(idpaquete).Siguiente();
}


//Red
const Red& Dcnet::DameRed() const{
	return red;
}

//Camino Recorrido
const Lista<hostname>& Dcnet::CaminoRecorrido(Nat idpaquete) const{
	typename Dicc<hostname, Datos>::const_Iterador itCompu = computadoras.CrearIt();
	
	bool yaEncontrado = false;
	Paquete p; //(0, 0, "", "");

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
Nat Dcnet::CantidadEnviados(hostname c)  const{ //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER
	return (porHostname.obtener(c))->SiguienteSignificado().cantEnvios;
}

//En Espera
Conj<Paquete>& Dcnet::EnEspera(hostname c)  const{ //DEBERIA SER CONST, PERO EXPLOTA AL USAR OBTENER
	return (porHostname.obtener(c))->SiguienteSignificado().paquetes;
}


Dcnet::Dcnet(){
	Dcnet(Red());
}


//Iniciar Dcnet
//Dcnet::Dcnet(const Red& r){

void Dcnet::IniciarDcnet(const Red& r) {

	//Copio la red
	red = Red(r);

	//Completo computadoras y porHostname:

	//creo un diccionario lineal
	computadoras = Dicc<hostname, Datos>();
	//creo un diccionario universal (trie)
	porHostname =  DiccString<typename Dicc<hostname, Dcnet::Datos>::Iterador>(); 

	//creo una lista vacía donde voy a guardar los hostnames y ordenarlos
	Lista<hostname> listaComp = Lista<hostname>();
	Conj<hostname> compus = r.Computadoras();
	Conj<hostname>::const_Iterador itCompus = compus.CrearIt();

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
	Nat cant = compus.Cardinal();
	hostname min;
	Lista<hostname>::Iterador itHostname;
	while (indice < cant ){
		//busco el minimo de la lista de hostnames
		itHostname = listaComp.CrearIt();
		min = itHostname.Siguiente();
		while (itHostname.HaySiguiente()){
			if (min > itHostname.Siguiente()){
				min = itHostname.Siguiente();
			}
			itHostname.Avanzar();
		}
		//Inicializo DATOS (con cantidad de envios en 0)
		Dcnet::Datos X = Datos(indice, Conj<Paquete>(), ColaLog<typename Conj<Paquete>::Iterador>(), diccLog<Nat,typename Conj<Paquete>::Iterador>(), 0);
		typename Dicc<hostname, Datos>::Iterador itX = computadoras.DefinirRapido(min, X);
		porHostname.definir(min, itX);

		//creo un iterador de la lista para eliminar el minimo que ya use
		itHostname = listaComp.CrearIt();
		while (itHostname.HaySiguiente()){
			if(itHostname.Siguiente() == min){
				itHostname.EliminarSiguiente();
				break;
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
	caminos = Arreglo<Arreglo<Lista<hostname> > >(n);

	//voy a crear un arreglo en cada posición de array caminos, el cual va a tener el mínimo camino
	while (itPC.HaySiguiente()){
		Arreglo<Lista<hostname> > arrayDestinos = Arreglo<Lista<hostname> >(n);
		while(itPC2.HaySiguiente()){
			if (r.HayCamino(itPC.SiguienteClave(), itPC2.SiguienteClave())){
				Conj<Lista<hostname> > caminosMinimos = r.CaminosMinimos(itPC.SiguienteClave(), itPC2.SiguienteClave());
				Conj<Lista<hostname> >::Iterador itConj = caminosMinimos.CrearIt();
				//de todos los caminos me quedo con uno
				//if (itConj.HaySiguiente()){
				arrayDestinos.Definir(itPC2.SiguienteSignificado().indice, itConj.Siguiente());
				//}
			}else{
				//si no hay camino, creo una lista vacia
				arrayDestinos.Definir(itPC2.SiguienteSignificado().indice, Lista<hostname>());
			}
			itPC2.Avanzar();
		}
		caminos.Definir(itPC.SiguienteSignificado().indice, arrayDestinos);
		itPC.Avanzar();
		itPC2 = computadoras.CrearIt();
	}

}

//Destructor
/*
~Dcnet() {
}
*/

//Crear Paquete
void Dcnet::CrearPaquete(const Paquete& p){
	typename Dicc<hostname, Datos>::Iterador itPC = *(porHostname.obtener(p.origen));
	typename Conj<Paquete>::Iterador itPaq = (itPC.SiguienteSignificado().paquetes).AgregarRapido(p);
	(itPC.SiguienteSignificado().cola).encolar(p.prioridad, itPaq);
	(itPC.SiguienteSignificado().paqPorid).Definir(p.idpaquete, itPaq); //MEMORY LEAK!!!!!!!!!!!!!!
}

//Avanzar segundo
void Dcnet::AvanzarSegundo(){


	//inicializo arreglo auxiliar en false
	Nat cant = computadoras.CantClaves();
	Nat i;
	Arreglo<Dcnet::TuplaDestinos> arreglo = Arreglo<Dcnet::TuplaDestinos>(cant);

	//inicializo variables
	
	Conj<Paquete>::Iterador itPaquete;
	Paquete paqueteDesencolado;
	Nat origen;
	Nat destino;
	hostname proxDest;
	Nat envios;
	typename Lista<hostname>::Iterador itlista;
	typename Dicc<hostname, Datos>::Iterador itdestino;
	Nat prioridad;
	Nat IDpaq;

	typename Dicc<hostname, Datos>::Iterador itCompu = computadoras.CrearIt();
	i = 0;

	while(itCompu.HaySiguiente()){
		if ( !(itCompu.SiguienteSignificado().cola.vacia()) ){
			//Borro el de mayor prioridad del heap
			itPaquete = (itCompu.SiguienteSignificado().cola).desencolar();
			//Lo elimino del dicc AA
			(itCompu.SiguienteSignificado().paqPorid).Borrar(itPaquete.Siguiente().idpaquete);
			//Guardo el paquete en una variable
			paqueteDesencolado = itPaquete.Siguiente();
			//Lo elimino del conjunto lineal de paquetes
			itPaquete.EliminarSiguiente();
			//Calculo proximo destino fijandome en la matriz
			origen = itCompu.SiguienteSignificado().indice;
			itdestino = *porHostname.obtener(paqueteDesencolado.destino);
			destino = itdestino.SiguienteSignificado().indice;
			//el proximo destino es el primero de la lista:
			itlista = caminos[origen][destino].CrearIt();
			proxDest = itlista.Siguiente();
			//Lo inserto en el arreglo junto con el destino sólo si el destino no era el final
			if (proxDest != paqueteDesencolado.destino){
				arreglo.Definir(i, TuplaDestinos(paqueteDesencolado, proxDest));				
			}
			//Aumento cantidad de envios
			itCompu.SiguienteSignificado().sumarEnvio();
			//Actualizo conMasEnvios
			envios = itCompu.SiguienteSignificado().cantEnvios;
			if (envios > conMasEnvios.SiguienteSignificado().cantEnvios){
				conMasEnvios = itCompu;
			}
		}
		itCompu.Avanzar();
		i++;
	}


	itCompu = computadoras.CrearIt();
	i = 0;


	while (itCompu.HaySiguiente()){
		if (arreglo.Definido(i)){
			//Busco el proxDest guardado en el arreglo por hostname
			itdestino = *porHostname.obtener(arreglo[i].destino);
			//agrego el paquete al conjunto de paquetes del prox destino
			itPaquete = itdestino.SiguienteSignificado().paquetes.AgregarRapido(arreglo[i].paquete);
			//encolo el heap del destino
			prioridad = arreglo[i].paquete.prioridad;
			itdestino.SiguienteSignificado().cola.encolar(prioridad, itPaquete);
			//lo agrego en el AA
			IDpaq = arreglo[i].paquete.idpaquete;
			itdestino.SiguienteSignificado().paqPorid.Definir(IDpaq, itPaquete);	// MEMORY LEAK!!!!!!!!!!!
		}
		i++;
		itCompu.Avanzar();
	}

}

//Paquete en transito
bool Dcnet::PaqueteEnTransito(Nat p) const{
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
const hostname& Dcnet::LaQueMasEnvio() const{
	return conMasEnvios.SiguienteClave();
}

//operador == (igualdad de dcnet)
bool Dcnet::operator==(Dcnet& d) const {
	//comparo redes usando == de red
	bool res;
	res = (this->DameRed() == d.DameRed());
	if (res){
		//defino variables
		typename Dicc<hostname, Datos>::const_Iterador itCompu = computadoras.CrearIt();
		hostname host;
		typename Conj<Paquete>::const_Iterador itpaq;
		Nat id;
		
		//recorro las computadoras
		while (itCompu.HaySiguiente() && res){
			host = itCompu.SiguienteClave();
			//comparo EnEspera usando == de conjunto lineal y cant. enviados
			res = (this->EnEspera(host) == d.EnEspera(host) && this->CantidadEnviados(host) == d.CantidadEnviados(host) );
			itpaq = (itCompu.SiguienteSignificado().paquetes).CrearIt();
			
			while (itpaq.HaySiguiente() && res){
				id = itpaq.Siguiente().idpaquete;
				//comparo caminosRecorridos usando == de listas enlazadas
				res = (this->CaminoRecorrido(id) == d.CaminoRecorrido(id));
				itpaq.Avanzar();
			}
			itCompu.Avanzar();
		}
	}
	return res;
}


std::ostream& Dcnet::ImprimirDcnet(std::ostream& os) const{
	Dicc<hostname, Datos>::const_Iterador itDcnet = computadoras.CrearIt();
	os << "Información de la Dcnet: " << std::endl;

	while(itDcnet.HaySiguiente()){
		os << "Hostname: " << itDcnet.SiguienteClave() << std::endl;
		os << "Indice: " << itDcnet.SiguienteSignificado().indice << std::endl;
		os << "Paquetes: " ;
			Conj<Paquete>::const_Iterador itPaq = itDcnet.SiguienteSignificado().paquetes.CrearIt();
			while (itPaq.HaySiguiente()){
				cout << std::endl;
				itPaq.Siguiente().ImprimirPaquete(os);
				itPaq.Avanzar();
			}
		os << std::endl;
		os << "Cantidad de envíos: " << itDcnet.SiguienteSignificado().cantEnvios << std::endl << std::endl;
		itDcnet.Avanzar();
	}
return os;
	//os << "caminos: ";
	//Mostrar(caminos, '[', ']');

}