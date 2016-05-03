// Memory.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "listaEnlazada.h"
#include<iostream>
#include<cstdlib>
using namespace std;
listaEnlazada lista;
int id=0;
int uam; //unidad de administracion de memoria

int main()
{
	int opcion = 0;
	lista.llenarPrimerNodo();
	cout << "Selecciona la opcion correcta" << endl;
	cout << "1-  agregar un proceso" << endl;
	cout << "2-  eliminar proceso" << endl;
	cout << "3-  Listar procesos" << endl;
	cin >> opcion;
	switch (opcion) {
	case 1:
		lista.llenarProceso();
		lista.mostrarLista();
		break;

	
	
	}

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
	lista.añadirProceso(primero);

}

listaEnlazada listaEnlazada::llenarProceso() {
	nodePtr procesos = new node();
	int desperdicio;
	int tamañoProceso; //uam
	int tamañoMemoria;
	cout << "inserta el tamaño de proceso" << endl;
	cin >> tamañoMemoria;
	procesos->estado = true;
	procesos->id = id++;
	procesos->tamañoMemoria = tamañoMemoria;
	procesos->tamañoProceso = tamañoMemoria / uam;
	procesos->inicioProceso = 0;
	lista.añadirProceso(procesos);
	
	return lista;

}

