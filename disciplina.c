#include <string.h>
#include "disciplina.h"

// Inicializa a Disciplina
Disciplina* criar_disciplina(char* codigo, char* nome, char* professor, int carga, int alunos) {
	// Validação básica dos dados de entrada
	if (!codigo || !nome || !professor || carga <= 0 || alunos < 0) return NULL;

	// Aloca memória
	Disciplina* d = (Disciplina*)malloc(sizeof(Disciplina));

	// Copia os dados para a nova estrutura.
	strcpy(d->codigo, codigo);
	strcpy(d->nome, nome);
	strcpy(d->professor, professor);
	d->carga_horaria = carga;
	d->quantidade_alunos = alunos;
	d->favorita = 0; // Por padrao, uma nova disciplina não é favorita
	return d;
}

//Imprime as informacoes de Disciplina
void imprimir_disciplina(void* info) {
	Disciplina* d = (Disciplina*)info; // Converte o ponteiro genérico para o tipo Disciplina
	printf("[%s] %s - Professor: %s, Carga: %d, Alunos: %d %s\n",
	       d->codigo, d->nome, d->professor, d->carga_horaria,
	       d->quantidade_alunos, d->favorita ? "(FAVORITA)" : ""); // Operador para mostrar se é favorita
}


//Libera a Disciplina
void liberar_disciplina(void* info) {
	if (info) free(info); // Libera a memória do ponteiro se ele não for nulo.
}


 //Encontra uma disciplina pelo codigo e favorita
void favorito_disciplina(Lista* cursos, const char* siglaCurso, const char* codigoDisciplina) {
	No* atual = cursos->inicio;
	Curso* curso = NULL;

	//Encontrar o curso pela sigla
	while (atual) {
		Curso* c = (Curso*)atual->info;
		if (strcmp(c->sigla, siglaCurso) == 0) {
			curso = c; // Curso encontrado
			break;
		}
		atual = atual->prox;
	}

	if (!curso) {
		printf("Curso não encontrado.\n");
		return;
	}

	//Encontrar a disciplina dentro da lista de disciplinas do curso.
	No* disc_no = curso->disciplinas->inicio;
	while (disc_no) {
		Disciplina* d = (Disciplina*)disc_no->info;
		if (strcmp(d->codigo, codigoDisciplina) == 0) {
			d->favorita = !d->favorita; // Inverte o valor 0 para 1 ou 1 para 0
			printf("Disciplina '%s' %s como favorita.\n",
			       codigoDisciplina, d->favorita ? "marcada" : "desmarcada");
			return; // Termina a função após encontrar e alterar
		}
		disc_no = disc_no->prox;
	}

	printf("Disciplina não encontrada.\n");
}


 //Imprime todas as disciplinas favoritas
void listar_disciplinas_favoritas(Lista* cursos) {
	No* atual = cursos->inicio;
	int encontrou = 0; //para saber se pelo menos uma foi encontrada.

	// percorre a lista de cursos.
	while (atual) {
		Curso* c = (Curso*)atual->info;
		No* disc_no = c->disciplinas->inicio;

		//percorre a lista de disciplinas de cada curso.
		while (disc_no) {
			Disciplina* d = (Disciplina*)disc_no->info;
			if (d->favorita) {
				imprimir_disciplina(d);
				encontrou = 1;
			}
			disc_no = disc_no->prox;
		}

		atual = atual->prox;
	}

	if (!encontrou) {
		printf("Nenhuma disciplina marcada como favorita.\n");
	}
}

 // imprime as disciplinas com maior numero de alunos
void listar_disciplinas_mais_inscritas(Lista* cursos) {
    No* atual = cursos->inicio;
    int maxAlunos = -1;

    // Descobrir qual é o número máximo de alunos
    while (atual) {
        Curso* c = (Curso*)atual->info;
        No* disc_no = c->disciplinas->inicio;
        while (disc_no) {
            Disciplina* d = (Disciplina*)disc_no->info;
            if (d->quantidade_alunos > maxAlunos) {
                maxAlunos = d->quantidade_alunos; // Atualiza o máximo
            }
            disc_no = disc_no->prox;
        }
        atual = atual->prox;
    }

    if (maxAlunos == -1) {
        printf("Nenhuma disciplina encontrada.\n");
        return;
    }

    // Imprimir todas as disciplinas que têm exatamente esse número máximo de alunos
    printf("Disciplinas com mais inscrições (%d alunos):\n", maxAlunos);
    atual = cursos->inicio;
    while (atual) {
        Curso* c = (Curso*)atual->info;
        No* disc_no = c->disciplinas->inicio;
        while (disc_no) {
            Disciplina* d = (Disciplina*)disc_no->info;
            if (d->quantidade_alunos == maxAlunos) {
                printf("Curso: %s | ", c->sigla); // Mostra o curso para dar contexto
                imprimir_disciplina(d);
            }
            disc_no = disc_no->prox;
        }
        atual = atual->prox;
    }
}


 // Busca uma disciplina especifica e mostra quantos alunos ela tem
void mostrar_alunos_disciplina(Lista* cursos, const char* siglaCurso, const char* codigoDisciplina) {
    No* atual = cursos->inicio;
    Curso* curso = NULL;

    // Procura o curso.
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

    // Procura a disciplina dentro do curso
    No* disc_no = curso->disciplinas->inicio;
    while (disc_no) {
        Disciplina* d = (Disciplina*)disc_no->info;
        if (strcmp(d->codigo, codigoDisciplina) == 0) {
            printf("A disciplina '%s' (%s) tem %d aluno(s) matriculado(s).\n",
                   d->nome, d->codigo, d->quantidade_alunos);
            return; // Encontrou e imprime e sai
        }
        disc_no = disc_no->prox;
    }

    printf("Disciplina '%s' não encontrada no curso '%s'.\n", codigoDisciplina, siglaCurso);
}