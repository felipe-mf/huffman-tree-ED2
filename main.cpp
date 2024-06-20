/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#include <sys/types.h>
#include <sys/stat.h>
#include "src/huffman.cpp"
#include "src/file_status.cpp"
#include "src/compacter.cpp"
#include "src/descompacter.cpp"
#include <iomanip>
#include <iostream>

int main(){
    std::string filename = "clarissa.txt"; 
    std::wifstream input(filename);
    wchar_t input_char;
    std::wstring input_string;

    auto pt = std::locale("");
    std::locale::global(pt);
    input.imbue(pt);

    if(!input){
        std::cout << "Falha ao abrir o arquivo de entrada!\n";
        exit(1);
    }
    
    while(input.get(input_char)) 
        input_string += input_char;
    
    HT::huffman huffman = HT::huffman(input_string);

    std::wstring encodedtext = huffman.get_encoded_text();
    
    std::wstring original = huffman.get_decoded_text();


    HT::file_status file = HT::file_status(filename, huffman.get_encoded_text());
    int op;

    HT::compacter comp = HT::compacter(encodedtext, huffman);
    comp.compactador();
    HT::descompacter desc = HT::descompacter();
    desc.descompactar();


    while(true){
        std::wcout << L"Bem vindo ao projeto de Codificação de Huffman!\n"
                   << L"1 - Visualizar a string original\n"
                   << L"2 - Visualizar a string em bits\n"
                   << L"3 - Visualizar tabela de bits\n"
                   << L"4 - Visualizar arvore .dot\n"
                   << L"5 - Visualizar diferença entre bytes dos arquivos\n"
                   << L"6 - Encerra o programa\n"
                   << L"Digite sua opção abaixo: \n";
        std::wcin >> op;

        switch (op)
        {
        case 1:
            std::wcout << L"--------------------------\n"
                       << L"String original: " << original << '\n'
                       << L"--------------------------\n";
            break;
        case 2:
            std::wcout << L"--------------------------\n"
                       << L"String em bits: " << encodedtext << '\n'
                       << L"--------------------------\n";
            break;
        case 3:
            huffman.show_table();
            break;
        case 4:
            huffman.show_tree();
            break;
        case 5:
            std::wcout << L"--------------------------\n"
                       << L"Tamanho original: " << file.tam_origin() << " bytes\n"
                       << L"Tamanho comprimido: " << file.tam_compressed() << " bytes\n"
                       << L"Diferença de: " << file.diff() << " bytes\n"
                       << L"Diminuiu: " << std::fixed << std::setprecision(2) << file.porcent() << "%\n"
                       << L"--------------------------\n";
            break;
        case 6:
            std::wcout << L"Encerrando o programa...\n";
            exit(0);
        default:
            std::wcout << L"Opcao inválida!\n"
                       << L"--------------------------\n";
            break;
        }
    }

    return 0;
}