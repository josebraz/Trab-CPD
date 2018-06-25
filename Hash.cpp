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

int Hash::collision(int hash_id, string word){
    Element in_test = this->table->at(hash_id);
    while (!in_test.empty() && word != in_test.get_word()){
        hash_id++; // colisoes
        this->colisoes++;
        if (hash_id >= this->max_size) hash_id=0; // volta do inicio
        in_test = this->table->at(hash_id);
    }
    return hash_id;
}

int Hash::get_number_of_char(char c){
    if(c >= 'a' && c <= 'z') return c - 'a' + 1;
    if(c >= 'A' && c <= 'Z') return c - 'A' + 1;
    return 0;
}

int Hash::hashing(string word){
    double ret = 0;
    for(int i=0; i<word.size(); i++)
        ret += pow(get_number_of_char(word[i]), 9)*(i+1);
    ret = fmod(ret, this->max_size);
    ret = collision(ret, word);
    return (int)ret;
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

// Quanto mais ocorencias a palavra tem, mais conhecemos ela
float occ_to_reliability(int occ){
    float temp = log(occ/0.15) / 0.08;
    if (temp > 100) return 100;
    if (temp < 0) return 0;
    return temp;
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
            // confiabilidade da amostra
            //float reliability = occ_to_reliability(get_occ(words[i]));
            sum_words += score_word * weight; //+ reliability);
            total_deviation += weight; // + reliability;
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
