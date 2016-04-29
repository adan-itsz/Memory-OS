#pragma once
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class listaEnlazada
{
private:

	typedef struct node {
		int unidadMemoria;
		int tamañoMemoria;
		int tamañoProceso;
		int id;
		bool estado; // 0 = hueco, 1 = proceso
		node* siguiente;
	}*nodePtr;

	nodePtr inicio; //inicio
	nodePtr actual; //actual
	nodePtr temporal; //temporal

public:
	listaEnlazada();
	void añadirNodo(int añadirDato);
	void eliminarNodo(int borrarDato);
	void mostrarLista();
};

#endif //!LISTAENLAZADA_H