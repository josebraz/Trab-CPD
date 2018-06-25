#ifndef ARCHTEXT_H
#define ARCHTEXT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Trie.h"

using namespace std;

const string NEGATIVES[] = {"no", "nothing", "nobody", "never"};

class ArchText{
public:
    static void read_file(vector<vector<string> > &, const string);
        static void read_file(vector<string> &, const string);
    static void construct_hash(vector<vector<string> > &, Hash &);
    static void construct_trie(vector<vector<string> > &, Trie &);
    static bool binary_search(vector<string>, string);
    static void remove_stop_words(vector<vector<string> > &);
    static vector<string> split(string&);
    static bool is_delim(char);
};

#endif
