#include "Controlador.h"

Controlador* Criardata(char *nome) //função que vai inicializar o arquivo nas arvores B's
{
        Controlador *A = malloc(sizeof(Controlador));
        struct Atendimento *Z;

	   A->Data = Criadata(nome); //cria ou devolve nome do arquivo, retornando o nome do arquivo ja e gravando no data do controlador
	   A->codigo = CriaArvoreB(); // cria a arvore 
	   //A->nome = CriaArvoreBString();

	   int i;

	   for(i = 0; i < NumAtendimentos(A->Data); i++){
            Z = LerDoData(A->Data,i);

            if(getStatus(Z) == 0 ){

                InsereB(A->codigo, getCodigo(Z));    //cria estrutura para o codigo e ja inicia antes de tudo a estrutura com o arquivo
         //       InsereBString(A->nome, getNome(Z));  //criar estrutura para o nome
            }
        }

    return A;
}

void Inserir(Controlador *A, struct Atendimento *R)
{

    	InsereB(A->codigo, getCodigo(R));// insere na arvore de codigos
        //InsereBString(A->nome, getNome(R)); // insere na arvore de nomes
        InserirData(A->Data,R); //insere no final do arqivo

}
int quantidade(Controlador* A){
	return NumAtendimentos(A->Data);
}

struct Atendimento * BuscarCodigo(Controlador *A, int a)
{
	   // busca na arvore
	   int existe = Busca(A->codigo, a);
	   if(existe == 0){ // se nao existe na arvore
            return NULL;
	   }
	   struct Atendimento  * R = malloc(sizeof(struct Atendimento));
	   R = LerDoData(A->Data, a); // lendo no arquivo com o codigo da posicao
	   return R;
}
struct Atendimento* RemoverAtendimento (Controlador *A, int a)
{
	// Remover da Arvore B e alterar a flag do Atendimento.

	   struct Atendimento *R;
        
        int existe = Busca(A->codigo, a);
        if(existe == 0){ // se nao existe na arvore
            return NULL;
        }
        
        int posicao = (Remove(A->codigo, a)); // removendo da B de código
        R = LerDoData(A->Data, posicao);   //lendo o arquivo da posicao p
        //RemoveBString(A->nome, getNome(R)); // removendo da B de nome
        mudaStatus(R);                // setar seu status como removido
        EscreveData(A->Data, R, posicao);  //escrever na sua posicao, ele mais a mudanca do removido

	   return R;

}
