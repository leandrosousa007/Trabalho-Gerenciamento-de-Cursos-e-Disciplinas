#include "curso.h"
#include <string.h>

//Inicializa o Curso
Curso* criar_curso(char* nome, char* sigla, char* faculdade, int vagas) {
    if (!nome || !sigla || !faculdade || vagas <= 0) return NULL;
    Curso* c = (Curso*)malloc(sizeof(Curso));
    strcpy(c->nome, nome);
    strcpy(c->sigla, sigla);
    strcpy(c->faculdade, faculdade);
    c->vagas = vagas;
    c->favorito = 0; // Por padrao, não é favorito
    c->disciplinas = criar_lista(); // Um novo curso começa com uma lista de disciplinas vazia
    return c;
}

//Imprime as informações de um curso e depois lista todas as suas disciplinas
void imprimir_curso(void* info) {
    Curso* c = (Curso*)info;
    printf("\n----------------------------------------\n");
    printf("%s (%s) - %s, Vagas: %d %s\n",
           c->nome, c->sigla, c->faculdade, c->vagas,
           c->favorito ? "(FAVORITO)" : "");
    if (c->disciplinas && c->disciplinas->tamanho > 0) {
        printf(" Disciplinas:\n");
        imprimir_lista(c->disciplinas, imprimir_disciplina); // Reutiliza a função de imprimir lista
    } else {
        printf(" Nenhuma disciplina cadastrada.\n");
    }
    printf("----------------------------------------\n");
}

//Libera a memória alocada para um curso
void liberar_curso(void* info) {
    if (!info) return;
    Curso* c = (Curso*)info;
    // destruir a lista de disciplinas ANTES de liberar o curso
    destruir_lista(&c->disciplinas, liberar_disciplina);
    free(c); // Agora libera a estrutura do curso
}

 //Encontra um curso pela sigla e alterna seu status de favorito
void favorito_curso(Lista* cursos, const char* sigla) {
    No* atual = cursos->inicio;

    while (atual) {
        Curso* c = (Curso*)atual->info;
        if (strcmp(c->sigla, sigla) == 0) {
            c->favorito = !c->favorito; // Inverte o valor de favorito
            printf("Curso '%s' %s como favorito.\n",
                   sigla, c->favorito ? "marcado" : "desmarcado");
            return; // Termina a função
        }
        atual = atual->prox;
    }

    printf("Curso não encontrado.\n");
}

//Imprime os cursos favoritos
void listar_cursos_favoritos(Lista* cursos) {
    No* atual = cursos->inicio;
    int encontrou = 0;

    while (atual) {
        Curso* c = (Curso*)atual->info;
        if (c->favorito) {
            imprimir_curso(c);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if (!encontrou) {
        printf("Nenhum curso marcado como favorito.\n");
    }
}

//Calcula a soma total de alunos de todas as disciplinas de um curso
int calcular_total_alunos(Curso* curso) {
    int total = 0;
    No* disc_no = curso->disciplinas->inicio;
    while (disc_no) {
        Disciplina* d = (Disciplina*)disc_no->info;
        total += d->quantidade_alunos; // Acumula o numero de alunos de cada disciplina
        disc_no = disc_no->prox;
    }
    return total;
}

//Encontra e lista o curso com o maior numero total de alunos.
void listar_curso_com_mais_alunos(Lista* cursos) {
    No* atual = cursos->inicio;
    int maxAlunos = -1;

    //Encontra o numero maximo de alunos em um unico curso
    while (atual) {
        Curso* c = (Curso*)atual->info;
        int totalAlunos = calcular_total_alunos(c); // Funcao auxiliar para obter o total

        if (totalAlunos > maxAlunos) {
            maxAlunos = totalAlunos;
        }
        atual = atual->prox;
    }

    if (maxAlunos == -1) {
        printf("Nenhum curso encontrado.\n");
        return;
    }

    //Imprime todos os cursos que tem esse numero maximo de alunos.
    printf("Curso(s) com mais alunos (%d no total):\n", maxAlunos);
    atual = cursos->inicio;
    while (atual) {
        Curso* c = (Curso*)atual->info;
        int totalAlunos = calcular_total_alunos(c);

        if (totalAlunos == maxAlunos) {
            imprimir_curso(c);
        }
        atual = atual->prox;
    }
}


 //Mostra o total de alunos para um curso especifico
void mostrar_alunos_curso(Lista* cursos, const char* siglaCurso) {
    No* atual = cursos->inicio;
    Curso* curso = NULL;

    // Procura o curso pela sigla
    while (atual) {
        Curso* c = (Curso*)atual->info;
        if (strcmp(c->sigla, siglaCurso) == 0) {
            curso = c;
            break;
        }
        atual = atual->prox;
    }

    if (!curso) {
        printf("Curso '%s' não encontrado.\n", siglaCurso);
        return;
    }

    // Se encontrou, calcula e imprime o total de alunos
    int totalAlunos = calcular_total_alunos(curso);
    printf("O curso '%s' tem %d aluno(s) matriculado(s) no total.\n",
           curso->nome, totalAlunos);
}