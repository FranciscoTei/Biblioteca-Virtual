#include "src/utils.h"
#include "src/autenticacao.h"
#include "src/usuario.h"
#include "src/color_print.h"
#include "dados/database.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int qtd = 0;
    int option = -1;
    int loggedIn = 0;
    load_dados();
    boasVindas();


    int opcao = -1;


    while (!loggedIn) {
        printf("     BIBLIOTECA VIRTUAL\n\n");
        printf("     1 - Login 🔑\n");
        printf("     2 - Registrar 📝\n");
        printf("     3 - Suporte 💬\n");
        printf("     0 - Sair 🔚\n\n▶️");
        scanf("%d", &option);

        switch (option) {
            case 1:
                loggedIn = autenticar();
                break;
            case 2:
                loggedIn = cadastrarUsuario();
                break;
            case 3:
                enviar_mensagem_suporte();
                break;
            case 0:
                limpar_tela();
                
                color_printf(COLOR_YELLOW, "Finalizando o programa.\n");
                return 0;
            default:
                limpar_tela();
                color_printf(COLOR_YELLOW, "Opção inválida.\n\n");
        }
        while ((getchar()) != '\n');
    }
    if (strcmp(usuario.cargo, "bibliotecario") == 0) {
        menu_inicial_bibliotecario();
        salva_dados();
    } else {
        menu_inicial_usuario();
        salva_dados();
    }
}