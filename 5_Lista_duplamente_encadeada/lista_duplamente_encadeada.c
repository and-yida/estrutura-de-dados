#include <stdio.h>
#include <stdlib.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void main(){

    struct aluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));
}