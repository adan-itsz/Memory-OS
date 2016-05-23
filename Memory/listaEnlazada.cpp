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
		n->desperdicio = nodo->desperdicio;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tamaņoMemoria -= n->tamaņoMemoria;
		auxMemoria->tamaņoProceso -= n->tamaņoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamaņoProceso+1;
		//auxMemoria = memoriaTotal;
		if (actual->tamaņoMemoria == memoriaTotal->tamaņoMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tamaņoProceso + 1;
				//auxMemoria->tamaņoProceso ;
		}
	}
	else {
		
		auxMemoria->tamaņoMemoria -= n->tamaņoMemoria;
		auxMemoria->tamaņoProceso -= n->tamaņoProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tamaņoProceso + 1;
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

				delPtr->tamaņoMemoria += inicio->tamaņoMemoria;
				delPtr->tamaņoProceso += inicio->tamaņoProceso;
				delPtr->desperdicio = (delPtr->tamaņoProceso * uam) - delPtr->tamaņoMemoria;
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
				//inicio->tamaņoMemoria = 0;
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
					auxMemoria->tamaņoMemoria =0;
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
			
				temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
				temporal->tamaņoMemoria += actual->tamaņoMemoria;
				temporal->tamaņoProceso += delPtr->tamaņoProceso;
				temporal->tamaņoProceso += actual->tamaņoProceso;
				temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;
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
			temporal->tamaņoMemoria += delPtr->tamaņoMemoria;
			temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
			if (temporal->tamaņoMemoria % uam != 0) {
				temporal->tamaņoProceso += 1;
			}
			//temporal->tamaņoProceso += delPtr ->tamaņoProceso;
			temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;
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
			actual->tamaņoMemoria += delPtr->tamaņoMemoria;
			actual->tamaņoProceso = actual->tamaņoMemoria / uam;
			if (actual->tamaņoMemoria % uam != 0) {
				actual->tamaņoProceso += 1;
			}
			actual->desperdicio = (actual->tamaņoProceso * uam) - actual->tamaņoMemoria;
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

	cout << "H/P \t |Inicio Proceso	\t|Tamaņo de Proceso\t|Tamaņo UAM\t|Desperdicio\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tamaņoMemoria << "\t\t\t |" << actual->tamaņoProceso << "\t\t|"<<actual->desperdicio <<"\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" <<0 << "\t\t\t |" << auxMemoria->tamaņoProceso << "\t\t|" << 0 << "|" << endl;
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
	int sum  = 1;
	listaEnlazada lista;
	int uam = lista.obtenerUAM();
	
 	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {

		if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
			aņadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		while (actual != NULL && ban!=true) {
			
			if (actual->estado == false && actual->tamaņoProceso > nodo->tamaņoProceso) {
				ban = true;
				aux = actual->siguiente;
				temporal = nodo;
				aux2 = actual;
				aux3 = nodo->tamaņoMemoria;
				aux4 = nodo->tamaņoProceso;
				
				//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;
				temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;

				actual->tamaņoMemoria = aux3;
				actual->tamaņoProceso = aux4;

				temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
				if (temporal->tamaņoMemoria % uam != 0) {
					temporal->tamaņoProceso += 1;
					sum += 1;
				}

				if (actual->tamaņoMemoria % uam != 0) {
					sum += 1;
				}	
				
				actual->estado = true;
				actual->desperdicio = (aux4 * uam) - aux3;
				temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;

				
				temporal->estado = false;

				temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
			else if (actual->estado == false && actual->tamaņoProceso == nodo->tamaņoProceso){
				listaEnlazada lista;
				int uam = lista.obtenerUAM();
				actual->estado = true;
				actual->tamaņoMemoria = nodo->tamaņoMemoria;
				actual->desperdicio= (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria ;
				ban = true;
			}
			
			actual = actual->siguiente;
			
		}
		
		if (actual == NULL && !ban) {
			if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
				aņadirProceso(nodo);
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
		if (nodo->tamaņoMemoria <= auxMemoria->tamaņoMemoria) {
			aņadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		if(identificadorInicio == 0){
			while (actual != NULL && ban != true) {

				if (actual->estado == false && actual->tamaņoMemoria > nodo->tamaņoMemoria) {
					
					ban = true;
					aux = actual->siguiente;
					temporal = nodo;
					aux2 = actual;
					aux3 = nodo->tamaņoMemoria;
					aux4 = nodo->tamaņoProceso;

					
					temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;
					//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;

					actual->tamaņoMemoria = aux3;
					actual->tamaņoProceso = aux4;

					temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
					if (temporal->tamaņoMemoria % uam != 0) {
					temporal->tamaņoProceso += 1;
					sum += 1;
					}

					if (actual->tamaņoMemoria % uam != 0) {
						sum += 1;
					}
					
					actual->estado = true;
					actual->desperdicio = (aux4 * uam) - aux3;
					temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;


					temporal->estado = false;

					temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
				else if (actual->estado == false && actual->tamaņoProceso == nodo->tamaņoProceso) {
					listaEnlazada lista;
					int uam = lista.obtenerUAM();
					actual->estado = true;
					actual->tamaņoMemoria = nodo->tamaņoMemoria;
					actual->desperdicio = (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria;
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
				if (temporal->id == identificadorInicio && auxMemoria->tamaņoProceso >= nodo->tamaņoProceso)
				{
					identificadorInicio = temporal->id;
					aņadirProceso(nodo);
				}
				else
				{
					identificadorInicio = 1;
					if (actual->estado == false && actual->tamaņoProceso > nodo->tamaņoProceso) {
						ban = true;
						aux = actual->siguiente;
						temporal = nodo;
						aux2 = actual;
						aux3 = nodo->tamaņoMemoria;
						aux4 = nodo->tamaņoProceso;

						//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;
						temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;

						actual->tamaņoMemoria = aux3;
						actual->tamaņoProceso = aux4;

						temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
						if (temporal->tamaņoMemoria % uam != 0) {
							temporal->tamaņoProceso += 1;
							sum += 1;
						}

						if (actual->tamaņoMemoria % uam != 0) {
							sum += 1;
						}

						listaEnlazada lista;
						int uam = lista.obtenerUAM();

						actual->estado = true;
						actual->desperdicio = (aux4 * uam) - aux3;
						temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;


						temporal->estado = false;

						temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
					else if (actual->estado == false && actual->tamaņoProceso == nodo->tamaņoProceso) {
						listaEnlazada lista;
						int uam = lista.obtenerUAM();
						actual->estado = true;
						actual->tamaņoMemoria = nodo->tamaņoMemoria;
						actual->desperdicio = (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria;
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
					if (auxMemoria->tamaņoProceso >= nodo->tamaņoProceso)
					{
						identificadorInicio = 1;
					}
					else
					{
						identificadorInicio = 0;
					}		
						if (actual->estado == false && actual->tamaņoMemoria > nodo->tamaņoMemoria) {

							ban = true;
							aux = actual->siguiente;
							temporal = nodo;
							aux2 = actual;
							aux3 = nodo->tamaņoMemoria;
							aux4 = nodo->tamaņoProceso;


							temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;
							//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;

							actual->tamaņoMemoria = aux3;
							actual->tamaņoProceso = aux4;

							temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
							if (temporal->tamaņoMemoria % uam != 0) {
								temporal->tamaņoProceso += 1;
								sum += 1;
							}

							if (actual->tamaņoMemoria % uam != 0) {
								sum += 1;
							}

							actual->estado = true;
							actual->desperdicio = (aux4 * uam) - aux3;
							temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;


							temporal->estado = false;

							temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
						else if (actual->estado == false && actual->tamaņoProceso == nodo->tamaņoProceso) {
							listaEnlazada lista;
							int uam = lista.obtenerUAM();
							actual->estado = true;
							actual->tamaņoMemoria = nodo->tamaņoMemoria;
							actual->desperdicio = (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria;
							//identificadorInicio = actual->siguiente->id;
							ban = true;
							
						}
						actual = actual->siguiente;
				}		
			}*/
		if (actual == NULL && !ban) {
			if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
				aņadirProceso(nodo);
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
	nodePtr aux2 = 0;
	int aux3, aux4;
	int sum = 0;
	listaEnlazada lista;
	int uam = lista.obtenerUAM();
	var = 0;
	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
			aņadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {
		
	//	var = inicio->tamaņoMemoria;
	    //var = inicio->tamaņoProceso;
		while (actual != NULL)// encontrar el menor
		{
			if (var >= actual->tamaņoProceso && actual->estado == false && actual->tamaņoProceso >= nodo->tamaņoProceso)
			{
				var = actual->tamaņoProceso;
			}
			
			else if (var <= actual->tamaņoProceso&& actual->estado == false && actual->tamaņoProceso >= nodo->tamaņoProceso) {

					var = actual->tamaņoProceso;
				}
			
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tamaņoProceso == var && actual->tamaņoProceso == nodo->tamaņoProceso) {

				actual->estado = true;
				actual->tamaņoMemoria = nodo->tamaņoMemoria;
				actual->desperdicio = (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria;
				identificadorInicio = temporal->id;
				ban = true;
			}

			else if (actual->estado == false && actual->tamaņoProceso == var) {

				ban = true;
				aux = actual->siguiente;
				temporal = nodo;
				aux2 = actual;
				aux3 = nodo->tamaņoMemoria;
				aux4 = nodo->tamaņoProceso;


				temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;
				//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;

				actual->tamaņoMemoria = aux3;
				actual->tamaņoProceso = aux4;

				temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
				if (temporal->tamaņoMemoria % uam != 0) {
					temporal->tamaņoProceso += 1;
					sum += 1;
				}

				if (actual->tamaņoMemoria % uam != 0) {
					sum += 1;
				}

				actual->estado = true;
				actual->desperdicio = (aux4 * uam) - aux3;
				temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;


				temporal->estado = false;

				temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
			actual = actual->siguiente;


		}
		if (actual == NULL && !ban) {
			if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
				aņadirProceso(nodo);
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
	nodePtr aux2;
	int aux3, aux4;
	int sum = 0;
	listaEnlazada lista;
	int uam = lista.obtenerUAM();
	var = 0;
	actual = inicio;
	temporal = inicio;
	bool ban = false;
	if (vacia()) {
		if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
			aņadirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {

	//	var = inicio->tamaņoMemoria;
		while (actual != NULL)
		{
			if (var <= actual->tamaņoProceso && actual->estado == false && actual->tamaņoProceso >= nodo->tamaņoProceso)
			{
				var = actual->tamaņoMemoria;
			}
			else if (var < actual->tamaņoProceso&& actual->estado == false && actual->tamaņoProceso >= nodo->tamaņoProceso) {

				var = actual->tamaņoMemoria;
			}
			actual = actual->siguiente;
		}

		if (var < auxMemoria->tamaņoProceso) {
			aņadirProceso(nodo);
		}
		else {

			actual = inicio;

			while (actual != NULL && ban != true) {
				if (actual->estado == false && actual->tamaņoProceso == var && actual->tamaņoProceso == nodo->tamaņoProceso) {
					actual->estado = true;
					actual->tamaņoMemoria = nodo->tamaņoMemoria;
					actual->desperdicio = (nodo->tamaņoProceso * uam) - nodo->tamaņoMemoria;
					identificadorInicio = temporal->id;
					ban = true;
				}
				else if (actual->estado == false && actual->tamaņoProceso == var) {

					ban = true;
					aux = actual->siguiente;
					temporal = nodo;
					aux2 = actual;
					aux3 = nodo->tamaņoMemoria;
					aux4 = nodo->tamaņoProceso;


					temporal->tamaņoMemoria = aux2->tamaņoMemoria - temporal->tamaņoMemoria;
					//temporal->tamaņoProceso = aux2->tamaņoProceso - temporal->tamaņoProceso;

					actual->tamaņoMemoria = aux3;
					actual->tamaņoProceso = aux4;

					temporal->tamaņoProceso = temporal->tamaņoMemoria / uam;
					if (temporal->tamaņoMemoria % uam != 0) {
						temporal->tamaņoProceso += 1;
						sum += 1;
					}

					if (actual->tamaņoMemoria % uam != 0) {
						sum += 1;
					}

					actual->estado = true;
					actual->desperdicio = (aux4 * uam) - aux3;
					temporal->desperdicio = (temporal->tamaņoProceso * uam) - temporal->tamaņoMemoria;


					temporal->estado = false;

					temporal->inicioProceso = aux2->inicioProceso + aux2->tamaņoProceso + 1;


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
				 
				actual = actual->siguiente;

			}
		}
		if (actual == NULL && !ban) {
			if (nodo->tamaņoProceso <= auxMemoria->tamaņoProceso) {
				aņadirProceso(nodo);
			}

			else {
				cout << "No hay memoria suficiente" << endl;
			}
		}
	}

}