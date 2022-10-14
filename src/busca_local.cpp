#include "busca_local.h"

float vizinho_aleatorio(int n, vector<int> &s, float *custos) {
    float fo;

    // dois int aleatorios diferentes
    int i, j, qtd, random, offset = 100, range = 300;
    // enquanto é possivel tirar da pilha i
    do {
        j = rand() % n;
        // enquanto i for igual a j 
        do i = rand() % n;
        while (i == j);

        random = offset + (rand() % range);
    } while((s[i] - random) < 0);

    // taking from i and putting on j
    s[i] -= random;
    s[j] += random;

    // funcao objetivo 
    fo = calcula_fo(n, s, custos);

    return fo;
}