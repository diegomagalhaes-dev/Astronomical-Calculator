// Funções da classe "Calculadora"
#include "NumGigante.h"
#include <iostream>
#include <stack>

using namespace std;

#include "Calculadora.h"
#include "NumGigante.cpp"

// Inicializa o "resultado" e a "memoria"
Calculadora::Calculadora()
{
    resultado = new NumGigante();
    memoria = new NumGigante();
    return;
}

// Exibe o menu de funcionalidades da calculadora
void Calculadora::exibirMenu()
{
    cout << "= Ler        | *  Multiplicar" << endl;
    cout << "? Exibir     | m= Guardar na memória" << endl;
    cout << "# Limpar     | m? Exibir memória" << endl;
    cout << "+ Adicionar  | m# Limpar memória" << endl;
    cout << "- Subtrair   | x  Encerrar" << endl
         << endl;
    return;
}

// Gera um número gigante a partir da string digitada pelo usuário
// Retorna a "memoria" se a string digitada corresponde à "m"
NumGigante *Calculadora::validarEntrada()
{
    string entrada;
    cout << "Entrada: ";
    getline(cin, entrada);

    if (entrada == "m")
        return memoria;
    return new NumGigante(entrada);
}
// Destrói o resultado e o reinicia com o valor digitado pelo usuário
void Calculadora::ler()
{
    limpar(resultado);
    adicionar();
    return;
}
// Imprime o NumGigante na tela
void Calculadora::exibir(NumGigante *num)
{
    num->exibir();
    cout << endl;
    return;
}
// Destroi o NumGigante e reinicia seu valor para 0
void Calculadora::limpar(NumGigante *num)
{
    delete num;
    num = new NumGigante();
    return;
}

// Copia o NumGigante "resultado" para a "memoria"
void Calculadora::gravarMemoria()
{
    NumGigante::Node *temp = resultado->head;
    limpar(memoria);
    while (temp != nullptr)
    {
        memoria->inserirNoFim(temp->key);
        temp = temp->next;
    }
    memoria->negativo = resultado->negativo;
    memoria->removerInicio();
    return;
}

// Lida com os diferentes casos na adição
void Calculadora::adicionar()
{
    NumGigante *entrada = validarEntrada();
    bool resultadoMaior = maior(resultado, entrada) == resultado;

    if (resultado->negativo)
    {
        if (entrada->negativo)
        { // - a - b
            adicionarPrivado(entrada);
        }
        else
        { // - a + b
            subtrairPrivado(entrada);
            resultado->negativo = resultadoMaior;
        }
    }
    else
    {
        if (entrada->negativo)
        { // a - b
            subtrairPrivado(entrada);
            resultado->negativo = !resultadoMaior;
        }
        else
        { // a + b
            adicionarPrivado(entrada);
        }
    }
    return;
}
// Lida com os diferentes casos na subtração
void Calculadora::subtrair()
{
    NumGigante *entrada = validarEntrada();
    NumGigante *maiorNumero = maior(resultado, entrada);

    if (resultado->negativo)
    {
        if (entrada->negativo)
        { // - a + b
            subtrairPrivado(entrada);
        }
        else
        { // - a - b
            adicionarPrivado(entrada);
        }
    }
    else
    {
        if (entrada->negativo)
        { // a + b
            adicionarPrivado(entrada);
        }
        else
        { // a - b
            subtrairPrivado(entrada);
        }
    }
    return;
}
// Lida com os diferentes casos na multiplicação
void Calculadora::multiplicar()
{
    NumGigante *entrada = validarEntrada();

    // o resultado será negativo em caso de sinais diferentes
    if (resultado->negativo == entrada->negativo)
    {
        resultado->negativo = false;
    }
    else
    {
        resultado->negativo = true;
    }
    multiplicarPrivado(entrada);
    resultado->removerZeros();
    return;
}

