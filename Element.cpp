#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "Element.h"

using namespace std;

Element::Element(string word, int sum){
    this->word = word;
    this->values = new vector<short>;
    values->push_back(sum);
}

Element::Element(){
    this->word = "";
    this->values = new vector<short>;
}

// media
float Element::get_average(){
    return get_sum()/(float)get_occ();
}

float Element::get_deviation(){
    float middle = get_average(), sum_variance = 0;
    for(int i = 0; i<this->values->size(); i++)
        sum_variance += pow(values->at(i) - middle, 2);
    if(this->values->size() > 1)
        return sqrt(sum_variance/(float)this->values->size());
    else
        return 1; // o valor medio entre 0 e 2
}

int Element::get_occ(){
    return this->values->size();
}

vector<short>* Element::get_values(){
    return this->values;
}

string Element::get_word(){
    return this->word;
}

bool Element::empty(){
    return this->values->size() == 0 || word.empty();
}

int Element::get_sum(){
    int sum = 0;
    for(vector<short>::iterator it = values->begin() ; it != values->end(); ++it)
        sum += *it;

    return sum;
}

void Element::print(){
    cout << word << "\tocc.: " << values->size() << "\tsum: " << get_sum() << endl;
}

Element& Element::operator+=(const Element& e){
    for(int i=0; i<e.values->size(); i++)
        this->values->push_back(e.values->at(i));
    return *this;
}

Element& Element::operator=(const Element& e){
    this->word = e.word;
    this->values = e.values;
    return *this;
}

bool Element::operator==(const Element& e){
    return word.compare(e.word) == 0;
}

bool Element::operator!=(const Element& e){
    return word.compare(e.word) != 0;
}

bool Element::operator>(const Element& e){
    return values->size() > e.values->size();
}

bool Element::operator<(const Element& e){
    return values->size() < e.values->size();
}

bool Element::operator>=(const Element& e){
    return values->size() >= e.values->size();
}

bool Element::operator<=(const Element& e){
    return values->size() <= e.values->size();
}

// compara de this tem mais ocorrencias que e
bool Element::compare_occ(Element e){
    if(values->size() > e.values->size())
        return true;
    else
        return false;
}

// compara se this é mais positivo que e
bool Element::compare_positive(Element e){
    if(this->get_average() > e.get_average())
        return true;
    else if (this->get_average() == e.get_average()) // criterio de desempate
        return (this->get_occ() > e.get_occ());
    else
        return false;
}

// compara se this é mais negativo que e
bool Element::compare_negative(Element e){
    if(this->get_average() < e.get_average())
        return true;
    else if (this->get_average() == e.get_average()) // criterio de desempate
        return (this->get_occ() > e.get_occ());
    else
        return false;
}

ostream& operator<<(ostream& os, const Element& e){
    int sum=0;
    for(int i=0; i<e.values->size(); i++) // calcula soma
        sum += e.values->at(i);

    os << e.word << ((e.word.size() <= 7) ? "\t\t" : "\t") <<
    "occ.: " << e.values->size() << "  \tsum: " << sum << endl;
    return os;
}
