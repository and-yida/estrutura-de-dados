#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct usuario{
    int chave;
};

// definição lista
struct lista{
    int qtd;
    struct usuario usuarios[MAX];
};

typedef struct lista Lista;

void inicializa_lista(Lista* li){
    li->qtd = 0;
}

int tamanho(Lista* li){
    return li->qtd;
}

// busca a posição do elemento desejado
// retorna -1 se a lista não existe ou se o elemento não foi encontrado
int busca_por_elemento(Lista* li, int chave){
    if(li == NULL)
        return -1;
    int i = 0;
    while(i<li->qtd && li->usuarios[i].chave != chave)
        i++;
    if(i == li->qtd)    //elemento nao encontrado
        return 0;
    return i;
}

// busca o elemento da posição desejada e retorna um usuario
// retorna -1 se a lista não existe ou se o elemento não foi encontrado
int busca_por_posicao(Lista* li, int posicao, struct usuario *u){
    if(li == NULL)
        return -1;
    u = li[posicao].usuarios;
    return u;
}

void impressao(Lista* li){
    int i, tamanho;
    tamanho = li->qtd;
    for(i=0; i<tamanho; i++){
        printf("Chave: %d\n",li->usuarios[i].chave);
    }
}