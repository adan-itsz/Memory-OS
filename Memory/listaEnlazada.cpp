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
		n->desperdicio = nodo->desperdicio;
		
	
	if (inicio != NULL) {
		actual = inicio;
		while (actual->siguiente != NULL)
		{			
			actual = actual->siguiente;
		}

		
		actual->siguiente = n;
		

		auxMemoria->tama�oMemoria -= n->tama�oMemoria;
		auxMemoria->tama�oProceso -= n->tama�oProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tama�oProceso+1;
		//auxMemoria = memoriaTotal;
		if (actual->tama�oMemoria == memoriaTotal->tama�oMemoria) {//si es el primer proceso y comienza en 0
			n->inicioProceso = 0;
		}
		else {
			n->inicioProceso = actual->inicioProceso + actual->tama�oProceso + 1;
				//auxMemoria->tama�oProceso ;
		}
	}
	else {
		
		auxMemoria->tama�oMemoria -= n->tama�oMemoria;
		auxMemoria->tama�oProceso -= n->tama�oProceso;
		auxMemoria->inicioProceso += n->inicioProceso + n->tama�oProceso + 1;
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

				delPtr->tama�oMemoria += inicio->tama�oMemoria;
				delPtr->tama�oProceso += inicio->tama�oProceso;
				delPtr->desperdicio = (delPtr->tama�oProceso * uam) - delPtr->tama�oMemoria;
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
				//inicio->tama�oMemoria = 0;
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
					auxMemoria->tama�oMemoria =0;
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
			
				temporal->tama�oMemoria += delPtr->tama�oMemoria;
				temporal->tama�oMemoria += actual->tama�oMemoria;
				temporal->tama�oProceso += delPtr->tama�oProceso;
				temporal->tama�oProceso += actual->tama�oProceso;
				temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;
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
			temporal->tama�oMemoria += delPtr->tama�oMemoria;
			temporal->tama�oProceso = temporal->tama�oMemoria / uam;
			if (temporal->tama�oMemoria % uam != 0) {
				temporal->tama�oProceso += 1;
			}
			//temporal->tama�oProceso += delPtr ->tama�oProceso;
			temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;
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
			actual->tama�oMemoria += delPtr->tama�oMemoria;
			actual->tama�oProceso = actual->tama�oMemoria / uam;
			if (actual->tama�oMemoria % uam != 0) {
				actual->tama�oProceso += 1;
			}
			actual->desperdicio = (actual->tama�oProceso * uam) - actual->tama�oMemoria;
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

	cout << "H/P \t |Inicio Proceso	\t|Tama�o de Proceso\t|Tama�o UAM\t|Desperdicio\t|ID|" << endl;
		while (actual != NULL )
		{
			cout << actual->estado << "\t |" << actual->inicioProceso << "\t\t\t\t |" << actual->tama�oMemoria << "\t\t\t |" << actual->tama�oProceso << "\t\t|"<<actual->desperdicio <<"\t\t|" << actual->id << "|" << endl;
			actual = actual->siguiente;		
		}

	cout << 0 << "\t |" << auxMemoria->inicioProceso << "\t\t\t\t |" <<0 << "\t\t\t |" << auxMemoria->tama�oProceso << "\t\t|" << 0 << "|" << endl;
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

		if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
			a�adirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		while (actual != NULL && ban!=true) {
			
			if (actual->estado == false && actual->tama�oProceso > nodo->tama�oProceso) {
				ban = true;
				aux = actual->siguiente;
				temporal = nodo;
				aux2 = actual;
				aux3 = nodo->tama�oMemoria;
				aux4 = nodo->tama�oProceso;
				
				//temporal->tama�oProceso = aux2->tama�oProceso - temporal->tama�oProceso;
				temporal->tama�oMemoria = aux2->tama�oMemoria - temporal->tama�oMemoria;

				actual->tama�oMemoria = aux3;
				actual->tama�oProceso = aux4;

				temporal->tama�oProceso = temporal->tama�oMemoria / uam;
				if (temporal->tama�oMemoria % uam != 0) {
					temporal->tama�oProceso += 1;
					sum += 1;
				}

				if (actual->tama�oMemoria % uam != 0) {
					sum += 1;
				}	
				
				actual->estado = true;
				actual->desperdicio = (aux4 * uam) - aux3;
				temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;

				
				temporal->estado = false;

				temporal->inicioProceso = aux2->inicioProceso + aux2->tama�oProceso + 1;


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
			else if (actual->estado == false && actual->tama�oProceso == nodo->tama�oProceso){
				listaEnlazada lista;
				int uam = lista.obtenerUAM();
				actual->estado = true;
				actual->tama�oMemoria = nodo->tama�oMemoria;
				actual->desperdicio= (nodo->tama�oProceso * uam) - nodo->tama�oMemoria ;
				ban = true;
			}
			
			actual = actual->siguiente;
			
		}
		
		if (actual == NULL && !ban) {
			if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
				a�adirProceso(nodo);
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
		if (nodo->tama�oMemoria <= auxMemoria->tama�oMemoria) {
			a�adirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}

	else {
		if(identificadorInicio == 0){
			while (actual != NULL && ban != true) {

				if (actual->estado == false && actual->tama�oMemoria > nodo->tama�oMemoria) {
					
					ban = true;
					aux = actual->siguiente;
					temporal = nodo;
					aux2 = actual;
					aux3 = nodo->tama�oMemoria;
					aux4 = nodo->tama�oProceso;

					
					temporal->tama�oMemoria = aux2->tama�oMemoria - temporal->tama�oMemoria;
					//temporal->tama�oProceso = aux2->tama�oProceso - temporal->tama�oProceso;

					actual->tama�oMemoria = aux3;
					actual->tama�oProceso = aux4;

					temporal->tama�oProceso = temporal->tama�oMemoria / uam;
					if (temporal->tama�oMemoria % uam != 0) {
					temporal->tama�oProceso += 1;
					sum += 1;
					}

					if (actual->tama�oMemoria % uam != 0) {
						sum += 1;
					}
					
					actual->estado = true;
					actual->desperdicio = (aux4 * uam) - aux3;
					temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;


					temporal->estado = false;

					temporal->inicioProceso = aux2->inicioProceso + aux2->tama�oProceso + 1;


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
				else if (actual->estado == false && actual->tama�oProceso == nodo->tama�oProceso) {
					listaEnlazada lista;
					int uam = lista.obtenerUAM();
					actual->estado = true;
					actual->tama�oMemoria = nodo->tama�oMemoria;
					actual->desperdicio = (nodo->tama�oProceso * uam) - nodo->tama�oMemoria;
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
				if (temporal->id == identificadorInicio && auxMemoria->tama�oProceso >= nodo->tama�oProceso)
				{
					identificadorInicio = temporal->id;
					a�adirProceso(nodo);
				}
				else
				{
					identificadorInicio = 1;
					if (actual->estado == false && actual->tama�oProceso > nodo->tama�oProceso) {
						ban = true;
						aux = actual->siguiente;
						temporal = nodo;
						aux2 = actual;
						aux3 = nodo->tama�oMemoria;
						aux4 = nodo->tama�oProceso;

						//temporal->tama�oProceso = aux2->tama�oProceso - temporal->tama�oProceso;
						temporal->tama�oMemoria = aux2->tama�oMemoria - temporal->tama�oMemoria;

						actual->tama�oMemoria = aux3;
						actual->tama�oProceso = aux4;

						temporal->tama�oProceso = temporal->tama�oMemoria / uam;
						if (temporal->tama�oMemoria % uam != 0) {
							temporal->tama�oProceso += 1;
							sum += 1;
						}

						if (actual->tama�oMemoria % uam != 0) {
							sum += 1;
						}

						listaEnlazada lista;
						int uam = lista.obtenerUAM();

						actual->estado = true;
						actual->desperdicio = (aux4 * uam) - aux3;
						temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;


						temporal->estado = false;

						temporal->inicioProceso = aux2->inicioProceso + aux2->tama�oProceso + 1;


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
					else if (actual->estado == false && actual->tama�oProceso == nodo->tama�oProceso) {
						listaEnlazada lista;
						int uam = lista.obtenerUAM();
						actual->estado = true;
						actual->tama�oMemoria = nodo->tama�oMemoria;
						actual->desperdicio = (nodo->tama�oProceso * uam) - nodo->tama�oMemoria;
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
					if (auxMemoria->tama�oProceso >= nodo->tama�oProceso)
					{
						identificadorInicio = 1;
					}
					else
					{
						identificadorInicio = 0;
					}		
						if (actual->estado == false && actual->tama�oMemoria > nodo->tama�oMemoria) {

							ban = true;
							aux = actual->siguiente;
							temporal = nodo;
							aux2 = actual;
							aux3 = nodo->tama�oMemoria;
							aux4 = nodo->tama�oProceso;


							temporal->tama�oMemoria = aux2->tama�oMemoria - temporal->tama�oMemoria;
							//temporal->tama�oProceso = aux2->tama�oProceso - temporal->tama�oProceso;

							actual->tama�oMemoria = aux3;
							actual->tama�oProceso = aux4;

							temporal->tama�oProceso = temporal->tama�oMemoria / uam;
							if (temporal->tama�oMemoria % uam != 0) {
								temporal->tama�oProceso += 1;
								sum += 1;
							}

							if (actual->tama�oMemoria % uam != 0) {
								sum += 1;
							}

							actual->estado = true;
							actual->desperdicio = (aux4 * uam) - aux3;
							temporal->desperdicio = (temporal->tama�oProceso * uam) - temporal->tama�oMemoria;


							temporal->estado = false;

							temporal->inicioProceso = aux2->inicioProceso + aux2->tama�oProceso + 1;


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
						else if (actual->estado == false && actual->tama�oProceso == nodo->tama�oProceso) {
							listaEnlazada lista;
							int uam = lista.obtenerUAM();
							actual->estado = true;
							actual->tama�oMemoria = nodo->tama�oMemoria;
							actual->desperdicio = (nodo->tama�oProceso * uam) - nodo->tama�oMemoria;
							//identificadorInicio = actual->siguiente->id;
							ban = true;
							
						}
						actual = actual->siguiente;
				}		
			}*/
		if (actual == NULL && !ban) {
			if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
				a�adirProceso(nodo);
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
		if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
			a�adirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {
		
	//	var = inicio->tama�oMemoria;
		while (actual != NULL)
		{
			
			
			if (var >= actual->tama�oProceso && actual->estado == false && actual->tama�oProceso >= nodo->tama�oProceso)
			{
				var = actual->tama�oProceso;
			}
			
			else if (var < actual->tama�oProceso&& actual->estado == false && actual->tama�oProceso >= nodo->tama�oProceso) {

					var = actual->tama�oProceso;
				}
			
			actual = actual->siguiente;
		}

		actual = inicio;

		while (actual != NULL && ban != true) {

			if (actual->estado == false && actual->tama�oProceso == var ) {
				actual->estado = true;
				ban = true;

				aux = actual->siguiente;
				aux2 = nodo->tama�oProceso;
				temporal = nodo;

				temporal->tama�oProceso = actual->tama�oProceso - temporal->tama�oProceso;
				actual->tama�oProceso = aux2;

				actual->tama�oMemoria =  nodo->tama�oMemoria;
				temporal->tama�oProceso = actual->tama�oProceso-temporal->tama�oProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tama�oProceso;
				
				if (temporal->tama�oProceso == 0) {
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
			if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
				a�adirProceso(nodo);
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
		if (nodo->tama�oMemoria <= auxMemoria->tama�oMemoria) {
			a�adirProceso(nodo);
		}

		else {
			cout << "No hay memoria suficiente" << endl;
		}
	}
	else {

	//	var = inicio->tama�oMemoria;
		while (actual != NULL)
		{


			if (var <= actual->tama�oMemoria && actual->estado == false && actual->tama�oMemoria >= nodo->tama�oMemoria)
			{
				var = actual->tama�oMemoria;
			}
			else if (var < actual->tama�oMemoria&& actual->estado == false && actual->tama�oMemoria >= nodo->tama�oMemoria) {

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

				actual->tama�oProceso = nodo->tama�oProceso;
				temporal->tama�oProceso = actual->tama�oProceso - temporal->tama�oProceso;
				temporal->inicioProceso = actual->inicioProceso + actual->tama�oMemoria;
				if (temporal->tama�oMemoria == 0) {
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
			if (nodo->tama�oProceso <= auxMemoria->tama�oProceso) {
				a�adirProceso(nodo);
			}

			else {
				cout << "No hay memoria suficiente" << endl;
			}
		}
	}

}