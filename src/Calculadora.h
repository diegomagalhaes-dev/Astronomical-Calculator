// Cabeçalhos da classe "Calculadora"
#ifndef CALCULADORA_H
#define CALCULADORA_H

#include "NumGigante.h"

// Calculadora para opereações com números representados por Listas Encadeadas
class Calculadora
{
public:
    // armazena o resultado calculado até o momento
    NumGigante *resultado;
    // memoria para gravar resultados
    NumGigante *memoria;

    Calculadora();

    void exibirMenu();

    NumGigante *validarEntrada();
    void ler();
    void exibir(NumGigante *num);
    void limpar(NumGigante *num);

    void gravarMemoria();

    // OPERAÇÕES
    // as operaçoes pedem um valor de entrada ao usuário, lidam
    // com os diferentes casos possíveis, invocam as funções de
    // operação privadas e corrrigem o sinal do "resultado"
    void adicionar();
    void subtrair();
    void multiplicar();
    NumGigante *maior(NumGigante *a, NumGigante *b);

private:
    // OPERAÇÕES
    // envolvem o "resultado" e a "entrada" desejada
    // o sinal dos numeros nao é modificado nessas funções
    void adicionarPrivado(NumGigante *entrada);
    void subtrairPrivado(NumGigante *entrada);
    void processarSubtracao(NumGigante::Node *maior, NumGigante::Node *menor);
    void multiplicarPrivado(NumGigante *entrada);
};

#endif