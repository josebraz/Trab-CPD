#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Informações de uma palavra em um determinado comentario
 */
class InfoComment{
public:
    int n_comment;      // o numero do comentario
    short int n_word;   // posição da palavra no comentario
    short int rating;   // avaliação do comentario

    InfoComment(int, short int, short int);
    void print();
};

/*
 * Todas as informações de uma palavra e contem ponteiros
 * para outros nodos de uma TRIE, logo é um vertice da arvore Trie
 */
class Trie{
public:
    bool is_word;                       // se é uma palavra terminada
    vector<InfoComment>* v_comments;    // informações da palavra
    vector<Trie*>* p_sons;              // os filhos do nodo (de A a Z)

    Trie();     // construtor
    void add_info(InfoComment);
    void insert_node(string, InfoComment, int = 0); // insere uma nova palavra na arvore
    void get_info(string, int = 0);      // imprime as informações da palavra
    bool print_prefix(string, int = 0); // imprime todas as palavras com o prefixo
    void print_comments(int = 0);      // imprime as informações em v_comments
    bool print(string = "", bool = false); // imprime a arvore a partir de "this"
    int get_index(char);
};

#endif
