#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"

#include "../DCNET/dcnet.h"

//#include ...

namespace aed2 {

class Driver
{
    public:

        Driver();

        ~Driver();

        /// Observadores Red //////////////////////////////////////////////////////////

        Nat CantidadComputadoras() const;
        const Computadora& IesimaComputadora(const Nat i) const ;
        
        Nat CantidadInterfacesDe(const Computadora& c) const;
        Interfaz IesimaInterfazDe(const Computadora& c, const Nat i) const ;

        Interfaz IntefazUsada(const Computadora& c1, const Computadora& c2) const;

        bool conectadas(const Computadora& c1, const Computadora& c2) const;

        /// Armado Red ////////////////////////////////////////////////////////////////

        void AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci);
        
        void Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2);
    

       /// Observadores DCNet //////////////////////////////////////////////////////////////
    
        Nat CantidadNodosRecorridosPor(const idPaquete& p) const;
        const Computadora& IesimoNodoRecorridoPor(const idPaquete& p, const Nat i) const;

        Nat CantidadEnviadosPor(const Computadora& c) const;
    
        Nat CantidadEnEsperaEn(const Computadora& c) const;
        const idPaquete& IesimoEnEsperaEn(const Computadora& c, const Nat i) const;

        /// Acciones DCNet ////////////////////////////////////////////////////////////

        void CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad);
        
        void AvanzarSegundo();
        
        const Computadora& laQueMasEnvio() const;
        
        // Auxiliares para ver los Paquetes
        const Computadora& origen(const idPaquete& p) const; 
        const Computadora& destino(const idPaquete& p) const; 
        Nat prioridad(const idPaquete& p) const; 

        

        std::ostream& ImprimirDcnet(std::ostream& os) const {
            d.ImprimirDcnet(os);
            return os;
        }
        
    private:

    /*********************************************************************
     * TODO: Va a ser necesario instanciar privadamente un Modulo DCNet  *
     * con el cuál interactuar. Además, pueden declarar todas las        *
     * funciones auxiliares que les hagan falta.                         *
     *********************************************************************/

     Dcnet d;
     Red r;

     bool iniciada; // inicio al avanzar el primer segundo o agregar el primer idPaquete, y ya no se puede modificar la red

     Nat proximoid;
   
}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
