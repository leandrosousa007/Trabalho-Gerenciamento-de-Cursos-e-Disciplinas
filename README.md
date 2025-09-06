# Sistema de Gerenciamento de Cursos e Disciplinas

Este é o projeto final da disciplina de **Algoritmos e Estruturas de Dados I (AED I)**. O objetivo foi desenvolver em linguagem C um sistema de console para gerenciar cursos e suas respectivas disciplinas, utilizando como estrutura de dados principal uma lista duplamente encadeada genérica.

## Autores

  * **Leandro Evaristo de Sousa** 
  * **Mateus Alves Viegas** 

## Principais Funcionalidades

O sistema oferece uma gama de funcionalidades para gerenciar a vida acadêmica de uma instituição, divididas em módulos de fácil acesso.

### Gerenciamento de Cursos

  * **Inserção e Remoção:** Adicionar novos cursos ao sistema ou remover cursos existentes de forma segura.
  * **Listagem Completa:** Visualizar todos os cursos cadastrados com suas respectivas informações (sigla, faculdade, vagas).
  * **Favoritos:** Marcar ou desmarcar cursos como "favoritos" para filtragem rápida.

### Gerenciamento de Disciplinas

  * **Adição e Remoção Contextual:** Adicionar ou remover disciplinas diretamente de um curso específico.
  * **Listagem por Curso:** Visualizar todas as disciplinas pertencentes a um determinado curso.
  * **Favoritos:** Marcar ou desmarcar disciplinas como "favoritas".

### Relatórios e Consultas

  * **Visão Geral:** Gerar um relatório completo de todos os cursos e suas respectivas listas de disciplinas.
  * **Filtro de Favoritos:** Listar apenas os cursos ou disciplinas que foram marcados como favoritos.
  * **Análise de Vagas:** Gerar relatórios para identificar:
      * O(s) curso(s) com o maior número total de alunos.
      * A(s) disciplina(s) com o maior número de alunos inscritos.
  * **Consultas Específicas:** Verificar a quantidade total de alunos em um curso ou em uma disciplina específica.

### Persistência de Dados

  * **Carregamento Inicial:** O sistema é capaz de ler e carregar um conjunto de dados pré-definidos a partir de um arquivo `teste.txt` ao ser inicializado, facilitando testes e demonstrações.
