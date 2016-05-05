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
		auxMemoria = nodo;
		ban = true;
	}
	else {
		n->siguiente = NULL;
		n->estado = nodo->estado;
		n->id = nodo->id;
		n->tamaņoMemoria = nodo->tamaņoMemoria;
		n->tamaņoProceso = nodo->tamaņoProceso;
		n->inicioProceso = nodo->inicioProceso;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tamaņoMemoria -= n->tamaņoMemoria;
		auxMemoria->tamaņoProceso -= n->tamaņoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamaņoMemoria;
		//auxMemoria = memoriaTotal;
		if (actual->tamaņoMemoria == memoriaTotal->tamaņoMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tamaņoMemoria;
		}
	}
	else {
		
		auxMemoria->tamaņoMemoria -= n->tamaņoMemoria;
		auxMemoria->tamaņoProceso -= n->tamaņoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamaņoMemoria;
		inicio = n;
	}
}
}

void listaEnlazada::eliminarNodo(int Id) {
	//delPtr = actual, actual = siguiente, temporal = anterior
	nodePtr delPtr = NULL;
	temporal = inicio;
	actual = inicio;
	bool bandera = false;
	while (actual != NULL && actual->id != Id) {
		actual = actual->siguiente;
		
	}

	if (actual->id==1) {
		delPtr = inicio;//temporal
	    
		inicio = inicio->siguiente;
		inicio->tamaņoMemoria += delPtr->tamaņoMemoria;
		inicio->tamaņoProceso += delPtr->tamaņoProceso;
		inicio->inicioProceso = 0;
		delete delPtr;

		temporal = NULL;
	}
	else {
		while (temporal != NULL && temporal->id != Id - 1)
		{
			temporal = temporal->siguiente;
		}
	}
	
	if (actual == NULL) {
	cout<< Id << "No esta en la lista\n";
		//delete delPtr;
	}
	else {

		delPtr = actual;
		actual = actual->siguiente;	

		if(actual == NULL) {
			//actual = inicio;
			//actual->estado = false;
		}

	if(temporal != NULL ) {
		if (temporal->estado == false && actual->estado == false && delPtr->id != 1 ) {
			
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoMemoria += actual->tamaņoMemoria;
				temporal->tamaņoProceso += delPtr->tamaņoProceso;
				temporal->tamaņoProceso += actual->tamaņoProceso;
				delPtr = actual;
				actual = actual->siguiente;

				temporal->siguiente = actual; //junta nodos;

		}
		

		 else if(temporal-> estado == false){
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoProceso += delPtr ->tamaņoProceso;
			temporal-> siguiente = actual;
			delete delPtr;
		}

		else if (actual->estado == false ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tamaņoMemoria += delPtr->tamaņoMemoria;
			actual->tamaņoProceso += delPtr->tamaņoProceso;
			temporal->siguiente = actual;
			delete delPtr;
		}

		else if (temporal->estado == true && actual->estado == true ) {

			delPtr->estado = false;
		}
	}
		//temporal->siguiente = actual; //conecta la lista
		/* if (delPtr == inicio)
		{
			inicio = inicio->siguiente;
			temporal = NULL;
		}*/
		
		cout << "El proceso " << Id << "ha sido eliminado\n";
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

void listaEnlazada::posicionarUltimo() {
	actual = inicio;
	temporal = inicio;
	while (actual != NULL) {
	
		actual = actual->siguiente;
	}
	while (temporal->siguiente != actual) {
		temporal = temporal->siguiente;
	}

}
