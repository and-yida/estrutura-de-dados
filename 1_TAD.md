# TIPO ABSTRATO DE DADOS

A ideia de tipo abstrato de dados (TAD) é a de desvincular o tipo de dado (valores e operações) de sua implementação.  
Dividimos a programação em duas etapas:  
  - Aplicação (definição)
  - Implementação.  

No que diz respeito à aplicação, o TAD pressupõe um conjunto de valores e o conjunto de operações sobre estes valores. Definidos esses conjuntos, pode-se implementar aquele tipo de dado. A implementação de um TAD é chamada de estrutura de dados.  
Um tipo abstrato de dados requer que operações gerais sejam permitidas sobre os dados sem se ligar a uma representação particular. Isso implica no ocultamento de dados, isto é, o usuário manipula apenas as operações mas não acessa diretamente os dados.  
As operações para a manipulação de dados incluem: criação da estrutra; inclusão e remoção de elementos; acesso a um elemento; etc.  

## Implementando um TAD

Uma boa técnica de programação consiste em implementar os TADs em arquivos separados do programa principal. Para isso, geralmente separa-se a declaração e a implementação em dois arquivos:  
  - NomeDoTAD.h : com a declaração  
  - NomeDoTAD.c : com a implementação  
O arquivo ".h" contém: protótipos das funções, tipos de ponteiro e dados globalmente acessíveis.  
O arquivo ".c" contém: declaração do tipo de dados e implementação das suas funções.  

Ex.:

`ContaBancaria.h`
```c
    //definição do tipo
    typedef struct
    {
    int numero;
    double saldo;
    } ContaBancaria;
    
    //cabeçalho das funções
    void Inicializa(ContaBancaria* conta, int numero, double saldo);
    void Deposito (ContaBancaria* conta, double valor);
    void Saque (ContaBancaria* conta, double valor);
    void Imprime (ContaBancaria conta);
```

`ContaBancaria.c`
```c
    #include <stdio.h>
    #include "Contabancaria.h"
    
    void Inicializa(ContaBancaria* conta, int numero, double saldo)
    {
        (*conta).numero = numero;
        (*conta).saldo = saldo;
    }
    void Deposito (ContaBancaria* conta, double valor)
    {
        (*conta).saldo += valor;
    }
    void Saque (ContaBancaria* conta, double valor)
    {
        (*conta).saldo -= valor;
    }
    void Imprime (ContaBancaria conta)
    {
        printf("Numero: %d\n", conta.numero);
        printf("Saldo: %f\n", conta.saldo);
    }
```

`Main.c`
```c
    #include <stdio.h>
    #include <stdlib.h>
    #include "ContaBancaria.c"
    #include <conio.h>
    
    int main (int argc, char **argv)
    {
        ContaBancaria conta1;
        Inicializa(&conta1, 918556, 300.00);
        printf("\nAntes da movimentacao:\n ");
        Imprime(conta1);
        Deposito(&conta1, 50.00);
        Saque(&conta1, 70.00);
        printf("\nDepois da movimentacao:\n ");
        Imprime (conta1);
        getch();
    }
```

No caso acima, ContaBancaria.h, ContaBancaria.c e Main.c devem estar na mesma pasta.
