#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Element.h"

using namespace std;

class Hash {
private:
    vector<Element> *table; // array de ponteiros strings (tabela)
    int max_size;           // tamanho maximo da tabela
    int size;               // tamanho ocupado realmente
    int colisoes;           // numero de colisoes

public:
    Hash(int);
    float get_average(string);
    int get_occ(string);    // retorna quantas vezes a palavra apareceu
    float get_deviation(string);
    float get_score_phrase(string);
    int get_number_of_char(char);
    vector<Element>* get_table();
    int hashing(string);
    int h1(string);
    int h2(string);
    void print_table();
    bool put(Element name);

    Element& operator[](int);
};

#endif
