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

	/*computadora compu4 = computadora("compu4", i);
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
	//computadora c10 = computadora("c10", i);
	
	red2.AgregarCompu(c1);
	red2.AgregarCompu(c2);
	red2.AgregarCompu(c3);
	red2.AgregarCompu(c4);
	red2.AgregarCompu(c5);
	red2.AgregarCompu(c6);
	red2.AgregarCompu(c7);
	red2.AgregarCompu(c8);
	red2.AgregarCompu(c9);

	c1 = computadora("c10", i);

	red2.AgregarCompu(c1);

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
	
	//red2.ImprimirRed(cout);

	Red red3 = Red(red2);

	cout << endl << "Red2 == Red3?: " << ImprimirBool(red2==red3) << endl;

	red3.Conectar("c10", 5, "c2", 5);
	red3.Conectar("c7", 5, "c4", 5);
	//red3.ImprimirRed(cout);

	cout << endl << "Red2 == Red3?: " << ImprimirBool(red2==red3) << endl;

	/*prueba para ==
	Red redprueba1 = Red();
	Red redprueba2 = Red();

	redprueba1.AgregarCompu(c1);
	redprueba1.AgregarCompu(c2);
	redprueba1.Conectar("c10", 2, "c2", 1);

	redprueba2.AgregarCompu(c2);
	redprueba2.AgregarCompu(c1);
	redprueba2.Conectar("c2", 1, "c10", 2);
	cout << endl << "prueba == : " << ImprimirBool(redprueba1==redprueba2) << endl;
	*/


	auto red4 = Red();
	red4.AgregarCompu(c2);
	red4.AgregarCompu(c3);
	red4.AgregarCompu(c4);

	cout << red4.Computadoras() << endl;	

	Conj<hostname> compus = red4.Computadoras();

	compus.Eliminar("c2");

	cout << compus << endl;

	red4.Interfaces("c2").Eliminar(1);
	
	cout << red4.Interfaces("c2") << endl;



    return 0;
}



