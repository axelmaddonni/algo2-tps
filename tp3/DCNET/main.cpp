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

	/*

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
	
	red.ImprimirRed(cout);	
	
	//d1.ImprimirDcnet(cout);

	Paquete p1(1, 5, "compu1", "compu3");
	Paquete p2(2, 1, "compu3", "compu2");
	Paquete p3(3, 1, "compu1", "compu2");

	d1.CrearPaquete(p1);
	d1.CrearPaquete(p2);
	d1.CrearPaquete(p3);

	cout << "ANTES" << endl;

	d1.ImprimirDcnet(cout);

	d1.AvanzarSegundo();

	cout << "DESPUES" << endl;
	d1.ImprimirDcnet(cout);

	d1.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d1.ImprimirDcnet(cout);

	cout << d1.LaQueMasEnvio() << endl;
	*/

	Red red2 = Red();
	computadora c1 = computadora("c1", i);
	computadora c2 = computadora("c2", i);
	computadora c3 = computadora("c3", i);
	computadora c4 = computadora("c4", i);
	computadora c5 = computadora("c5", i);
	computadora c6 = computadora("c6", i);
	computadora c7 = computadora("c7", i);
	computadora c8 = computadora("c8", i);
	computadora c9 = computadora("c9", i);
	computadora c10 = computadora("c10", i);
	
	red2.AgregarCompu(c1);
	red2.AgregarCompu(c2);
	red2.AgregarCompu(c3);
	red2.AgregarCompu(c4);
	red2.AgregarCompu(c5);
	red2.AgregarCompu(c6);
	red2.AgregarCompu(c7);
	red2.AgregarCompu(c8);
	red2.AgregarCompu(c9);
	red2.AgregarCompu(c10);

	red2.Conectar("c1",1,"c2", 1);
	red2.Conectar("c1",2,"c3", 1);
	red2.Conectar("c1",3,"c5", 1);
	red2.Conectar("c1",4,"c6", 1);
	red2.Conectar("c1",5,"c4", 1);
	red2.Conectar("c2",2,"c4", 2);
	red2.Conectar("c2",3,"c3", 2);
	red2.Conectar("c3",3,"c4", 3);
	red2.Conectar("c7",1,"c8", 1);
	red2.Conectar("c8",2,"c9", 1);
	red2.Conectar("c9",2,"c10", 1);
	red2.Conectar("c10",2,"c8", 3);
	red2.Conectar("c7",2,"c10", 3);
	red2.Conectar("c10", 5, "c2", 5);
	red2.Conectar("c7", 5, "c4", 5);

	//red2.ImprimirRed(cout);

	Dcnet d2;
	d2.IniciarDcnet(red2);

	Paquete p(1, 5, "c1", "c3");
	d2.CrearPaquete(p);
	p = Paquete(2, 3, "c9", "c5");
	d2.CrearPaquete(p);
	p = Paquete(3, 1, "c9", "c1");
	d2.CrearPaquete(p);

	d2.ImprimirDcnet(cout);

	

	d2.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d2.ImprimirDcnet(cout);
	
	

	d2.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d2.ImprimirDcnet(cout);

	
	/*

	d2.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d2.ImprimirDcnet(cout);

	d2.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d2.ImprimirDcnet(cout);

	d2.AvanzarSegundo();
	cout << "DESPUES" << endl;
	d2.ImprimirDcnet(cout);

	red2.ImprimirRed(cout);
	cout << d2.LaQueMasEnvio() << endl;

	*/

	return 0;
}



