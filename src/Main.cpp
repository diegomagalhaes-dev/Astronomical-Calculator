// Programa para demonstar as funcionalidades da Calculadora
#include <iostream>
#include <string>
#include "Calculadora.cpp"

using namespace std;

int main()
{

    Calculadora calc;
    char opcao = ' ';
    bool encerrar = false;

    while (encerrar == false)
    {
        calc.exibirMenu();

        cout << "Digite uma opcão: ";
        string opcao;
        getline(cin, opcao);

        switch (opcao[0])
        {
        case '=':
            calc.ler();
            break;
        case '?':
            calc.exibir(calc.resultado);
            break;
        case '#':
            calc.limpar(calc.resultado);
            break;
        case '+':
            calc.adicionar();
            break;
        case '-':
            calc.subtrair();
            break;
        case '*':
            calc.multiplicar();
            break;
        case 'm':
        case 'M':
            switch (opcao[1])
            {
            case '=':
                calc.gravarMemoria();
                break;
            case '?':
                calc.exibir(calc.memoria);
                break;
            case '#':
                calc.limpar(calc.memoria);
                break;
            default:
                cout << "Opção Inválida!";
            }
            break;
        case 'x':
        case 'X':
            encerrar = true;
            break;
        default:
            cout << "Opção Inválida!";
        }
        cout << endl;
    }
}