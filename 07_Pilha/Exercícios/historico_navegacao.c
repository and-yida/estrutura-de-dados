#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX 100

struct Paginas {
    char url[30];
};

typedef struct pilha {
    struct Paginas vetor[MAX];
    int topo;
} Pilha;


void inicializa(Pilha* P) {
    P->topo = 0; // pilha vazia
}

void visitar(Pilha* P, struct Paginas *paginas, int *contador){
    int i = *contador;      // i recebe o conteúdo de contador de visitas
    if (i >= 5) {
        printf("\n Número máximo de visitas atingido!\n");
        return;
    }
    push(P, &(paginas[i]));  // adiciona, em visitadas, a página correspondente ao contador atual
    imprime_abrir(P);
    (*contador)++;          // incrementa o número da visita
}

// "abre a página" - imprime a página para indicar que foi aberta
void imprime_abrir(Pilha* P) {
    printf("\n Link aberto: %s\n", P->vetor[P->topo - 1].url);
}

// insere
void push(Pilha* P, struct Paginas *pagina){
    // se pilha cheia
    if (P->topo == MAX){
        printf("\n Operação indisponível: máximo de páginas alcançada.\n");
        return;       
    }
    P->vetor[P->topo] = *pagina;     // topo recebe pagina
    P->topo++;      // atualiza topo com a próxima posição
}

// remove
void pop(Pilha* P){
    // se pilha vazia
    if (P->topo == 0){
        printf("\n Operação indisponível: pilha vazia.\n");
        return;
    }
    P->topo--;      // atualiza topo
}

// voltar consiste retirar a página atual de visitadas, inserí-la em removidas e exibir a entrada mais recente de visitadas
// pop em visitadas, push em removidas
void voltar(Pilha* P, Pilha* removidas, struct Paginas *pagina){
    // se a pilha de visitadas estiver vazia ou conter somente um elemento, não há como voltar
    if(P->topo <= 1){
        printf("\n Operação indisponível: não há páginas visitadas.\n");
        return;
    }  
    else{
        if (removidas->topo == MAX){
            printf("\n Operação indisponível: máximo de páginas alcançada.\n");
            return;       
        }
        // copia a página atual para a pilha de removidas e realiza um pop na pilha visitadas
        *pagina = P->vetor[P->topo - 1];
        push(removidas, pagina);        // removidas recebe pagina
        pop(P);     // pop na pilha visitadas
        printf("\nLink aberto: %s", P->vetor[P->topo - 1].url);
    }  
}

// avançar consiste em retirar a entrada mais recente de removidas, inserí-la em visitadas e exibir a entrada mais recente de visitadas
// pop em removidas, push em visitadas
void avancar(Pilha* P, Pilha* removidas, struct Paginas *pagina){
    // se a pilha de removidas estiver vazia, não há como avançar
    if(removidas->topo == 0){
        printf("\n Operação indisponível: não há outras páginas visitadas.\n");
        return;
    }
    else{
        *pagina = removidas->vetor[removidas->topo - 1];
        push(P, pagina);
        pop(removidas);
        printf("\n Link aberto: %s", P->vetor[P->topo - 1].url);
    }
}

void main() {
    
    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    Pilha pilha_visitadas;
    Pilha pilha_removidas;
    int escolha;
    int visita = 0;    // contador para visitas. vamos supor que somente as 5 urls do vetor 'paginas' podem ser acessadas
    struct Paginas pagina;

    struct Paginas paginas[5] = {{"www.google.com"},
                                 {"www.youtube.com"},
                                 {"www.gmail.com"},
                                 {"www.linkedin.com"},
                                 {"www.instagram.com"}
                                };

    inicializa(&pilha_visitadas);
    inicializa(&pilha_removidas);

    // menu de operações
    while(1) {
        printf("\n\n----------Menu----------\n\n");
        printf("1 - Avançar\n");
        printf("2 - Voltar\n");
        printf("3 - Abrir novo link\n");
        printf("4 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch(escolha) {
            case 1:
                avancar(&pilha_visitadas, &pilha_removidas, &pagina);
                break;
            case 2:
                voltar(&pilha_visitadas, &pilha_removidas, &pagina);
                break;
            case 3:
                visitar(&pilha_visitadas, paginas, &visita);
                break;
            case 4:
                return;       // sai do menu
            default:
                printf("\n--Opção inválida!");
        }
    }

    // Retorna codificação padrão do Windows
    SetConsoleOutputCP(CPAGE_DEFAULT);

}