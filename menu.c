#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "menu.h"       
#include "curso.h"      
#include "disciplina.h" 

//Função para comparar um curso com uma sigla
int comparar_curso_por_sigla(const void* curso_info, const void* sigla) {
    const Curso* c = (const Curso*)curso_info;
    const char* s = (const char*)sigla;
    return strcmp(c->sigla, s);
}

//Função de para comparar uma disciplina com um código
int comparar_disciplina_por_codigo(const void* disciplina_info, const void* codigo) {
    const Disciplina* d = (const Disciplina*)disciplina_info;
    const char* c = (const char*)codigo;
    return strcmp(d->codigo, c);
}

// --------------------- MENUS ---------------------

void menu_principal(Lista* cursos) {
    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Gerenciar Cursos\n");
        printf("2. Gerenciar Disciplinas\n");
        printf("3. Relatórios\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1: menu_cursos(cursos); break;
            case 2: menu_disciplinas(cursos); break;
            case 3: menu_relatorios(cursos); break;
            case 0: break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// --------------------- MENU CURSOS ---------------------

void menu_cursos(Lista* cursos) {
    int opcao;
    char nome[100], sigla[10], faculdade[100];
    int vagas;

    do {
        printf("\n=== GERENCIAR CURSOS ===\n");
        printf("1. Inserir Curso\n");
        printf("2. Listar Cursos\n");
        printf("3. Favoritar Curso\n");
        printf("4. Remover Curso\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome do curso: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;

                printf("Faculdade: ");
                fgets(faculdade, sizeof(faculdade), stdin);
                faculdade[strcspn(faculdade, "\n")] = 0;

                printf("Vagas: ");
                scanf("%d", &vagas);
                getchar();

                // Cria e insere curso
                {
                    Curso* c = criar_curso(nome, sigla, faculdade, vagas);
                    if (c) {
                        inserir_no_fim(cursos, c);
                        printf("Curso '%s' inserido com sucesso!\n", sigla);
                    } else {
                        printf("Erro ao criar curso.\n");
                    }
                }
                break;

            case 2:
                printf("\n=== LISTA DE CURSOS ===\n");
                imprimir_lista(cursos, imprimir_curso);
                break;

            case 3:
                printf("Digite a sigla do curso para favoritar/desfavoritar: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;
                favorito_curso(cursos, sigla);
                break;
                
            case 4: 
                printf("Digite a SIGLA do curso a ser removido: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;

                if (remover_no(cursos, sigla, comparar_curso_por_sigla, liberar_curso)) {
                    printf("Curso '%s' removido com sucesso!\n", sigla);
                } else {
                    printf("Curso '%s' não encontrado.\n", sigla);
                }
                break;
        
        }

    } while (opcao != 0);
}

// --------------------- MENU DISCIPLINAS ---------------------

void menu_disciplinas(Lista* cursos) {
    int opcao;
    char sigla[10], codigo[20], nome[100], professor[100];
    int carga, alunos;

    do {
        printf("\n=== GERENCIAR DISCIPLINAS ===\n");
        printf("1. Inserir Disciplina em Curso\n");
        printf("2. Listar Disciplinas de Curso\n");
        printf("3. Favoritar Disciplina\n");
        printf("4. Remover Disciplina de Curso\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;

                // Encontrar curso
                {
                    No* atual = cursos->inicio;
                    Curso* curso = NULL;
                    while (atual) {
                        Curso* c = (Curso*)atual->info;
                        if (strcmp(c->sigla, sigla) == 0) {
                            curso = c;
                            break;
                        }
                        atual = atual->prox;
                    }
                    if (!curso) { printf("Curso não encontrado.\n"); break; }

                    printf("Código da disciplina: ");
                    fgets(codigo, sizeof(codigo), stdin);
                    codigo[strcspn(codigo, "\n")] = 0;

                    printf("Nome da disciplina: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    printf("Professor: ");
                    fgets(professor, sizeof(professor), stdin);
                    professor[strcspn(professor, "\n")] = 0;

                    printf("Carga horária: ");
                    scanf("%d", &carga);

                    printf("Quantidade de alunos: ");
                    scanf("%d", &alunos);
                    getchar();

                    Disciplina* d = criar_disciplina(codigo, nome, professor, carga, alunos);
                    if (d) {
                        inserir_no_fim(curso->disciplinas, d);
                        printf("Disciplina '%s' inserida com sucesso!\n", codigo);
                    }
                }
                break;

            case 2:
                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;

                {
                    No* atual = cursos->inicio;
                    Curso* curso = NULL;
                    while (atual) {
                        Curso* c = (Curso*)atual->info;
                        if (strcmp(c->sigla, sigla) == 0) {
                            curso = c;
                            break;
                        }
                        atual = atual->prox;
                    }
                    if (!curso) { printf("Curso não encontrado.\n"); break; }
                    printf("\n=== DISCIPLINAS DO CURSO %s ===\n", curso->sigla);
                    imprimir_lista(curso->disciplinas, imprimir_disciplina);
                }
                break;

            case 3:
                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;

                printf("Código da disciplina: ");
                fgets(codigo, sizeof(codigo), stdin);
                codigo[strcspn(codigo, "\n")] = 0;
                favorito_disciplina(cursos, sigla, codigo);
                break;
                
            case 4: 
                printf("Digite a sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;
                
                //encontrar o curso
                No* no_curso = cursos->inicio;
                Curso* curso_encontrado = NULL;
                while(no_curso){
                    Curso* c = (Curso*)no_curso->info;
                    if(strcmp(c->sigla, sigla) == 0){
                        curso_encontrado = c;
                        break;
                    }
                    no_curso = no_curso->prox;
                }

                if (!curso_encontrado) {
                    printf("Curso '%s' não encontrado.\n", sigla);
                    break;
                }

                printf("Digite o CÓDIGO da disciplina a ser removida: ");
                fgets(codigo, sizeof(codigo), stdin);
                codigo[strcspn(codigo, "\n")] = 0;

                if (remover_no(curso_encontrado->disciplinas, codigo, comparar_disciplina_por_codigo, liberar_disciplina)) {
                    printf("Disciplina '%s' removida com sucesso do curso '%s'!\n", codigo, sigla);
                } else {
                    printf("Disciplina '%s' não encontrada no curso '%s'.\n", codigo, sigla);
                }
                break;
        }

    } while (opcao != 0);
}

// --------------------- MENU RELATÓRIOS ---------------------

void menu_relatorios(Lista* cursos) {
    int opcao;
    char sigla[10], codigo[20];
    do {
        printf("\n=== RELATÓRIOS ===\n");
        printf("1. Listar todos os cursos e disciplinas\n");
        printf("2. Cursos favoritos\n");
        printf("3. Disciplinas favoritas\n");
        printf("4. Disciplinas mais inscritas\n");
        printf("5. Curso com mais alunos\n");
        printf("6. Quantidade de alunos na disciplina\n");
        printf("7. Quantidade de alunos no curso\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                imprimir_lista(cursos, imprimir_curso);
                break;

            case 2:
                printf("\n=== CURSOS FAVORITOS ===\n");
                listar_cursos_favoritos(cursos);
                break;

            case 3:
                printf("\n=== DISCIPLINAS FAVORITAS ===\n");
                listar_disciplinas_favoritas(cursos);
                break;
                
            case 4:
                printf("\n=== DISCIPLINAS MAIS INSCRITAS ===\n");
                listar_disciplinas_mais_inscritas(cursos);
                break;
                
            case 5:
                printf("\n=== CURSO COM MAIS ALUNOS ===\n");
                listar_curso_com_mais_alunos(cursos);
                break;   
                
            case 6:
                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;
                printf("Código da disciplina: ");
                fgets(codigo, sizeof(codigo), stdin);
                codigo[strcspn(codigo, "\n")] = 0;
                mostrar_alunos_disciplina(cursos, sigla, codigo);
                break;
                
            case 7: {
                printf("Sigla do curso: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = 0;
                mostrar_alunos_curso(cursos, sigla);
                break;
            }
        }
    } while (opcao != 0);
}


// --------------------- CARREGAR DADOS DE ARQUIVO ---------------------

void carregar_dados_de_arquivo(Lista* cursos) {
    FILE* arquivo = fopen("teste.txt", "r");
    if (!arquivo) {
        printf("Arquivo 'teste.txt' não encontrado. Iniciando com dados vazios.\n");
        return;
    }

    char linha[512];
    Curso* ultimo_curso = NULL;

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove o '\n' do final da linha, se houver
        linha[strcspn(linha, "\n")] = 0;
        
        // Pega o primeiro caractere para decidir se é Curso ou Disciplina
        char* tipo = strtok(linha, ";");
        if (!tipo) continue; // Linha vazia

        if (strcmp(tipo, "C") == 0) { // É um curso
            char* nome = strtok(NULL, ";");
            char* sigla = strtok(NULL, ";");
            char* faculdade = strtok(NULL, ";");
            int vagas = atoi(strtok(NULL, ";"));

            if (nome && sigla && faculdade && vagas > 0) {
                Curso* c = criar_curso(nome, sigla, faculdade, vagas);
                if (c) {
                    inserir_no_fim(cursos, c);
                    ultimo_curso = c; // Guarda referência ao último curso adicionado
                }
            }
        } else if (strcmp(tipo, "D") == 0) { // É uma disciplina
            if (!ultimo_curso) continue; // Ignora disciplina se não houver um curso para associar

            char* codigo = strtok(NULL, ";");
            char* nome = strtok(NULL, ";");
            char* professor = strtok(NULL, ";");
            int carga = atoi(strtok(NULL, ";"));
            int alunos = atoi(strtok(NULL, ";"));

            if (codigo && nome && professor && carga > 0 && alunos >= 0) {
                Disciplina* d = criar_disciplina(codigo, nome, professor, carga, alunos);
                if (d) {
                    // Adiciona a disciplina na lista do último curso lido
                    inserir_no_fim(ultimo_curso->disciplinas, d);
                }
            }
        }
    }

    fclose(arquivo);
    printf("Dados carregados de 'teste.txt' com sucesso!\n");
}