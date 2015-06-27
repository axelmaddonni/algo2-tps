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
        void operator=(tupla otro) { /*padre = otro.padre*/; prio = otro.prio; valor = otro.valor; }
    };

    int minHijos(AB<tupla> pad)
    {
        if ((pad.izq) || (pad.der))
        {
            if (pad.izq)
            {
                if (pad.der) 
                {
                    if (pad.izq->val.prio < pad.der->val.prio) return 0; 
                    else return 1; 
                }
                else return 0;
            }
            else return 1;
        }
        else return 2;
    }
    
    AB<tupla> arb;
    int size;

public:
    
    Heap() : arb(AB<tupla>()), size(0) {} 

    void encolar(P, V); 
    void desencolar();
    const V& proximo();
    //void mostrar();
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
        //pad = pad.val().padre;
        pad = nuevo.val().padre;
        /*
        V valAux = nuevo->raiz().valor;
        nuevo->raiz().valor = nuevo->raiz().padre->raiz().valor;
        nuevo->raiz().padre->raiz().valor = valAux;
        P prioAux = nuevo->raiz().prio;
        nuevo->raiz().prio = nuevo->raiz().padre->raiz().prio;
        nuevo->raiz().padre->raiz().prio = prioAux;
        nuevo = nuevo->raiz().padre;
        */
    }
}

/*
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
    if (size == 0) {return;}
    if (size == 1)
    {
        delete &arb;
        size--;
    }
    AB<tupla> *puntero = &arb;
    for (int i = sizeVec.Longitud() - 2; i >= 0; i--)
    {
        if (i > 0)
        {
            if (!sizeVec[i]) puntero = puntero->izq();
            else puntero = puntero->der();
        }
        else
        {
            if (!sizeVec[i]) 
            {
                puntero = puntero->izq();
                (puntero->raiz().padre)->setearIzq(nullptr);
            }
            else
            {
                puntero = puntero->der();
                (puntero->raiz().padre)->setearDer(nullptr);
            }
            puntero->nodoSwap(arb.primero);
            size--;
            delete puntero;
        }
    }
    AB<tupla> *it = &arb;
    int min = minHijos(*it);
    while (min < 2)
    {
        if (min == 0 && (it->izq)->prio < it->prio) 
        {
            it->nodoSwap(it->izq);
            it = it->izq;
        }
        else if (min == 1 && (it->der)->prio < it->prio)
        {
            it->nodoSwap(it->der);
            it = it->der;
        }
        else break;
        min = it->nodoMin();
    }
}*/

/*template<class P, class V>
void Heap<P, V>::mostrar()
{
    if (arb.primero) (arb.primero)->mostrarNodo();
}*/

template<typename P, typename V>
const V& Heap<P, V>::proximo()
{
    typename AB<tupla>::Iterador it = typename AB<tupla>::Iterador(arb);
    return it.val().valor;
}


template<class P, class V>
bool Heap<P, V>::vacia()
{
    return (size == 0);
}
   

#endif //HEAP_HPP_
