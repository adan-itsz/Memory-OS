#pragma once
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class listaEnlazada
{
private:

	typedef struct node {
		int inicioProceso = 0;//inicio del proceso
		int tamañoMemoria;
		int tamañoProceso = 0;//tamaño en unidades de memoria
		int id;
		bool estado; // 0 = hueco, 1 = proceso
		node* siguiente;
	}*nodePtr;

	nodePtr inicio; //inicio
	nodePtr actual; //actual
	nodePtr temporal; //temporal

public:
	listaEnlazada();
	void añadirProceso(nodePtr nodo);
	void eliminarNodo(int borrarDato);
	void mostrarLista();
	void llenarPrimerNodo();
	listaEnlazada llenarProceso();

};

#endif //!LISTAENLAZADA_H