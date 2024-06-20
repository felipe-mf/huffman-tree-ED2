/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include <iostream>
#pragma once

namespace HT{

class file_status{

public:
    file_status(std::string _original, std::wstring _comprimido):original(_original), comprimido(_comprimido){}

    /// Função para obter o tamanho original do arquivo. 
    [[nodiscard]]int tam_origin()const noexcept;
    ///Função para obter o tamanho comprimido do arquivo.
    [[nodiscard]]int inline tam_compressed()const noexcept;
    ///Função para pegar a diferença em bytes do arquivo original e do comprimido.
    [[nodiscard]]int inline diff()const noexcept;
    ///Função para pegar a porcentagem da diferença. 
    [[nodiscard]]double inline porcent()const noexcept;
private:
    std::string original;
    std::wstring comprimido;
};

}