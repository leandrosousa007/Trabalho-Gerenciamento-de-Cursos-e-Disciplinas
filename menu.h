#ifndef MENU_H
#define MENU_H

#include "lista.h"

// --- FUNCOES DE MENU ---

//Menu Principal
void menu_principal(Lista* cursos);

//Menu Cursos
void menu_cursos(Lista* cursos);

//Menu Disciplinas
void menu_disciplinas(Lista* cursos);

//Menu Relatorios
void menu_relatorios(Lista* cursos);


// --- FUNCSO DE CARREGAMENTO DE DADOS ---

//LE um arquivo de texto e insere a lista de cursos e disciplinas.
void carregar_dados_de_arquivo(Lista* cursos);

#endif