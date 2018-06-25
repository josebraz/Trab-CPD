#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Hash.h"
#include "Element.h"
#include "ArchText.h"
#include "Heap.h"
#include "Trie.h"

using namespace std;

/* read_file()
 * Le o arquivo e coloca as palavras em um vetor de vetores de string cada um
 * começando por um numero, a avaliação do comentario, seguido pelas palavras
 */
void ArchText::read_file(vector<vector<string> > &vv_s, const string s){
    string line;
    ifstream file_in(s.c_str());
    while(getline(file_in, line)) // roda para cada linha
        vv_s.push_back(split(line));
}

void ArchText::read_file(vector<string> &vv_s, const string s){
    string line;
    ifstream file_in(s.c_str());
    while(getline(file_in, line)) // roda para cada linha
        vv_s.push_back(line);
}

void ArchText::construct_hash(vector<vector<string> > &vv_s, Hash &hash_table){
    for(int i=0; i<vv_s.size(); i++){
        // o score é o ultimo caractere da linha
        int score = vv_s[i].back()[0] - '0';
        // pula os dois IDs e o score no final
        for(int j=2; j<vv_s[i].size()-1; j++)
            if (!vv_s[i][j].empty())
                hash_table.put(Element(vv_s[i][j], score));
    }
}

void ArchText::construct_trie(vector<vector<string> > &vv_s, Trie &trie_tree){
    for(int i=0; i<vv_s.size(); i++){
        int score = vv_s[i][0][0] - '0';
        for(int j=1; j<vv_s[i].size(); j++)
            if (!vv_s[i][j].empty()){
                trie_tree.insert_node(vv_s[i][j], InfoComment(i, j, score));
            }
    }
}

bool ArchText::binary_search(vector<string> v_s, string s){
    int r = v_s.size()-1, l = 0, m;
    while(true){
        if (l > r) return false;
        m = (r + l)/2;
        if(v_s[m].compare(s) < 0)
            l = m+1;
        else if(v_s[m].compare(s) > 0)
            r = m-1;
        else
            return true;
    }
}

void ArchText::remove_stop_words(vector<vector<string> > &vv_s){
    vector<string> stopwords;       // vetor que guarda as stopwords
    ifstream stop_file("stopwords.txt"); // arquivo que contem as stopwords
    string temp;        // string temporaria
    while(stop_file >> temp) stopwords.push_back(temp);
    // roda para o vv_s inteiro
    for(int i=0; i<vv_s.size(); i++)
        for(int j=1; j<vv_s[i].size(); j++)
            // faz uma pesquisa binaria para saber se a palavra esta é stopword
            if(binary_search(stopwords, vv_s[i][j]))
                vv_s[i].erase(vv_s[i].begin()+j--);
}

bool ArchText::is_delim(char c){
    return (c == ' ' || c == '\'' || c == '.' || c == ',' || c == '-' ||
            c == '`' || c == '\t' || c == '?' || c == ';' || c == '!' ||
            c == ':' || c == '\n' || c == '\\' || c == '/');
}

vector<string> ArchText::split(string &s) {
    vector<string> elems;
    int start=0, end=0;
    while(end < s.size()){
        while(end < s.size() && !is_delim(s[end])) end++; // acha o delimitador
        if (end != start){
            string temp(s.begin()+start, s.begin()+end); // cria a string palavra
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // tolower
            elems.push_back(temp); // insere no vetor
        }
        while(end < s.size() && is_delim(s[end])) end++; // pula o delim
        start = end; // recomeça com tudo igual
    }
    return elems;
}
