/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/Huffman.hpp"


void HT::Huffman::fillCharFrequenciesMap() noexcept{
    for(const wchar_t &c: text)
        charFrequencies[c]++;
}

void HT::Huffman::generateHuffmanCodes(HT::Node *node, std::wstring code){
    if(!node) return;
    if(charFrequencies.count(node->getCharacter()) && !node->getLeftNode() && !node->getRightNode()){
        huffmanCodes[node->getCharacter()]=code;
        huffmanDecodes[code]=node->getCharacter(); 
    }
    Huffman::generateHuffmanCodes(node->getLeftNode(), code+ L"0");
    Huffman::generateHuffmanCodes(node->getRightNode(), code+ L"1");
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
    Huffman::generateHuffmanCodes(root, L"");
}

[[nodiscard]] std::wstring HT::Huffman::getEncodedText() noexcept{
    std::wstring ans= L"";
    for(const wchar_t &c:text)
        ans+=huffmanCodes[c];
    return ans;
}

[[nodiscard]]std::wstring HT::Huffman::getDecodedText() noexcept{
    std::wstring ans= L"";
    std::wstring code= L"";
    std::wstring encoded = getEncodedText();
    for(const wchar_t &c: encoded){
        code+=c;
        if(huffmanDecodes.count(code)){
            ans+=huffmanDecodes[code];
            code= L"";
        }
    }
    return ans;
}

void HT::Huffman::showTable() const noexcept{
    std::wcout << L"-----TABELA-----\n";
    for(const auto &c: huffmanCodes)
        std::wcout << c.first << L" = " << c.second << std::endl;
    std::wcout << L"----------------\n";
}


void HT::Huffman::deleteRoot(Node *root){
    if(!root) return;
    deleteRoot(root->getLeftNode());
    deleteRoot(root->getRightNode());
    delete root;
}

HT::Huffman::~Huffman(){deleteRoot(root);} // Método destrutor usando a funcao de deletar como parametro
