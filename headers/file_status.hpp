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

    [[nodiscard]]int tam_origin()const noexcept;
    [[nodiscard]]int inline tam_compressed()const noexcept;
    [[nodiscard]]int inline diff()const noexcept;
    [[nodiscard]]double inline porcent()const noexcept;
private:
    std::string original;
    std::wstring comprimido;
};

}