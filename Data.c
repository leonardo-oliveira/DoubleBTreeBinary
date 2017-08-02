#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"


struct Data * Criadata(char * nome){

    struct Data *a = malloc(sizeof(struct Data));
       a->nomeArq = nome;

    if ((a->arq = fopen(nome, "rb")) != NULL){  //se existir 
    	fseek(a->arq, 0, SEEK_SET);
        fread(&(a->quantidade), sizeof(int), 1, a->arq);
        printf("%d",a->quantidade);
    } else{
        a->arq = fopen(nome, "wb");    //caso nao exista
        a->quantidade = 0; // cabeçalho
        fwrite(&(a->quantidade), sizeof(int), 1, a->arq);
    }

    return a;
}

void InserirData(struct Data * A, struct Atendimento * R)
{

    if(A->arq == NULL)
	{
		exit(EXIT_FAILURE);
	}
	

    fseek(A->arq, (sizeof(int) + A->quantidade*sizeof(struct Atendimento)), SEEK_SET); // cabeçalho + a quantidade de registros
	fwrite(R, sizeof(struct Atendimento), 1, A->arq);    //esreve o registro no final do arquivo
	A->quantidade++; // incremendo o cabeçalho
    fseek(A->arq, 0, SEEK_SET); // posiciona cabeça em 0
	fwrite(&(A->quantidade), sizeof(int), 1, A->arq); //atualiza cabeçalho

}

struct Atendimento * LerDoData(struct Data *A, int p)
{

    if (p > A->quantidade || p < 0){
        return NULL;
    } else{   //tamanho do cabeçalho (int) mais p(posicao)* o tamanho da struct
        
        fseek(A->arq, (sizeof(int) + p*sizeof(struct Atendimento)), SEEK_SET); //multiplica p, posicionando a cabeça de leitura no lugar correto
        struct Atendimento  *a = malloc(sizeof(struct Atendimento));
        fread(a, sizeof(struct Atendimento), 1, A->arq); // le o registro;
        return a;
    }

}

int NumAtendimentos(struct Data * A)
{
    return A->quantidade;
}

void EscreveData(struct Data *A, struct Atendimento * R, int p)
{
    fseek(A->arq, (sizeof(int) + p*sizeof(struct Atendimento)), SEEK_SET); // posiciona a cabeça de leitura no lugar correto
    fwrite(R, sizeof(struct Atendimento), 1, A->arq); // faz a leitura do arquivo
}
