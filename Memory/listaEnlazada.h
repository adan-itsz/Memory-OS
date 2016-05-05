#pragma once
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class listaEnlazada
{
private:

	typedef struct node {
		int inicioProceso = 0;//inicio del proceso
		int tamaņoMemoria;
		int tamaņoProceso = 0;//tamaņo en unidades de memoria
		int id;
		bool estado; // 0 = hueco, 1 = proceso
		node* siguiente;
	}*nodePtr;

	nodePtr inicio; //inicio
	nodePtr actual; //actual
	nodePtr temporal; //temporal
	nodePtr auxMemoria;//se usa para hacer referencia a memoria total
	nodePtr memoriaTotal;
public:
	listaEnlazada();
	void aņadirProceso(nodePtr nodo);
	void eliminarNodo(int borrarDato);
	void mostrarLista();
	void llenarPrimerNodo();
	void llenarProceso();
	void posicionarUltimo();
	
};

#endif //!LISTAENLAZADA_H