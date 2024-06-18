#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool insere_posicao(Lista* li, struct usuario u, int i){
    int k;
    // casos em que não é possível inserir: lista não existe, a lista está cheia ou a posição i é inválida
    if(li == NULL || li->qtd == MAX || i<0 || i>li->qtd)
        return false;
    // posicionamos na primeira posição livre ao fim da lista e, de trás para frente,
    // vamos atribuindo que a posição atual recebe a anterior
    for(k=li->qtd; k>i; k--)
        li->usuarios[k] = li->usuarios[k-1];
    // a posição desejada recebe o novo usuário 
    li->usuarios[i] = u;
    // incrementa o tamanho da lista
    li->qtd++;
    return true;
}

bool remove(Lista* li, int chave){
    if(li == NULL)
        return false;
    int k, i = 0;
    // busca a posição do elemento a ser excluído
    while(i<li->qtd && li->usuarios[i].chave != chave)
        i++;
    if(i == li->qtd)    //elemento nao encontrado
        return false;
    // a partir da posição i, vamos atribuindo à posição atual o elemento posterior
    for(k=i; k<li->qtd-1; k++)
        li->usuarios[k] = li->usuarios[k+1];
    li->qtd--;
    return true;
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

void reinicializa_lista(Lista* li){
    li->qtd = 0;
}