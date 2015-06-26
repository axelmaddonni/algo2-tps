#ifndef AB_HPP_
#define AB_HPP_

#include <iostream>

using std::cout;

template<typename V>
class AB
{

private:

    struct Nodo
    {
        Nodo* izquierdo;
        Nodo* derecho;
        V val;
        
        Nodo(V valor) : izquierdo(nullptr), derecho(nullptr), val(valor) {}
       
    };

    void borrar(Nodo *aBorrar)
    {
        if (aBorrar->izquierdo.primero) borrar(aBorrar->izquierdo.primero);
        if (aBorrar->derecho.primero) borrar(aBorrar->derecho.primero);
        delete aBorrar;
    }

    
    Nodo* primero;

public:

    AB() : primero(nullptr) {}
    AB(V a) : primero(new Nodo(a)) {}
    AB(AB i, V a, AB d)
    {
        primero = new Nodo(a);
        primero->izq = i.primero;
        primero->der = d.primero;
    }


    void borrarAB() { primero = nullptr; }
    
    /*
    ~AB()
    {
        if (primero) 
        {
            cout << "Borrando 0x" << (unsigned long) primero << '\n';
            delete primero;
        }
    }
    */
 
    class Iterador
    {
    
    friend class AB<V>;

    private: 

        Nodo *actual;

        Iterador(Nodo *nuevo) : actual(nuevo) {}
    
    public:
        
        Iterador() : actual(nullptr) {}
        Iterador(AB<V> nuevo) : actual(nuevo.primero) {}
        ~Iterador() { delete this; }

        void izq() { actual = actual->izquierdo; }
        void der() { actual = actual->derecho;   }
        AB<V>* act() { return (AB<V>*) &actual; }
        V& val() { return actual->val; }
        void setearIzq(AB nuevo) { actual->izquierdo = nuevo; }
        void setearDer(AB nuevo) { actual->derecho = nuevo; }
        void setearIzq(V nuevo) { actual->izquierdo = new Nodo(nuevo); }
        void setearDer(V nuevo) { actual->derecho = new Nodo(nuevo); }       
        void asignar(V nuevo) { actual->val = nuevo; }

        Iterador itIzq() { return Iterador(actual->izquierdo); }
        Iterador itDer() { return Iterador(actual->derecho); }

        void swapVal(Iterador otro)
        {
            V valAux = actual->val;
            actual->val = otro.actual->val;
            otro.actual->val = valAux;
        }

        operator bool() const  { return (bool)actual; }

    };


    void operator=(Iterador nuevo) { primero = nuevo->actual; }
    void operator=(V nuevo) { primero = new Nodo(nuevo); }
    //void asignar(V nuevo) { cout << "LA RECONCHA DE LA LORA MALPARIDA" << '\n'; primero = (Nodo *&&) new Nodo(nuevo); }
    Iterador crearIt() { return Iterador(primero); }
};


#endif //AB_HPP_
