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

namespace HT{

class Huffman{   

public:
    /// construtor já inicializando o texto para codificar (o construtor já chama o método para achar a frequencia de cada caracter)
    Huffman(std::string _text): text(_text){
        fillCharFrequenciesMap();
    }

    /// Cria a arvore de huffman e chama a função que ira gerar os códigos(generateHuffmanCodes) 
    void encoder();

    /// retorna os bits já codificados do texto de entrada
    [[nodiscard]] std::string getEncodedText() noexcept;

    /// retorna o texto decodificado 
    [[nodiscard]] std::string getDecodedText() noexcept;

    /// Só para ver se a tabela está correta (a princípio está)
    void showTable() const noexcept;

private:
    HT::Node *root;
    std::string text;
    std::map<char, int> charFrequencies;
    std::map<char, std::string> huffmanCodes;
    std::map<std::string, char> huffmanDecodes;

    /// Preenche o map com a frequencia de cada caracter
    void fillCharFrequenciesMap() noexcept;

    /// Percorre a arvore e gera o codigo para cada caracter
    void generateHuffmanCodes(HT::Node *node, std::string code);

    /// estrutura para comparar na priority queue
    struct cmp{
        inline bool operator()(HT::Node* a, HT::Node* b) const noexcept{
            return a->getFrequency() > b->getFrequency();
        }
    };   

};

}