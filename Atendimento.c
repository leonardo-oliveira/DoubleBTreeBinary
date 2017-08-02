#include "Atendimento.h"
#include <string.h>


struct Atendimento * CriaAtendimento(char nome[30], char identidade[30], char dataVisita[30], char descricao[30], int c)
{
	struct Atendimento *A = malloc(sizeof(struct Atendimento));
	
	strcpy(A->nome, nome);
	strcpy(A->identidade, identidade);
	strcpy(A->dataVisita, dataVisita);
	strcpy(A->descricao, descricao);
	A->status = 0;
	A->codigo = c;

	return A;
}

char* getIdentidade (struct Atendimento* A)
{
	return A->identidade;	
}

char* getNome (struct Atendimento * A)
{
	return A->nome;
}

int getCodigo (struct Atendimento * A)
{
	return A->codigo;
}

int getStatus(struct Atendimento * A)
{
	return A->status;
}
void mudaStatus(struct Atendimento * A)
{
      A->status = 1;
}
void listarAtendimento(struct Atendimento *A){
	printf ("\nNome:%s\nIdentidade: %s\nDescricao: %s\nCodigo: %d\n", A->nome, A->identidade, A->descricao, A->codigo);
}
