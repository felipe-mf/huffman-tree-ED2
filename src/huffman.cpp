/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/huffman.hpp"


void HT::huffman::fill_char_frequencies_map() noexcept{
    for(const wchar_t &c: text)
        char_frequencies[c]++;
}

void HT::huffman::generate_huffman_codes(HT::node *node, std::wstring code){
    if(!node) return;
    if(char_frequencies.count(node->get_character()) && !node->get_leftnode() && !node->get_rightnode()){
        huffman_codes[node->get_character()]=code; //Insere uma string na posicao do caracter do nodo
        huffman_decodes[code]=node->get_character(); //Insere caracter na posicao da string code
    }
    huffman::generate_huffman_codes(node->get_leftnode(), code+ L"0");
    huffman::generate_huffman_codes(node->get_rightnode(), code+ L"1");
}

void HT::huffman::encoder(){
    std::priority_queue<HT::node*, std::vector<HT::node*>, huffman::cmp> fila;
    for(const auto &c: char_frequencies){
        auto nodo = new HT::node(c.first, c.second, nullptr, nullptr);
        fila.push(nodo);
    }
    while(fila.size() > 1){
        HT::node *left = fila.top();
        fila.pop();
        HT::node *right = fila.top();
        fila.pop();
        int soma = left->get_frequency() + right->get_frequency();
        auto nodo = new HT::node('\n', soma, left, right);
        fila.push(nodo);
    }
    root = fila.top();
    fila.pop();
    huffman::generate_huffman_codes(root, L"");
}

[[nodiscard]] std::wstring HT::huffman::get_encoded_text() noexcept{
    std::wstring ans= L"";
    for(const wchar_t &c:text)
        ans+=huffman_codes[c];
    return ans;
}

[[nodiscard]]std::wstring HT::huffman::get_decoded_text() noexcept{
    std::wstring ans= L"";
    std::wstring code= L"";
    std::wstring encoded = get_encoded_text();
    for(const wchar_t &c: encoded){
        code+=c;
        if(huffman_decodes.count(code)){
            ans+=huffman_decodes[code];
            code= L"";
        }
    }
    return ans;
}

void HT::huffman::show_table() const noexcept{
    std::wcout << L"-----TABELA-----\n";
    for(const auto &c: huffman_codes)
        std::wcout << c.first << L" = " << c.second << std::endl;
    std::wcout << L"----------------\n";
}


void HT::huffman::delete_root(node *root){
    if(!root) return;
    delete_root(root->get_leftnode());
    delete_root(root->get_rightnode());
    delete root;
}

std::wstring HT::huffman::traverse_tree(HT::node *node, std::wstring code, std::wstring ans){
    if(!node) return ans;
    if(node->get_leftnode() || node->get_rightnode()){
        std::wstring aux=L"";
        if(code == L"") aux += L"root";
        aux += code;
        aux+= L"[label=";
        aux+= std::to_wstring(node->get_frequency());
        aux+= L"]\n";
        ans += aux;
    }
    ans = traverse_tree(node->get_leftnode(), code+ L"0", ans);
    ans = traverse_tree(node->get_rightnode(), code+ L"1", ans);
    return ans;
}

void HT::huffman::links(HT::node *node, std::wofstream &dot){
    if(!node) return;
    static std::unordered_map<std::wstring,int>feitos;
    
    links(node->get_leftnode(), dot);
    links(node->get_rightnode(), dot);
    if(huffman_codes.count(node->get_character())){
    std::wstring entrada = huffman_codes[node->get_character()];
    std::wstring saida(1,(node->get_character()));

    while(entrada.size()>0 && entrada!=L"root"){
        entrada.erase(--entrada.end());
        if(entrada == L"") entrada = L"root";
        if(saida == L"" && node->get_leftnode()){
            saida = huffman_codes[node->get_leftnode()->get_character()];
            saida.erase(--saida.end());
        } else if(saida == L"" && node->get_rightnode()){
            saida = huffman_codes[node->get_rightnode()->get_character()];
            saida.erase(--saida.end());
        }
        std::wstring linha = entrada + L" -> " + saida + L"\n";
        if(!feitos.count(linha))
            dot << linha;
        feitos[linha]++;
        saida=entrada;
    }
    }
}



void HT::huffman::show_tree(){
    std::wofstream dot("/tmp/show.dot");
    dot << "digraph{\n";
    dot << "\tedge [label=0];\n";
    dot << "\tgraph [ranksep=0];\n";
    for(const auto &n : huffman_codes){
        dot << "\t"
        << n.first
        << " [shape=record, label=\"{{" << n.first << "|" << char_frequencies[n.first] << "}|" << n.second << "}\"];\n";
    }
    std::wstring ans = traverse_tree(root, L"", L"");
    dot << ans;
    links(root, dot);
    dot << "}\n";
    dot.close();
    system("dot /tmp/show.dot -Tx11");

    }


    HT::huffman::~huffman(){delete_root(root);} // Método destrutor usando a funcao de deletar