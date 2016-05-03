#include "stdafx.h"
#include "listaEnlazada.h"
#include <iostream>
#include <cstdlib>

using namespace std;


//CONSTRUCTOR
listaEnlazada::listaEnlazada() {
	inicio = NULL;
	actual = NULL;
	temporal = NULL;
}
bool ban = false;

void listaEnlazada::a�adirProceso(nodePtr nodo) {
	nodePtr memoriaTotal = new node;
	nodePtr n = new node; //crea nodo
	n->siguiente = NULL;
	n->estado = nodo->estado;
	n->id = nodo->id;
	n->tama�oMemoria = nodo->tama�oMemoria;
	n->tama�oProceso = nodo->tama�oProceso;
	n->inicioProceso = nodo->inicioProceso;
//	n->inicioProceso += actual->tama�oProceso;
	if(!ban) {
		memoriaTotal = n;
		ban = true;
	}
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{
			actual = actual->siguiente;
		}
		actual->siguiente = n;
		memoriaTotal->tama�oMemoria -= n->tama�oMemoria;
		memoriaTotal->tama�oProceso -= n->tama�oProceso;
		if (actual->tama�oMemoria == memoriaTotal->tama�oMemoria){//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}else {
			n->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;
		}
	}
	else {
		inicio = n;
	}
}

void listaEnlazada::eliminarNodo(int eliminarDato) {
	//delPtr = actual, actual = siguiente, temporal = anterior
	nodePtr delPtr = NULL;
	temporal = inicio;
	actual = inicio;
	while (actual != NULL && actual->id != eliminarDato) {
		temporal = actual;
		actual = actual->siguiente;
	}
	if (actual == NULL) {
		cout << eliminarDato << "No esta en la lista\n";
		delete delPtr;
	}
	else {

		delPtr = actual;
		actual = actual->siguiente;

		if(actual-> estado == false){
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tama�oMemoria += delPtr->tama�oMemoria;
			actual->tama�oProceso += delPtr -> tama�oProceso;
			temporal->siguiente = actual;
			delete delPtr;
		}

		if(temporal-> estado == false){
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oProceso += delPtr ->tama�oProceso;
			temporal-> siguiente = actual;
			delete delPtr;
		}

		if(actual->estado == false && actual->estado ==false){
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oMemoria += actual->tama�oMemoria;
			temporal->tama�oProceso += delPtr ->tama�oProceso;
			temporal->tama�oProceso += actual->tama�oProceso;
			delete delPtr;
			delPtr = actual;
			actual = actual->siguiente;

			temporal-> siguiente = actual; //junta nodos;
		}

		temporal->siguiente = actual; //conecta la lista
		if (delPtr == inicio)
		{
			inicio = inicio->siguiente;
			temporal = NULL;
		}
		delete delPtr;
		cout << "El valor " << eliminarDato << "ha sido eliminado\n";
	}
}

void listaEnlazada::mostrarLista() {

	actual = inicio;
	cout << "H/P \t |Inicio Proceso	\t|Tama�o de Proceso\t|Tama�o UAM\t|ID|" << endl;
	while (actual != NULL)
	{
		cout<< actual->estado << "\t |" << actual->inicioProceso <<"\t\t |" << actual->tama�oMemoria << "\t |" << actual->tama�oProceso << "\t|" << actual->id << "\t |" << endl ;
		actual = actual->siguiente;
	}
}
