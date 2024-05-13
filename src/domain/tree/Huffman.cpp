/*
@author: Jean Bonadeo Dal Santo
@author: Felipe M. Fagundes
*/
#include "../../../header/Huffman.hpp"
#include "Node.cpp"
#include <string>
#include <map>
#include <queue>
#include <iostream>


void Huffman::fillCharFrequenciesMap(){
    for(char c: text){
        charFrequencies[c]++;;
    }
}

void Huffman::generateHuffmanCodes(HT::Node *node, std::string code){
    if(!node) return;
    if(charFrequencies.count(node->getCharacter()) && !node->getLeftNode() && !node->getRightNode()){
        huffmanCodes[node->getCharacter()]=code;
        huffmanDecodes[code]=node->getCharacter(); 
    }
    Huffman::generateHuffmanCodes(node->getLeftNode(), code+"0");
    Huffman::generateHuffmanCodes(node->getRightNode(), code+"1");
}

Huffman::Huffman(std::string _text): text(_text){
    fillCharFrequenciesMap();
}

void Huffman::encode(){
    std::priority_queue<HT::Node*, std::vector<HT::Node*>, Huffman::cmp> fila;

    for(auto c: charFrequencies){
        auto nodo = new HT::Node(c.first, c.second, nullptr, nullptr);
        fila.push(nodo);
    }

    while(fila.size() > 1){
        HT::Node *left = fila.top();
        fila.pop();
        HT::Node *right = fila.top();
        fila.pop();
        int soma = left->getFrequency() + right->getFrequency();
        auto nodo = new HT::Node('\n', soma, left, right);
        fila.push(nodo);
    }
    auto last = fila.top();
    fila.pop();
    Huffman::generateHuffmanCodes(root = last, "");
}

std::string Huffman::decode(std::string encodedText){       //provavelmente apagar
    std::string ans="";
    HT::Node* current = root;
    for(char c: encodedText){
        current = (c == '0' ? current->getLeftNode() : current->getRightNode());
        if(current->getCharacter() != '\0'){
            ans+=current->getCharacter();
            current = root; 
        }
    }
    return ans;
}

std::string Huffman::getEncodedText(){
    std::string ans="";
    for(char c:text){
        ans+=huffmanCodes[c];
    }
    return ans;
}

std::string Huffman::getDecodedText(){
    std::string ans="";
    std::string code="";
    std::string encoded = getEncodedText();
    for(char c: encoded){
        code+=c;
        if(huffmanDecodes.count(code)){
            ans+=huffmanDecodes[code];
            code="";
        }
    }
    return ans;
}

void Huffman::ShowTable(){
    std::cout << "-----TABELA-----\n";
    for(auto c: huffmanCodes){
        std::cout << c.first << " = " << c.second << std::endl;
    }
}
