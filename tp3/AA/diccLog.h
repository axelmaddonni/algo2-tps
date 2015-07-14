#ifndef AA_HPP_
#define AA_HPP_

#include <iostream>
#include "../AB/AB.hpp"

using aed2::Nat;

template<typename C, typename S>
class diccLog {
	private:
		struct tupla {
			C clave;
			Nat nivel;
			S significado;


			tupla(C clavei, Nat niveli, S significadoi) {
				clave = clavei;
				nivel = niveli;
				significado = significadoi;
			}
		};

		struct tuplaAB {
			diccLog<C,S>::tupla val;
			tuplaAB izq;
			tuplaAB der;

			tuplaAB(diccLog<C,S>::tupla valor, tuplaAB izquierdo, tuplaAB derecho) {
				val = valor;
				izq = izquierdo;
				der = derecho;
			}
		};

		AB<tupla> nodo_ab;
		bool nil;

		void Torsion(typename AB<tupla>::Iterador &itArbol);
		void Division(typename AB<tupla>::Iterador &itArbol);
		void Nivelar(typename AB<tupla>::Iterador &itArbol);
		void DefinirNodo(C cla, S sig, typename AB<tupla>::Iterador nodoActual);
		void BorrarNodo(C cla, typename AB<tupla>::Iterador nodoActual);
	public:

		//Vacio() -> res : diccLog(C, S)
		//Pre = {true}
		//Post = {res =obs vacio()}
		//O(1)
		diccLog();

		//Definido?(in d: diccLog(C,S), in c: C) -> res : Bool
		//Pre = {true}
		//Post = {res =obs def?(c,d)}
		//O(log(n)*comparar(C))
		bool Definido(const C cla) const;

		//Significado(in d: diccLog(C,S), in c: C) -> res : S
		//Pre = {def?(c,d)}
		//Post = {res =obs obtener(c,d)}
		//O(log(n)*comparar(C) + copiar(S))
		S Significado(const C cla) const;

		//Definir(in/out) d: diccLog(C,S), in c: C, in s: S)
		//Pre = {!def?(c,d) AND d=d0}
		//Post = {d =obs definir(c,do)}
		//O(log(n))
		void Definir(const C cla, const S sig);

		//Borrar(in/out d: diccLog(C,S), in c: C)
		//Pre = {def?(c,d) AND d=d0}
		//Post = {d =obs borrar(c,do)}
		//O(log(n)*comparar(C) + max(borrar(C),borrar(S)) + max(copiar(C),copiar(S)))
		void Borrar(const C cla);


		//otros
		~diccLog();
		void printD();
		void printI();
		void printID();
		void printDI();

};


///FUNCIONES
template<typename C, typename S>
diccLog<C,S>::diccLog() {
	nil = true;
}

template<typename C, typename S>
bool diccLog<C,S>::Definido(const C cla) const {
	if (nil) {
		return 0;
	}
	typename AB<tupla>::Iterador nodoActual = nodo_ab.crearIt();
	int i = 0;
	while(nodoActual && i<4) {
		if (nodoActual.val().clave==cla) {
			return 1;
		} else if (nodoActual.val().clave < cla) {
			nodoActual.der();
		} else {
			nodoActual.izq();
		}
		i++;
	}
	return 0;
}

template<typename C, typename S>
S diccLog<C,S>::Significado(const C cla) const {
	typename AB<tupla>::Iterador nodoActual = nodo_ab.crearIt();
	while(nodoActual) {
		if (nodoActual.val().clave==cla) {
			break;
		} else if (nodoActual.val().clave < cla) {
			nodoActual.der();
		} else {
			nodoActual.izq();
		}
	}
	return nodoActual.val().significado;
}

//--- nuevo Definir (recursivo)
template<typename C, typename S>
void diccLog<C,S>::Definir(C cla, S sig) {
	if (nil) {
		nodo_ab = tupla(cla,1,sig);
		nil=false;
	} else {
		typename AB<tupla>::Iterador nodoActual = nodo_ab.crearIt();
		DefinirNodo(cla,sig,nodoActual);
	}

}

