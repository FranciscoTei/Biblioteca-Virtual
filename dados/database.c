#include "database.h"

Usuario usuarios[MAX_USUARIOS];
Bibliotecario bibliotecarios[MAX_BIBLIOTECARIOS];
Livro livros[MAX_LIVROS];
Historico historico[MAX_HISTORICO];
MensagemSuporte mensagens_suporte[MAX_MENSAGENS];
EmprestimoAtivo emprestimos_ativos[MAX_EMPRESTIMOS];

int mensagens_count = 0;
Usuario usuario;

void load_dados() {
    FILE *file;

    file = fopen("dados/livros.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_LIVROS && fscanf(file, "%99[^\n]\n%99[^\n]\n%99[^\n]\n%99[^\n]\n%d\n%d\n", 
            livros[i].titulo, livros[i].genero, livros[i].autor, livros[i].isbn, &livros[i].qtd_disponivel, &livros[i].qtd_total) != EOF; i++);
        fclose(file);
    }

    file = fopen("dados/usuarios.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_USUARIOS && fscanf(file, "%s %s %s %s %s %s %s %s\n", 
            usuarios[i].matricula,
            usuarios[i].nome,
            usuarios[i].data_nascimento,
            usuarios[i].nacionalidade,
            usuarios[i].email,
            usuarios[i].senha,
            usuarios[i].data_registro,
            usuarios[i].cargo) != EOF; i++);
        fclose(file);
    }

    file = fopen("dados/bibliotecarios.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_BIBLIOTECARIOS && fscanf(file, "%s %s %s %s %s %s %s %s\n", 
            bibliotecarios[i].matricula,
            bibliotecarios[i].nome,
            bibliotecarios[i].data_nascimento,
            bibliotecarios[i].nacionalidade,
            bibliotecarios[i].email,
            bibliotecarios[i].senha,
            bibliotecarios[i].data_registro,
            bibliotecarios[i].cargo) != EOF; i++);
        fclose(file);
    }
    
    file = fopen("dados/historico.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_HISTORICO && fscanf(file, "%s\n%s\n%s\n%s\n", 
            historico[i].acao, historico[i].data_hora, historico[i].detalhes, historico[i].usuario_responsavel) != EOF; i++);
        fclose(file);
    }

    file = fopen("dados/mensagens_suporte.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_MENSAGENS && fscanf(file, "%99[^\n]\n%99[^\n]\n%199[^\n]\n%19[^\n]\n%19[^\n]\n",
            mensagens_suporte[i].usuario, mensagens_suporte[i].email, mensagens_suporte[i].mensagem, 
            mensagens_suporte[i].data_hora, mensagens_suporte[i].status) != EOF; i++) {
            mensagens_count++;
            }
        fclose(file);
    }

    file = fopen("dados/emprestimos_ativos.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_EMPRESTIMOS && fscanf(file, "%s %s %s %s\n", 
            emprestimos_ativos[i].matricula_usuario, emprestimos_ativos[i].isbn_livro, 
            emprestimos_ativos[i].data_emprestimo, emprestimos_ativos[i].data_retorno_prevista) != EOF; i++);
        fclose(file);
    }
}

void salva_dados() {
    FILE *file;

    file = fopen("dados/livros.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_LIVROS && livros[i].titulo[0] != '\0'; i++) {
            fprintf(file, "%s\n%s\n%s\n%s\n%d\n%d\n", livros[i].titulo, livros[i].genero, livros[i].autor, 
                livros[i].isbn, livros[i].qtd_disponivel, livros[i].qtd_total);
        }
        fclose(file);
    }

    file = fopen("dados/usuarios.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_USUARIOS && usuarios[i].matricula[0] != '\0'; i++) {
            fprintf(file, "%s %s %s %s %s %s %s %s\n",               
                usuarios[i].matricula,
                usuarios[i].nome,
                usuarios[i].data_nascimento,
                usuarios[i].nacionalidade,
                usuarios[i].email,
                usuarios[i].senha,
                usuarios[i].data_registro,
                usuarios[i].cargo);
        }
        fclose(file);
    }

    file = fopen("dados/bibliotecarios.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_BIBLIOTECARIOS && bibliotecarios[i].matricula[0] != '\0'; i++) {
            fprintf(file, "%s %s %s %s %s %s %s %s\n",
                bibliotecarios[i].matricula,
                bibliotecarios[i].nome,
                bibliotecarios[i].data_nascimento,
                bibliotecarios[i].nacionalidade,
                bibliotecarios[i].email,
                bibliotecarios[i].senha,
                bibliotecarios[i].data_registro,
                bibliotecarios[i].cargo);
        }
        fclose(file);
    }

    file = fopen("dados/historico.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_HISTORICO && historico[i].acao[0] != '\0'; i++) {
            fprintf(file, "%s\n%s\n%s\n%s\n", historico[i].acao, historico[i].data_hora, historico[i].detalhes, 
                historico[i].usuario_responsavel);
        }
        fclose(file);
    }

    file = fopen("dados/mensagens_suporte.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_MENSAGENS && mensagens_suporte[i].usuario[0] != '\0'; i++) {
            fprintf(file, "%s\n%s\n%s\n%s\n%s\n", mensagens_suporte[i].usuario, mensagens_suporte[i].email, 
                mensagens_suporte[i].mensagem, mensagens_suporte[i].data_hora, mensagens_suporte[i].status);
        }
        fclose(file);
    }

    file = fopen("dados/emprestimos_ativos.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_EMPRESTIMOS && emprestimos_ativos[i].matricula_usuario[0] != '\0'; i++) {
            fprintf(file, "%s %s %s %s\n", emprestimos_ativos[i].matricula_usuario, emprestimos_ativos[i].isbn_livro, 
                emprestimos_ativos[i].data_emprestimo, emprestimos_ativos[i].data_retorno_prevista);
        }
        fclose(file);
    }
}