// Adiciona o NumGigante "entrada" ao "resultado"
void Calculadora::adicionarPrivado(NumGigante *entrada)
{

    stack<NumGigante::Node *> A;
    // os nodes da "entrada" não serão modificados
    stack<int> B;

    NumGigante::Node *pA = resultado->head;
    NumGigante::Node *pB = entrada->head;

    // coloca os valores de cada NumGigante em uma stack
    while (pA != nullptr)
    {
        A.push(pA);
        pA = pA->next;
    }

    while (pB != nullptr)
    {
        B.push(pB->key);
        pB = pB->next;
    }

    // armazena o valor que sobra caso a soma passe de 9
    int resto = 0;

    // soma os valores das stacks
    while (!A.empty() || !B.empty() || resto != 0)
    {
        NumGigante::Node *soma = nullptr;

        if (!A.empty())
        {
            soma = A.top();
            soma->key += resto;
            A.pop();
        }
        else
        {
            resultado->inserirNoInicio(resto);
            soma = resultado->head;
        }

        if (!B.empty())
        {
            soma->key += B.top();
            B.pop();
        }

        if (soma->key > 9)
        {
            resto = soma->key / 10;
            soma->key = soma->key % 10;
        }
        else
            resto = 0;
    }
    return;
}
// Prepara o NumGigante "resultado" e "entrada" para subtração
void Calculadora::subtrairPrivado(NumGigante *entrada)
{
    int diferenca = resultado->comprimento - entrada->comprimento;
    NumGigante::Node *maior = nullptr, *menor = nullptr;

    // se ouver diferença no comprimento dos NumGigante
    // cria nodes com valor zero para igualar o comprimento
    if (diferenca != 0)
    {
        if (diferenca > 0)
        {
            while (diferenca > 0)
            {
                entrada->inserirNoInicio(0);
                --diferenca;
            }
            maior = resultado->head;
            menor = entrada->head;
        }
        else
        {
            while (diferenca < 0)
            {
                resultado->inserirNoInicio(0);
                ++diferenca;
            }
            maior = entrada->head;
            menor = resultado->head;
        }
    }
    else
    {
        // se os NumGigante tem o mesmo tamanho
        // descobre qual tem maior valor
        //(independente do sinal)
        NumGigante::Node *pA = resultado->head, *pB = entrada->head;
        while (pA != nullptr && pB != nullptr)
        {
            if (pA->key != pB->key)
            {
                maior = pA->key > pB->key ? resultado->head : entrada->head;
                menor = pA->key < pB->key ? resultado->head : entrada->head;
                break;
            }
            pA = pA->next;
            pB = pB->next;
        }
        if (maior == menor)
        {
            limpar(resultado);
            return;
        }
    }

    // subtrai o menor do maior
    processarSubtracao(maior, menor);

    // corrige os ponteiros
    if (menor == resultado->head)
    {
        if (entrada != memoria)
            entrada->head = menor;
        resultado->head = maior;
        resultado->negativo = true;
    }

    // remove zeros do inicio dos NumGigante
    resultado->removerZeros();
    entrada->removerZeros();

    return;
}
// Subtrai o NumGigante "menor" do "maior"
void Calculadora::processarSubtracao(NumGigante::Node *maior,
                                     NumGigante::Node *menor)
{
    stack<NumGigante::Node *> A;
    // os Nodes do "menor" não serão modificados
    stack<int> B;

    NumGigante::Node *pA = maior;
    NumGigante::Node *pB = menor;

    // coloca os valores de cada NumGigante em uma Stack
    while (pA != nullptr)
    {
        A.push(pA);
        pA = pA->next;
    }

    while (pB != nullptr)
    {
        B.push(pB->key);
        pB = pB->next;
    }

    // verdadeiro quando o digito minuendo for menor que o subtraendo,
    // precisando "emprestar" +10 do pŕoximo digito
    bool emprestou = false;

    // subtrai os valores da stack
    while (!A.empty())
    {
        NumGigante::Node *sub = A.top();
        int digito1 = sub->key;
        int digito2 = B.top();
        A.pop();
        B.pop();

        if (emprestou)
        {
            --digito1;
            emprestou = false;
        }

        if (digito1 < digito2)
        {
            digito1 += 10;
            emprestou = true;
        }

        sub->key = digito1 - digito2;
    }

    return;
}
// Multiplica o NumGigante "resultado" pela "entrada"
void Calculadora::multiplicarPrivado(NumGigante *entrada)
{
    stack<int> A; // Representa o multiplicando
    stack<int> B; // Representa o multiplicador

    NumGigante::Node *pA = resultado->head;
    NumGigante::Node *pB = entrada->head;

    // coloca os valores de cada NumGigante em uma stack
    while (pA != nullptr)
    {
        A.push(pA->key);
        pA = pA->next;
    }

    while (pB != nullptr)
    {
        B.push(pB->key);
        pB = pB->next;
    }

    // Reinicia o "resultado" com valor zero
    limpar(resultado);
    // Representa quantos zeros serão adicionado ao produto atual
    int dezena = 0;
    while (!B.empty())
    {
        NumGigante *produto = new NumGigante();
        produto->removerInicio();

        int prod = 0, resto = 0;

        // Adiciona um 0 ("multiplica por 10") ao produto atual
        // De acordo com a dezena do multiplicador
        for (int i = 0; i < dezena; ++i)
        {
            produto->inserirNoInicio(0);
        }
        ++dezena;

        stack<int> temp = A;
        while (!temp.empty())
        {
            prod = (temp.top() * B.top() + resto) % 10;
            resto = (temp.top() * B.top() + resto) / 10;
            produto->inserirNoInicio(prod);
            temp.pop();
        }
        B.pop();

        if (resto != 0)
        {
            produto->inserirNoInicio(resto);
        }

        // Adiciona o produto atual ao resultado
        adicionarPrivado(produto);
    }

    return;
}

// Retorna o maior número gigante entre "a" e "b"
NumGigante *Calculadora::maior(NumGigante *a, NumGigante *b)
{
    if (a->comprimento > b->comprimento)
        return a;

    if (b->comprimento > a->comprimento)
        return b;

    // em caso de comprimento igual compara os valores

    NumGigante::Node *pA = a->head, *pB = b->head;
    NumGigante::Node *maior = nullptr;

    while (pA != nullptr && pB != nullptr)
    {
        if (pA->key != pB->key)
        {
            maior = pA->key > pB->key ? a->head : b->head;
            break;
        }
        pA = pA->next;
        pB = pB->next;
    }

    if (maior == a->head)
        return a;

    return b;
}
