## LISTA ESTÁTICA
<br />

A lista estática trata-se de um array (vetor).  
Vantagens:  
  - Acesso rápido e direto aos elementos (índice);
  - Tempo constante para acessar um elemento;
  - Facilidade em modificar dados.  

Desvantagens:  
  - Definição prévia do tamanho do array;
  - Dificuldade em inserção e remoção de elementos, por conta da necessidade de deslocamento de outros elementos.

<br />

## IMPLEMENTANDO UMA LISTA ESTÁTICA

### lista.h

Tipo de dado armazenado
```c
  struct aluno{
        int matricula;
        char nome[30];
        float n1,n2,n3;
    };
```

Tamanho do vetor
```c
    #define MAX 100
```

Apelido para "lista"
```c
    typedef struct lista Lista;
```

```c
Protótipos das funções - ex.:
    Lista* cria_lista();
    void libera_lista(Lista* li);
    int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
```

### lista.c

Tipo de "lista"
```c
    //definindo a lista
    struct lista{
        //qtd remete à quantidade de posições já ocupadas na lista
        int qtd;
        struct aluno dados[MAX];
    };
```

Implementação das funções  
Ex.:
```c
    Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->qtd = 0;
    return li;
    }
 ```
  O ponteiro *li passa a apontar para o campo qtd, que recebe o valor 0 - isto é, a lista está vazia.  

  Ex.: 
  ```c
    int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
        if(li == NULL || pos <= 0 ||  pos > li->qtd)
            return 0;
        *al = li->dados[pos-1];
        return 1;
    }
```

<br />

## OBTENDO INFORMAÇÕES DA LISTA

### Exemplo de código  

Obtendo o tamanho da lista
```c
    int tamanho_lista(Lista* li){
        if(li == NULL)                                              //se o ponteiro não retornar nada, há um erro
            return -1;
        else
            return li->qtd;                                         //caso não haja erro, retorna o valor do ponteiro apontando para qtd
    }

    //No programa principal
    int x = tamanho_lista(li);
```

<br />

## INSERÇÃO

Inserção ordenada na lista estática
```c
    int insere_lista_ordenada(Lista* li, struct aluno al){
        if(li == NULL)
            return 0;
        if(li->qtd == MAX)//lista cheia
            return 0;
        int k,i = 0;
        while(i<li->qtd && li->dados[i].matricula < al.matricula)           //percorre a lista enquanto não atingiu o fim da lista (qtd) e enquanto o dado matrícula da lista for menor do que a matrícula que estamos tentando inserir
            i++;

        for(k=li->qtd-1; k >= i; k--)                                       //delocando todos os elementos, a partir do fim da lista,para a próxima posição para inserir o novo dado al, enquanto o contador k for menor ou igual àquela posição i encontrada
            li->dados[k+1] = li->dados[k];                                  //no deslocamento, a posição seguinte recebe o dado da posição atual

        li->dados[i] = al;                                                  //a posição i recebe o novo dado al
        li->qtd++;                                                          //o tamanho da lista é incrementado pois agora há um elemento a mais
        return 1;
    }
```

<br />
<br />
<br />
<br />

_________________________________________

<sub> Fontes:  
BACKES, A. https://programacaodescomplicada.wordpress.com/indice/estrutura-de-dados/  
CORREIA, R. C. M. Estrutura de Dados I. </sub>
