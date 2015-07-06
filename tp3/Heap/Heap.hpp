#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <iostream>
#include <cassert>
#include "../AB/AB.hpp"
#include "../aed2/Vector.h"

using std::cout;
using aed2::Vector;

template<typename V>
class /*Min*/ ColaLog
{

private:

    struct tupla
    {
        typename AB<tupla>::Iterador padre;
        int prio;
        V valor;

        tupla(int prioridad, V val) : padre(typename AB<tupla>::Iterador()), prio(prioridad), valor(val) {}
        void operator=(tupla otro) { prio = otro.prio; valor = otro.valor; }
    };

    typename AB<tupla>::Iterador minHijos(typename AB<tupla>::Iterador& it)
    {
        typename AB<tupla>::Iterador itI = it.itIzq();
        typename AB<tupla>::Iterador itD = it.itDer();
        if (itI || itD)
        {
            if (itI)
            {
                if (itD) 
                {
                    if (itI.val().prio < itD.val().prio) return itI; 
                    else return itD; 
                }
                else return itI;
            }
            else return itD;
        }
        else return itI; //podria ser cualquiera, total ambos son nulos...
    }

    
    
    AB<tupla> arb;
    int size;

public:
    
    ColaLog() : arb(AB<tupla>()), size(0) {} 

    void encolar(int, V); 
    V desencolar();
    V proximo();
    bool vacia();

    bool inv ()
    {
        auto it = typename AB<tupla>::Iterador(arb);
        if (it) {
            return invNodo(it);
        }
    }

    bool invNodo(typename AB<tupla>::Iterador it)
    {
        if (!it) return true;
        auto itI = it.itIzq();
        auto itD = it.itDer();
        if (itI && itI.val().prio < it.val().prio) return false;
        else if (itD && itD.val().prio < it.val().prio) return false;
        else return invNodo(itI) && invNodo(itD);
    }
};




template<typename V>
void ColaLog<V>::encolar (int prioridad, V valor)
{
    size++;
    if (size == 1) 
    {
        arb = tupla(prioridad, valor); 
        return;
    }
    Vector<bool> sizeVec = Vector<bool>();
    int sz = size;
    while (sz > 0)
    {
        sizeVec.AgregarAtras(sz % 2);
        sz = sz >> 1;
    }
    typename AB<tupla>::Iterador puntero = arb.crearIt();
    typename AB<tupla>::Iterador nuevo;
    for (int i = sizeVec.Longitud() - 2; i >= 0; i--)
    {
        if (i > 0)
        {
            if (!sizeVec[i]) puntero.izq();
            else puntero.der();
        }
        else
        {
            if (!sizeVec[i])
            {
                puntero.setearIzq(tupla(prioridad, valor)); 
                nuevo = puntero.itIzq();
                nuevo.val().padre = puntero;
            }
            else
            {
                puntero.setearDer(tupla(prioridad, valor)); 
                nuevo = puntero.itDer();
                nuevo.val().padre = puntero;
            }
        }
    }
    typename AB<tupla>::Iterador pad = nuevo.val().padre;
    while ((bool)pad && nuevo.val().prio < pad.val().prio)
    {
        nuevo.swapVal(pad);
        nuevo = pad;
        pad = nuevo.val().padre;
    }
}

template<typename V>
V ColaLog<V>::desencolar ()
{
    auto sizeVec = Vector<bool>();
    int sz = size;
    while (sz > 0)
    {
        sizeVec.AgregarAtras(sz % 2);
        sz = sz >> 1;
    }
    if (size == 0) assert(false);
    V ret = proximo();
    if (size == 1)
    {
        arb.reset();
        size--;
        return ret;
    }
    auto puntero = typename AB<tupla>::Iterador(arb);
    auto it = typename AB<tupla>::Iterador(arb);
    for (int i = sizeVec.Longitud() - 2; i >= 0; i--)
    {
        if (i > 0)
        {
            if (!sizeVec[i]) puntero.izq();
            else puntero.der();
        }
        else
        {
            if (!sizeVec[i]) 
            {
                puntero.izq();
                puntero.val().padre.borrarIzq();
            }
            else
            {
                puntero.der();
                puntero.val().padre.borrarDer();
            }
            it.swapVal(puntero);
            size--;
            puntero.borrar();
        }
    }
    auto itHijo = typename AB<tupla>::Iterador(arb);
    itHijo = minHijos(it);    
    while (itHijo)
    {
        if (itHijo.val().prio > it.val().prio) break;
        else
        {
            it.swapVal(itHijo);
            it = itHijo;
        }
        itHijo = minHijos(it);
    }
    return ret;
}

template<typename V>
V ColaLog<V>::proximo()
{
    if (!vacia())
    {
        typename AB<tupla>::Iterador it = typename AB<tupla>::Iterador(arb);
        return it.val().valor;
    }
    else assert(false);
}


template<typename V>
bool ColaLog<V>::vacia()
{
    return (size == 0);
}
   

#endif //HEAP_HPP_
