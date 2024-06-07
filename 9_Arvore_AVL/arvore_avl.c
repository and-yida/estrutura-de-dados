#include <stdio.h>
#include <stdlib.h>

struct No{
    int dado;
    int altura;
    struct No *esq;
    struct No *dir;
};

// ponteiro para a raiz da árvore
typedef struct No* Arvore;

Arvore* cria_arvore(){
    Arvore* raiz = (Arvore*) malloc(sizeof(Arvore));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

// percorre toda a esquerda, libera o nó folha, passa para a direita, se houver
// e vai liberando assim recursivamente os nós ascendentes
void libera_No(struct No* no){
    if(no == NULL)
        return;
    libera_No(no->esq);
    libera_No(no->dir);
    free(no);
    no = NULL;
}

// por fim, libera a raiz
void libera_Arvore(Arvore* raiz){
    if(raiz == NULL)
        return;
    libera_No(*raiz);   //libera cada nó
    free(raiz);   //libera a raiz
}

int estaVazia(Arvore *raiz){
    if(raiz == NULL)    // se houve erro na criação
        return 1;
    if(*raiz == NULL)   // se a árvore está vazia
        return 1;
    return 0;
}

//-----Funções auxiliares----

// retorna a altura do nó
int altura_No(struct No* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

// calcula o fator de balanceamento do nó a partir das alturas das sub-árvores filhas
int fatorBalanceamento_No(struct No* no){
    return labs(altura_No(no->esq) - altura_No(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}


//---------------------------


// percorre toda a esquerda até o nó folha, compara com a direita, se houver,
// e a maior altura entre os dois é retornada. a altura em um ponto é dada pela altura acumulada + 1.
// ascende recursivamente na árvore calculando as alturas até a raiz
int altura(Arvore *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura(&((*raiz)->esq));
    int alt_dir = altura(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return(alt_esq + 1);
    else
        return(alt_dir + 1);
}

// como a altura corresponde também ao número de nós, vai somando as alturas
// até o nó raiz
int total_No(Arvore *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = total_No(&((*raiz)->esq));
    int alt_dir = total_No(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

// imprime o valor do nó;
// visita o nó esquerdo e imprime; 
// visita o nó direito e imprime. 
void preOrdem(Arvore *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->dado);   // começa pela raiz
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}

// visita o nó esquerdo;
// imprime o valor do nó;
// visita o nó direito. 
void emOrdem(Arvore *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem(&((*raiz)->esq));
        printf("%d\n",(*raiz)->dado);
        emOrdem(&((*raiz)->dir));
    }
}

// visita o nó esquerdo;
// visita o nó direito;
// mostra o valor do nó. 
void posOrdem(Arvore *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir));
        printf("%d\n",(*raiz)->dado);
    }
}

void main(){
    
    Arvore* raiz = cria_arvore();

    int res,i;
    int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6};

    raiz = cria_arvore();

    for(i=0;i<N;i++){
        res = insere_ArvAVL(raiz,dados[i]);
    }
}