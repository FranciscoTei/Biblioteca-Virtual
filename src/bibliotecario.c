#include "../dados/database.h"
#include "../src/mensagens.h"
#include "../src/utils.h"
#include "../src/color_print.h"
#include "../src/configuracoes.h"
#include "../src/bibliotecario.h"
#include <stdio.h>

#include <stdlib.h>
#include <string.h>



void menu_inicial_bibliotecario() {
  int opcao;

  do {
    printf("     MENU INICIAL\n\n");
    printf("     📚 1. Biblioteca\n");
    printf("     ✉️  2. Mensagens (%d)\n", contar_mensagens_pendentes());
    printf("     ⚙️  3. Configurações\n");
    printf("     🔚 0. Sair \n \n");
    printf("Escolha uma opção: ");
    color_printf(COLOR_WHITE, "");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        menu_biblioteca();
        break;
    case 2:
        ler_mensagens_suporte();
        break;
    case 3:
        menu_configuracoes();
        break;
    case 0:
      limpar_tela();
      color_printf(COLOR_YELLOW, "Finalizando o programa.\n\n");
      return 0;
      break;
    default:
        limpar_tela();
        color_printf(COLOR_YELLOW, "❌ Opção inválida.\n Tente novamente.\n\n");
      break;
    }
  } while (opcao != 0);
}

void menu_biblioteca() {
    limpar_tela();
    int opcao;

    do {
        printf("\n     📚 BIBLIOTECA 📚\n\n");
        printf("     🔍 1. Procurar livros\n");
        printf("     ➕ 2. Adicionar livros\n");
        printf("     ✏️  3. Atualizar livros\n");
        printf("     🗑️  4. Deletar livros\n");
        printf("     🔙 0. Voltar\n");
        printf("\nEscolha uma opção: ");
        color_printf(COLOR_WHITE, "");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
          procurar_livros();
          break;
        case 2:
          adicionar_livro();
          break;
        case 3:
          atualizar_livro();
          break;
        case 4:
          deletar_livro();
          break;
        case 0:
          limpar_tela();
          break;
        default:
            limpar_tela();
            color_printf(COLOR_YELLOW, "❌ Opção inválida.\n Tente novamente.\n\n");
        }
    } while (opcao != 0);
}

