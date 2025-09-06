#include <stdio.h>
#include "lista.h"
#include "curso.h"
#include "menu.h" 

int main() {
    //Cria a estrutura de dados principal
    Lista* cursos = criar_lista();
    
    //Carrega os dados iniciais do arquivo
    carregar_dados_de_arquivo(cursos); 

    printf("\n=== SISTEMA DE GERENCIAMENTO DE CURSOS E DISCIPLINAS ===\n");

    //Inicia a interface com o usuário.
    menu_principal(cursos);

    //Libera toda a memória alocada ao encerrar.
    destruir_lista(&cursos, liberar_curso);
    printf("Sistema encerrado.\n");
    
    return 0;
}