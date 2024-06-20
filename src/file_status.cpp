/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/file_status.hpp"
#include <sys/stat.h>

[[nodiscard]] int HT::file_status::tam_origin() const noexcept{
    struct stat x;
    const char* arq = original.c_str();
    stat(arq, &x);
    return x.st_size;
}

[[nodiscard]] int inline HT::file_status::tam_compressed() const noexcept{
    return comprimido.size() / static_cast<size_t>(8);
}

[[nodiscard]] int inline HT::file_status::diff() const noexcept{
    return abs(tam_origin() - tam_compressed());
}

[[nodiscard]] double inline HT::file_status::porcent() const noexcept{
    return (static_cast<double>(diff()) / static_cast<double>(tam_origin()) * 100);
}