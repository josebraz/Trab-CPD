O programa foi escrito em C++ e testado apenas em sistemas Linux.
Há um Makefile para facilitar a compilação direto do terminal.
Cada classe contem um arquivo .cpp e um .h. As classes são:
* ArchText  : Classe abstrata que contém as funções envolvendo arquivos e criadores de outras classes.
* Element   : Classe que engloba as características de um palavra, como o nome e vetor de todas as avaliações da palavra.
* Hash      : Tabela de Hash que guarda os Elements.
* Trie      : Árvore Trie que contém as palavras que apareceram no texto, seus locais e suas avaliações.
