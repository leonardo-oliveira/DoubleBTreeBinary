#ifndef Data_H
#define Data_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Atendimento.h"

struct Data
{
    FILE * arq;
    char * nomeArq;
    int quantidade;
};

struct Data * Criadata(char * nome);
void InserirData(struct Data * A, struct Atendimento * R);
struct Atendimento * LerDoArquivo(struct Data *A, int p);
int NumAtendimentos(struct Data * A);
void EscreveArquivo(struct Data *A, struct Atendimento * R, int p);

#endif