void procurar_livros() {
  limpar_tela();
  char termo[100];
  printf("     📕 BUSCAR LIVRO 📕\n\n");
  printf("Digite o nome do livro ou autor: ");
  color_print(COLOR_WHITE, "");
  fgets(termo, sizeof(termo), stdin);
  termo[strcspn(termo, "\n")] = '\0';

  for (int i = 0; i < MAX_LIVROS; i++) {
    if ((strstr(livros[i].titulo, termo) != NULL) ||
        (strstr(livros[i].autor, termo) != NULL)) {
      limpar_tela();
      printf("     🔎 RESULTADO DA BUSCA 🔎\n\n");
      printf("Livro encontrado:\n");
        color_print(COLOR_BLUE, "Título: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].titulo);
        
        color_print(COLOR_BLUE, "Gênero: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].genero);
        
        color_print(COLOR_BLUE, "Autor: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].autor);
        
        color_print(COLOR_BLUE, "ISBN: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].isbn);
        
        color_print(COLOR_BLUE, "Qtd disponível: ");
        color_print(COLOR_WHITE, "%d\n", livros[i].qtd_disponivel);
        
        color_print(COLOR_BLUE, "Qtd total: ");
        color_print(COLOR_WHITE, "%d\n", livros[i].qtd_total);

      if (livros[i].qtd_disponivel > 0) {
          color_printf(COLOR_GREEN, "Disponível para empréstimo.\n\n");
      } else {
          color_printf(COLOR_RED, "Não disponível para empréstimo.\n\n");
      }
      color_printf(COLOR_L_BLUE, "Para retornar digite 0.\n");
      int opcao;
      scanf("%d", &opcao);
      limpar_tela();
      return;
    }
  }
    limpar_tela();
    color_printf(COLOR_YELLOW, "Livro não encontrado.\n");
}

void adicionar_livro() {
  limpar_tela();
  for (int i = 0; i < MAX_LIVROS; i++) {
    if (livros[i].qtd_total == 0) {
      printf("     📘 NOVO LIVRO 📘\n\n");
      color_printf(COLOR_BLUE, "Título: ");
      color_printf(COLOR_WHITE, "");
      fgets(livros[i].titulo, sizeof(livros[i].titulo), stdin);
      livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

      color_printf(COLOR_BLUE, "Gênero: ");
      color_printf(COLOR_WHITE, "");
      fgets(livros[i].genero, sizeof(livros[i].genero), stdin);
      livros[i].genero[strcspn(livros[i].genero, "\n")] = '\0';

      color_printf(COLOR_BLUE, "Autor: ");
      color_printf(COLOR_WHITE, "");
      fgets(livros[i].autor, sizeof(livros[i].autor), stdin);
      livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

      color_printf(COLOR_BLUE, "ISBN: ");
      color_printf(COLOR_WHITE, "");
      fgets(livros[i].isbn, sizeof(livros[i].isbn), stdin);
      livros[i].isbn[strcspn(livros[i].isbn, "\n")] = '\0';

      color_printf(COLOR_BLUE, "Quantidade total: ");
      color_printf(COLOR_WHITE, "");
      scanf("%d", &livros[i].qtd_total);
        
      livros[i].qtd_disponivel = livros[i].qtd_total;
        
      getchar();
      limpar_tela();
      color_printf(COLOR_GREEN, "Livro adicionado ao acervo com sucesso.\n\n");
        
      return;
    }
  }
    limpar_tela();
    color_printf(COLOR_YELLOW, "Não há espaço para adicionar mais livros no acervo.\n\n");
}

void atualizar_livro() {
  limpar_tela();
  char isbn[20];
  printf("\nDigite o ISBN do livro a ser atualizado: ");
  color_print(COLOR_WHITE, "");
  fgets(isbn, sizeof(isbn), stdin);
  isbn[strcspn(isbn, "\n")] = '\0';

  for (int i = 0; i < MAX_LIVROS; i++) {
    if (strcmp(livros[i].isbn, isbn) == 0) {
      limpar_tela();
      printf("     🔎 RESULTADO DA BUSCA 🔎\n\n");
      printf("Livro encontrado:\n");
        color_print(COLOR_BLUE, "Título: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].titulo);

        color_print(COLOR_BLUE, "Gênero: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].genero);

        color_print(COLOR_BLUE, "Autor: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].autor);

        color_print(COLOR_BLUE, "ISBN: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].isbn);

        color_print(COLOR_BLUE, "Qtd disponível: ");
        color_print(COLOR_WHITE, "%d\n", livros[i].qtd_disponivel);

        color_print(COLOR_BLUE, "Qtd total: ");
        color_printf(COLOR_WHITE, "%d\n\n", livros[i].qtd_total);

      char input[100];

      color_printf(COLOR_YELLOW, "Digite # em qualquer campo para não alterar\n\n");

      color_print(COLOR_BLUE, "Digite o novo título:\n▶️ ");
      color_print(COLOR_WHITE, "");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      if (strcmp(input, "#") != 0) {
        strcpy(livros[i].titulo, input);
      }

      color_print(COLOR_BLUE, "Digite o novo gênero :\n▶️ ");
      color_print(COLOR_WHITE, "");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      if (strcmp(input, "#") != 0) {
        strcpy(livros[i].genero, input);
      }

      color_print(COLOR_BLUE, "Digite o novo autor:\n▶️ ");
      color_print(COLOR_WHITE, "");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      if (strcmp(input, "#") != 0) {
        strcpy(livros[i].autor, input);
      }

      color_print(COLOR_BLUE, "Digite a nova quantidade disponível:\n▶️");
      color_print(COLOR_WHITE, "");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      if (strcmp(input, "#") != 0) {
        livros[i].qtd_disponivel = atoi(input);
      }

      color_print(COLOR_BLUE, "Digite a nova quantidade total:\n▶️");
      color_print(COLOR_WHITE, "");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      if (strcmp(input, "#") != 0) {
        livros[i].qtd_total = atoi(input);
      }

      color_print(COLOR_L_BLUE, "\nConfirma as alterações? (s/n):\n▶️");
      char confirmacao;
      color_print(COLOR_WHITE, "");
      scanf(" %c", &confirmacao);
      getchar();
      limpar_tela();
      if (confirmacao == 's') {
        color_printf(COLOR_GREEN, "Livro atualizado com sucesso.\n\n");
      } else {
        color_printf(COLOR_RED, "Alterações canceladas.\n\n");
      }
      return;
    }
  }
    color_printf(COLOR_YELLOW, "Livro não encontrado.\n\n");
}

void deletar_livro() {
  limpar_tela();
  char isbn[20];
  printf("Digite o ISBN do livro a ser deletado:\n▶");
  color_print(COLOR_WHITE, "");
  fgets(isbn, sizeof(isbn), stdin);
  isbn[strcspn(isbn, "\n")] = '\0';

  for (int i = 0; i < MAX_LIVROS; i++) {
    if (strcmp(livros[i].isbn, isbn) == 0) {
      limpar_tela();
      printf("     🔎 RESULTADO DA BUSCA 🔎\n\n");
      printf("Livro encontrado:\n");
        color_print(COLOR_BLUE, "Título: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].titulo);

        color_print(COLOR_BLUE, "Gênero: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].genero);

        color_print(COLOR_BLUE, "Autor: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].autor);

        color_print(COLOR_BLUE, "ISBN: ");
        color_print(COLOR_WHITE, "%s\n", livros[i].isbn);

        color_print(COLOR_BLUE, "Qtd disponível: ");
        color_print(COLOR_WHITE, "%d\n", livros[i].qtd_disponivel);

        color_print(COLOR_BLUE, "Qtd total: ");
        color_printf(COLOR_WHITE, "%d\n\n", livros[i].qtd_total);

      printf("\nConfirma a exclusão do livro? (s/n): ");
      char confirmacao;
      color_print(COLOR_WHITE, "");
      scanf(" %c", &confirmacao);
      getchar();
      limpar_tela();
      if (confirmacao == 's') {
        livros[i].titulo[0] = '\0';
        livros[i].genero[0] = '\0';
        livros[i].autor[0] = '\0';
        livros[i].isbn[0] = '\0';
        livros[i].qtd_disponivel = 0;
        livros[i].qtd_total = 0;
          color_printf(COLOR_BLUE, "Livro deletado com sucesso.\n\n");
      } else {
          color_printf(COLOR_RED, "Operação cancelada.\n\n");
      }
      return;
    }
  }
    limpar_tela();
    color_printf(COLOR_YELLOW, "Livro não encontrado.\n\n");
}

void colocar_livro_em_manutencao() {
    char isbn[20];
    int quantidade_manutencao;

    printf("\nDigite o ISBN do livro: ");
    color_print(COLOR_WHITE, "");
    scanf("%19s", isbn);

    for (int i = 0; i < MAX_LIVROS; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0) {
          limpar_tela();
          printf("     🔎 RESULTADO DA BUSCA 🔎\n\n");
          printf("Livro encontrado:\n");
            color_print(COLOR_BLUE, "Título: ");
            color_print(COLOR_WHITE, "%s\n", livros[i].titulo);

            color_print(COLOR_BLUE, "Gênero: ");
            color_print(COLOR_WHITE, "%s\n", livros[i].genero);

            color_print(COLOR_BLUE, "Autor: ");
            color_print(COLOR_WHITE, "%s\n", livros[i].autor);

            color_print(COLOR_BLUE, "ISBN: ");
            color_print(COLOR_WHITE, "%s\n", livros[i].isbn);

            color_print(COLOR_BLUE, "Qtd disponível: ");
            color_print(COLOR_WHITE, "%d\n", livros[i].qtd_disponivel);

            color_print(COLOR_BLUE, "Qtd total: ");
            color_printf(COLOR_WHITE, "%d\n\n", livros[i].qtd_total);

            printf("Este é o livro? (s/n): ");
            char confirmacao;
            color_print(COLOR_WHITE, "");
            scanf("%c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S') {
                printf("Quantos exemplares irão para manutenção? ");
                color_print(COLOR_WHITE, "");
                scanf("%d", &quantidade_manutencao);
                limpar_tela();
                if (quantidade_manutencao <= livros[i].qtd_disponivel) {
                    livros[i].qtd_disponivel -= quantidade_manutencao;
                    color_printf(COLOR_GREEN, "Livro atualizado com sucesso. %d exemplares em manutenção.\n\n", quantidade_manutencao);

                    salvar_historico("manutenção", isbn, livros[i].titulo);
                } else {
                    color_printf(COLOR_RED, "Quantidade inválida. Não há exemplares suficientes disponíveis.\n\n");
                }
            } else {
                color_printf(COLOR_RED, "Operação cancelada.\n\n");
            }
            return;
        }
    }
    color_printf(COLOR_YELLOW, "Livro com ISBN %s não encontrado.\n\n", isbn);
}

void salvar_historico(const char *acao, const char *isbn, const char *titulo) {
    char detalhes[255];
    char data_hora[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(data_hora, sizeof(data_hora), "%02d:%02d %02d/%02d/%d", tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    snprintf(detalhes, sizeof(detalhes), "%s (%s) %s o livro %s (%s).", usuario.nome, usuario.matricula, acao, titulo, isbn);

    for (int i = 0; i < MAX_HISTORICO; i++) {
        if (historico[i].acao[0] == '\0') {
            strcpy(historico[i].acao, acao);
            strcpy(historico[i].data_hora, data_hora);
            strcpy(historico[i].detalhes, detalhes);
            strcpy(historico[i].usuario_responsavel, usuario.nome);
            break;
        }
    }
}

