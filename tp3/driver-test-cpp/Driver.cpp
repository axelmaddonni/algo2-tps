#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver() {
    
    r = Red();
    d = Dcnet();
    iniciada = false;
    proximoid = 1;

}

Driver::~Driver() {

    //~Red(r);
    //~Dcnet(d);

}

// TAD RED

Nat Driver::CantidadComputadoras() const {
    
    return r.Computadoras().Cardinal();

}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    
	auto it = r.Computadoras().CrearIt();
    Nat aux = i;
    while (it.HaySiguiente() and aux > 0){
        aux--;
        it.Avanzar();
    }
    return it.Siguiente();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    
    return r.Interfaces(c).Cardinal();

}

Interfaz Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{
    
    Conj<Interfaz> conji = r.Interfaces(c);
    Conj<Interfaz>::const_Iterador it = conji.CrearIt();
    Nat aux = i;
    while (it.HaySiguiente() and aux > 0){
        aux--;
        it.Avanzar();
    }
    return it.Siguiente();

} 

Interfaz Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    
    return r.InterfazUsada(c1,c2);

}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    
    return r.Conectadas(c1, c2);
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    
    #ifdef DEBUG
    assert( not iniciada );
    #endif

    computadora c(ip, ci);
    r.AgregarCompu(c);

}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    
    #ifdef DEBUG
    assert( not iniciada );
    #endif

    r.Conectar(c1, i1, c2, i2);
}
	
	
Nat Driver::CantidadNodosRecorridosPor(const idPaquete& p) const {
    // auto it = d.CaminoRecorrido(p).CrearIt();
    // std::cout << "---empieza camino" << std::endl;
    // while (it.HaySiguiente()){
    //     std::cout << it.Siguiente() << std::endl;
    //     it.Avanzar();
    // }
    // std::cout << "---termina camino" << std::endl;

    return d.CaminoRecorrido(p).Longitud()+1;

}

const Computadora& Driver::IesimoNodoRecorridoPor(const idPaquete& p, const Nat i) const {
    
    if(i == 0){
        return d.damePaquete(p).origen;
    }
    auto it = d.CaminoRecorrido(p).CrearIt();
    Nat aux = i-1;
    while (it.HaySiguiente() and aux > 0){
        aux--;
        it.Avanzar();
    }
    return it.Siguiente();

}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    
    return d.CantidadEnviados(c);

}
	
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    
    return d.EnEspera(c).Cardinal();
}

const idPaquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {
    
    auto it = d.EnEspera(c).CrearIt();
    Nat aux = i;
    while (it.HaySiguiente() and aux > 0){
        aux--;
        it.Avanzar();
    }
    return it.Siguiente().idpaquete;
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    
    if (!iniciada) {
        d.IniciarDcnet(r);
        iniciada = true;
    }

    Paquete p(proximoid, prioridad, origen, destino);
    d.CrearPaquete(p);
    proximoid++;

}
		
void Driver::AvanzarSegundo() {

    if (!iniciada) {
        d.IniciarDcnet(r);
        iniciada = true;
    }
    
    d.AvanzarSegundo();

}
		
const Computadora& Driver::laQueMasEnvio() const {
    /*
    const Computadora& referenciahostname(d.LaQueMasEnvio());
    return referenciahostname;
    */
    return d.LaQueMasEnvio();
}

const Computadora& Driver::origen(const idPaquete& p) const {
   
    return d.damePaquete(p).origen;
} 

const Computadora& Driver::destino(const idPaquete& p) const { 
    
    return d.damePaquete(p).destino;
}

Nat Driver::prioridad(const idPaquete& p) const { 
    
    return d.damePaquete(p).prioridad;
}
		


} // namespace aed2

