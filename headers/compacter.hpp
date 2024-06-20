/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include <fstream>
#include <cwchar>
#include <iostream>
#include <cstdlib>
#include <bitset>
#pragma once


namespace HT{

class compacter{
    
public:
    compacter(const std::wstring &_encoded, const HT::huffman &_huffman) : encoded(_encoded), huffman(_huffman){}

    /// Função para converter a wstring encoded gerada pela huffman em bytes, além de salvar o arquivo compactado.
    void compactador();

private:
    std::wstring encoded;
    HT::huffman huffman;

    ///Função usada dentro do compacter para obter os meta dados da árvore.
    void codificator();

};

}