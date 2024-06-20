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

auto pt = std::locale("");
void compactar(){
    std::wcout << L"=========== Compactador huffman ===========\n"
               << L"Digite o nome do arquivo que deseja compactar: ";
    std::wstring fn; 
    std::wcin >> fn;
    std::string filename(fn.begin(),fn.end());
    std::wifstream input(filename);
    if(!input){
        std::wcout << "Falha ao abrir o arquivo de entrada!\n";
        exit(1);
    }
    input.imbue(pt);
    std::wcout << L"\nIniciando processo...\n";

    wchar_t input_char;
    std::wstring input_string;

    while(input.get(input_char)) 
        input_string += input_char;
    std::wcout << L"Criando árvore de Huffman...\n";
    HT::huffman huffman = HT::huffman(input_string);

    std::wstring original = huffman.get_decoded_text();
    std::wstring encodedtext = huffman.get_encoded_text();

    HT::file_status file = HT::file_status(filename, huffman.get_encoded_text());
    std::wcout << L"Iniciando processo de compactação...\n";
    HT::compacter comp = HT::compacter(huffman.get_encoded_text() , huffman);
    comp.compactador();

    int op;
    std::wcout << L"Arquivo compactado com sucesso!\n\n";
    while(true){
        std::wcout << L"====== Escolha uma opção ======\n"
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
}

void descompactar(){
    std::wcout << L"Iniciando processo de descompactação...\n";
    HT::descompacter desc = HT::descompacter();
    desc.descompactar();
    std::wcout << L"Arquivo descompactado com sucesso\n";
}



int main(){
    std::locale::global(pt);

    std::wcout << L"Bem vindo ao projeto de Codificação de Huffman!\n\n"
               << L"Escolha a opção abaixo para continuar\n"
               << L"1 - Compactar arquivo (.txt)\n"
               << L"2 - Descompactar arquivo\n\n"
               << L"Digite uma opção válida: ";
    wchar_t op;
    std::wcin >> op;
    while(op != '1' && op != '2'){
        std::wcout << L"\nDigite uma opção válida: ";
        std::wcin >> op;
    }

    if(op == '1')
        compactar();
    else if(op == '2')
        descompactar();

    return 0;
} 