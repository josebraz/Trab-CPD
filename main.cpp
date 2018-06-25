#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <math.h>

#include "Hash.h"
#include "Element.h"
#include "ArchText.h"
#include "Heap.h"
#include "Trie.h"

using namespace std;

void make_test(Hash hash_table){
    vector<vector<string> > vv_teste;
    ofstream file_out("out_test.csv");
    ArchText::read_file(vv_teste, "test.tsv");
    file_out << "PhraseId,Sentiment" << endl; // coloca o cabeçalho no arquivo
    // pula o cabeçalho no arquivo
    for(int i=1; i<vv_teste.size(); i++){
        string phrase;                          // string que vai montar a frase
        for(int j=2; j<vv_teste[i].size()-1; j++) // pula os IDs
            phrase += vv_teste[i][j] + " ";
        phrase += vv_teste[i].back();

        int score = round(hash_table.get_score_phrase(phrase));
        file_out << vv_teste[i][0] << "," << score << endl;

    }

}

int main(){
    vector<vector<string> > vv_s;
    Hash hash_table(30000);
    Trie trie_tree;

    string phrase, word;
    float score, deviation;
    vector<string> v;

    cout << "Lendo o banco de dados..." << endl;
    // Preparação dos dados
    ArchText::read_file(vv_s, "train.tsv");
    ArchText::remove_stop_words(vv_s);

    cout << "Construindo as estruturas..." << endl;
    // construtor das estruturas
    ArchText::construct_hash(vv_s, hash_table);
    ArchText::construct_trie(vv_s, trie_tree);
    Heap heap_trie_occ(hash_table.get_table(), 0);
    Heap heap_trie_pos(hash_table.get_table(), 1);
    Heap heap_trie_neg(hash_table.get_table(), 2);

    while(true){
        system("clear");
        int choice;
        cout << "Escolha uma opção:" << endl;
        cout << "[1] Avaliar uma frase" << endl;
        cout << "[2] Informações da palavra" << endl;
        cout << "[3] Lista de palavras começando com..." << endl;
        cout << "[4] Palavras mais populares" << endl;
        cout << "[5] Palavras mais positivas" << endl;
        cout << "[6] Palavras mais negativas" << endl;
        cout << "[7] Imprimir Hash" << endl;
        cout << "[8] Fazer teste do kaggle" << endl;

        cin >> choice;
        system("clear");

        switch(choice){
        case 1: cout << "Diga sua frase em ingles: ";
                getline(cin, phrase);
                getline(cin, phrase);
                cout << "Cada palavra tem score:" << endl;
                v = ArchText::split(phrase);
                for(int i=0; i<v.size(); i++)
                    if(hash_table.get_average(v[i]) != -1)
                        cout << v[i] << "\tmedia: " <<
                        hash_table.get_average(v[i]) << "\tdesvio: "<<
                        hash_table.get_deviation(v[i]) << endl;

                score = hash_table.get_score_phrase(phrase);
                cout << ((score > 2) ? "Positivo :)" : "Negativo :(") << endl;
                cout << "Score da frase foi de: " << score << endl;
                break;
        case 2: cout << "Diga sua palavra em ingles: ";
                getline(cin, phrase);
                getline(cin, phrase);
                transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
                v = ArchText::split(phrase);

                // imprime de acordo com as preferencias da ultima palavra
                if(v[v.size()-1] == "positiva")
                    trie_tree.get_info(v[0], 1);
                else if(v[v.size()-1] == "negativa")
                    trie_tree.get_info(v[0], -1);
                else
                    trie_tree.get_info(v[0]);

                score = hash_table.get_average(v[0]);
                deviation = hash_table.get_deviation(v[0]);
                cout << "Média: " << score << endl;
                cout << "Desvio: " << deviation << endl;
                break;
        case 3: cout << "Diga sua palavra em ingles: ";
                cin >> word;
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                trie_tree.print_prefix(word);
                break;
        case 4: heap_trie_occ.sort();
                heap_trie_occ.print();
                break;
        case 5: heap_trie_pos.sort();
                heap_trie_pos.print();
                break;
        case 6: heap_trie_neg.sort();
                heap_trie_neg.print();
                break;
        case 7: hash_table.print_table();
                break;
        case 8: cout << "Efetuando o teste..." << endl;
                make_test(hash_table);
                cout << "Teste gravado em out_test.csv" << endl;
                break;
        default: break;
        }
        cin.get();
        cin.get();
    }
    //hash_table.print_table();
}
