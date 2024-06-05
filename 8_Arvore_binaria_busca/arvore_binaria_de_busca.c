#include <stdio.h>
#include <stdlib.h>

struct No{
    int dado;
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

int insere(Arvore* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct No* novo;
    novo = (struct No*) malloc(sizeof(struct No));
    if(novo == NULL)
        return 0;
    novo->dado = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    // procura o local para o novo nó
    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct No* atual = *raiz;
        struct No* ant = NULL;
        // navega nos nós até chegar em um nó folha
        while(atual != NULL){
            ant = atual;
            if(valor == atual->dado){
                free(novo);
                return 0;   // elemento já existe
            }

            if(valor > atual->dado)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        // insere como filho do nó folha
        if(valor > ant->dado)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

// busca pelo nó a ser removido, enquanto a função remove_atual
// resolve as dependências em relação a remoção
int remove_Arvore(Arvore *raiz, int valor){
    if(raiz == NULL)
        return 0;

    struct No* ant = NULL;
    struct No* atual = *raiz;
    while(atual != NULL){
        // se achou o nó a ser removido, invoca remove_atual
        if(valor == atual->dado){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        // se não achou, continua percorrendo a árvore
        ant = atual;
        if(valor > atual->dado)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

// trata as pendências do nó a ser removido
struct No* remove_atual(struct No* atual) {
    struct No *no1, *no2;
    // primeiro caso: se o nó é folha ou tem um filho apenas
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    // segundo caso: se o nó possui dois filhos, vai buscar o nó mais à direita na sub-árvore da esquerda
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // copia o nó achado em questão para o lugar do nó removido
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

// retorna 0 se o valor não se encontra na árvore, e 1 se o valor foi encontrado com sucesso
int consulta(Arvore *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct No* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->dado){
            return 1;
        }
        if(valor > atual->dado)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

// busca que retorna o nó procurado
// nos casos em que a árvore é inválida ou o valor não existe, retorna um nó com informações "vazias"
struct No busca(Arvore *raiz, int valor, struct No *encontrado){
    if(raiz == NULL)
        encontrado->dado = 0;
        encontrado->dir = NULL;
        encontrado->esq = NULL;
        return *encontrado;

    struct No* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->dado){
            encontrado->dado = atual->dado;
            encontrado->dir = atual->dir;
            encontrado->esq = atual->esq;
            return *encontrado;
        }
        if(valor > atual->dado)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    encontrado->dado = 0;
    encontrado->dir = NULL;
    encontrado->esq = NULL;
    return *encontrado;
}


void main(){

    int n = 8, dados[8] = {50,100,30,20,40,45,35,37};

    // ponteiro de ponteiro para a raiz
    Arvore* raiz = cria_arvore();

    int i;
    for(i=0; i<n; i++)
        insere(raiz,dados[i]);

    int alt = altura(raiz);
    int total_nos = total_No(raiz);
}