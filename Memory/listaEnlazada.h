#pragma once
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class listaEnlazada
{
private:

	typedef struct node {
		int unidadMemoria;
		int tamaņoMemoria;
		int tamaņoProceso;
		int id;
		bool estado; // 0 = hueco, 1 = proceso
		node* siguiente;
	}*nodePtr;

	nodePtr inicio; //inicio
	nodePtr actual; //actual
	nodePtr temporal; //temporal

public:
	listaEnlazada();
	void aņadirNodo(int aņadirDato);
	void eliminarNodo(int borrarDato);
	void mostrarLista();
};

#endif //!LISTAENLAZADA_H