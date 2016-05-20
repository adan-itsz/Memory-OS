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
		int desperdicio;
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
	void añadirProceso(nodePtr nodo);
	void eliminarNodo(int borrarDato);
	void mostrarLista();
	void llenarPrimerNodo();
	void llenarProceso();
	bool vacia();
	void primerAjuste(nodePtr node);
	void siguienteAjuste(nodePtr node);
	void peorAjuste(nodePtr node);
	void mejorAjuste(nodePtr node);
	
};

#endif //!LISTAENLAZADA_H