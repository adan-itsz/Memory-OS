// Memory.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "listaEnlazada.h"
#include<iostream>
#include<cstdlib>
using namespace std;
listaEnlazada lista;
int id=1;
int uam; //unidad de administracion de memoria

int main()
{
	int opcion = 0;
	int opcion2 = 0;
	lista.llenarPrimerNodo();
	do {
		cout << "Selecciona la opcion correcta" << endl;
		cout << "1-  agregar un proceso" << endl;
		cout << "2-  eliminar proceso" << endl;
		cout << "3-  Listar procesos" << endl;
		cin >> opcion;
		switch (opcion) {
		case 1:
				cout << "Selecciona el algoritmo " << endl;
				cout << "1-  Primer ajuste" << endl;
				cout << "2-  Siguiente ajuste" << endl;
				cout << "3-  Peor ajuste" << endl;
				cout << "4-  mejor ajuste" << endl;
				cin >> opcion2;
				switch (opcion2) {

				case 1: lista.llenarProceso();
					break;
				}
			
			break;
		case 2:
			int idEliminar;
			cout << "Introduce el ID del proceso a eliminar" << endl;
			cin >> idEliminar;
			lista.eliminarNodo(idEliminar);

		case 3:
			lista.mostrarLista();
			break;




		}

		if (lista.vacia() == true) {
			id = 1;
		}

	} while (opcion != -1);

	system("pause");
    return 0;
}

void listaEnlazada::llenarPrimerNodo() {
	nodePtr primero = new node;
	int tamMemoria = 0;
	
	int desperdicio;
	cout << "Inserta el tamaño de memoria" << endl;
	cin >> tamMemoria;
	cout << "inserta el tamaño en unidad de administracion de memoria" << endl;
	cin >> uam;
	desperdicio = 0;
	primero->estado = false;
	primero->id = 0;
	primero->tamañoMemoria = tamMemoria;
	primero->tamañoProceso = tamMemoria / uam;
	primero->inicioProceso = 0;
	lista.añadirProceso(primero);

}

void listaEnlazada::llenarProceso() {
	nodePtr procesos = new node();
	int desperdicio;
	int tamañoProceso; //uam
	int tamañoMemoria;
	cout << "inserta el tamaño de proceso en memoria" << endl;
	cin >> tamañoMemoria;
	procesos->estado = true;
	procesos->id = id++;
	procesos->tamañoMemoria = tamañoMemoria;
	procesos->tamañoProceso = tamañoMemoria / uam;
	procesos->inicioProceso;
	lista.primerAjuste(procesos);
	

}

