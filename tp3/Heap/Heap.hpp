#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <iostream>
#include "AB.hpp"
#include "Vector.h"

using std::cout;
using aed2::Vector;

template<typename P, typename V>
class /*Min*/ Heap
{

private:

    struct tupla
    {
        typename AB<tupla>::Iterador padre;
        P prio;
        V valor;

        tupla(P prioridad, V val) : padre(typename AB<tupla>::Iterador()), prio(prioridad), valor(val) {}
        void operator=(tupla otro) { /*padre = otro.padre;*/ prio = otro.prio; valor = otro.valor; }
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
        else return itI; //podria ser cualquier, total ambos son nulos...
    }
    
    AB<tupla> arb;
    int size;

public:
    
    Heap() : arb(AB<tupla>()), size(0) {} 

    void encolar(P, V); 
    void desencolar();
    const V& proximo();
    bool vacia();

};




template<typename P, typename V>
void Heap<P, V>::encolar (P prioridad, V valor)
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

template<typename P, typename V>
void Heap<P, V>::desencolar ()
{
    Vector<bool> sizeVec = Vector<bool>();
    int sz = size;
    while (sz > 0)
    {
        sizeVec.AgregarAtras(sz % 2);
        sz = sz >> 1;
    }
    if (size == 0) return;
    typename AB<tupla>::Iterador puntero = typename AB<tupla>::Iterador(arb);
    if (size == 1)
    {
        puntero.borrar();
        size--;
        return;
    }
    typename AB<tupla>::Iterador it = typename AB<tupla>::Iterador(arb);
    typename AB<tupla>::Iterador itHijo = typename AB<tupla>::Iterador(arb);
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
    itHijo = minHijos(it);    
    while (itHijo)
    {
        if (itHijo.val().prio > it.val().prio) break;
        else
        {
            it.swapVal(itHijo);
            if (itHijo == it.itIzq()) it.izq();
            else it.der();
        }
        itHijo = minHijos(it);
    }
}

template<typename P, typename V>
const V& Heap<P, V>::proximo()
{
    typename AB<tupla>::Iterador it = typename AB<tupla>::Iterador(arb);
    if (it) return it.val().valor;
}


template<class P, class V>
bool Heap<P, V>::vacia()
{
    return (size == 0);
}
   

#endif //HEAP_HPP_
