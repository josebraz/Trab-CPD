all: prog
	./prog

prog: main Hash Element ArchText Heap Trie
	g++ -o prog main.o Hash.o Element.o ArchText.o Heap.o Trie.o

main: main.cpp
	g++ -c main.cpp

Hash: Hash.cpp
	g++ -c Hash.cpp

Element: Element.cpp
	g++ -c Element.cpp

ArchText: ArchText.cpp
	g++ -c ArchText.cpp

Heap: Heap.cpp
	g++ -c Heap.cpp

Trie: Trie.cpp
	g++ -c Trie.cpp
