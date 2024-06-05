#include "../headers/file_status.hpp"
#include <sys/stat.h>

[[nodiscard]]int HT::file_status::tam_origin()const noexcept{
    struct stat x;
    const char* arq = original.c_str();
    stat(arq, &x);
    return x.st_size;
}

[[nodiscard]]int inline HT::file_status::tam_compressed()const noexcept{
    return comprimido.size()/8;
}

[[nodiscard]]int inline HT::file_status::diff()const noexcept{
    return abs(tam_origin() - tam_compressed());
}

[[nodiscard]]double inline HT::file_status::porcent()const noexcept{
    return ((double)diff() / (double)tam_origin() * 100);
}

