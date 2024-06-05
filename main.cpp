#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "src/huffman.cpp"
#include "src/file_status.cpp"
//#include "../../header/Huffman.hpp"

using namespace std;

int main (){
    string filename = "clarissa.txt"; 
    wifstream input(filename);
    wchar_t input_char;
    wstring input_string;

    auto pt = locale("");
    locale::global(pt);
    input.imbue(pt);

    if(!input){
        cout << "Falha ao abrir o arquivo de entrada!\n";
        exit(1);
    }
    
    while (input.get(input_char)) {
        input_string += input_char;
    }
    
    HT::huffman huffman = HT::huffman(input_string); /// O prefixo L precisa ser usado pois trata-se de uma wstring.

    wstring encodedtext = huffman.get_encoded_text();
    
    wstring original = huffman.get_decoded_text();

    // double encoded_size = huffman.get_encoded_text().size()/8.0; // Tamanho em bytes apos compressao
    // double pre_size = input_string.size() * sizeof(wchar_t); // Tamanho antes da compressao
    // double absolute = fabs(((encoded_size - pre_size) / pre_size) * 100);


    HT::file_status file = HT::file_status(filename, huffman.get_encoded_text());
    int op;

    while(true){
        wcout << L"Bem vindo ao projeto de Codificação de Huffman!\n";
        wcout << L"1 - Visualizar a string original\n";
        wcout << L"2 - Visualizar a string em bits\n";
        wcout << L"3 - Visualizar tabela de bits\n";
        wcout << L"4 - Visualizar arvore .dot\n";
        wcout << L"5 - Visualizar diferença entre bytes dos arquivos\n";
        wcout << L"6 - Encerra o programa\n";
        wcout << L"Digite sua opção abaixo: \n";
        wcin >> op;

        switch (op)
        {
        case 1:
            wcout << L"--------------------------\n";
            wcout << L"String original: " << original << endl;
            wcout << L"--------------------------\n";
            break;
        case 2:
            wcout << L"--------------------------\n";
            wcout << L"String em bits: " << encodedtext << endl;
            wcout << L"--------------------------\n";
            break;
        case 3:
            huffman.show_table();
            break;
        case 4:
            huffman.show_tree();
            break;
        case 5:
            // wcout << "--------------------------\n";
            // wcout << "Tamanho antes da codificacao: " << pre_size << " bytes\n";
            // wcout << "Tamanho decodificado: " << encoded_size << " bytes\n";
            // wcout << "Diferenca absoluta " << fixed << setprecision(2)<< absolute << "%\n";
            // wcout << "--------------------------\n";
            wcout << L"--------------------------\n"
                  << L"Tamanho original: " << file.tam_origin() << " bytes\n"
                  << L"Tamanho comprimido: " << file.tam_compressed() << " bytes\n"
                  << L"Diferença de: " << file.diff() << " bytes\n"
                  << L"Diminuiu: " << fixed << setprecision(2) << file.porcent() << "%\n"
                  << L"--------------------------\n";
            break;
        case 6:
            wcout << L"Encerrando o programa...\n";
            exit(0);
        default:
            wcout << L"Opcao inválida!\n";
            wcout << L"--------------------------\n";
            break;
        }
    }

    return 0;
}

/*
RECADO
as funções básicas do funcionamento estão prontas
os .hpp fiz desse jeito

***é preciso implementar o destrutor da árvore, para liberar a memória (feito)

***fazer a main console, pode ser um hubzinho, faz um while e bota as opções (feito -> basico, melhorar)
1- digitar texto ou arquivo a ser aberto
2- mostrar tabela de codificação
3- mostrar texto codificado
4- mostrar texto decodificado

***refatorar o codigo para utilizar o unicode e não a ASCII, a wstring (feito -> apenas cuidar pra usar padrao unicode de agr em diante)

***fazer um gerador de arquivo .dot

***compacter e descompacter não fiz nada to pensando se é valido fazer essas classes

*/