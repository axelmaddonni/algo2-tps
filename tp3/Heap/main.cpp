#include <iostream>
#include "Heap.hpp"

using std::cout;
using std::endl;

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
    return 0;
}
