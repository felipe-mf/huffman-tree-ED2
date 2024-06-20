/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include "../headers/huffman.hpp"

// Pode ser inline
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

void HT::huffman::traverse_tree(HT::node *node, std::wstring code, std::wofstream &dot, std::unordered_map<std::wstring,std::wstring>&traverses, std::wstring dir) noexcept{
    if(!node) return;
    if(node->get_leftnode() || node->get_rightnode()){
        std::wstring ans=L"";
        ans+=L"\"";
        if(code == L"") ans += L"root";
        ans += L"" + code + L"\"" + L"[label=" + std::to_wstring(node->get_frequency()) + L"]\n";
        dot << ans;
        traverses[code] = dir;
    }
    traverse_tree(node->get_leftnode(), code+ L"0", dot, traverses, L"0");
    traverse_tree(node->get_rightnode(), code+ L"1", dot, traverses, L"1");
    return;
}

void HT::huffman::links(HT::node *node, std::wofstream &dot, std::wstring dir, std::unordered_map<std::wstring, std::wstring>&traverses, std::unordered_map<std::wstring,int>&feitos)noexcept{
    if(!node) return;
    
    links(node->get_leftnode(), dot, L"0", traverses, feitos);
    links(node->get_rightnode(), dot, L"1", traverses, feitos);
    if(huffman_codes.count(node->get_character())){
    std::wstring entrada = huffman_codes[node->get_character()];
    std::wstring saida(1,(node->get_character()));

    while(entrada.size()>0 && entrada!=L"root"){
        entrada.erase(--entrada.end());
        if(entrada == L"") entrada = L"root";
        if(saida == L" ") saida = L"SPACE";
        else if(iscntrl(saida[0])) saida = L"ENDL";
        else if(saida == L"\"") saida = L"2ASPAS";
        else if(saida == L"\'") saida = L"ASPAS";

        if(traverses.count(saida)) dir = traverses[saida];
        std::wstring linha = L"" + entrada + L" -> \"" + saida + L"\"[label=" + dir + L"]\n";
        std::wstring linha_feita = L" -> \"" + saida + L"\"";
        saida=entrada;
        if(!feitos.count(linha_feita)){
            feitos[linha_feita]++;
            dot << linha;
        }
        
    }
    }
}

void HT::huffman::show_tree()noexcept{
    std::wofstream dot("show.dot");
    dot << "digraph{\n";
    dot << "\tedge [label=0];\n";
    dot << "\tgraph [ranksep=0];\n";
    for(const auto &n : huffman_codes){
        std::wstring c(1,n.first);
        if(c == L" ") c = L"SPACE";
        else if(iscntrl(n.first)) c = L"ENDL";
        else if(c == L"\"") c = L"2ASPAS";
        else if(c == L"\'") c = L"ASPAS";
        std::wstring c_label = c;
        if(c_label == L"{") c_label = L"\\{";
        if(c_label == L">") c_label = L"\\>";

        dot << "\t\""
        << c
        << "\" [shape=record, label=\"{{" << c_label << "|" << char_frequencies[n.first] << "}|" << n.second << "}\"];\n";
    }
    std::unordered_map<std::wstring, std::wstring> traverses;
    std::unordered_map<std::wstring,int>feitos;
    traverse_tree(root, L"", dot, traverses, L"0");
    links(root, dot, L"0", traverses, feitos);
    dot << "}\n";
    dot.close();
    system("dot show.dot -Tx11");

    }


    HT::huffman::~huffman(){ delete_root(root); } // Método destrutor usando a funcao de deletar