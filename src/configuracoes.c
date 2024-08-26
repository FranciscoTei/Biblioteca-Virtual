#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dados/database.h"
#include "../src/configuracoes.h"
#include "../src/color_print.h"



void menu_configuracoes() {
    limpar_tela();
    int opcao;

    do {
        printf("     ⚙️  CONFIGURAÇÕES ⚙️ \n\n");
        printf("     👤 1. Meu perfil\n");
        printf("     ✉️  2. Alterar Email\n");
        printf("     🔒 3. Alterar Senha\n");
        printf("     🚫 4. Restringir usuário\n");
        printf("     🗑️  5. Deletar conta\n");
        printf("     💾 6. Salvar dados\n");
        printf("     🔙 0. Voltar\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                meu_perfil();
                break;
            case 2:
                alterar_email();
                break;
            case 3:
                alterar_senha();
                break;
            case 4:
                restringir_usuario();
                break;
            case 5:
                deletar_conta();
                break;
            case 6:
                salva_dados();
                limpar_tela();
                color_printf(COLOR_GREEN, "Dados salvos com sucesso.\n\n");
                break;
            case 0:
                limpar_tela();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0 && opcao != 6);
}

void meu_perfil() {
    limpar_tela();
    int opcao;
    printf("     MEU PERFIL\n\n");
    color_print(COLOR_BLUE, "Nome: ");
    color_print(COLOR_WHITE, "%s\n", usuario.nome);

    color_print(COLOR_BLUE, "Matrícula: ");
    color_print(COLOR_WHITE, "%s\n", usuario.matricula);

    color_print(COLOR_BLUE, "Email: ");
    color_print(COLOR_WHITE, "%s\n", usuario.email);

    color_print(COLOR_BLUE, "Data de Nascimento: ");
    color_print(COLOR_WHITE, "%s\n", usuario.data_nascimento);

    color_print(COLOR_BLUE, "Nacionalidade: ");
    color_print(COLOR_WHITE, "%s\n", usuario.nacionalidade);

    color_print(COLOR_BLUE, "Status: ");
    color_print(COLOR_WHITE, "%s\n", usuario.cargo);

    color_print(COLOR_BLUE, "Data de Registro: ");
    color_printf(COLOR_WHITE, "%s\n\n", usuario.data_registro);
    printf("Digite 0 para voltar:\n ");
    scanf("%d", &opcao);
    limpar_tela();
}

void alterar_email() {
    limpar_tela();
    char novo_email[100];
    printf("     MUDANÇA DE EMAIL\n\n");
    color_print(COLOR_BLUE, "Digite o novo email: ");
    color_printf(COLOR_WHITE, "");
    fgets(novo_email, sizeof(novo_email), stdin);
    novo_email[strcspn(novo_email, "\n")] = '\0';

    if (!validarEmail(novo_email)) {
        limpar_tela();
        color_printf(COLOR_YELLOW, "❌ Email inválido.\n\n");
        return 0;
    } else {
    
        printf("\nConfirmar a alteração de email para ");
        color_printf(COLOR_GREEN, novo_email);
        printf(" (s/n)?\n");
        char confirmacao;
        scanf(" %c", &confirmacao);
        getchar();
        limpar_tela();
        if (confirmacao == 's') {
            strcpy(usuario.email, novo_email);
            color_printf(COLOR_GREEN, "Email alterado com sucesso!\n\n");
        } else {
            color_printf(COLOR_RED, "Alteração de email cancelada.\n\n");
        }
    }
}

void alterar_senha() {
    limpar_tela();
    char nova_senha[100];
    char confirmacao_senha[100];

    printf("     MUDANÇA DE SENHA\n\n");
    color_print(COLOR_BLUE, "Digite a nova senha: ");
    color_printf(COLOR_WHITE, "");
    fgets(nova_senha, sizeof(nova_senha), stdin);
    nova_senha[strcspn(nova_senha, "\n")] = '\0';

    color_print(COLOR_BLUE, "Confirme a nova senha: ");
    color_printf(COLOR_WHITE, "");
    fgets(confirmacao_senha, sizeof(confirmacao_senha), stdin);
    confirmacao_senha[strcspn(confirmacao_senha, "\n")] = '\0';
    limpar_tela();
    if (strcmp(nova_senha, confirmacao_senha) == 0) {
        strcpy(usuario.senha, nova_senha);
        color_printf(COLOR_GREEN, "Senha alterada com sucesso!\n\n");
    } else {
        color_printf(COLOR_RED, "As senhas não coincidem.\nTente novamente.\n\n");
    }
}

void restringir_usuario() {
    limpar_tela();
    char matricula[20];
    printf("     RESTRINGIR USUÁRIO:\n\n");
    color_print(COLOR_BLUE, "Digite a matrícula do usuário a ser restrito: ");
    color_printf(COLOR_WHITE, "");
    fgets(matricula, sizeof(matricula), stdin);
    matricula[strcspn(matricula, "\n")] = '\0';
    limpar_tela();
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].matricula, matricula) == 0) {
            printf("     RESTRINGIR USUÁRIO:\n\n");
            color_print(COLOR_GREEN, "Usuário encontrado:\n");
            color_print(COLOR_BLUE, "Nome: ");
            color_print(COLOR_WHITE, "%s\n", usuarios[i].nome);
            
            color_print(COLOR_BLUE, "Matrícula: ");
            color_print(COLOR_WHITE, "%s\n", usuarios[i].matricula);
            
            color_print(COLOR_BLUE, "Email: ");
            color_print(COLOR_WHITE, "%s\n", usuarios[i].email);
            
            color_print(COLOR_BLUE, "Cargo: ");
            color_printf(COLOR_WHITE, "%s\n\n", usuarios[i].cargo);

            printf("Confirmar restrição do usuário (s/n)? ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            getchar();
            limpar_tela();
            if (confirmacao == 's') {
                strcpy(usuarios[i].cargo, "restrito");
                color_printf(COLOR_GREEN, "Usuário restrito com sucesso!\n\n");
            } else {
                color_printf(COLOR_RED, "Operação de restrição cancelada.\n\n");
            }
            return;
        }
    }
    limpar_tela();
    color_printf(COLOR_RED, "Usuário não encontrado.\n\n");
}

int deletar_conta() {
    limpar_tela();
    char confirmacao[50];
    printf("     DELETAR CONTA\n\n");
    color_print(COLOR_L_BLUE, "Digite a seguinte frase para confirmar:");
    color_printf(COLOR_GREEN, "\nEu desejo deletar esta conta.\n\n");
    color_printf(COLOR_RED, "Esta ação é irreversível.\n\n");
    color_printf(COLOR_BLUE, "Confirmação: ");
    color_print(COLOR_WHITE, "");
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = '\0';

    if (strcmp(confirmacao, "Eu desejo deletar esta conta.") == 0) {

        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarios[i].matricula, usuario.matricula) == 0) {
                memset(&usuarios[i], 0, sizeof(Usuario));
                limpar_tela();
                color_printf(COLOR_GREEN, "Conta deletada com sucesso.\n\n");
                salva_dados();
                exit(0);
                break;
            }
        }
        return 1;
    } else {
        limpar_tela();
        color_printf(COLOR_RED, "Frase incorreta. A conta não foi deletada.\n\n");
        return 0;
    }
}