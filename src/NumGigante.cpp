// Funções da classe "NumGigante"
#include <ctype.h>
#include <iostream>

#include "NumGigante.h"

using namespace std;

// Inicia a Lista Encadeada com o valor 0
NumGigante::NumGigante()
{
    tail = head = new Node(0);
    comprimento = 1;
    negativo = false;
    return;
}
// Gera uma Lista Encadeada a partir de uma string
// Cada digito ocupará um Node
NumGigante::NumGigante(string numero)
{
    tail = head = nullptr;
    negativo = false;
    for (char c : numero)
    {
        if (isdigit(c))
        {
            inserirNoFim(c - '0');
        }
    }
    return;
}

// Insere um Node com o valor desejado no início da Lista Encadeada
void NumGigante::inserirNoInicio(int key)
{
    ++comprimento;
    Node *newNode = new Node(key);
    newNode->next = head;
    tail = head = newNode;
    return;
}
// Insere um node com o valor desejado no final da Lista Encadeada
void NumGigante::inserirNoFim(int key)
{
    ++comprimento;
    Node *newNode = new Node(key);
    if (head == nullptr)
    {
        tail = head = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = tail->next;
    }
    return;
}
// Remove um Node do inicio da Lista Encadeada
void NumGigante::removerInicio()
{
    if (head == nullptr)
        return;
    --comprimento;
    Node *next = head->next;
    if (tail == head)
        tail = next;
    delete head;
    head = next;
    return;
}
// Remove Nodes com valor zero no início da Lista Encadeada
void NumGigante::removerZeros()
{
    while (comprimento > 1 && head->key == 0)
    {
        removerInicio();
    }
    return;
}
// Exibe o valor de cada Node na Lista Encadeadada do início ao fim
void NumGigante::exibir()
{
    if (head == nullptr)
    {
        cout << "NULL";
    }
    else
    {
        if (negativo)
            cout << '-';
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->key;
            temp = temp->next;
        }
    }
    return;
}
