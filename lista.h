#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// --- ESTRUTURAS ---

// Estrutura do Nó da lista.
typedef struct No {
    void* info;         // Ponteiro genérico para armazenar a informação(Curso, Disciplina)
    struct No* ant;     // Ponteiro para o nó anterior na lista.
    struct No* prox;    // Ponteiro para o próximo nó na lista.
} No;

// Estrutura da Lista, que controla toda a coleção de nós(No Descritor)
typedef struct {
    No* inicio;     // Ponteiro para o primeiro nó da lista
    No* fim;        // Ponteiro para o último nó da lista
    int tamanho;    // Armazena o número de elementos na lista para acesso rápido
} Lista;

// --- FUNÇÕES ---

Lista* criar_lista(); // Aloca memória para uma nova lista e a inicializa

// Libera a memória de cada nó e da própria lista.
// Recebe um ponteiro para uma função que sabe como liberar a memória do dado específico (info)
void destruir_lista(Lista** lista_ref, void (liberar_info)(void*));

// Inserção
void inserir_no_fim(Lista* lista, void* info);   // Adiciona um novo elemento no final da lista
void inserir_no_inicio(Lista* lista, void* info);// Adiciona um novo elemento no início da lista

//Remove o primeiro nó da lista que corresponde a um critério de busca
//a lista que o no sera removeido,criterio um ponteiro para o dado de busca, comparar_info ponteiro para func que compara, liberar
int remover_no(Lista* lista, const void* criterio, int (*comparar_info)(const void*, const void*), void (*liberar_info)(void*));


// Impressão
// Percorre a lista e imprime cada elemento.
void imprimir_lista(const Lista* lista, void (imprimir_info)(void*));

#endif