template<typename C, typename S>
void diccLog<C,S>::DefinirNodo(C cla, S sig, typename AB<tupla>::Iterador nodoActual) {
	if (nodoActual.val().clave < cla) {
		if (nodoActual.itDer()) {
			DefinirNodo(cla, sig, nodoActual.itDer());
		} else {
			nodoActual.setearDer(tupla(cla,1,sig));
		}
	} else {
		if (nodoActual.itIzq()) {
			DefinirNodo(cla, sig, nodoActual.itIzq());
		} else {
			nodoActual.setearIzq(tupla(cla,1,sig));
		}
	}
	Torsion(nodoActual);
	Division(nodoActual);
}



template<typename C, typename S>
void diccLog<C,S>::Borrar(C cla) 
{
    typename AB<tupla>::Iterador nodoActual = nodo_ab.crearIt();
    //si es la raiz
    if (nodoActual.val().clave==cla && !nodoActual.itDer() && !nodoActual.itIzq()) 
    {
        nodo_ab.reset();
        nil=true;
    }
    else 
    {
        BorrarNodo(cla, nodoActual);
    }
}

template<typename C, typename S>
void diccLog<C,S>::BorrarNodo(C cla, typename AB<tupla>::Iterador nodoActual) {
	if (nodoActual.val().clave < cla) {
		//el nodo que busco está para la derecha
			//si el nodo de la derecha es el que busco y no tiene hijos lo borro
		if (nodoActual.itDer().val().clave == cla && !nodoActual.itDer().itDer() && !nodoActual.itDer().itIzq()) {
			nodoActual.borrarPostaDer();
		} else {
			//sigo hacia la derecha con recursion
			BorrarNodo(cla, nodoActual.itDer());
		}
	} else if (nodoActual.val().clave > cla) {
		//el nodo que busco está para la izquierda
		if (nodoActual.itIzq().val().clave == cla && !nodoActual.itIzq().itDer() && !nodoActual.itIzq().itIzq()) {
			//si el nodo de la izquierda es el que busco y no tiene hijos lo borro
			nodoActual.borrarPostaIzq();
		} else {
			//sigo hacia la izquierda con recursion
			BorrarNodo(cla, nodoActual.itIzq());
		}
	} else if (!nodoActual.itIzq()) {
		//si estoy parado en el nodo que quiero borrar y no tiene hijo izquierdo
		typename AB<tupla>::Iterador nodoAux = nodoActual.itDer();
		//voy guardando el padre
		typename AB<tupla>::Iterador nodoPadre = nodoActual;
		//voy uno hacia la derecha y todo hacia la izquierda // busco el sucesor
		bool hayIzq = false;
		while (nodoAux.itIzq()) {
			nodoPadre = nodoAux;
			nodoAux.izq();
			hayIzq = true;
		}
		//hago un swap del izquierdo del aux (el último hacia la izquierda) y del que voy a borrar
		nodoActual.swapVal(nodoAux);
		//borro el hijo correspondiente del padre
		if (hayIzq) {
			nodoPadre.borrarPostaIzq();
		} else {
			nodoPadre.borrarPostaDer();
		}
	} else {
		//si estoy parado en el nodo que quiero borrar
		typename AB<tupla>::Iterador nodoAux = nodoActual.itIzq();
		//voy guardando el padre
		typename AB<tupla>::Iterador nodoPadre = nodoActual;
		//voy uno hacia la izquierda y todo hacia la derecha // busco el predecesor
		bool hayDer = false;
		while (nodoAux.itDer()) {
			nodoPadre = nodoAux;
			nodoAux.der();
			hayDer = true;
		}
		//hago un swap del derecho del aux (el último hacia la derecha) y del que voy a borrar
		nodoActual.swapVal(nodoAux);
		//borro el hijo correspondiente del padre
		if (hayDer) {
			nodoPadre.borrarPostaDer();
		} else {
			nodoPadre.borrarPostaIzq();
		}
	}

	Nivelar(nodoActual);
	Torsion(nodoActual);

	Division(nodoActual);
}


template<typename C, typename S>
diccLog<C,S>::~diccLog() {

		typename AB<tupla>::Iterador itArbol;
		itArbol = nodo_ab.crearIt();
		itArbol.borrar();
		nil = true;
		nodo_ab.borrarAB();
}

