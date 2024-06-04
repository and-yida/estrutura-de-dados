#include <stdio.h>
#include <stdlib.h>

// definição do nó da lista
struct elemento{
    char caractere;
    struct elemento *prox;
};

typedef struct elemento Elem;

// ponteiro para ponteiro: receberá o endereço para a lista a ser criada
typedef struct elemento* String;

String* cria_lista(){
    String* li = (String*) malloc(sizeof(String));
    // se deu certo, preenche os campos do primeiro elemento com NULL
    if(li != NULL)
        *li = NULL;
    return li;
}

int insere_lista_final(String* li, char c){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->caractere = c;
    no->prox = NULL;
    if((*li) == NULL){ // lista vazia
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}


int consulta_iguais(String* str1, String* str2){
    if(str1 == NULL || str2 == NULL)
        return 0;
    Elem *no1 = *str1, *no2 = *str2;
    int flag = 0;
    while(no1->caractere == no2->caractere && no1 != NULL && no2 != NULL){
        no1 = no1->prox;
        no2 = no2->prox;
    }
    if(no1 == NULL && no2 != NULL){
        flag = 1;
        return flag;
    }
    if(no1 != NULL && no2 == NULL){
        flag = 1;
        return flag;
    }
    return flag;
}