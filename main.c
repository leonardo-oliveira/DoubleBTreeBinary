#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"
#include "ArvoreB.h"
#include "ArvoreBString.h"
#include "Controlador.h"

int inicializaMenu()
{
    char nomeArquivo[15];
    char nome[30];
    char data[30];
    char descricao[30];
    char identidade[35];
    struct Atendimento *A;
    Controlador* Control = Criardata("binario.dat");
    int opcao;
            while(1){
                scanf("%d", &opcao);
                if (opcao == 1){
                    int codigo = quantidade(Control);
                    printf("Digite o nome do paciente:\n");
                    scanf("%s", nome);
                    printf("Digite a descricao do atendimento:\n");
                    scanf("%s", &descricao);
                    printf("Digite a identidade\n");
                    scanf("%s", &identidade);
                    printf("Digite a data\n");
                    scanf("%s", &data);
                    printf("%d", codigo);
                    A = CriaAtendimento(nome,identidade, data, descricao, codigo);
                    Inserir(Control, A);
                    printf("%d", codigo);
                }
                if (opcao == 2){
                    int x;
                    scanf("%d", &x);
                    A = BuscarCodigo(Control, x);
                    listarAtendimento(A);

                }
            }
}
int main()
{
	inicializaMenu();
	return 0;
}

