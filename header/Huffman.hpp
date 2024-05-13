/*
@author: Jean Bonadeo Dal Santo
@author: Felipe M. Fagundes
*/
#pragma once
#include "Node.hpp"
#include <string>
#include <map>
#include <queue>
#include <iostream>

class Huffman{
    private:
        HT::Node *root;
        std::string text;
        std::map<char, int> charFrequencies;
        std::map<char, std::string> huffmanCodes;
        std::map<std::string, char> huffmanDecodes;

        /// @brief Preenche o map com a frequencia de cada caracter
        void fillCharFrequenciesMap();

        /// @brief Percorre a arvore e gera o codigo para cada caracter
        void generateHuffmanCodes(HT::Node *node, std::string code);

        /// @brief estrutura para comparar na priority queue
        struct cmp {
            bool operator()(HT::Node* a, HT::Node* b) {
                return a->getFrequency() > b->getFrequency();
            }
        };      

    public:
        /// @brief construtor já inicializando o texto para codificar (o construtor já chama o método para achar a frequencia de cada caracter)
        Huffman(std::string _text);

        /// @brief Cria a arvore de huffman e chama a função que ira gerar os códigos(generateHuffmanCodes) 
        void encode();

        /// @brief Peguei do vídeo do cara codando em Java, acho q nao funciona (criei a getDecodedText q funciona) Provavelmente vamos excluir essa
        std::string decode(std::string encodedText);

        /// @brief retorna os bits já codificados do texto de entrada
        std::string getEncodedText();

        /// @brief retorna o texto decodificado 
        std::string getDecodedText();

        /// @brief Só para ver se a tabela está correta (a princípio está)
        void ShowTable();

};