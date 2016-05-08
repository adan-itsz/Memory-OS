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
	int bandera = 0;
	
	while (actual != NULL && actual->id != Id) {
		
		actual = actual->siguiente;
		
	}

	if (actual->id == 1) {
		delPtr = inicio;
		if (inicio->siguiente == NULL) {
			auxMemoria->tamaņoMemoria += inicio->tamaņoMemoria;
			auxMemoria->tamaņoProceso += inicio->tamaņoProceso;
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
				inicio->tamaņoMemoria += delPtr->tamaņoMemoria;
				inicio->tamaņoProceso += delPtr->tamaņoProceso;
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

				while (temporal != NULL && temporal->siguiente != delPtr)
				{
					temporal = temporal->siguiente;
				}
				actual = inicio;
				while (actual != NULL && actual->siguiente != temporal)
				{
					actual = actual->siguiente;
				}

				if (temporal->estado == false)
				{
					temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
					temporal->tamaņoProceso += delPtr->tamaņoProceso;
					delete delPtr;
					delPtr = NULL;
					delPtr = temporal;
					auxMemoria->tamaņoMemoria += temporal->tamaņoMemoria;
					auxMemoria->tamaņoProceso += temporal->tamaņoProceso;
					auxMemoria->inicioProceso = temporal->inicioProceso;
					delete delPtr;
					delPtr = NULL;

					if (actual == NULL)
					{
						inicio = NULL;
					}
					else
					{
						actual->siguiente = NULL;
					}
					
					bandera = 1;			
				}
				else if(temporal-> estado == true)
				{
					auxMemoria->tamaņoMemoria += delPtr->tamaņoMemoria;
					auxMemoria->tamaņoProceso += delPtr->tamaņoProceso;
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

		while (temporal != NULL && temporal->siguiente != delPtr)
		{
			temporal = temporal->siguiente;
		}

		if(temporal != NULL ) {
			if (temporal->estado == false && actual->estado == false) {
			
				temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
				temporal->tamaņoMemoria += actual->tamaņoMemoria;
				temporal->tamaņoProceso += delPtr->tamaņoProceso;
				temporal->tamaņoProceso += actual->tamaņoProceso;
				delete delPtr;
				delPtr = NULL;
				actual = actual->siguiente;
				temporal->siguiente = actual; //junta nodos;

		}	
		 else if(temporal-> estado == false && actual->estado == true){
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoProceso += delPtr ->tamaņoProceso;
			temporal-> siguiente = actual;
			delete delPtr;
			delPtr = NULL;
			temporal->siguiente = actual;
		}

		else if (actual->estado == false && temporal-> estado == true ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tamaņoMemoria += delPtr->tamaņoMemoria;
			actual->tamaņoProceso += delPtr->tamaņoProceso;			
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

	cout << "H/P \t |Inicio Proceso	\t|Tamaņo de Proceso\t|Tamaņo UAM\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tamaņoMemoria << "\t\t\t |" << actual->tamaņoProceso << "\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tamaņoMemoria << "\t\t\t |" << auxMemoria->tamaņoProceso << "\t\t|" << 0 << "|" << endl;
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
void listaEnlazada::primerAjuste(nodePtr node) {
	nodePtr nodo = node;
	nodePtr aux;
 	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		aņadirProceso(nodo);
	}

	else {
		while (actual != NULL && ban!=true) {
			
			if (actual->estado == false && actual->tamaņoProceso >= nodo->tamaņoProceso) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				temporal = nodo;

				temporal->tamaņoMemoria = actual->tamaņoMemoria - nodo->tamaņoMemoria;
				actual->tamaņoMemoria = nodo->tamaņoMemoria;
				temporal->tamaņoProceso = actual->tamaņoProceso- nodo->tamaņoProceso;
				actual->tamaņoProceso= nodo->tamaņoProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tamaņoMemoria;

				actual->siguiente = temporal;
				temporal->siguiente = aux;

				actual = inicio;
				while (actual->siguiente!=NULL)
				{
					actual = actual->siguiente;
				}
				temporal->id = actual->id + 1;
				temporal->estado = false;

			}
			else {

				
			}
			
			actual = actual->siguiente;
			
		}
		
		if (actual == NULL && !ban) {
			aņadirProceso(nodo);
		}
	}


}