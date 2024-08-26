#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/usuario.h"
#include "../dados/database.h"
#include "../src/mensagens.h"
#include "../src/configuracoes.h"
#include "../src/utils.h"
#include "../src/color_print.h"
#include "../src/bibliotecario.h"



void menu_inicial_usuario() {
  int opcao;

  do {
      printf("     MENU INICIAL\n\n");
      printf("     📚 1. Biblioteca\n");
      printf("     ✉️  2. Suporte\n", contar_mensagens_pendentes());
      printf("     ⚙️  3. Configurações\n");
      printf("     🔚 0. Sair \n \n");
    printf("Escolha uma opção: ");
      color_print(COLOR_WHITE, "");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
        menu_biblioteca_usuario();
        break;
    case 2:
        enviar_mensagem_suporte();
        break;
    case 3:
        menu_configuracoes();
        break;
    case 0:
      return;
      break;
    default:
      color_printf(COLOR_YELLOW, "Opção inválida. Tente novamente.\n\n");
      break;
    }
  } while (opcao != 0);
}

void menu_biblioteca_usuario() {
  limpar_tela();
  int opcao;

  do {
    printf("     📚 BIBLIOTECA 📚\n\n");
    printf("     📕 1. Procurar livros\n");
    printf("     📖 2. Realizar empréstimo\n");
    printf("     🔄 3. Realizar devolução\n");
    printf("     ⭐ 4. Recomendações\n");
    printf("     🔙 0. Voltar\n\n");
    printf("Escolha uma opção: ");
    color_print(COLOR_WHITE, "");
    scanf("%d", &opcao);

    getchar();

    switch (opcao) {
    case 1:
      procurar_livros();
      break;
    case 2:
      realizar_emprestimo();
      break;
    case 3:
      realizar_devolucao();
      break;
    case 4:
      recomendar_livros();
      break;
    case 0:
      limpar_tela();
      break;
    default:
      color_printf(COLOR_YELLOW, "Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);
}

void biblioteca_virtual() {
    int opcao;

    do {
        printf("\nBiblioteca Virtual:\n");
        printf("1 - Empréstimo\n");
        printf("2 - Devolução\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                realizar_emprestimo();
                break;
            case 2:
                realizar_devolucao();
                break;
            case 0:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void realizar_emprestimo() {
    char isbn[20];
    int indice_livro;
    limpar_tela();
    color_printf(COLOR_BLUE, "Digite o ISBN do livro que deseja pegar emprestado:\n▶");
    color_print(COLOR_WHITE, "");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    indice_livro = encontrar_livro_por_isbn(isbn);

    if (indice_livro == -1) {
        color_printf(COLOR_YELLOW, "Livro não encontrado.\n\n");
        return;
    }

    Livro *livro = &livros[indice_livro];

    if (livro->qtd_disponivel > 0) {
        limpar_tela();
        color_print(COLOR_BLUE, "     📕 EMPRÉSTIMO DE LIVRO 📕 \n\n");
        color_printf(COLOR_BLUE, "Livro encontrado:\n");
        color_printf(COLOR_BLUE, "Título: "); color_printf(COLOR_WHITE, "%s\n", livro->titulo);
        color_printf(COLOR_BLUE, "Autor: "); color_printf(COLOR_WHITE, "%s\n", livro->autor);
        color_printf(COLOR_BLUE, "Gênero: "); color_printf(COLOR_WHITE, "%s\n", livro->genero);
        color_printf(COLOR_BLUE, "ISBN: "); color_printf(COLOR_WHITE, "%s\n", livro->isbn);
        color_printf(COLOR_BLUE, "Quantidade disponível: "); color_printf(COLOR_WHITE, "%d\n", livro->qtd_disponivel);
        color_printf(COLOR_BLUE, "\nDeseja confirmar o empréstimo? (s/n): ");

        color_printf(COLOR_WHITE, "");
        char confirmacao;
        scanf("%c", &confirmacao);
        getchar();

        if (confirmacao == 's' || confirmacao == 'S') {
 
            for (int i = 0; i < MAX_EMPRESTIMOS; i++) {
                if (emprestimos_ativos[i].matricula_usuario[0] == '\0') {
                    strcpy(emprestimos_ativos[i].matricula_usuario, usuario.matricula);
                    strcpy(emprestimos_ativos[i].isbn_livro, livro->isbn);

                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(emprestimos_ativos[i].data_emprestimo, sizeof(emprestimos_ativos[i].data_emprestimo), "%d/%m/%Y", t);

                    t->tm_mday += 7;
                    mktime(t);
                    strftime(emprestimos_ativos[i].data_retorno_prevista, sizeof(emprestimos_ativos[i].data_retorno_prevista), "%d/%m/%Y", t);

                    livro->qtd_disponivel--;
                    limpar_tela();
                    color_printf(COLOR_GREEN, "Empréstimo realizado com sucesso!\n\n");
                    break;
                }
            }
        } else {
            color_printf(COLOR_RED, "Empréstimo cancelado.\n\n");
        }
    } else {
        color_printf(COLOR_YELLOW, "Não há exemplares disponíveis para empréstimo.\n\n");
    }
}

void realizar_devolucao() {
    char isbn[20];
    int indice_emprestimo;
    limpar_tela();
    color_printf(COLOR_BLUE, "Digite o ISBN do livro que deseja devolver:\n▶");
    color_print(COLOR_WHITE, ""); 
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    indice_emprestimo = encontrar_emprestimo_ativo(usuario.matricula, isbn);

    if (indice_emprestimo == -1) {
        limpar_tela();
        color_printf(COLOR_YELLOW, "Você não tem esse livro emprestado.\n\n");
        return;
    }
    limpar_tela();
    color_print(COLOR_BLUE, "     📕 DEVOLUÇÃO DE LIVRO 📕 \n\n");
    color_printf(COLOR_BLUE, "Livro encontrado:\n");
    color_printf(COLOR_BLUE, "Título: "); color_printf(COLOR_WHITE, "%s\n", livros[indice_emprestimo].titulo);
    color_printf(COLOR_BLUE, "Autor: "); color_printf(COLOR_WHITE, "%s\n", livros[indice_emprestimo].autor);
    color_print(COLOR_BLUE, "ISBN: "); color_printf(COLOR_WHITE, "%s\n", isbn);
    
    printf("\nDeseja confirmar a devolução? (s/n): ");

    char confirmacao;
    color_print(COLOR_WHITE, ""); 
    scanf("%c", &confirmacao);
    getchar();

    if (confirmacao == 's' || confirmacao == 'S') {
        memset(&emprestimos_ativos[indice_emprestimo], 0, sizeof(EmprestimoAtivo));

        for (int i = 0; i < MAX_LIVROS; i++) {
            if (strcmp(livros[i].isbn, isbn) == 0) {
                livros[i].qtd_disponivel++;
                limpar_tela();
                color_printf(COLOR_GREEN, "Devolução realizada com sucesso!\n\n");
                break;
            }
        }
    } else {
        limpar_tela();
        color_printf(COLOR_RED, "Devolução cancelada.\n\n");
    }
}

int encontrar_livro_por_isbn(char *isbn) {
    for (int i = 0; i < MAX_LIVROS; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

int encontrar_emprestimo_ativo(char *matricula, char *isbn) {
    for (int i = 0; i < MAX_EMPRESTIMOS; i++) {
        if (strcmp(emprestimos_ativos[i].matricula_usuario, matricula) == 0 &&
            strcmp(emprestimos_ativos[i].isbn_livro, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

void recomendar_livros() {
    char genero[50];
    int encontrados = 0;
    limpar_tela();
    color_print(COLOR_L_BLUE, "     📕 RECOMENDAÇÃO DE LIVRO 📕 \n\n");
    color_print(COLOR_BLUE, "Digite o gênero do livro que deseja procurar:\n▶");
    color_print(COLOR_WHITE, "");
    scanf(" %49[^\n]", genero);
    limpar_tela();
    color_print(COLOR_L_BLUE, "     📕 RECOMENDAÇÃO DE LIVRO 📕 \n\n");
    color_printf(COLOR_BLUE, "Livros encontrados no gênero '%s':\n", genero);

    for (int i = 0; i < MAX_LIVROS; i++) {
        if (livros[i].qtd_total > 0 && strcmp(livros[i].genero, genero) == 0) {

            color_printf(COLOR_BLUE, "Título: "); color_printf(COLOR_WHITE, "%s\n", livros[i].titulo);
            color_printf(COLOR_BLUE, "Autor: "); color_printf(COLOR_WHITE, "%s\n", livros[i].autor);
            color_printf(COLOR_BLUE, "Gênero: "); color_printf(COLOR_WHITE, "%s\n", livros[i].genero);
            color_printf(COLOR_BLUE, "ISBN: "); color_printf(COLOR_WHITE, "%s\n", livros[i].isbn);
            color_printf(COLOR_BLUE, "Quantidade disponível: "); color_printf(COLOR_WHITE, "%d\n", livros[i].qtd_disponivel);
            color_printf(COLOR_BLUE, "Quantidade Total: "); color_printf(COLOR_WHITE, "%d\n", livros[i].qtd_total);
            color_printf(COLOR_BLUE, "\nDeseja confirmar o empréstimo? (s/n): ");


            if (livros[i].qtd_disponivel > 0) {
                color_printf(COLOR_GREEN, "Status: Disponível para empréstimo\n");
            } else {
                color_printf(COLOR_RED, "Status: Não disponível para empréstimo\n");
            }

            encontrados++;
        }
    }

    if (encontrados == 0) {
        limpar_tela();
        color_printf(COLOR_RED,"Nenhum livro encontrado no gênero '%s'.\n\n", genero);
    }
}
