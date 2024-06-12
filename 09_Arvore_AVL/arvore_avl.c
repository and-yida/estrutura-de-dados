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


//---------------------------

//----------Rotações---------

// As rotações são aplicadas no ancestral mais próximo do nó inserido
// cujo fator de balanceamento passa a ser +2 ou -2.
// As funções abaixo, portanto, recebem esse ancestral, que corresponde
// à raiz da sub-árvore a ser rotacionada.


// A partir da raiz da sub-árvore:
// direita do filho da esquerda se torna a sua esquerda. 
// direita do filho da esquerda recebe a raiz. 
// filho da esquerda se torna raiz. 
void RotacaoLL(Arvore *raiz){
    struct No *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->altura = maior(altura_No((*raiz)->esq),altura_No((*raiz)->dir)) + 1;
    no->altura = maior(altura_No(no->esq),(*raiz)->altura) + 1;
    *raiz = no;
}

// A partir da raiz da sub-árvore:
// esquerda do filho da direita se torna a sua direita. 
// esquerda do filho da direita recebe a raiz. 
// filho da direita se torna raiz. 
void RotacaoRR(Arvore *raiz){
    struct No *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->altura = maior(altura_No((*raiz)->esq),altura_No((*raiz)->dir)) + 1;
    no->altura = maior(altura_No(no->dir),(*raiz)->altura) + 1;
    (*raiz) = no;
}

// rotação à esquerda no filho da esquerda; rotação à direta na raiz
void RotacaoLR(Arvore *raiz){
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

// rotação à direita no filho da direita; rotação à esquerda na raiz
void RotacaoRL(Arvore *raiz){
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}


//---------------------------

int insere_Arvore(Arvore *raiz, int valor){

    int res;    // variável para indicar o sucesso da inserção

    // árvore vazia ou nó folha
    if(*raiz == NULL){
        struct No *novo;
        novo = (struct No*)malloc(sizeof(struct No));
        if(novo == NULL)
            return 0;

        novo->dado = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    // para esquerda
    struct No *atual = *raiz;
    if(valor < atual->dado){
        if((res = insere_Arvore(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_No(atual) >= 2){
                if(valor < (*raiz)->esq->dado ){    // esquerda
                    RotacaoLL(raiz);
                }else{  // direita
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        // para direita
        if(valor > atual->dado){
            if((res = insere_Arvore(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_No(atual) >= 2){
                    if((*raiz)->dir->dado < valor){     // direita
                        RotacaoRR(raiz);
                    }else{  // esquerda
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    // atualiza a altura do nó
    atual->altura = maior(altura_No(atual->esq),altura_No(atual->dir)) + 1;

    return res;
}

// função auxiliar caso o nó removido tenha 2 filhos.
// procura o elemento mais à esquerda da árvore da direita para substituir o nó removido
struct No* procuraMenor(struct No* atual){
    struct No *no1 = atual;
    struct No *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_Arvore(Arvore *raiz, int valor){
	if(*raiz == NULL){
	    printf("Valor não existe!!\n");
	    return 0;
	}

    int res;

    // se o valor for menor que o valor da raiz, prossegue para a árvore da esquerda
	if(valor < (*raiz)->dado){
        // quando a remoção aí acontece
	    if((res = remove_Arvore(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_No(*raiz) >= 2){
                // se desbalanceada, testa a altura da sub-árvore da direita
                if(altura_No((*raiz)->dir->esq) <= altura_No((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

    // se o valor for menor que o maior da raiz, prossegue para a árvore da direita
	if((*raiz)->dado < valor){
        // quando a remoção aí acontece
	    if((res = remove_Arvore(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_No(*raiz) >= 2){  // se desbalanceada, testa a altura da sub-árvore da esquerda
                if(altura_No((*raiz)->esq->dir) <= altura_No((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

    // encontrou o valor
	if((*raiz)->dado == valor){
        // nó tem 1 filho ou nenhum
        // 1 filho: o filho substitui o nó
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
			struct No *antecessor = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(antecessor);

		// nó tem 2 filhos
        }else {
            // procura a valor mais à esquerda (menor valor) da sub-ávore da direita
            // para substituir o nó removido
			struct No* temp = procuraMenor((*raiz)->dir);
			(*raiz)->dado = temp->dado;
			remove_Arvore(&(*raiz)->dir, (*raiz)->dado);
            if(fatorBalanceamento_No(*raiz) >= 2){
				if(altura_No((*raiz)->esq->dir) <= altura_No((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_No((*raiz)->esq),altura_No((*raiz)->dir)) + 1;
		return 1;
	}

    // atualiza a altura da raiz
	(*raiz)->altura = maior(altura_No((*raiz)->esq),altura_No((*raiz)->dir)) + 1;

	return res;
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