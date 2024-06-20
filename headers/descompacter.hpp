/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include <fstream>
#include <cwchar>
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <unordered_map>
#pragma once


namespace HT{

class descompacter{
    
public:

    descompacter(){};

    void descompactar();

private:
    std::wstring binario;
    std::unordered_map<std::wstring, wchar_t> map_cod;
    
    std::wstring byte_binary_to_string(char byte);

    void save(int tam) noexcept;

};

}