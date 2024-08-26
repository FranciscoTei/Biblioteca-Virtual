#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mensagens.h"
#include "../src/utils.h"
#include "../src/color_print.h"

extern MensagemSuporte mensagens_suporte[MAX_MENSAGENS];
extern int mensagens_count;


void enviar_mensagem_suporte() {
    limpar_tela();
    if (mensagens_count >= MAX_MENSAGENS) {
        limpar_tela();
        color_print(COLOR_YELLOW, "O limite de mensagens foi atingido. Não é possível enviar novas mensagens.\n\n");
        return;
    }

    MensagemSuporte *nova_mensagem = &mensagens_suporte[mensagens_count];
    color_print(COLOR_L_BLUE, "     SUPORTE\n\n");

    if (usuario.matricula[0] != '\0') {
        strncpy(nova_mensagem->usuario, usuario.nome, sizeof(nova_mensagem->usuario) - 1);
        strncpy(nova_mensagem->email, usuario.email, sizeof(nova_mensagem->email) - 1);
    } else {
        color_print(COLOR_BLUE, "Digite seu nome: ");
        color_print(COLOR_WHITE, "");
        scanf(" %[^\n]", nova_mensagem->usuario);

        color_print(COLOR_BLUE, "Forneça um email para contato: ");
        color_print(COLOR_WHITE, "");
        scanf(" %[^\n]", nova_mensagem->email);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strftime(nova_mensagem->data_hora, sizeof(nova_mensagem->data_hora), "%d/%m/%Y %H:%M:%S", &tm);
    strcpy(nova_mensagem->status, "pendente");

    char mensagem[200];
    color_print(COLOR_BLUE, "Digite sua mensagem (digite 'cancelar' para voltar ao menu): ");
    color_print(COLOR_WHITE, "");
    scanf(" %[^\n]", mensagem);

    if (strcmp(mensagem, "cancelar") == 0) {
        limpar_tela();
        color_printf(COLOR_YELLOW, "❌ Operação cancelada.\n");
        return;
    }

    strncpy(nova_mensagem->mensagem, mensagem, sizeof(nova_mensagem->mensagem) - 1);

    mensagens_count++;
    limpar_tela();
    color_printf(COLOR_GREEN, "Sua mensagem foi enviada com sucesso.\nO suporte responderá por email.\n\n");
}

void ler_mensagens_suporte() {
    int pagina = 0;
    int mensagens_por_pagina = 5;
    int total_paginas = (mensagens_count + mensagens_por_pagina - 1) / mensagens_por_pagina;

    while (1) {
        limpar_tela();
        printf("=== Página %d de %d ===\n\n", pagina + 1, total_paginas);
        for (int i = pagina * mensagens_por_pagina; i < (pagina + 1) * mensagens_por_pagina && i < mensagens_count; i++) {
            MensagemSuporte *mensagem = &mensagens_suporte[mensagens_count - 1 - i];
            
            color_print(COLOR_BLUE, "Nome: ");
            color_print(COLOR_WHITE, "%s\n", mensagem->usuario);

            color_print(COLOR_BLUE, "Email: ");
            color_print(COLOR_WHITE, "%s\n", mensagem->email);

            color_print(COLOR_BLUE, "Data/Hora: ");
            color_print(COLOR_WHITE, "%s\n\n", mensagem->data_hora);

            color_print(COLOR_BLUE, "Mensagem: ");
            color_print(COLOR_WHITE, "%s\n", mensagem->mensagem);

            color_print(COLOR_BLUE, "Status: ");
            if (strcmp(mensagem->status, "pendente") == 0) {
                color_printf(COLOR_RED, "%s\n\n", mensagem->status);

                strcpy(mensagem->status, "lida");
            } else {
                color_print(COLOR_GREEN, "%s\n\n", mensagem->status);
            }
            color_print(COLOR_L_BLUE, "---------------------------\n");
        }

        if (total_paginas > 1) {
            printf("1 - Página anterior | 2 - Próxima página | 0 - Sair\n");
            int opcao;
            scanf("%d", &opcao);

            if (opcao == 1 && pagina > 0) {
                pagina--;
            } else if (opcao == 2 && pagina < total_paginas - 1) {
                pagina++;
            } else if (opcao == 0) {
                limpar_tela();
                break;
            }
        } else {
            printf("Pressione 0 para sair.\n");
            int opcao;
            scanf("%d", &opcao);
            if (opcao == 0) {
                limpar_tela();
                break;
            }
        }
    }
}

int contar_mensagens_pendentes() {
    int count = 0;
    for (int i = 0; i < MAX_MENSAGENS; i++) {
        if (strcmp(mensagens_suporte[i].status, "pendente") == 0) {
            count++;
        }
    }
    return count;
}
