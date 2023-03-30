## LISTA
<br />
Uma estrutura de dados do tipo lista é uma sequência de elementos do mesmo tipo.  
Existem dois tipos de alocação de memória: estática e dinâmica.  
Na alocação estática, espaço de memória é alocado no momento da compilação. Isso exige a definição do número máximo de elementos quando da sua declaração.  
O acesso é sequencial, isto é, os elementos se apresentam de forma consecutiva na memória. Dessa forma, podemos fazer uso da indexação.  
Na alocação dinâmica, o espaço de memória é alocado em tempo de execução. O tamanho muda conforme inserção e remoção de elementos.  
O acesso é encadeado, de forma que cada elemento pode estar em uma área distinta da memória. Para acessar um elemento, é preciso percorrer todos os seus antecessores na lista.  
A lista possui pelo menos dois campos: um para os dados, e um ponteiro que aponta para o próximo elemento.

