#include "busca_local.h"

float vizinho_aleatorio(int n, vector<int> &s, float *custos)
{
    float fo;

    // dois int aleatorios diferentes
    int i, j, qtd, random, offset = 100, range = 300;
    // enquanto é possivel tirar da pilha i
    do
    {
        j = rand() % n;
        // enquanto i for igual a j
        do
            i = rand() % n;
        while (i == j);

        random = offset + (rand() % range);
    } while ((s[i] - random) < 0);

    // taking from i and putting on j
    s[i] -= random;
    s[j] += random;

    // funcao objetivo
    fo = calcula_fo(n, s, custos);

    return fo;
}

float descidaRandomica(int n, vector<int> &s, float *custos, int iterMax)
{
    int iter = 0;
    float fo, fo_viz;
    clock_t inicio_CPU, fim_CPU;

    // funcao objetiva da soluao corrente
    fo = calcula_fo(n, s, custos);

    // solution vector for neighbor
    vector<int> s_viz = s;

    limpa_arquivo((char *)"output/descidaRandom.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char *)"output/descidaRandom.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);

    // iterations without improvement
    while (iter < iterMax)
    {
        iter++;
        // get random neighbor
        fo_viz = vizinho_aleatorio(n, s_viz, custos);

        // if neighbor is better
        if (fo_viz < fo)
        {
            // cout << "melhorou de " << fo << " para " << fo_viz << endl;
            s = s_viz;
            fo = fo_viz;
            imprime_fo((char *)"output/descidaRandom.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter);
            // restart iteration
            iter = 0;
        }
    }

    return fo;
}