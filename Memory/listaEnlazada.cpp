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
 
void listaEnlazada::a�adirProceso(nodePtr nodo) {
	
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
		n->tama�oMemoria = nodo->tama�oMemoria;
		n->tama�oProceso = nodo->tama�oProceso;
		n->inicioProceso = nodo->inicioProceso;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tama�oMemoria -= n->tama�oMemoria;
		auxMemoria->tama�oProceso -= n->tama�oProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tama�oMemoria;
		//auxMemoria = memoriaTotal;
		if (actual->tama�oMemoria == memoriaTotal->tama�oMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;
		}
	}
	else {
		
		auxMemoria->tama�oMemoria -= n->tama�oMemoria;
		auxMemoria->tama�oProceso -= n->tama�oProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tama�oMemoria;
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
		inicio->tama�oMemoria += delPtr->tama�oMemoria;
		inicio->tama�oProceso += delPtr->tama�oProceso;
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
			
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oMemoria += actual->tama�oMemoria;
				temporal->tama�oProceso += delPtr->tama�oProceso;
				temporal->tama�oProceso += actual->tama�oProceso;
				delPtr = actual;
				actual = actual->siguiente;

				temporal->siguiente = actual; //junta nodos;

		}
		

		 else if(temporal-> estado == false){
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oProceso += delPtr ->tama�oProceso;
			temporal-> siguiente = actual;
			delete delPtr;
		}

		else if (actual->estado == false ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tama�oMemoria += delPtr->tama�oMemoria;
			actual->tama�oProceso += delPtr->tama�oProceso;
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
	cout << "H/P \t |Inicio Proceso	\t|Tama�o de Proceso\t|Tama�o UAM\t|ID|" << endl;
	while (actual != NULL)
	{
		cout<< actual->estado << "\t |" << actual->inicioProceso <<"\t\t\t\t |" << actual->tama�oMemoria << "\t\t\t |" << actual->tama�oProceso << "\t\t|" << actual->id << "|" << endl ;
		actual = actual->siguiente;
	} 

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tama�oMemoria << "\t\t\t |" << auxMemoria->tama�oProceso << "\t\t|" << 0 << "|" << endl;
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
