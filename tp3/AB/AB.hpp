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
        AB izquierdo;
        AB derecho;
        V val;
        
        Nodo(V valor) : izquierdo(AB<V>()), derecho(AB<V>()), val(valor) {}
       
    };

    void borrar(Nodo *aBorrar)
    {
        //if (aBorrar->izquierdo) borrar(aBorrar->izquierdo);
        //if (aBorrar->derecho) borrar(aBorrar->derecho);
        delete aBorrar;
    }

    
    Nodo* primero;

    operator Nodo*() const { return primero; }

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
    
    ///*
    ~AB()
    {
            if (primero) 
        {
            borrar(primero);
            borrarAB();
        }
    }
    //*/
 
    class Iterador
    {
    
    friend class AB<V>;

    private: 

        Nodo *actual;

        Iterador(Nodo *nuevo) : actual(nuevo) {}
    
    public:
        
        Iterador() : actual(nullptr) {}
        Iterador(AB<V>& nuevo) : actual(nuevo.primero) {}

        void izq() { actual = actual->izquierdo; }
        void der() { actual = actual->derecho;   }
        AB<V>* act() { return (AB<V>*) &actual; }
        V& val() { return actual->val; }
        void setearIzq(AB& nuevo) { actual->izquierdo = nuevo; }
        void setearDer(AB& nuevo) { actual->derecho = nuevo; }
        void setearIzq(V nuevo) { actual->izquierdo = new Nodo(nuevo); }
        void setearDer(V nuevo) { actual->derecho = new Nodo(nuevo); }       
        void asignar(V nuevo) { actual->val = nuevo; }
        //falso borrar que no borra NO TE CONFIES
        //borrar solo sirve recursivamente a los hijos, pero no borra el actual
        void borrar() { delete actual; }
        //borrarIzq y borrarDer solo setean los punteros como nulos,
        void borrarIzq() { actual->izquierdo = nullptr; }
        void borrarDer() { actual->derecho = nullptr; }
        //estos si borran
        void borrarPostaIzq() { 
            delete *(AB<V>*) &(actual->izquierdo);
            borrarIzq();
        }
        void borrarPostaDer() { 
            delete *(AB<V>*) &(actual->derecho);
            borrarDer();
        }
        
        Iterador itIzq() { return Iterador(actual->izquierdo); }
        Iterador itDer() { return Iterador(actual->derecho); }

        void swapVal(Iterador otro)
        {
            V valAux = actual->val;
            actual->val = otro.actual->val;
            otro.actual->val = valAux;
        }

        operator bool() const  { return (bool)actual; }
        bool operator==(AB<V>& otro) { return otro.primero == actual; }

    };


    void operator=(const Iterador& nuevo) { primero = nuevo.actual; }
    void operator=(V nuevo) { primero = new Nodo(nuevo); }
    Iterador crearIt() const { return Iterador(primero); }

    void reset()
    {
        Nodo *aux = primero;
        if (aux) borrar(aux);
        primero = nullptr;
    }

};


#endif //AB_HPP_
