#ifndef CONTROLADOR_H
#define CONTROLADOR_H

//#include "ArvoreBString.c"
#include "Atendimento.h"
#include "ArvoreB.h"
#include "Data.h"
#include <stdlib.h>



typedef struct
{
	struct Data *Data;
	struct ArvoreB* codigo;
	//struct ArvoreBString* nome;

} Controlador;

Controlador* Criardata(char *nome);
void Inserir( Controlador *A, struct Atendimento *R);
struct Atendimento * BuscarCodigo(Controlador *A, int c);
struct Atendimento* RemoverAtendimento (Controlador *A, int c);
int quantidade(Controlador* A);

#endif
