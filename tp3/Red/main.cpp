#include <iostream>
#include "Red.h"

using std::cout;
using std::endl;

	String ImprimirBool (bool valor){
		if (valor) return "True";
		else return "False";
	}


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
	red.AgregarCompu(compu1);
	red.AgregarCompu(compu2);
	red.AgregarCompu(compu3);

	red.Conectar("compu1", 1, "compu2", 1);
	red.Conectar("compu2", 2, "compu3", 3);

	/*
	cout << red.UsaInterfaz("compu2", 1) << endl;
	cout << red.UsaInterfaz("compu2", 2) << endl;
	cout << red.UsaInterfaz("compu2", 3) << endl;
	cout << red.UsaInterfaz("compu2", 4) << endl;
	cout << red.UsaInterfaz("compu2", 1) << endl;
	*/

	//red.ImprimirRed(cout);

	computadora compu4 = computadora("compu4", i);
	computadora compu5 = computadora("compu5", i);
	computadora compu6 = computadora("compu6", i);

	red.AgregarCompu(compu4);
	red.AgregarCompu(compu5);
	red.AgregarCompu(compu6);

	red.Conectar("compu1", 2, "compu4", 1);
	red.Conectar("compu4", 2, "compu3", 1);
	red.Conectar("compu4", 3, "compu2", 3);
	red.Conectar("compu5", 1, "compu2", 4);
	red.Conectar("compu4", 4, "compu5", 2);

	red.Conectar("compu6", 1, "compu3", 2);

	red.ImprimirRed(cout);


	cout << "Estan conectadas 6 y 1?: " << ImprimirBool(red.Conectadas("compu6", "compu1")) << endl;
	cout <<"Hay camino entre 6 y 1?: " << ImprimirBool(red.HayCamino("compu6", "compu1")) << endl;
	cout << "Caminos minimos entre 6 y 1: " << endl;
	Mostrar(cout, red.CaminosMinimos("compu6", "compu1"), '[', ']');
	cout << endl << endl;


    return 0;
}



