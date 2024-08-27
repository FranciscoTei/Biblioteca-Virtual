#include "../dados/database.h"
#include "../src/color_print.h"
#include "../src/autenticacao.h"
#include "../src/utils.h"

void boasVindas() {
    color_print(COLOR_L_GREEN, "");
    printf("======== Bem-vindo à Biblioteca Virtual ========\n");
    printf("       Seu Portal de Conhecimento e Leitura       \n");
    printf("=================================================\n\n");
    color_print(COLOR_L_BLUE, "");
}


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

bool validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at != NULL && dot != NULL && at < dot;
}

int autenticar() {
    limpar_tela();
    char nome[100];
    char senha[50];
    FILE *log;
    time_t tempo = time(NULL);

    printf("     LOGIN\n\n");
    color_print(COLOR_BLUE, "Nome: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", nome);
    color_print(COLOR_BLUE, "Senha: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", senha);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            usuario = usuarios[i];
            limpar_tela();
            color_printf(COLOR_GREEN, "Bem-vindo, %s!\n\n", usuario.nome);

            log = fopen("logs.txt", "a");
            if (log == NULL) {
                printf("\n❌ Não foi possível abrir o arquivo de logs.\n");
                return 0;
            }
            fprintf(log, "Usuário %s efetuou login em %s", usuario.nome, ctime(&tempo));
            fclose(log);

            return 1;
        }
    }
    limpar_tela();
    color_printf(COLOR_YELLOW, "❌ Nome ou senha incorretos. Tente novamente.\n\n");
    return 0;
}


int cadastrarUsuario() {
    limpar_tela();
    char email[100];

    printf("     CADASTRO DE USUÁRIO\n\n");
    
    color_print(COLOR_BLUE, "Matrícula: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.matricula);
    
    color_print(COLOR_BLUE, "Nome: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.nome);
    
    color_print(COLOR_BLUE, "Data de Nascimento (dd/mm/aaaa): ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.data_nascimento);
    
    color_print(COLOR_BLUE, "Nacionalidade: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.nacionalidade);
    
    color_print(COLOR_BLUE, "Email: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", email);
    
    color_print(COLOR_BLUE, "Senha: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.senha);
    
    color_print(COLOR_BLUE, "Cargo: ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", usuario.cargo);

    if (!validarEmail(email)) {
        limpar_tela();
        color_printf(COLOR_YELLOW, "❌ Digite um email válido.\n\n");
        return 0;
    }

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            limpar_tela();
            color_printf(COLOR_YELLOW, "❌ Email já registrado.\n\n");
            return 0;
        }
    }

    strcpy(usuario.email, email);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (usuarios[i].matricula[0] == '\0') {
            usuarios[i] = usuario;
            limpar_tela();
            color_printf(COLOR_GREEN, "Cadastro efetuado com sucesso.\n");

            color_printf(COLOR_L_GREEN, "Bem-vindo, ");
            color_printf(COLOR_BLUE, "%s!\n\n", usuario.nome);
            return 1;
        }
    }
    limpar_tela();
    color_printf(COLOR_YELLOW, "❌ Limite máximo de usuários atingido.\n\n");
    return 0;
}

