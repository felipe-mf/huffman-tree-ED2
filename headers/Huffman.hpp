/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#pragma once
#include "Node.hpp"
#include <string>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>


namespace HT{

class Huffman{   

public:
    /// construtor já inicializando o texto para codificar (o construtor já chama o método para achar a frequencia de cada caracter)
    Huffman(std::wstring _text): text(_text){
        fillCharFrequenciesMap();
    }

    /// Cria a arvore de huffman e chama a função que ira gerar os códigos(generateHuffmanCodes) 
    void encoder();

    /// retorna os bits já codificados do texto de entrada
    [[nodiscard]] std::wstring getEncodedText() noexcept;

    /// retorna o texto decodificado 
    [[nodiscard]] std::wstring getDecodedText() noexcept;

    /// Só para ver se a tabela está correta (a princípio está)
    void showTable() const noexcept;

    /// Método destrutor
    ~Huffman();
    



private:
    HT::Node *root;
    std::wstring text;
    std::map<wchar_t, int> charFrequencies;
    std::map<wchar_t, std::wstring> huffmanCodes;
    std::map<std::wstring, wchar_t> huffmanDecodes;


    /// Deleta um no
    void deleteRoot(Node *root);

    /// Preenche o map com a frequencia de cada caracter
    void fillCharFrequenciesMap() noexcept;

    /// Percorre a arvore e gera o codigo para cada caracter
    void generateHuffmanCodes(HT::Node *node, std::wstring code);

    /// estrutura para comparar na priority queue
    struct cmp{
        inline bool operator()(HT::Node* a, HT::Node* b) const noexcept{
            return a->getFrequency() > b->getFrequency();
        }
    };   

};



}

