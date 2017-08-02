#include "ArvoreB.h"

#define REMOCAO_NORMAL 1
#define REMOCAO_MENOR 0
#define NAO_PROMOVE 0
#define PROMOVE 1
#define CHAVE_JA_EXISTE 2

struct ArvoreB* CriaArvoreB()
{
	struct ArvoreB *A = malloc(sizeof(struct ArvoreB));
	A->raiz = malloc(sizeof(struct No));
	A->raiz->numElementos = 0;
	int i;
	for(i = 0; i < ORDEM; i++)
		A->raiz->Filho[i] = NULL;

	return A;
}

int Busca(struct ArvoreB *A, int e)
{
	//Árvore não foi criada
	if(A == NULL) return 0;

	return BuscaInterno(A->raiz, e);
}

int BuscaInterno(struct No *N, int e)
{
	if(N==NULL) return 0;
	
	//Percorre as Chave do nó enquanto e for maior que a chave atual
	int i = 0;
	while(i < N->numElementos && e > N->Chave[i])
		i++;

	//Se não encontrou a chave, busca no filho
	if(i == N->numElementos || e != N->Chave[i])
		return BuscaInterno(N->Filho[i], e);

	//Encontrou a chave
	return 1;
}

void InsereB(struct ArvoreB *A, int e)
{
	//Árvore não foi criada ainda
	if(A == NULL) return;

	int itemPromovido;
	struct No *filhoDItemPromovido;
	if( InsereInterno(A->raiz, e, &itemPromovido, &filhoDItemPromovido) == PROMOVE)
	{
		struct No *aux = A->raiz;
		A->raiz = malloc(sizeof(struct No));
		A->raiz->Chave[0] = itemPromovido;
		A->raiz->Filho[0] = aux;
		A->raiz->Filho[1] = filhoDItemPromovido;
		A->raiz->numElementos = 1;
	}
}

void Divide(struct No *N, int *itemPromovido, struct No **filhoDItemPromovido)
{
	//Declara vetores para armazenar as Chave e também os Filho da página cheia
	int Chave[ORDEM];
	struct No *Filho[ORDEM+1];

	//Copia os elementos para os vetores auxiliares
	int i;
	for(i = 0; i < N->numElementos && (*itemPromovido) > N->Chave[i]; i++)
	{
		Chave[i] = N->Chave[i];
		Filho[i] = N->Filho[i];
	}

	Filho[i] = N->Filho[i];
	Chave[i] = *itemPromovido;
	Filho[i+1] = *filhoDItemPromovido;
	i++;

	for(; i < ORDEM; i++)
	{
		Chave[i] = N->Chave[i-1];
		Filho[i+1] = N->Filho[i];
	} 

	//Declara uma nova página para fazer o split
	int meio = ORDEM/2;
	*filhoDItemPromovido = malloc(sizeof(struct No));
	(*filhoDItemPromovido)->numElementos = ORDEM-1-meio;

	//Seleciona o elemento do meio da página estourada
	*itemPromovido = Chave[meio];

	//Copia a primeira metade para a página da esquerda
	N->numElementos = meio;
	for(i = 0; i < meio; i++)
	{
		N->Chave[i] = Chave[i];
		N->Filho[i] = Filho[i];
	}
	N->Filho[i] = Filho[i];

	//Coopia a segunda metade para apágina da direita
	int j;
	for(i = meio+1, j = 0; i < ORDEM; i++, j++)
	{
		(*filhoDItemPromovido)->Chave[j] = Chave[i];
		(*filhoDItemPromovido)->Filho[j] = Filho[i];
	}
	(*filhoDItemPromovido)->Filho[j] = Filho[i];
}

int InsereInterno(struct No *N, int e, int *itemPromovido, struct No **filhoDItemPromovido)
{
	//Se for um nó nulo, insere na página pai
	if(N == NULL)
	{
		*itemPromovido = e;
		*filhoDItemPromovido = NULL;
		return PROMOVE;
	}

	//Senão, procura o ponto i onde e deveria estar na página atual
	int i;
	for(i = 0; i < N->numElementos && e > N->Chave[i]; i++);

	//Se o item e já estiver na página, retorna
	if(i < N->numElementos && e == N->Chave[i] )
	{
		printf("ERRO, item ja existente\n");
		return CHAVE_JA_EXISTE;
	}
	//Senão, manda inserir na página filha adequada
	int retorno = InsereInterno(N->Filho[i], e, itemPromovido, filhoDItemPromovido);

	//Se nenhum item for promovido da página filha, retorna
	if(retorno == NAO_PROMOVE || retorno == CHAVE_JA_EXISTE)
		return retorno;

	//Se um item for promovido e houver espaço nesta página
	if(N->numElementos < ORDEM-1)
	{
		int pos = i;
		for(i = N->numElementos; i > pos; i--)
		{
			N->Chave[i] = N->Chave[i-1];
			N->Filho[i+1] = N->Filho[i];
		} 
		N->Chave[pos] = *itemPromovido;
		N->Filho[pos+1] = *filhoDItemPromovido;
		N->numElementos++;
		return NAO_PROMOVE;
	}
	//Se não houver espaço, faz a divisão de página
	//itemPromovido será o pivô e filhoDItemPromovido será a nova página, o pivô será inserido na página pai
	Divide(N, itemPromovido, filhoDItemPromovido);
	return PROMOVE; 
}


