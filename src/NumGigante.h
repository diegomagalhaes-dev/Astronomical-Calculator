// Cabeçalhos da classe "NumGigante"
#ifndef NUMGIGANTE_H
#define NUMGIGANTE_H

#include <string>
using namespace std;

// Lista Encadeada para representar valores muito grandes
class NumGigante
{
public:
    // Node da Lista Encadeada
    struct Node
    {
        int key;
        Node *next;

        Node()
        {
            key = 0;
            next = nullptr;
        }
        Node(int _key)
        {
            key = _key;
            next = nullptr;
        }
    };

    // Representa o primeiro Node da Lista Encadeada
    Node *head;
    // Representa o último Node da Lista Encadeada
    Node *tail;

    // Quantidade de nodes na Lista Encadeada
    int comprimento;

    // Verdadeiro quando a Lista Encadeada representar um valor negativo
    bool negativo;

    NumGigante();
    NumGigante(string numero);

    void exibir();

    // Inserção e remoção de Nodes
    void inserirNoInicio(int key);
    void inserirNoFim(int key);
    void removerInicio();
    void removerZeros();
};

#endif