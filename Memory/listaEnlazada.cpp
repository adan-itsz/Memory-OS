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
	auxMemoria = NULL;
	memoriaTotal = NULL;
	
}
bool ban = false;
 
void listaEnlazada::aņadirProceso(nodePtr nodo) {
	
	nodePtr n = new node; //crea nodo
	if (!ban) {
		memoriaTotal = new node;
		memoriaTotal = n;
		auxMemoria = memoriaTotal;
		ban = true;
	}
	else {
		n->siguiente = NULL;
		n->estado = nodo->estado;
		n->id = nodo->id;
		n->tamaņoMemoria = nodo->tamaņoMemoria;
		n->tamaņoProceso = nodo->tamaņoProceso;
		n->inicioProceso = nodo->inicioProceso;
		//	n->inicioProceso += actual->tamaņoProceso;
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{
			actual = actual->siguiente;
		}
		actual->siguiente = n;
		memoriaTotal->tamaņoMemoria -= n->tamaņoMemoria;
		memoriaTotal->tamaņoProceso -= n->tamaņoProceso;
		memoriaTotal->inicioProceso = n->inicioProceso + n->tamaņoMemoria;
		auxMemoria = memoriaTotal;
		if (actual->tamaņoMemoria == memoriaTotal->tamaņoMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tamaņoMemoria;
		}
	}
	else {
		inicio = n;
	}
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
			actual->tamaņoMemoria += delPtr->tamaņoMemoria;
			actual->tamaņoProceso += delPtr -> tamaņoProceso;
			temporal->siguiente = actual;
			delete delPtr;
		}

		if(temporal-> estado == false){
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoProceso += delPtr ->tamaņoProceso;
			temporal-> siguiente = actual;
			delete delPtr;
		}

		if(actual->estado == false && actual->estado ==false){
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoMemoria += actual->tamaņoMemoria;
			temporal->tamaņoProceso += delPtr ->tamaņoProceso;
			temporal->tamaņoProceso += actual->tamaņoProceso;
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
	cout << "H/P \t |Inicio Proceso	\t|Tamaņo de Proceso\t|Tamaņo UAM\t|ID|" << endl;
	while (actual != NULL)
	{
		cout<< actual->estado << "\t |" << actual->inicioProceso <<"\t\t\t\t |" << actual->tamaņoMemoria << "\t\t\t |" << actual->tamaņoProceso << "\t\t|" << actual->id << "|" << endl ;
		actual = actual->siguiente;
	}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tamaņoMemoria << "\t\t\t |" << auxMemoria->tamaņoProceso << "\t\t|" << 0 << "|" << endl;
}
