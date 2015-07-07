#include <iostream>
#include "dcnet.h"

using std::cout;
using std::endl;



int main(){

	Conj<interfaz> i = Conj<interfaz>();
	i.AgregarRapido(1);
	i.AgregarRapido(2);
	i.AgregarRapido(3);
	i.AgregarRapido(4);
	i.AgregarRapido(5);
	computadora compu1 = computadora("compu1", i);
	computadora compu2 = computadora("compu2", i);
	computadora compu3 = computadora("compu3", i);

	Red red = Red();
	red.AgregarCompu(compu2);
	red.AgregarCompu(compu3);
	red.AgregarCompu(compu1);

	red.Conectar("compu1", 1, "compu2", 1);
	red.Conectar("compu2", 2, "compu3", 3);

	Dcnet d1(red);
	
	//red.ImprimirRed(cout);	
	
	d1.ImprimirDcnet(cout);

	Paquete p1 = Paquete(1, 5, "compu1", "compu3");
	Paquete p2(2, 1, "compu3", "compu2");

	d1.crearPaquete(p1);

	d1.ImprimirDcnet(cout);

	d1.avanzarSegundo();

    return 0;
}



