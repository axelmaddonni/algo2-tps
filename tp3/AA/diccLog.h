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

		AB<tupla> nodo_ab;
		bool nil;
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
		bool Definido(const C cla);

		//Significado(in d: diccLog(C,S), in c: C) -> res : S
		//Pre = {def?(c,d)}
		//Post = {res =obs obtener(c,d)}
		//O(log(n)*comparar(C) + copiar(S))
		S Significado(const C cla);

		//Definir(in/out) d: diccLog(C,S), in c: C, in s: S)
		//Pre = {!def?(c,d) AND d=d0}
		//Post = {d =obs definir(c,do)}
		//O(log(n))
		void Definir(const C cla, const S sig);

		//Borrar(in/out d: diccLog(C,S), in c: C)
		//Pre = {def?(c,d) AND d=d0}
		//Post = {d =obs borrar(c,do)}
		//O(log(n)*comparar(C) + max(borrar(C),borrar(S)) + max(copiar(C),copiar(S)))
		void Borrar(const C c);


		//otros
		~diccLog();

};


///FUNCIONES
template<typename C, typename S>
diccLog<C,S>::diccLog() {
	nil = true;
}

/*template<typename C, typename S>
bool diccLog<C,S>::Definido(const C cla) {
	nodoActual
}*/

template<typename C, typename S>
diccLog<C,S>::~diccLog() {
	if (nil==false) {
		nodo_ab.borrarAB();
	}
}










#endif //AA_HPP_