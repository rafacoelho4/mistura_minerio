#include "util.h"

/* cria memoria para um vetor de tam posicoes */
float *cria_vetor_float(int tam)
{
    float *vetor;

    vetor = (float *)malloc(tam * sizeof(float));
    if (!vetor)
    {
        cout << "Falta memoria para alocar o vetor de ponteiros";
        exit(1);
    }
    return vetor;
}

void imprime_solucao(int n, vector<int> &s)
{
    for (int i = 0; i < n && s[i] != -1; i++)
        cout << "Pilha " << i + 1 << ": " << s[i] << endl;
}

float calcula_fo(int n, vector<int> &s, float *custo)
{
    float fo = 0;

    for (int i = 0; i < n; i++)
        fo += s[i] * custo[i];

    return fo;
}
