/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/Huffman.hpp"

void HT::Huffman::fillCharFrequenciesMap() noexcept{
    for(const char &c: text)
        charFrequencies[c]++;
}

void HT::Huffman::generateHuffmanCodes(HT::Node *node, std::string code){
    if(!node) return;
    if(charFrequencies.count(node->getCharacter()) && !node->getLeftNode() && !node->getRightNode()){
        huffmanCodes[node->getCharacter()]=code;
        huffmanDecodes[code]=node->getCharacter(); 
    }
    Huffman::generateHuffmanCodes(node->getLeftNode(), code+"0");
    Huffman::generateHuffmanCodes(node->getRightNode(), code+"1");
}

void HT::Huffman::encoder(){
    std::priority_queue<HT::Node*, std::vector<HT::Node*>, Huffman::cmp> fila;
    for(const auto &c: charFrequencies){
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
    root = fila.top();
    fila.pop();
    Huffman::generateHuffmanCodes(root, "");
}

[[nodiscard]] std::string HT::Huffman::getEncodedText() noexcept{
    std::string ans="";
    for(const char &c:text)
        ans+=huffmanCodes[c];
    return ans;
}

[[nodiscard]]std::string HT::Huffman::getDecodedText() noexcept{
    std::string ans="";
    std::string code="";
    std::string encoded = getEncodedText();
    for(const char &c: encoded){
        code+=c;
        if(huffmanDecodes.count(code)){
            ans+=huffmanDecodes[code];
            code="";
        }
    }
    return ans;
}

void HT::Huffman::showTable() const noexcept{
    std::cout << "-----TABELA-----\n";
    for(const auto &c: huffmanCodes)
        std::cout << c.first << " = " << c.second << std::endl;
    std::cout << "----------------\n";
}
