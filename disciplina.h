#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "lista.h"
#include "curso.h" 

// Estrutura que representa uma disciplina.
typedef struct {
    char codigo[20];        // Código único da disciplina
    char nome[100];         // Nome completo da disciplina
    char professor[100];    // Nome do professor
    int carga_horaria;      // Carga horária em horas
    int quantidade_alunos;  // Número de alunos inscritos
    int favorita;           // Marcar se a disciplina é favorita
} Disciplina;

// --- FUNÇÕES ---

// Cria uma nova disciplina
Disciplina* criar_disciplina(char* codigo, char* nome, char* professor, int carga, int alunos);

// Imprime os detalhes de uma disciplina
void imprimir_disciplina(void* info);

// Libera a memória de uma disciplina 
void liberar_disciplina(void* info);

// Alterna o status de favorita de uma disciplina específica dentro de um curso
void favorito_disciplina(Lista* cursos, const char* siglaCurso, const char* codigoDisciplina);

// Percorre todos os cursos e lista todas as disciplinas marcadas como favoritas
void listar_disciplinas_favoritas(Lista* cursos);

// Encontra e lista a disciplina com o maior número de alunos inscritos
void listar_disciplinas_mais_inscritas(Lista* cursos);

// Mostra a quantidade de alunos para uma disciplina específica em um curso
void mostrar_alunos_disciplina(Lista* cursos, const char* siglaCurso, const char* codigoDisciplina);

#endif