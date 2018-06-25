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
    float get_average();
    float get_deviation();
    int get_sum();
    int get_occ();          // retorna quantas vezes a palavra apareceu
    bool empty();
    void print();

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

    friend ostream& operator<<(std::ostream&, const Element&);

};

#endif
