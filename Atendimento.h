#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include <stdlib.h>
#include <stdio.h>

struct Atendimento
{
	char nome[30];
	char identidade[30];
	int codigo;
	char dataVisita[30];
	char descricao[30];
	int status;
};

struct Atendimento* criaAtendimento(char nome[30], char identidade[30], char dataVisita[30], char descricao[30], int c);
char* getNome (struct Atendimento * A);
int getCodigo (struct Atendimento * A);
int getStatus(struct Atendimento* a);
void setStatus (struct Atendimento * A, int codigo);
void mudaStatus(struct Atendimento * A);
void listarAtendimento(struct Atendimento *A);
#endif
