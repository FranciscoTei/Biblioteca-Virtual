#ifndef AUTENTICACAO_H
#define AUTENTICACAO_H

#include <stdbool.h>

void boasVindas();

bool validarEmail(const char *email);

int autenticar(); 

int cadastrarUsuario();

#endif