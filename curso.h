#ifndef CURSO_H
#define CURSO_H

#include "lista.h"
#include "disciplina.h" 

// Estrutura que representa um curso
typedef struct {
    char nome[100];
    char sigla[10];
    char faculdade[100];
    int vagas;
    int favorito;       // marcar se o curso é favorito
    Lista* disciplinas; // Ponteiro para uma Lista de Disciplinas
} Curso;

// --- FUNÇÕES ---

// Inicializa um novo curso.
Curso* criar_curso(char* nome, char* sigla, char* faculdade, int vagas);

// Imprime os detalhes de um curso e, em seguida, chama imprimir_lista para suas disciplinas
void imprimir_curso(void* info);

// Libera a memória de um curso, incluindo a destruição de sua lista de disciplinas
void liberar_curso(void* info);

// Alterna o status de favorito de um curso
void favorito_curso(Lista* cursos, const char* sigla);

// Lista todos os cursos marcados como favoritos
void listar_cursos_favoritos(Lista* cursos);

// Encontra e lista o curso com o maior somatorio de alunos em suas disciplinas
void listar_curso_com_mais_alunos(Lista* cursos);

// Mostra o numero total de alunos matriculados em um curso
void mostrar_alunos_curso(Lista* cursos, const char* siglaCurso);

#endif