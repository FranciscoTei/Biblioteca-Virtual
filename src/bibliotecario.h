#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

void menu_inicial_bibliotecario();
void menu_biblioteca();
void procurar_livros();
void adicionar_livro();
void atualizar_livro();
void deletar_livro();
void salvar_historico(const char *acao, const char *isbn, const char *titulo);
void colocar_livro_em_manutencao();

#endif