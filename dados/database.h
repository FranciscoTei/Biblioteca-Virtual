#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 50
#define MAX_BIBLIOTECARIOS 5
#define MAX_LIVROS 100
#define MAX_HISTORICO 100
#define MAX_MENSAGENS 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    char titulo[100];
    char genero[50];
    char autor[100];
    char isbn[20];
    int qtd_disponivel;
    int qtd_total;
} Livro;

typedef struct {
    char matricula[20];
    char nome[100];
    char data_nascimento[11];
    char nacionalidade[50];
    char email[100];
    char senha[50];
    char data_registro[11];
    char cargo[50];
} Usuario;

typedef struct {
    char matricula[20];
    char nome[100];
    char data_nascimento[11];
    char nacionalidade[50];
    char email[100];
    char senha[50];
    char data_registro[11];
    char cargo[50];
} Bibliotecario;

typedef struct {
    char acao[50];
    char data_hora[20];
    char detalhes[255];
    char usuario_responsavel[100];
} Historico;

typedef struct {
    char usuario[100];
    char email[100];
    char mensagem[200];
    char data_hora[20];
    char status[20];
} MensagemSuporte;

typedef struct {
    char matricula_usuario[20];
    char isbn_livro[20];
    char data_emprestimo[11];
    char data_retorno_prevista[11];
} EmprestimoAtivo;

extern Usuario usuarios[MAX_USUARIOS];
extern Bibliotecario bibliotecarios[MAX_BIBLIOTECARIOS];
extern Livro livros[MAX_LIVROS];
extern Historico historico[MAX_HISTORICO];
extern MensagemSuporte mensagens_suporte[MAX_MENSAGENS];
extern EmprestimoAtivo emprestimos_ativos[MAX_EMPRESTIMOS];

extern Usuario usuario;

void load_dados();
void salva_dados();

#endif
