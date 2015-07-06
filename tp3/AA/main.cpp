#include "../aed2.h"
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


    clave = 2;
    test.Borrar(clave);

    clave = 3;
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

    test.Definir(15, 2);
    test.Definir(34, 8);
    test.Definir(20, 23);
    test.Definir(6, 53);
    test.Definir(29, 4);
    test.Definir(21, 40);

    cout << "Hacia la derecha" << endl;
    test.printD();
    cout << endl;
    cout << "Hacia la izquierda" << endl;
    test.printI();
    cout << endl;
    cout << "Hacia la derecha izquierda" << endl;
    test.printDI();
    cout << endl;
    cout << "Hacia la izquierda derecha" << endl;
    test.printID();
    cout << endl;

    return 0;
}
