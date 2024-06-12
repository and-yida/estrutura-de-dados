#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int vFila[MAX]; 
    int inicio; 
	int fim;
} Fila;

int inicializacao(Fila *fila) {
	fila->inicio = 0; 
	fila->fim = 0; 
}

short vazia(Fila *fila){// verifica se a fila está vazia
	if (fila->inicio == fila->fim)
		return 1;
	else 
		return 0;
}

short cheia(Fila *fila){ // verifica se a fila está cheia
	if (fila->fim == MAX)
		return 1;
	else 
		return 0;
}

void inserir(Fila *fila, int elemento){
	if(cheia(fila)) {
		printf("Fila Cheia!!!");	
	}
	else{
		fila->vFila[fila->fim] = elemento;
		fila->fim++;
	}
} 
// Sendo a variável fila->fim inicializada com o valor 0, primeiro insere o elemento e depois incrementa (adiciona 1 no fila->fim) 

void remover(Fila *fila, int *elemento){
	if (vazia(fila)){
		printf("Fila Vazia - Não há elementos na fila para remoção!!!");	
	}
	else{
		*elemento = fila->vFila[fila->inicio] ;
		fila->inicio++;
	}
}
// Sendo a variável fila->inicio  inicializada com o valor 0, primeiro remove o elemento e depois decrementa (subtrai 1 do fila->inicio)

void obterIncioFila(Fila *fila, int *elemento){
	if (vazia(fila)) 
		printf("Fila Vazia - Não há elementos na fila!!!");	
	else 
		*elemento = fila->vFila[fila->inicio] ;
}
// Retorna o elemento que está no inicio da fila (fila->inicio)


void main(){
	int i, elemIni, elemRem;
	Fila F1;
	inicializacao(&F1);
	if(vazia(&F1))
		printf("\nFila vazia!");
		
	//Inserindo valores na fila
	inserir(&F1, 1);
	inserir(&F1, 1);
	inserir(&F1, 2);
	inserir(&F1, 3);
	inserir(&F1, 5);
	inserir(&F1, 8);
	inserir(&F1, 13);
	inserir(&F1, 21);
	inserir(&F1, 34);
	inserir(&F1, 55);
	printf("\nInseri 10 elementos!");
	
	if(cheia(&F1))
		printf("\nFila cheia!");
		
	//Imprimindo a fila
	printf("\nInicio: %d", F1.inicio);
	printf("\nFim: %d\n", F1.fim);
	for(i=0 ; i<MAX ; i++)
		printf("%d ", F1.vFila[i]);
		
	obterIncioFila(&F1, &elemIni);
	printf("\nElemento do inicio: %d", elemIni);
	
	remover(&F1, &elemRem);
	printf("\nRemovi o elemento: %d", elemRem);
	remover(&F1, &elemRem);
	printf("\nRemovi o elemento: %d", elemRem);
	remover(&F1, &elemRem);
	printf("\nRemovi o elemento: %d", elemRem);
	remover(&F1, &elemRem);
	printf("\nRemovi o elemento: %d", elemRem);
	
	//Imprimindo a fila
	printf("\nInicio: %d", F1.inicio);
	printf("\nFim: %d\n", F1.fim);
	for(i=0 ; i<MAX ; i++)
		printf("%d ", F1.vFila[i]);
	
	//Verificando a limitação dessa implementação
	printf("\n");
	inserir(&F1, 89);

}