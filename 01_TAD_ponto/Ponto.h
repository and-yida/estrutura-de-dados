//Arquivo Ponto.h
//Aqui encontramos a declaração/definição
//Declaramos um ponteiro e os protótipos das funções

typedef struct ponto Ponto;                         //Ponto será o apelido desta struct

//Cria um novo ponto
Ponto* pto_cria(float x, float y);
//Libera um ponto
void pto_libera(Ponto* p);
//Acessa os valores "x" e "y" de um ponto
int pto_acessa(Ponto* p, float* x, float* y);
//Atribui os valores "x" e "y" a um ponto
int pto_atribui(Ponto* p, float x, float y);
//Calcula a distância entre dois pontos
float pto_distancia(Ponto* p1, Ponto* p2);
