# IMPLEMENTANDO UM TAD

Vamos considerar um programa que manipula dados sobre dois pontos.  

## PONTO.H
O arquivo ".h" contém a declaração/definição. Aqui é onde declaramos ponteiros e os protótipos das funções.  
Declarando um apelido para a struct dos nossos dados, o que facilitará implementar as funções  
```c
typedef struct ponto Ponto;                             //Ponto será o apelido desta struct
```
Protótipo das funções - exemplos de funções que serão utilizadas:
```c
    Ponto* pto_cria(float x, float y);                      //Cria um novo ponto
    int pto_atribui(Ponto* p, float x, float y);            //Atribui os valores "x" e "y" a um ponto
```

## PONTO.C
O arquivo ".c" contém a implementação. Aqui é onde declaramos os tipos de dados e implementamos as funções.  
Definindo o tipo de dado:
```c
    struct ponto{
        float x;
        float y;
    };
```

Implementando funções
```c
    Ponto* pto_cria(float x, float y){                      //passamos os parâmetros x e y, conforme definição da função
    Ponto* p = (Ponto*) malloc(sizeof(Ponto));              //alocamos espaço de memória para armazenar os pontos
    if(p != NULL){                                          //se a alocação deu certo
        p->x = x;                                               //atribui os valores de x e y para os campos x e y de ponto (struct)
        p->y = y;
    }
    return p;                                               //finalizada a atribuição, retorna o ponto (ponteiro p)
    }

    int pto_acessa(Ponto* p, float* x, float* y){
    if(p == NULL)
        return 0;
    *x = p->x;                                             //criamos dois ponteiros *x e *y que recebem o conteúdo de x e y (apontados por p)
    *y = p->y;
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