template<typename C, typename S>
void diccLog<C,S>::Nivelar(typename AB<tupla>::Iterador &itArbol) {
	Nat nivel_correcto = 1;
	if (itArbol.itIzq()) {
		if (!itArbol.itDer() || itArbol.itIzq().val().nivel < itArbol.itDer().val().nivel) {
			nivel_correcto = itArbol.itIzq().val().nivel + 1;
		} else {
			nivel_correcto = itArbol.itDer().val().nivel + 1;
		}
	} else if (itArbol.itDer()) {
		nivel_correcto = itArbol.itDer().val().nivel + 1;
	}
	if (nivel_correcto < itArbol.val().nivel) {
		itArbol.val().nivel = nivel_correcto;
		if (itArbol.itDer() && nivel_correcto < itArbol.itDer().val().nivel) {
			itArbol.itDer().val().nivel = nivel_correcto;
		}
	}
}

template<typename C, typename S>
void diccLog<C,S>::Torsion(typename AB<tupla>::Iterador &itArbol) {
	if (!itArbol || !itArbol.itIzq()) {
		return;
	}
	if (itArbol.itIzq().val().nivel == itArbol.val().nivel) {
		typename AB<tupla>::Iterador itAux;
		itAux = itArbol.itIzq();
		itArbol.swapVal(itAux);
		if (itAux.itIzq()) {
			itArbol.setearIzq(*itAux.itIzq().act());
		} else {
			itArbol.borrarIzq();
		}
		if (itAux.itDer()) {
			itAux.setearIzq(*itAux.itDer().act());
		} else {
			itAux.borrarIzq();
		}
		if (itArbol.itDer()) {
			itAux.setearDer(*itArbol.itDer().act());
		} else {
			itAux.borrarDer();
		}
		itArbol.setearDer(*itAux.act());
	}
	return;
}

template<typename C, typename S>
void diccLog<C,S>::Division(typename AB<tupla>::Iterador &itArbol) {
	if (!itArbol || !itArbol.itDer() || !itArbol.itDer().itDer()) {
		return;
	}
	if (itArbol.itDer().itDer().val().nivel == itArbol.val().nivel) {
		typename AB<tupla>::Iterador itAux;
		itAux = itArbol.itDer();

		itArbol.swapVal(itAux);

		itArbol.setearDer(*itAux.itDer().act());
		if (itAux.itIzq()) {
			itAux.setearDer(*itAux.itIzq().act());
		} else {
			itAux.borrarDer();
		}

		if (itArbol.itIzq()) {
			itAux.setearIzq(*itArbol.itIzq().act());
		} else {
			itAux.borrarIzq();
		}
		itArbol.setearIzq(*itAux.act());
		itArbol.val().nivel ++;
	}
}










template<typename C, typename S>
void diccLog<C,S>::printD() {
	typename AB<tupla>::Iterador itArbol = nodo_ab.crearIt();
	while (itArbol) {
		std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		itArbol.der();
	} 
}

template<typename C, typename S>
void diccLog<C,S>::printI() {
	typename AB<tupla>::Iterador itArbol = nodo_ab.crearIt();
	while (itArbol) {
		std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		itArbol.izq();
	} 
}

template<typename C, typename S>
void diccLog<C,S>::printID() {
	typename AB<tupla>::Iterador itArbol = nodo_ab.crearIt();
	std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
	if (itArbol.itIzq())  {
		itArbol.izq();
		std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		while (itArbol.itDer()) {
			itArbol.der();
			std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		}
	}
}

template<typename C, typename S>
void diccLog<C,S>::printDI() {
	typename AB<tupla>::Iterador itArbol = nodo_ab.crearIt();
	std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
	if (itArbol.itDer()) {
		itArbol.der();
		std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		while (itArbol.itIzq()) {
			itArbol.izq();
			std::cout << itArbol.val().clave << " -> " << itArbol.val().nivel << std::endl;//" -> " << itArbol.val().significado << std::endl;
		}
	}
}


/*template<typename C, typename S>
void diccLog<C,S>::armarMatriz(typename AB<tupla>::Iterador it, char[][] &matriz) {
	return NULL;
}

template<typename C, typename S>
void diccLog<C,S>::mostrarAB() {
	typename AB<tupla>::Iterador it = nodo_ab.crearIt();
	diccLog<C,S>::tuplaAB arb;
	char matriz[it.val().nivel+1][it.val().nivel*4];
	armarMatriz(it, matriz);


}*/



#endif //AA_HPP_
