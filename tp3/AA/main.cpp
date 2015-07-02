#include "diccLog.h"
#include <iostream>

using std::cout;
using std::endl;


int main()
{
    auto test = diccLog<int, int>();
    int clave;
    test.Definir(1, 1);
    clave = 1;
    cout  << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 2;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    test.Definir(4, 4);
    clave = 4;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    test.Definir(3, 3);
    clave = 3;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    test.Definir(2, 2);
    clave = 2;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 5;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    cout << endl;

    //Hasta aca corre bien, pero con memory leaks

    cout << endl << "Borrando: 2, 5." << endl;
    
    //Aca se rompe y tira SegFault

    clave = 2;
    test.Borrar(clave);
    clave = 5;
    test.Borrar(clave);
    clave = 1;
    cout  << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 2;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 4;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 3;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 2;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    clave = 5;
    cout  << endl << "La clave " << clave << (test.Definido(clave)? " " : " no ") << "esta definida.";
    if (test.Definido(clave)) cout << "Su significado es: " << test.Significado(clave);
    cout << endl;
    return 0;
}
