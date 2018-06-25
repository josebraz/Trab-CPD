#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Element.h"

using namespace std;

class Heap {
private:
	int size;                     // tamanho do heap
	int type;
	vector<Element> *heap_vector; // vetor que guarda os elementos

public:
	// construtors
	// type: 0 - maior ocorencias
	//		 1 - mais positivas
	//		 2 - mais negativas
	Heap(int = 0);
	Heap(Element[], int, int = 0);
	Heap(vector<Element>*, int = 0);

	// getters
	int get_size();
	Element get_node(int);
	int get_index_father(int);
	Element get_father(int);
	Element get_left_son(int);
	Element get_right_son(int);

	// setters
	void set_size(int size) {this->size = size;}

	// functions
	void heapify(int);     // coloca na posicao correta um elemento
	void build();              // mantem a propriedade de heap
	void sort();               // ordena o vetor
	void print();              // printa o vetor
	void insert(Element);      // insere um elemento
	Element max_element();     // retorna o elemento maximo
	Element remove_max_element();
};

#endif
