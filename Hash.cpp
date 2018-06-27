#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Hash.h"
#include "Element.h"
#include "ArchText.h"

using namespace std;

Hash::Hash(int max_size){
    this->max_size = max_size;
    this->table = new vector<Element>(this->max_size, Element());
    this->colisoes = 0;
    this->size = 0;
}

bool Hash::put(Element name){
    int hash_id = hashing(name.get_word());

    if (name == this->table->at(hash_id)){ // ja esta na tabela
        this->table->at(hash_id) += name;
    }else{ // não esta na tabela, logo temos de inserir
        this->table->at(hash_id) = name;
        this->size++;
    }
    return true;
}

int Hash::get_number_of_char(char c){
    if(c >= 'a' && c <= 'z') return c - 'a' + 1;    // letras minusculas
    if(c >= 'A' && c <= 'Z') return c - 'A' + 1;    // letras maiusculas
    if(c >= '0' && c <= '9') return (c - '0') + ('z'-'a') + 1; // numeros
    return 1; // outras coisas
}

int Hash::h1(string word){
    double h1 = 0;
    for(int i=0; i<word.size(); i++)
        h1 += pow(get_number_of_char(word[i]), 9);

    h1 = fmod(h1, this->max_size);
    return (int)h1;
}

int Hash::h2(string word){
    double h2 = 0;
    for(int i=0; i<word.size(); i++)
        h2 += pow(get_number_of_char(word[i]), 7);

    h2 = fmod(h2, 17939);
    return (int)h2;
}

int Hash::hashing(string word){
    int hash_id, h1 = this->h1(word), h2 = this->h2(word);
    int i = 0;
    Element in_test;
    // repete até que ache um lugar na tabela
    do{
        hash_id = (h1 + i*h2 + (int)pow(i, 2)) % this->max_size;
        in_test = this->table->at(hash_id);
        i++;
    } while(!in_test.empty() && word != in_test.get_word());
    this->colisoes += (i-1);    // salva as colisoes
    return (int)hash_id;
}

float Hash::get_average(string word){
    int id = hashing(word);         // acha o id de word
    if (this->table->at(id).get_word() == word)
        return this->table->at(id).get_average();
    else
        return -1;          // não achou a palavra na tabela
}

float Hash::get_deviation(string word){
    int id = hashing(word);         // acha o id de word
    if (this->table->at(id).get_word() == word)
        return this->table->at(id).get_deviation();
    else
        return -1;          // não achou a palavra na tabela
}

int Hash::get_occ(string word){
    int id = hashing(word);         // acha o id de word
    if (this->table->at(id).get_word() == word)
        return this->table->at(id).get_occ();
    else
        return -1;          // não achou a palavra na tabela
}

// Quanto maior o desvio padrão, menos confiável a amostra é
float deviation_to_weight(float deviation){
    float temp = log(deviation/2) / -0.04;
    if (temp > 100) return 100;
    if (temp < 0) return 0;
    return temp;
}

float Hash::get_score_phrase(string phrase){
    vector<string> words = ArchText::split(phrase);
    float sum_words = 0;
    float total_deviation = 0;
    for(int i=0; i<words.size(); i++){
        // se não conhecemos a palavra, nao vamos considerar
        // se conhecermos vamos fazer uma media ponderada
        float score_word = get_average(words[i]);
        if (score_word != -1){
            // peso obtido a partir do desvio
            float weight = deviation_to_weight(get_deviation(words[i]));
            
            sum_words += score_word * weight;
            total_deviation += weight;
        }
    }
    if (total_deviation != 0)
        return sum_words/total_deviation;
    else
        return 2;
}

Element& Hash::operator[](int i) {
    if(i < this->max_size)
        return this->table->at(i);
}

vector<Element>* Hash::get_table(){
    return this->table;
}

void Hash::print_table(){
    // i = index table, l = size real
    for(int i=0, l=0; l<size; l++){
        while(table->at(i).empty()) i++;
        cout << "N: " << i << ((i < 9999) ? "\t\t" : "\t") << table->at(i++);
    }
    cout << "Colisoes: " << this->colisoes << endl;
    cout << "proporcao: " << this->size/(float)this->max_size*100 << "\%" << endl;
}
