#include <iostream>
#include "Red.h"

using std::cout;
using std::endl;



int main(){

	Conj<interfaz> i1 = Conj<interfaz>();
	i1.AgregarRapido(1);
	Conj<interfaz> i2 = Conj<interfaz>(i1);
	i2.AgregarRapido(2);
	Conj<interfaz> i3 = Conj<interfaz>(i2);
	i3.AgregarRapido(3);

	computadora compu1 = computadora("compu1", i1);
	computadora compu2 = computadora("compu2", i2);
	computadora compu3 = computadora("compu3", i2);
	
	Red red = Red();
	red.AgregarCompu(compu1);
	red.AgregarCompu(compu2);
	red.AgregarCompu(compu3);

	red.Conectar("compu1", 1, "compu2", 1);

	cout << red.UsaInterfaz("compu2", 1) << endl;
	cout << red.UsaInterfaz("compu2", 2) << endl;
	cout << red.UsaInterfaz("compu2", 3) << endl;
	cout << red.UsaInterfaz("compu2", 4) << endl;
	cout << red.UsaInterfaz("compu2", 1) << endl;

    return 0;
}



