#ifndef USUARIO_H
#define USUARIO_H

#include "../dados/database.h"

void menu_biblioteca_usuario();
void realizar_emprestimo();
void realizar_devolucao();
int encontrar_livro_por_isbn(char *isbn);
int encontrar_emprestimo_ativo(char *matricula, char *isbn);
void recomendar_livros();

void menu_inicial_usuario();
void procurar_livros();

#endif