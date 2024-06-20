/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/compacter.hpp"


    void HT::compacter::compactador(){
        std::ofstream saida("/tmp/arq_compactado.txt", std::ios::binary);
        char byte = 0;
        int rep = 0;
    
        for (auto c : encoded) {
            if (c == '1') {
                byte |= 1 << (7 - rep);
            }
            rep++;
            if (rep == 8) {
                saida << byte;
                rep = 0;
                byte = 0;
            }
        }
        if (rep > 0) {
            byte <<= (8 - rep);
            saida << byte;
        }
        
        saida.close();
        codificator();
        system("tar -cf arq_zipado.tar -C /tmp codificacao.txt arq_compactado.txt");



    }

    void HT::compacter::codificator(){
        int tam = huffman.get_size_tree();
        auto mapa = huffman.get_huffman_codes();
        std::wofstream saida("/tmp/codificacao.txt");
        saida << tam;
        for(auto par: mapa){
            saida << par.first << L' ' << par.second << L'\n';
        }
    }
