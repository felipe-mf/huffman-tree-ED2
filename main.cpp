#include <bits/stdc++.h>
#include "src/huffman.cpp"
//#include "../../header/Huffman.hpp"

using namespace std;

int main (){
    HT::huffman huffman = HT::huffman(L"aaaabbbccd"); /// O prefixo L precisa ser usado pois trata-se de uma wstring.

    huffman.encoder();
    wstring encodedtext = huffman.get_encoded_text();
    //wcout << "string em bits: " << encodedtext << endl;

    
    wstring original = huffman.get_decoded_text();
    

    int op;

    while(true){
        wcout << "Bem vindo ao projeto de Codificação de Huffman!\n";
        wcout << "1 - Visualizar a string original\n";
        wcout << "2 - Visualizar a string em bits\n";
        wcout << "3 - Visualizar tabela de bits\n";
        wcout << "4 - Encerra o programa\n";
        wcout << "Digite sua opção abaixo: \n";
        wcin >> op;

        switch (op)
        {
        case 1:
            wcout << "--------------------------\n";
            wcout << "String original: " << original << endl;
            wcout << "--------------------------\n";
            break;
        case 2:
            wcout << "--------------------------\n";
            wcout << "String em bits: " << encodedtext << endl;
            wcout << "--------------------------\n";
            break;
        case 3:
            huffman.show_table();
            break;
        case 4:
            wcout << "Encerrando o programa...\n";
            exit(0);
        default:
            wcout << "Opcao inválida!\n";
            wcout << "--------------------------\n";
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