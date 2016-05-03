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
	cout << "Inserta el tama�o de memoria" << endl;
	cin >> tamMemoria;
	cout << "inserta el tama�o en unidad de administracion de memoria" << endl;
	cin >> uam;
	desperdicio = 0;
	primero->estado = false;
	primero->id = 0;
	primero->tama�oMemoria = tamMemoria;
	primero->tama�oProceso = tamMemoria / uam;
	lista.a�adirProceso(primero);

}

listaEnlazada listaEnlazada::llenarProceso() {
	nodePtr procesos = new node();
	int desperdicio;
	int tama�oProceso; //uam
	int tama�oMemoria;
	cout << "inserta el tama�o de proceso" << endl;
	cin >> tama�oMemoria;
	procesos->estado = true;
	procesos->id = id++;
	procesos->tama�oMemoria = tama�oMemoria;
	procesos->tama�oProceso = tama�oMemoria / uam;
	procesos->inicioProceso = 0;
	lista.a�adirProceso(procesos);
	
	return lista;

}

