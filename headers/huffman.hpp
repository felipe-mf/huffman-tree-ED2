/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#pragma once
#include "node.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>


namespace HT{

class huffman{   

public:
    /// construtor já inicializando o texto para codificar (o construtor já chama o método para achar a frequencia de cada caracter)
    huffman(std::wstring _text): text(_text){
        fill_char_frequencies_map();
    }

    /// Cria a arvore de huffman e chama a função que ira gerar os códigos(generatehuffmanCodes) 
    void encoder();

    /// retorna os bits já codificados do texto de entrada
    [[nodiscard]] std::wstring get_encoded_text() noexcept;

    /// retorna o texto decodificado 
    [[nodiscard]] std::wstring get_decoded_text() noexcept;

    /// Só para ver se a tabela está correta (a princípio está)
    void show_table() const noexcept;

    std::wstring traverse_tree(node *node, std::wstring code, std::wstring ans);

    void links(HT::node *node, std::wofstream &dot);
  
    /// Método destrutor
    ~huffman();

    void show_tree(); /// Funcao para mostrar a arvore 
    



private:
    HT::node *root;
    std::wstring text;
    std::map<wchar_t, int> char_frequencies;
    std::map<wchar_t, std::wstring> huffman_codes;
    std::map<std::wstring, wchar_t> huffman_decodes;


    /// Deleta um no
    void delete_root(node *root);

    /// Preenche o map com a frequencia de cada caracter
    void fill_char_frequencies_map() noexcept;

    /// Percorre a arvore e gera o codigo para cada caracter
    void generate_huffman_codes(HT::node *node, std::wstring code);

    /// estrutura para comparar na priority queue
    struct cmp{
        inline bool operator()(HT::node* a, HT::node* b) const noexcept{
            return a->get_frequency() > b->get_frequency();
        }
    };
      

};



}

