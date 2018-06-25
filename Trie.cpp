#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Trie.h"

using namespace std;

InfoComment::InfoComment(int n_comment, short int n_word, short int rating){
    this->n_comment = n_comment;
    this->n_word = n_word;
    this->rating = rating;
}

void InfoComment::print(){
    cout << "Comentario #" << this->n_comment << ", Palavra #" << this->n_word
         << ", Sentiment #" << this->rating << endl;
}

Trie::Trie(){
    this->v_comments = new vector<InfoComment>;
    this->is_word = false;
    this->p_sons = new vector<Trie*>(26, NULL);
}

// adiciona informações no vetor de comentarios
void Trie::add_info(InfoComment info){
    this->v_comments->push_back(info);
    this->is_word = true;
}

int Trie::get_index(char c){
    if(c >= 'a' && c <= 'z')
        return c - 'a';
    else if(c == 9)
        return 0;
    else
        return 27;
}

/* insert_node
 * recebe uma palavra "word" e insere a primeira letra, chamando recursivamente
 * para inserir as outras letras ate que a palavra so tenha uma letra, nesse
 * ponto a inserção tambem coloca as informações de "info" no nodo
 */
void Trie::insert_node(string word, InfoComment info, int i){
    int index_p = get_index(word[i]);    // calcula o indice
    if (i < word.size() && index_p < 26){ // cria mais nodos de corte
        if(this->p_sons->at(index_p) == NULL) // cria novo nodo se não existir
            this->p_sons->at(index_p) = new Trie();
        this->p_sons->at(index_p)->insert_node(word, info, ++i);
    } else
        this->add_info(info); // adiciona mais informações sobre a palavra
}

void Trie::get_info(string word, int op){
    if (word.size() > 0){ // cria mais nodos de corte
        int index_p = get_index(word[0]);    // calcula o indice
        if (index_p < 26 && this->p_sons->at(index_p) != NULL){
            word.erase(word.begin()); // apaga o caractere ja inserido na arvore
            this->p_sons->at(index_p)->get_info(word, op);
        }
    } else
        this->print_comments(op);
}

// Imprime todos os comentarios da palavra
void Trie::print_comments(int op){
    for(int i=0; i<this->v_comments->size(); i++)
        if(op < 0 && this->v_comments->at(i).rating < 2)
            this->v_comments->at(i).print();
        else if(op > 0 && this->v_comments->at(i).rating > 2)
            this->v_comments->at(i).print();
        else if (op == 0)
            this->v_comments->at(i).print();
}

// imprime todas as palavras começando com word
void Trie::print_prefix(string word, int i){
    if (i < word.size()){ // cria mais nodos de corte
        int index_p = get_index(word[i]);    // calcula o indice
        if (index_p < 26 && this->p_sons->at(index_p) != NULL)
            this->p_sons->at(index_p)->print_prefix(word, ++i);
    } else
        this->print(word);
}

// imprime a arvore toda
void Trie::print(string prefix){
    for(int i=0; i<26; i++){
        Trie* temp = this->p_sons->at(i);
        if(temp != NULL){
            prefix += (char)('a'+i);
            if(temp->is_word)
                cout << prefix << endl;
            temp->print(prefix);
            prefix.erase(prefix.end()-1);
        }
    }
}
