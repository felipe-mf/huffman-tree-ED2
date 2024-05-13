#include <bits/stdc++.h>
#include "../domain/tree/Huffman.cpp"
//#include "../../header/Huffman.hpp"

using namespace std;

int main (){
    Huffman huffman = Huffman("aaaabbbccd");

    huffman.encode();
    string encodedtext = huffman.getEncodedText();
    cout << encodedtext << endl;

    huffman.ShowTable();

    string original = huffman.getDecodedText();
    cout << original << endl;

    return 0;
}


/*
RECADO
as funções básicas do funcionamento estão prontas
os .hpp fiz desse jeito

***é preciso implementar o destrutor da árvore, para liberar a memória

***fazer a main console, pode ser um hubzinho, faz um while e bota as opções 
1- digitar texto ou arquivo a ser aberto
2- mostrar tabela de codificação
3- mostrar texto codificado
4- mostrar texto decodificado

***refatorar o codigo para utilizar o unicode e não a ASCII, a wstring

***fazer um gerador de arquivo .dot

***compacter e descompacter não fiz nada to pensando se é valido fazer essas classes

*/