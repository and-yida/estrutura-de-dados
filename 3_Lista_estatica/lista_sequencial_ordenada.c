#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

// definição lista
struct lista{
    int qtd;
    struct aluno dados[MAX];
};

typedef struct lista Lista;

Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    if(li->qtd == MAX)//lista cheia
        return 0;
    int k,i = 0;
    while(i<li->qtd && li->dados[i].matricula < al.matricula)
        i++;

    for(k=li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];

    li->dados[i] = al;
    li->qtd++;
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if(li->qtd == 0)
        return 0;
    int k,i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    for(k=i; k< li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if(li->qtd == 0)
        return 0;
    int i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    li->qtd--;
    li->dados[i] = li->dados[li->qtd];
    return 1;
}

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0 ||  pos > li->qtd)
        return 0;
    *al = li->dados[pos-1];
    return 1;
}

int consulta_lista_elemento(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    int i = 0;
    while(i<li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd)//elemento nao encontrado
        return 0;

    *al = li->dados[i];
    return 1;
}

// busca binária deve receber, a princípio, inicio 0 e fim o último elemento da lista, retornado por ultimo_elemento()
// divide a lista no meio; se a posição meio for o elemento procurado, retorna meio.
// se não, compara se este elemento é menor ou maior que o procurado
// se o elemento procurado for maior que o meio, o início passa a ser meio+1 e a busca se dá na metade superior;
// se o elemento procurado for menor que o meio, o início se mantém e o fim passa a meio-1, buscando na metade inferior
int busca_binaria(Lista* li, struct aluno al, int inicio, int fim){
    int meio = (inicio+fim)/2;

    if(inicio>fim) return -1;       // se não achou o elemento
    else if(al.matricula == li->dados[meio].matricula) return meio;
    else if(al.matricula > li->dados[meio].matricula) return (busca_binaria(li,al,meio+1,fim));        // busca na metade superior
    else if(al.matricula < li->dados[meio].matricula)return (busca_binaria(li,al,inicio,meio-1));      // busca na metade inferior
}

// marca o fim da lista, para ser utilizado na busca binária
int ultimo_elemento(Lista* li){
    return li->qtd-1;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    int i;
    for(i=0; i< li->qtd; i++){
        printf("Matricula: %d\n",li->dados[i].matricula);
        printf("Nome: %s\n",li->dados[i].nome);
        printf("Notas: %f %f %f\n",li->dados[i].n1,
                                   li->dados[i].n2,
                                   li->dados[i].n3);
        printf("-------------------------------\n");
    }
}

void main(){

    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
    int i;
    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);

    imprime_lista(li);

    struct aluno al1 = {1,"Bianca",9.7,6.7,8.4};

    int tamanho = ultimo_elemento(li);
    int posicao = busca_binaria(li, al1, 0, tamanho);

    printf("\nPosição de Bianca: %d \n", posicao);

    struct aluno al4 = {4,"Ricardo",7.5,8.7,6.8};

    tamanho = ultimo_elemento(li);
    posicao = busca_binaria(li, al4, 0, tamanho);

    printf("\nPosição de Ricardo: %d \n", posicao);

    libera_lista(li);
    system("pause");
}
