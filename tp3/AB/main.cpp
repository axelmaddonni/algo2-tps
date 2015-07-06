#include "../aed2.h"
#include "AB.hpp"
#include <iostream>

using std::cout;
using std::endl;


int main() {
	auto ab = AB<int>();
	ab=9;
	typename AB<int>::Iterador it = ab.crearIt();
	it.setearDer(2);
	it.der();
	it.setearIzq(10);
	it.setearDer(35);
	it.borrarDer();
	return 0;
}