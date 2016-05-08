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
	int bandera = 0;
	
	while (actual != NULL && actual->id != Id) {
		
		actual = actual->siguiente;
		
	}

	if (actual->id == 1) {
		delPtr = inicio;
		if (inicio->siguiente == NULL) {
			auxMemoria->tamañoMemoria += inicio->tamañoMemoria;
			auxMemoria->tamañoProceso += inicio->tamañoProceso;
			auxMemoria->inicioProceso = inicio->inicioProceso;
			delete inicio;
			inicio = NULL;
			bandera = 1;
		}
		else
		{
			delPtr = inicio->siguiente;

			if (delPtr->estado == false) {
				inicio = inicio->siguiente;
				inicio->tamañoMemoria += delPtr->tamañoMemoria;
				inicio->tamañoProceso += delPtr->tamañoProceso;
				inicio->inicioProceso = 0;
				delete delPtr;
				delPtr = NULL;
				
			}
			
			else if (inicio->siguiente->estado == true) {
				inicio->estado = false;
				bandera = 1;
			}

		}
		
		

		temporal = NULL;
	}


	else {

		if (bandera == 0) {

			while (temporal->siguiente != NULL)
			{
				temporal = temporal->siguiente;
			}
			delPtr = temporal;

			if (delPtr->id == Id) {

				temporal = inicio;

				while (temporal != NULL && temporal->id != delPtr->id - 1)
				{
					temporal = temporal->siguiente;
				}
				actual = inicio;
				while (actual != NULL && actual->id != temporal->id - 1)
				{
					actual = actual->siguiente;
				}

				if (temporal->estado == false)
				{
					temporal->tamañoMemoria += delPtr->tamañoMemoria;
					temporal->tamañoProceso += delPtr->tamañoProceso;
					delete delPtr;
					delPtr = NULL;
					delPtr = temporal;
					auxMemoria->tamañoMemoria += temporal->tamañoMemoria;
					auxMemoria->tamañoProceso += temporal->tamañoProceso;
					auxMemoria->inicioProceso = temporal->inicioProceso;
					delete delPtr;
					delPtr = NULL;

					actual->siguiente = NULL;
					bandera = 1;			
				}
				else if(temporal-> estado == true)
				{
					auxMemoria->tamañoMemoria += delPtr->tamañoMemoria;
					auxMemoria->tamañoProceso += delPtr->tamañoProceso;
					auxMemoria->inicioProceso = delPtr->inicioProceso;
					delete delPtr;
					delPtr = NULL;
					temporal->siguiente = NULL;
					bandera = 1;
				}

			}
			temporal = NULL;
		}
	}
	
	if (actual == NULL && bandera == 0) {
	cout<< Id << "No esta en la lista\n";
		//delete delPtr;
	}
	else if (bandera == 0){

		nodePtr delPtr = NULL;
		temporal = inicio;
		actual = inicio;
		while (actual != NULL && actual->id != Id) {

			actual = actual->siguiente;

		}

		delPtr = actual;
		actual = actual->siguiente;	


		if(temporal != NULL ) {
			if (temporal->estado == false && actual->estado == false && delPtr->id != 1 ) {
			
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
			delPtr = NULL;
			temporal->siguiente = actual;
		}

		else if (actual->estado == false ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tamañoMemoria += delPtr->tamañoMemoria;
			actual->tamañoProceso += delPtr->tamañoProceso;			
			delete delPtr;
			delPtr = NULL;
			temporal->siguiente = actual;
		}

		else if (temporal->estado == true && actual->estado == true ) {

			delPtr->estado = false;
		}
	}
		
		cout << "El proceso " << Id << "ha sido eliminado\n";
	}
	
}

void listaEnlazada::mostrarLista() {

	actual = inicio;
	temporal = inicio;

	cout << "H/P \t |Inicio Proceso	\t|Tamaño de Proceso\t|Tamaño UAM\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tamañoMemoria << "\t\t\t |" << actual->tamañoProceso << "\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tamañoMemoria << "\t\t\t |" << auxMemoria->tamañoProceso << "\t\t|" << 0 << "|" << endl;
}

bool listaEnlazada::vacia() {

	if (inicio == NULL) {
		return true;
	}
	else
	{
		return false;
	}

}