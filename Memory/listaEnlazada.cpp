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
int var = 0;
 
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
	int bandera = 0;
	
	while (actual != NULL && actual->id != Id) {
		
		actual = actual->siguiente;
		
	}

	if (actual->id == 1) {
		delPtr = inicio;
		if (inicio->siguiente == NULL) {
			auxMemoria->tama�oMemoria += inicio->tama�oMemoria;
			auxMemoria->tama�oProceso += inicio->tama�oProceso;
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
				inicio->tama�oMemoria += delPtr->tama�oMemoria;
				inicio->tama�oProceso += delPtr->tama�oProceso;
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
					temporal->tama�oMemoria += delPtr->tama�oMemoria;
					temporal->tama�oProceso += delPtr->tama�oProceso;
					delete delPtr;
					delPtr = NULL;
					delPtr = temporal;
					auxMemoria->tama�oMemoria += temporal->tama�oMemoria;
					auxMemoria->tama�oProceso += temporal->tama�oProceso;
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
					auxMemoria->tama�oMemoria += delPtr->tama�oMemoria;
					auxMemoria->tama�oProceso += delPtr->tama�oProceso;
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
			
				temporal->tama�oMemoria += delPtr->tama�oMemoria;
				temporal->tama�oMemoria += actual->tama�oMemoria;
				temporal->tama�oProceso += delPtr->tama�oProceso;
				temporal->tama�oProceso += actual->tama�oProceso;
				delete delPtr;
				delPtr = NULL;
				actual = actual->siguiente;
				temporal->siguiente = actual; //junta nodos;

		}	
		 else if(temporal-> estado == false && actual->estado == true){
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oProceso += delPtr ->tama�oProceso;
			temporal-> siguiente = actual;
			delete delPtr;
			delPtr = NULL;
			temporal->siguiente = actual;
		}

		else if (actual->estado == false && temporal-> estado == true ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tama�oMemoria += delPtr->tama�oMemoria;
			actual->tama�oProceso += delPtr->tama�oProceso;			
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

	cout << "H/P \t |Inicio Proceso	\t|Tama�o de Proceso\t|Tama�o UAM\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tama�oMemoria << "\t\t\t |" << actual->tama�oProceso << "\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" << auxMemoria->tama�oMemoria << "\t\t\t |" << auxMemoria->tama�oProceso << "\t\t|" << 0 << "|" << endl;
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
	int aux2 = 0;
	
 	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		a�adirProceso(nodo);
	}

	else {
		while (actual != NULL && ban!=true) {
			
			if (actual->estado == false && actual->tama�oProceso >= nodo->tama�oProceso) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tama�oMemoria;
				temporal = nodo;

				temporal->tama�oMemoria = actual->tama�oMemoria - temporal->tama�oMemoria;
				actual->tama�oMemoria = aux2;
			
				actual->tama�oProceso = actual->tama�oProceso- nodo->tama�oProceso;
				temporal->tama�oProceso= nodo->tama�oProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;

				actual->siguiente = temporal;
				temporal->siguiente = aux;

				aux = inicio;
				var = aux->id;
				while (aux->siguiente!=NULL)
				{
					if(var <= aux->siguiente->id)
					{
						var = aux->siguiente->id;
					}
					aux = aux->siguiente;
				}
				temporal->id = var;
				temporal->estado = false;

			}
			else {

				
			}
			
			actual = actual->siguiente;
			
		}
		
		if (actual == NULL && !ban) {
			a�adirProceso(nodo);
		}
	}


}
int identificadorInicio = 0;
void listaEnlazada::siguienteAjuste(nodePtr node)
{
	nodePtr nodo = node;
	nodePtr aux;
	int aux2 = 0;
	
	actual = inicio;
	temporal = inicio;
	
	bool ban = false;
	if (vacia()) {
		a�adirProceso(nodo);
	}

	else {
		if(identificadorInicio == 0){
			while (actual != NULL && ban != true) {

				if (actual->estado == false && actual->tama�oProceso >= nodo->tama�oProceso) {
					actual->estado = true;
					ban = true;

					aux = actual->siguiente;
					temporal = nodo;
					aux2 = nodo->tama�oMemoria;

					temporal->tama�oMemoria = actual->tama�oMemoria - temporal->tama�oMemoria;
					actual->tama�oMemoria = aux2;
					
					actual->tama�oProceso = actual->tama�oProceso - nodo->tama�oProceso;

					temporal->tama�oProceso = nodo->tama�oProceso;
					temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;

					actual->siguiente = temporal;
					temporal->siguiente = aux;

					identificadorInicio = actual->id;

					aux = inicio;
					var = aux->id;
					while (aux->siguiente != NULL)
					{		
						if (var <= aux->siguiente->id)
						{
							var = aux->siguiente->id;
						}
						aux = aux->siguiente;
					}
					temporal->id = var;
					temporal->estado = false;

				 }
				actual = actual->siguiente;

			}
		}
		else if(identificadorInicio != 0)
		{
			while (actual!=NULL && actual->id != identificadorInicio)
			{
				actual = actual->siguiente;
			}

			while (actual != NULL && ban != true) {

				if (actual->estado == false && actual->tama�oProceso >= nodo->tama�oProceso) {
					actual->estado = true;
					ban = true;

					aux = actual->siguiente;
					temporal = nodo;
					aux2 = nodo->tama�oMemoria;

					temporal->tama�oMemoria = actual->tama�oMemoria - temporal->tama�oMemoria;
					actual->tama�oMemoria = aux2;

					actual->tama�oProceso = actual->tama�oProceso - nodo->tama�oProceso;
					temporal->tama�oProceso = nodo->tama�oProceso;

					temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;

					actual->siguiente = temporal;
					temporal->siguiente = aux;

					identificadorInicio = actual->id;

					aux = inicio;
					var = aux->id;
					while (aux->siguiente != NULL)
					{					
						if (var <= aux->siguiente->id)
						{
							var = aux->siguiente->id;
						}
						aux = aux->siguiente;
					}
					temporal->id = var;
					temporal->estado = false;

				}
				actual = actual->siguiente;

			}
			temporal = inicio;
			while (temporal->siguiente != NULL)
			{
				temporal = temporal->siguiente;
			}
			if (temporal->id == identificadorInicio)
			{
				identificadorInicio = 0;
			}
		}

		if (actual == NULL && !ban) {
			a�adirProceso(nodo);
		}
	}

}
void listaEnlazada::mejorAjuste(nodePtr node) {
	nodePtr nodo = node;
	nodePtr aux;
	int aux2 = 0;

	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		a�adirProceso(nodo);
	}
	else {

		while (actual->siguiente != NULL)
		{
			var = inicio->tama�oMemoria;
			if (var >= actual->tama�oMemoria && actual->estado == false && actual->tama�oMemoria >= nodo->tama�oMemoria)
			{
				var = actual->tama�oMemoria;
			}
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tama�oMemoria == var ) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tama�oMemoria;
				temporal = nodo;

				temporal->tama�oMemoria = actual->tama�oMemoria - temporal->tama�oMemoria;
				actual->tama�oMemoria = aux2;

				actual->tama�oProceso = actual->tama�oProceso - nodo->tama�oProceso;
				temporal->tama�oProceso = nodo->tama�oProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;

				actual->siguiente = temporal;
				temporal->siguiente = aux;

				aux = inicio;
				var = aux->id;
				while (aux->siguiente != NULL)
				{
					if (var <= aux->siguiente->id)
					{
						var = aux->siguiente->id;
					}
					aux = aux->siguiente;
				}
				temporal->id = var;
				temporal->estado = false;

			}

			actual = actual->siguiente;

		}
		if (actual == NULL && !ban) {
			a�adirProceso(nodo);
		}
	}
}
void listaEnlazada::peorAjuste(nodePtr node) {

	nodePtr nodo = node;
	nodePtr aux;
	int aux2 = 0;

	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		a�adirProceso(nodo);
	}
	else {

		while (actual->siguiente != NULL)
		{
			if (var <= actual->tama�oMemoria && actual->estado == false)
			{
				var = actual->tama�oMemoria;
			}
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tama�oMemoria == var) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tama�oMemoria;
				temporal = nodo;

				temporal->tama�oMemoria = actual->tama�oMemoria - temporal->tama�oMemoria;
				actual->tama�oMemoria = aux2;

				actual->tama�oProceso = actual->tama�oProceso - nodo->tama�oProceso;
				temporal->tama�oProceso = nodo->tama�oProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;

				actual->siguiente = temporal;
				temporal->siguiente = aux;

				aux = inicio;
				var = aux->id;
				while (aux->siguiente != NULL)
				{
					if (var <= aux->siguiente->id)
					{
						var = aux->siguiente->id;
					}
					aux = aux->siguiente;
				}
				temporal->id = var;
				temporal->estado = false;

			}

			actual = actual->siguiente;

		}
		if (actual == NULL && !ban) {
			a�adirProceso(nodo);
		}
	}
}