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

    void compactador();

private:
    std::wstring encoded;
    HT::huffman huffman;

    void codificator();

};

}