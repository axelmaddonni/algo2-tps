#include <iostream>
#include "aed2.h"

#include "Heap/Heap.hpp"
#include "AA/diccLog.h"
#include "TRIE/dicc_trie.h"


using std::cout;
using std::endl;
using aed2::Nat;
using aed2::String;

int main()
{
    Heap<int, char> test = Heap<int, char>();
    test.encolar(6, '6');
    cout << test.proximo() << endl;
    test.desencolar();
    test.encolar(9, '9');
    cout << test.proximo() << endl;
    test.encolar(4, '4');
    cout << test.proximo() << endl;
    test.encolar(3, '3');
    cout << test.proximo() << endl;
    test.encolar(7, '7');
    cout << test.proximo() << endl;
    test.encolar(8, '8');
    cout << test.proximo() << endl;
    test.encolar(3, '3');
    cout << test.proximo() << endl;
    test.encolar(5, '5');
    cout << test.proximo() << endl; 
    test.encolar(2, '2');
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    test.desencolar();
    cout << test.proximo() << endl;
    cout << "fin heap" << endl;

    diccLog<String, Nat> paquetesPorID = diccLog<String, Nat>();
    
    return 0;
}