void ImprimeInterno(struct No *N)
{
	if(N==NULL) return;

	int i;
	for(i = 0; i < N->numElementos; i++)
	{
		printf("%d ", N->Chave[i]);
	}
	printf("\n");

	for(i = 0; i < N->numElementos; i++)
	{
		ImprimeInterno(N->Filho[i]);
	}
	ImprimeInterno(N->Filho[i]);
}

int Remove_Interno(struct No *r, int e, int tipo)
{
	if(r == NULL) return e;

	int i = 0;
	if(tipo == REMOCAO_NORMAL) 
		while(i < r->numElementos && e > r->Chave[i])
			i++;

	if((tipo == REMOCAO_MENOR && r->Filho[i] == NULL) 
		|| (tipo == REMOCAO_NORMAL && i < r->numElementos && e == r->Chave[i]))
	{
		//Elemento encontrado
		if(r->Filho[i] == NULL)
		{
			//Folha, puxar todo mundo uma posição para trás
			int f = r->Chave[i];
			for(++i; i < r->numElementos; i++)
				r->Chave[i-1] = r->Chave[i];
			r->numElementos--;
			return f;
		}

		//remove pos i
		r->Chave[i] = Remove_Interno(r->Filho[i+1], e, REMOCAO_MENOR);
		i++;
	}
	else
	{
		//Elemento não encontrado
		Remove_Interno(r->Filho[i], e, tipo);
	}

	//Verifica se o filho onde ocorreu a remoção têm o número mínimo de elementos
	if(r->Filho[i] && r->Filho[i]->numElementos < (ORDEM-1)/2)
	{
		if(i > 0 && r->Filho[i-1]->numElementos > (ORDEM-1)/2)
		{
			//Recebe um item da esquerda
			int j;
			struct No *f = r->Filho[i];
			struct No *g = r->Filho[i-1];
			f->Filho[f->numElementos+1] = f->Filho[f->numElementos];
			for(j = f->numElementos; j > 0; j--)
			{
				f->Chave[j] = f->Chave[j-1];
				f->Filho[j] = f->Filho[j-1];
			}
			f->Chave[0] = r->Chave[i-1];
			f->Filho[0] = g->Filho[g->numElementos];
			(f->numElementos)++;
			r->Chave[i-1] = g->Chave[g->numElementos-1];
			(g->numElementos)--; 
		}
		else if(i < r->numElementos && r->Filho[i+1]->numElementos > (ORDEM-1)/2)
		{
			//Recebe um item da direita
			int j;
			struct No *f = r->Filho[i];
			struct No *g = r->Filho[i+1];

			f->Chave[f->numElementos] = r->Chave[i];
			f->Filho[f->numElementos+1] = g->Filho[0];
			(f->numElementos)++;
			r->Chave[i] = g->Chave[0];
			for(j = 1; j < g->numElementos; j++)
			{
				g->Chave[j-1] = g->Chave[j];
				g->Filho[j-1] = g->Filho[j]; 
			}
			g->Filho[j-1] = g->Filho[j];
			(g->numElementos)--; 
		}
		else
		{
			//Merge
			int j, k;

			struct No *f, *g;

			if(i>0)
			{
				f = r->Filho[i];
				g = r->Filho[i-1];
				i--;
			}
			else
			{
				g = r->Filho[i];
				f = r->Filho[i+1];
			}

			g->Chave[g->numElementos] = r->Chave[i];
			(g->numElementos)++;
			for(j = 0; j < f->numElementos; j++)
			{
				g->Chave[g->numElementos] = f->Chave[j];
				g->Filho[g->numElementos] = f->Filho[j];
				(g->numElementos)++;
			}
			g->Filho[g->numElementos] = f->Filho[j];
			free(f);
			for(; i < r->numElementos-1; i++)
			{
				r->Chave[i] = r->Chave[i+1];
				r->Filho[i+1] = r->Filho[i+2];
			}
			r->numElementos--;
		}
	}
	return e;
}

int Remove(struct ArvoreB *A, int e)
{
	if(A == NULL) return;

	int a = Remove_Interno(A->raiz, e, REMOCAO_NORMAL);

	if(A->raiz->numElementos == 0)
	{
		struct No *r = A->raiz;
		A->raiz = A->raiz->Filho[0];
		free(r);
	}
	return a;
}



