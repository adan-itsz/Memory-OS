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
 
void listaEnlazada::añadirProceso(nodePtr nodo) {
	
	nodePtr n = new node; //crea nodo
	if (!ban) {
		memoriaTotal = new node;
		memoriaTotal = n;
		auxMemoria = nodo;
		ban = true;
	}
	else {
		n->siguiente = NULL;
		n->estado = nodo->estado;
		n->id = nodo->id;
		n->tamañoMemoria = nodo->tamañoMemoria;
		n->tamañoProceso = nodo->tamañoProceso;
		n->inicioProceso = nodo->inicioProceso;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tamañoMemoria -= n->tamañoMemoria;
		auxMemoria->tamañoProceso -= n->tamañoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamañoMemoria;
		//auxMemoria = memoriaTotal;
		if (actual->tamañoMemoria == memoriaTotal->tamañoMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tamañoMemoria;
		}
	}
	else {
		
		auxMemoria->tamañoMemoria -= n->tamañoMemoria;
		auxMemoria->tamañoProceso -= n->tamañoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamañoMemoria;
		inicio = n;
	}
}
}

void listaEnlazada::eliminarNodo(int Id) {
	//delPtr = actual, actual = siguiente, temporal = anterior
	nodePtr delPtr = NULL;
	temporal = inicio;
	actual = inicio;
	while (actual != NULL && actual->id != Id) {
		temporal = actual->siguiente;
		actual = actual->siguiente;
		actual->estado = Id;
	}
	if (actual == NULL) {
	cout<< Id << "No esta en la lista\n";
		//delete delPtr;
	}
	else {

		delPtr = actual;
		actual = actual->siguiente;

		if (temporal->estado == false) {
			temporal->tamañoMemoria += delPtr->tamañoMemoria;
			temporal->tamañoMemoria += actual->tamañoMemoria;
			temporal->tamañoProceso += delPtr->tamañoProceso;
			temporal->tamañoProceso += actual->tamañoProceso;
			//delete delPtr;
			delPtr = actual;
			actual = actual->siguiente;

			temporal->siguiente = actual; //junta nodos;
		}
		

		 else if(temporal-> estado == false){
			temporal->tamañoMemoria += delPtr->tamañoMemoria;
			temporal->tamañoProceso += delPtr ->tamañoProceso;
			temporal-> siguiente = actual;
			delete delPtr;
		}

		else if (actual->estado == false) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tamañoMemoria += delPtr->tamañoMemoria;
			actual->tamañoProceso += delPtr->tamañoProceso;
			temporal->siguiente = actual;
			delete delPtr;
		}

		temporal->siguiente = actual; //conecta la lista
		 if (delPtr == inicio)
		{
			inicio = inicio->siguiente;
			temporal = NULL;
		}
		delPtr->estado = false;
		cout << "El proceso " << Id << "ha sido eliminado\n";
	}
	
}

void listaEnlazada::mostrarLista() {

	actual = inicio;
	cout << "H/P \t |Inicio Proceso	\t|Tamaño de Proceso\t|Tamaño UAM\t|ID|" << endl;
	while (actual != NULL)
	{
		cout<< actual->estado << "\t |" << actual->inicioProceso <<"\t\t\t\t |" << actual->tamañoMemoria << "\t\t\t |" << actual->tamañoProceso << "\t\t|" << actual->id << "|" << endl ;
		actual = actual->siguiente;
	}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tamañoMemoria << "\t\t\t |" << auxMemoria->tamañoProceso << "\t\t|" << 0 << "|" << endl;
}
