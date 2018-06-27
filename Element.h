#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Element{
private:
    string word;        // a palava guardada
    vector<short> *values;// lista de valores que a palavra ja assumiu

public:
    Element();
    Element(string, int);
    string get_word();
    vector<short>* get_values();
    float get_average();    // a media sum/occ
    float get_deviation();  // retorna o desvio padrao
    int get_sum();          // a soma dos elementos de values
    int get_occ();          // retorna quantas vezes a palavra apareceu
    bool empty();
    void print();

    // comparadores para a Heap Tree
    bool compare_occ(Element);
    bool compare_positive(Element);
    bool compare_negative(Element);

    Element& operator=(const Element&);
    Element& operator+=(const Element&);
    bool operator==(const Element&);
    bool operator>(const Element&);
    bool operator<(const Element&);
    bool operator>=(const Element&);
    bool operator<=(const Element&);
    bool operator!=(const Element&);

    // usar com o cout
    friend ostream& operator<<(std::ostream&, const Element&);

};

#endif
