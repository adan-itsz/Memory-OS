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
		n->desperdicio = nodo->desperdicio;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tamañoMemoria -= n->tamañoMemoria;
		auxMemoria->tamañoProceso -= n->tamañoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamañoProceso+1;
		//auxMemoria = memoriaTotal;
		if (actual->tamañoMemoria == memoriaTotal->tamañoMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tamañoProceso + 1;
				//auxMemoria->tamañoProceso ;
		}
	}
	else {
		
		auxMemoria->tamañoMemoria -= n->tamañoMemoria;
		auxMemoria->tamañoProceso -= n->tamañoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamañoProceso + 1;
		inicio = n;
	}
}
}

void listaEnlazada::eliminarNodo(int Id) {
	//delPtr = actual, actual = siguiente, temporal = anterior
	nodePtr delPtr = NULL;
	temporal = inicio;
	listaEnlazada lista;
	actual = inicio;
	int bandera = 0;
	int uam = lista.obtenerUAM();
	
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

				delPtr->tamañoMemoria += inicio->tamañoMemoria;
				delPtr->tamañoProceso += inicio->tamañoProceso;
				delPtr->desperdicio = (delPtr->tamañoProceso * uam) - delPtr->tamañoMemoria;
				delPtr->inicioProceso = 0;
				delPtr = inicio;
				inicio = inicio->siguiente;
				delete delPtr;
				delPtr = NULL;
				actual = inicio;
				actual = actual->siguiente;
				while (actual != NULL)
				{
					actual->inicioProceso -= 1;
					actual = actual->siguiente;
				}
				auxMemoria->inicioProceso -= 1;
				bandera = 1;
				
			}
			
			else if (inicio->siguiente->estado == true) {
				inicio->estado = false;
				//inicio->tamañoMemoria = 0;
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
					temporal->tamañoMemoria += delPtr->tamañoMemoria;
					temporal->tamañoProceso += delPtr->tamañoProceso;
					delete delPtr;
					delPtr = NULL;
					delPtr = temporal;
					auxMemoria->tamañoMemoria =0;
					auxMemoria->tamañoProceso += temporal->tamañoProceso;
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
					auxMemoria->tamañoMemoria += delPtr->tamañoMemoria;
					auxMemoria->tamañoProceso += delPtr->tamañoProceso;
					auxMemoria->inicioProceso = delPtr->inicioProceso+1;
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
			
				temporal->tamañoMemoria += delPtr->tamañoMemoria;
				temporal->tamañoMemoria += actual->tamañoMemoria;
				temporal->tamañoProceso += delPtr->tamañoProceso;
				temporal->tamañoProceso += actual->tamañoProceso;
				temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;
				delete delPtr;
				delPtr = NULL;
				actual = actual->siguiente;
				temporal->siguiente = actual; //junta nodos;
				while (actual != NULL)
				{
					actual->inicioProceso -= 2;
					actual = actual->siguiente;
				}
				auxMemoria->inicioProceso -= 2;
				

		}	
		 else if(temporal-> estado == false && actual->estado == true){
			temporal->tamañoMemoria += delPtr->tamañoMemoria;
			temporal->tamañoProceso = temporal->tamañoMemoria / uam;
			if (temporal->tamañoMemoria % uam != 0) {
				temporal->tamañoProceso += 1;
			}
			//temporal->tamañoProceso += delPtr ->tamañoProceso;
			temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;
			delete delPtr;
			delPtr = NULL;
			temporal->siguiente = actual;
			while (actual != NULL)
			{
				actual->inicioProceso -= 2;
				actual = actual->siguiente;
			}
			auxMemoria->inicioProceso -= 2;
			
			
		}

		else if (actual->estado == false && temporal-> estado == true ) {
			actual->inicioProceso = delPtr->inicioProceso;
			actual->tamañoMemoria += delPtr->tamañoMemoria;
			actual->tamañoProceso = actual->tamañoMemoria / uam;
			if (actual->tamañoMemoria % uam != 0) {
				actual->tamañoProceso += 1;
			}
			actual->desperdicio = (actual->tamañoProceso * uam) - actual->tamañoMemoria;
			delete delPtr;
			delPtr = NULL;
			temporal->siguiente = actual;
			actual = actual->siguiente;
			while (actual != NULL)
			{
				actual->inicioProceso -= 1;
				actual = actual->siguiente;
			}
			auxMemoria->inicioProceso -= 1;
			
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

	cout << "H/P \t |Inicio Proceso	\t|Tamaño de Proceso\t|Tamaño UAM\t|Desperdicio\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tamañoMemoria << "\t\t\t |" << actual->tamañoProceso << "\t\t|"<<actual->desperdicio <<"\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" <<0 << "\t\t\t |" << auxMemoria->tamañoProceso << "\t\t|" << 0 << "|" << endl;
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
	nodePtr aux2;
	int aux3;
	int aux4;
	int sum;
	listaEnlazada lista;
	int uam = lista.obtenerUAM();
	
 	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {

		if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
			añadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		while (actual != NULL && ban!=true) {
			
			if (actual->estado == false && actual->tamañoProceso > nodo->tamañoProceso) {
				ban = true;
				aux = actual->siguiente;
				temporal = nodo;
				aux2 = actual;
				aux3 = nodo->tamañoMemoria;
				aux4 = nodo->tamañoProceso;
				
				//temporal->tamañoProceso = aux2->tamañoProceso - temporal->tamañoProceso;
				temporal->tamañoMemoria = aux2->tamañoMemoria - temporal->tamañoMemoria;

				actual->tamañoMemoria = aux3;
				actual->tamañoProceso = aux4;

				temporal->tamañoProceso = temporal->tamañoMemoria / uam;
				if (temporal->tamañoMemoria % uam != 0) {
					temporal->tamañoProceso += 1;
					sum += 1;
				}

				if (actual->tamañoMemoria % uam != 0) {
					sum += 1;
				}	
				
				actual->estado = true;
				actual->desperdicio = (aux4 * uam) - aux3;
				temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;

				
				temporal->estado = false;

				temporal->inicioProceso = aux2->inicioProceso + aux2->tamañoProceso + 1;


				actual->siguiente = temporal;
				temporal->siguiente = aux;
				
				while (aux != NULL)
				{
					aux->inicioProceso += sum;
					aux = aux->siguiente;
				}
				auxMemoria->inicioProceso += sum;


				aux2 = inicio;
				var = aux2->id;
				while (aux2->siguiente!=NULL)
				{
					if(var <= aux2->siguiente->id)
					{
						var = aux2->siguiente->id;
					}
					aux2 = aux2->siguiente;
				}
				temporal->id = var;
				temporal->estado = false;
			}
			else if (actual->estado == false && actual->tamañoProceso == nodo->tamañoProceso){
				listaEnlazada lista;
				int uam = lista.obtenerUAM();
				actual->estado = true;
				actual->tamañoMemoria = nodo->tamañoMemoria;
				actual->desperdicio= (nodo->tamañoProceso * uam) - nodo->tamañoMemoria ;
				ban = true;
			}
			
			actual = actual->siguiente;
			
		}
		
		if (actual == NULL && !ban) {
			if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
				añadirProceso(nodo);
			}
			
			else {
				cout << "No hay memoria suficiente" << endl;
			}
			
		}
	}


}
int identificadorInicio = 0;
void listaEnlazada::siguienteAjuste(nodePtr node)
{
	nodePtr nodo = node;
	nodePtr aux;
	nodePtr aux2;
	int aux3;
	int aux4;
	int sum = 0;
	listaEnlazada lista;
	int uam = lista.obtenerUAM();
	int bande = 0;
	
	actual = inicio;
	temporal = inicio;
	
	bool ban = false;
	if (vacia()) {
		if (nodo->tamañoMemoria <= auxMemoria->tamañoMemoria) {
			añadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		if(identificadorInicio == 0){
			while (actual != NULL && ban != true) {

				if (actual->estado == false && actual->tamañoMemoria > nodo->tamañoMemoria) {
					
					ban = true;
					aux = actual->siguiente;
					temporal = nodo;
					aux2 = actual;
					aux3 = nodo->tamañoMemoria;
					aux4 = nodo->tamañoProceso;

					
					temporal->tamañoMemoria = aux2->tamañoMemoria - temporal->tamañoMemoria;
					//temporal->tamañoProceso = aux2->tamañoProceso - temporal->tamañoProceso;

					actual->tamañoMemoria = aux3;
					actual->tamañoProceso = aux4;

					temporal->tamañoProceso = temporal->tamañoMemoria / uam;
					if (temporal->tamañoMemoria % uam != 0) {
					temporal->tamañoProceso += 1;
					sum += 1;
					}

					if (actual->tamañoMemoria % uam != 0) {
						sum += 1;
					}
					
					actual->estado = true;
					actual->desperdicio = (aux4 * uam) - aux3;
					temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;


					temporal->estado = false;

					temporal->inicioProceso = aux2->inicioProceso + aux2->tamañoProceso + 1;


					actual->siguiente = temporal;
					temporal->siguiente = aux;

					
					while (aux != NULL)
					{
						aux->inicioProceso += sum;
						aux = aux->siguiente;
					}
					auxMemoria->inicioProceso += sum;


					aux2 = inicio;
					var = aux2->id;
					while (aux2->siguiente != NULL)
					{
						if (var <= aux2->siguiente->id)
						{
							var = aux2->siguiente->id;
						}
						aux2 = aux2->siguiente;
					}
					temporal->id = var;
					temporal->estado = false;
					identificadorInicio = temporal->id;

				 }
				else if (actual->estado == false && actual->tamañoProceso == nodo->tamañoProceso) {
					listaEnlazada lista;
					int uam = lista.obtenerUAM();
					actual->estado = true;
					actual->tamañoMemoria = nodo->tamañoMemoria;
					actual->desperdicio = (nodo->tamañoProceso * uam) - nodo->tamañoMemoria;
					identificadorInicio = temporal->id;
					ban = true;
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

				while (temporal->siguiente != NULL)
				{
					temporal = temporal->siguiente;
				}
				if (temporal->id == identificadorInicio && auxMemoria->tamañoProceso >= nodo->tamañoProceso)
				{
					identificadorInicio = temporal->id;
					añadirProceso(nodo);
				}
				else
				{
					identificadorInicio = 1;
					if (actual->estado == false && actual->tamañoProceso > nodo->tamañoProceso) {
						ban = true;
						aux = actual->siguiente;
						temporal = nodo;
						aux2 = actual;
						aux3 = nodo->tamañoMemoria;
						aux4 = nodo->tamañoProceso;

						//temporal->tamañoProceso = aux2->tamañoProceso - temporal->tamañoProceso;
						temporal->tamañoMemoria = aux2->tamañoMemoria - temporal->tamañoMemoria;

						actual->tamañoMemoria = aux3;
						actual->tamañoProceso = aux4;

						temporal->tamañoProceso = temporal->tamañoMemoria / uam;
						if (temporal->tamañoMemoria % uam != 0) {
							temporal->tamañoProceso += 1;
							sum += 1;
						}

						if (actual->tamañoMemoria % uam != 0) {
							sum += 1;
						}

						listaEnlazada lista;
						int uam = lista.obtenerUAM();

						actual->estado = true;
						actual->desperdicio = (aux4 * uam) - aux3;
						temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;


						temporal->estado = false;

						temporal->inicioProceso = aux2->inicioProceso + aux2->tamañoProceso + 1;


						actual->siguiente = temporal;
						temporal->siguiente = aux;

						while (aux != NULL)
						{
							aux->inicioProceso += sum;
							aux = aux->siguiente;
						}
						auxMemoria->inicioProceso += sum;


						aux2 = inicio;
						var = aux2->id;
						while (aux2->siguiente != NULL)
						{
							if (var <= aux2->siguiente->id)
							{
								var = aux2->siguiente->id;
							}
							aux2 = aux2->siguiente;
						}
						temporal->id = var;
						temporal->estado = false;
						//
						identificadorInicio = temporal->id;
					}
					else if (actual->estado == false && actual->tamañoProceso == nodo->tamañoProceso) {
						listaEnlazada lista;
						int uam = lista.obtenerUAM();
						actual->estado = true;
						actual->tamañoMemoria = nodo->tamañoMemoria;
						actual->desperdicio = (nodo->tamañoProceso * uam) - nodo->tamañoMemoria;
						ban = true;
						//
						identificadorInicio = temporal->id;
					}
				}				
				actual = actual->siguiente;
			}
			temporal = inicio;	
		}
		/*else {
				actual = inicio;
				while (actual->siguiente != NULL)
				{
					if (auxMemoria->tamañoProceso >= nodo->tamañoProceso)
					{
						identificadorInicio = 1;
					}
					else
					{
						identificadorInicio = 0;
					}		
						if (actual->estado == false && actual->tamañoMemoria > nodo->tamañoMemoria) {

							ban = true;
							aux = actual->siguiente;
							temporal = nodo;
							aux2 = actual;
							aux3 = nodo->tamañoMemoria;
							aux4 = nodo->tamañoProceso;


							temporal->tamañoMemoria = aux2->tamañoMemoria - temporal->tamañoMemoria;
							//temporal->tamañoProceso = aux2->tamañoProceso - temporal->tamañoProceso;

							actual->tamañoMemoria = aux3;
							actual->tamañoProceso = aux4;

							temporal->tamañoProceso = temporal->tamañoMemoria / uam;
							if (temporal->tamañoMemoria % uam != 0) {
								temporal->tamañoProceso += 1;
								sum += 1;
							}

							if (actual->tamañoMemoria % uam != 0) {
								sum += 1;
							}

							actual->estado = true;
							actual->desperdicio = (aux4 * uam) - aux3;
							temporal->desperdicio = (temporal->tamañoProceso * uam) - temporal->tamañoMemoria;


							temporal->estado = false;

							temporal->inicioProceso = aux2->inicioProceso + aux2->tamañoProceso + 1;


							actual->siguiente = temporal;
							temporal->siguiente = aux;


							while (aux != NULL)
							{
								aux->inicioProceso += sum;
								aux = aux->siguiente;
							}
							auxMemoria->inicioProceso += sum;


							aux2 = inicio;
							var = aux2->id;
							while (aux2->siguiente != NULL)
							{
								if (var <= aux2->siguiente->id)
								{
									var = aux2->siguiente->id;
								}
								aux2 = aux2->siguiente;
							}
							temporal->id = var;
							temporal->estado = false;
							//identificadorInicio = temporal->id;		
					}
						else if (actual->estado == false && actual->tamañoProceso == nodo->tamañoProceso) {
							listaEnlazada lista;
							int uam = lista.obtenerUAM();
							actual->estado = true;
							actual->tamañoMemoria = nodo->tamañoMemoria;
							actual->desperdicio = (nodo->tamañoProceso * uam) - nodo->tamañoMemoria;
							//identificadorInicio = actual->siguiente->id;
							ban = true;
							
						}
						actual = actual->siguiente;
				}		
			}*/
		if (actual == NULL && !ban) {
			if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
				añadirProceso(nodo);
			}
			else
			{
				cout << "No hay memoria suficiente" << endl;
			}
		}

	}

}
void listaEnlazada::mejorAjuste(nodePtr node) {
	nodePtr nodo = node;
	nodePtr aux;
	nodePtr auxParaEliminar;
	int aux2 = 0;
	var = 0;
	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
			añadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {
		
	//	var = inicio->tamañoMemoria;
		while (actual != NULL)
		{
			
			
			if (var >= actual->tamañoProceso && actual->estado == false && actual->tamañoProceso >= nodo->tamañoProceso)
			{
				var = actual->tamañoProceso;
			}
			
			else if (var < actual->tamañoProceso&& actual->estado == false && actual->tamañoProceso >= nodo->tamañoProceso) {

					var = actual->tamañoProceso;
				}
			
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tamañoProceso == var ) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tamañoProceso;
				temporal = nodo;

				temporal->tamañoProceso = actual->tamañoProceso - temporal->tamañoProceso;
				actual->tamañoProceso = aux2;

				actual->tamañoMemoria =  nodo->tamañoMemoria;
				temporal->tamañoProceso = actual->tamañoProceso-temporal->tamañoProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tamañoProceso;
				
				if (temporal->tamañoProceso == 0) {
					delete temporal;
					//temporal = NULL;

				}
					
				else {

				actual->siguiente = temporal;
				temporal->siguiente = aux;
				}
				
				//
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
			if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
				añadirProceso(nodo);
			}

			else {
				cout << "No hay memoria suficiente" << endl;
			}
		}
	}
}
void listaEnlazada::peorAjuste(nodePtr node) {
	nodePtr nodo = node;
	nodePtr aux;
	int aux2 = 0;
	var = 0;
	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		if (nodo->tamañoMemoria <= auxMemoria->tamañoMemoria) {
			añadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {

	//	var = inicio->tamañoMemoria;
		while (actual != NULL)
		{


			if (var <= actual->tamañoMemoria && actual->estado == false && actual->tamañoMemoria >= nodo->tamañoMemoria)
			{
				var = actual->tamañoMemoria;
			}
			else if (var < actual->tamañoMemoria&& actual->estado == false && actual->tamañoMemoria >= nodo->tamañoMemoria) {

				var = actual->tamañoMemoria;
			}
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tamañoMemoria == var) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tamañoMemoria;
				temporal = nodo;

				temporal->tamañoMemoria = actual->tamañoMemoria - temporal->tamañoMemoria;
				actual->tamañoMemoria = aux2;

				actual->tamañoProceso = nodo->tamañoProceso;
				temporal->tamañoProceso = actual->tamañoProceso - temporal->tamañoProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tamañoMemoria;
				if (temporal->tamañoMemoria == 0) {
					delete temporal;

				}

				else {

					actual->siguiente = temporal;
					temporal->siguiente = aux;
				}

				//
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
			if (nodo->tamañoProceso <= auxMemoria->tamañoProceso) {
				añadirProceso(nodo);
			}

			else {
				cout << "No hay memoria suficiente" << endl;
			}
		}
	}

}