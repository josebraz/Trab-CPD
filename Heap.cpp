#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Element.h"
#include "Heap.h"

using namespace std;

int Heap::get_size(){
	return this->size;
}

Element Heap::get_node(int index){
	return (this->size > index) ? heap_vector->at(index) : Element();
}

int Heap::get_index_father(int index){
	return (int)(index-1)/2;
}

Element Heap::get_father(int index){
	return heap_vector->at((index-1)/2);
}

Element Heap::get_left_son(int index){
	return (this->size > index*2+1) ? heap_vector->at(index*2+1) : Element();
}

Element Heap::get_right_son(int index){
	return (size > index*2+2) ? heap_vector->at(index*2+2) : Element();
}

Heap::Heap(int type){
	this->size = 0;
	this->type = type;
	heap_vector = new vector<Element>;
}

Heap::Heap(Element array[], int size, int type){
	heap_vector = new vector<Element>;
	for(int i = 0; i < size; i++)
		heap_vector->push_back(array[i]);
	this->size = size;
	this->type = type;
	build();
}

Heap::Heap(vector<Element> *v, int type){
	heap_vector = new vector<Element>;
	for(int i = 0; i < v->size(); i++)
		if(!v->at(i).empty())
			heap_vector->push_back(v->at(i));
	this->size = heap_vector->size();
	this->type = type;
	build();
}

void Heap::heapify(int index){
	int bigger = index;
	// dependendo do tipo do heap nos ordenamos de um jeito diferente
	switch (type) {
	case 0: // mais populares
		if (get_left_son(index).compare_occ(heap_vector->at(bigger)))
			bigger = index*2+1;
		if (get_right_son(index).compare_occ(heap_vector->at(bigger)))
			bigger = index*2+2;
		break;
	case 1: // mais positivas
		if (get_left_son(index).compare_positive(heap_vector->at(bigger)))
			bigger = index*2+1;
		if (get_right_son(index).compare_positive(heap_vector->at(bigger)))
			bigger = index*2+2;
		break;
	case 2: // mais negativas
		if (get_left_son(index).compare_negative(heap_vector->at(bigger)))
			bigger = index*2+1;
		if (get_right_son(index).compare_negative(heap_vector->at(bigger)))
			bigger = index*2+2;
	}

	if (bigger != index){
		// swap
		Element temp = heap_vector->at(index);
		heap_vector->at(index) = heap_vector->at(bigger);
		heap_vector->at(bigger) = temp;

		heapify(bigger);
	}
}

void Heap::build(){
	for(int i = get_size()/2; i >= 0; i--)
		heapify(i);
}

void Heap::sort(){
	build();
 	for (int i = get_size(); i > 0; i--){
		// troca o primeiro com o ultimo e reordena os heap
		// swap
		Element temp = heap_vector->at(0);
		heap_vector->at(0) = heap_vector->at(size-1);
		heap_vector->at(size-1) = temp;

		set_size(get_size()-1);
		heapify(0);
	}
	set_size(heap_vector->size());
}

void Heap::insert(Element e){
	int i = get_size();
	heap_vector->push_back(e);
	set_size(get_size()+1);
	while (i<0 && get_father(i) < e){
		heap_vector->at(i) = get_father(i);
		i = get_index_father(i);
	}
	heap_vector->at(i) = e;
}

Element Heap::max_element(){
	return heap_vector->at(0);
}

Element Heap::remove_max_element(){
	Element temp = heap_vector->at(0);
	heap_vector->at(0) = heap_vector->at(get_size()-1); // coloca ultimo em primeiro
	heap_vector->erase(heap_vector->end()); 		// apaga o primeiro elemento
	heapify(0); 								// reordena o primeiro
	return temp;
}

void Heap::print(){
 	for (int i = 0; i < get_size(); i++)
		cout << heap_vector->at(i);
}

void Heap::inverse_print(int k){
	int total = get_size();
 	for (int i = 1; i <= k; i++)
		cout << i << '\t' << heap_vector->at(total-i);
}
