#include "lista.h"

//Inicializa a Lista
Lista* criar_lista() {
    // Aloca memória para a estrutura da lista.
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (!l) return NULL; // Retorna NULL se malloc falhou.

    // Inicializa os ponteiros e o tamanho. Uma lista vazia não aponta para nada.
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    return l;
}

//Insere no fim
void inserir_no_fim(Lista* lista, void* info) {
    if (!lista || !info) return; // Verificação de segurança.

    // Cria (aloca memória para) o novo nó.
    No* novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL; // Como é o último, o próximo é NULL.
    novo->ant = lista->fim; // O anterior a ele é o antigo "fim" da lista.

    if (lista->fim) {
        // Se a lista não estava vazia, o antigo último nó agora aponta para o novo.
        lista->fim->prox = novo;
    } else {
        // Se a lista estava vazia, o início também é o novo nó.
        lista->inicio = novo;
    }
    // Atualiza o ponteiro do fim da lista para o novo nó.
    lista->fim = novo;
    lista->tamanho++; // Incrementa o contador de elementos.
}

//Insere no inicio
void inserir_no_inicio(Lista* lista, void* info) {
    if (!lista || !info) return; // Verificação de segurança.

    // Cria o novo nó.
    No* novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->ant = NULL; // Como é o primeiro, o anterior é NULL.
    novo->prox = lista->inicio; // O próximo dele é o antigo "início" da lista.

    if (lista->inicio) {
        // Se a lista não estava vazia, o antigo primeiro nó agora aponta para o novo (como anterior).
        lista->inicio->ant = novo;
    } else {
        // Se a lista estava vazia, o fim também é o novo nó.
        lista->fim = novo;
    }
    // Atualiza o ponteiro de início da lista para o novo nó.
    lista->inicio = novo;
    lista->tamanho++; // Incrementa o tamanho.
}

//Remove o primeiro no da lista que corresponde a um criterio de busca
int remover_no(Lista* lista, const void* criterio, int (*comparar_info)(const void*, const void*), void (*liberar_info)(void*)) {
    if (!lista || !criterio || !comparar_info) return 0;

    No* atual = lista->inicio;
    while (atual) {
        // Usa a função de callback para verificar se o item atual é o que procuramos
        if (comparar_info(atual->info, criterio) == 0) {
            // Se encontrou, agora vamos ajustar os ponteiros da lista
            
            if (atual->ant) {
                // Não é o primeiro no
                atual->ant->prox = atual->prox;
            } else {
                // É o primeiro nó, então o início da lista muda
                lista->inicio = atual->prox;
            }

            if (atual->prox) {
                // Não é o último nó
                atual->prox->ant = atual->ant;
            } else {
                // É o último nó, então o fim da lista muda
                lista->fim = atual->ant;
            }

            // Libera a memória do dado (info) usando a função
            if (liberar_info) {
                liberar_info(atual->info);
            }
            
            // Libera a memória do nó 
            free(atual);
            lista->tamanho--;
            
            return 1; //  item removido
        }
        atual = atual->prox;
    }

    return 0; // Item não encontrado
}

//Percorre a lista e imprime cada elemento usando uma função fornecida.
void imprimir_lista(const Lista* lista, void (imprimir_info)(void*)) {
    if (!lista) return;
    No* atual = lista->inicio; // Começa pelo primeiro nó.
    while (atual) { // Enquanto não chegar ao fim da lista (NULL).
        imprimir_info(atual->info); // Chama a função específica para imprimir o dado.
        atual = atual->prox; // Avança para o próximo nó.
    }
}

//Libera toda a lista
void destruir_lista(Lista** lista_ref, void (liberar_info)(void*)) {
    if (!lista_ref || !(*lista_ref)) return;

    No* atual = (*lista_ref)->inicio; // Começa pelo início da lista.
    while (atual) {
        No* temp = atual; // Guarda o nó atual.
        atual = atual->prox; // Avança para o próximo, antes de apagar o atual.

        if (liberar_info) {
            // Se foi fornecida uma função para liberar a 'info', chama-a.
            liberar_info(temp->info);
        }
        free(temp); // Libera a memória do nó em si.
    }
    free(*lista_ref); // Libera a memória da estrutura da lista.
    *lista_ref = NULL; // Define o ponteiro original como NULL para evitar uso após liberação.
}