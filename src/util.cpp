#include "util.h"

int *cria_vetor(int tam)
{
    int *vetor;

    vetor = (int *)malloc(tam * sizeof(int));
    if (!vetor)
    {
        cout << "Falta memoria para alocar o vetor de ponteiros";
        exit(1);
    }
    return vetor;
}

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

float **cria_matriz_float(int nlinhas, int ncolunas)
{
    int i;
    float **matriz;

    matriz = (float **)malloc(nlinhas * sizeof(float *));
    if (!matriz)
    {
        cout << "Falta memoria para alocar a matriz de ponteiros\n";
        exit(1);
    }
    for (i = 0; i < nlinhas; i++)
    {
        matriz[i] = (float *)malloc(ncolunas * sizeof(float));
        if (!matriz[i])
        {
            cout << "Falta memoria para alocar a matriz de ponteiros.\n";
            exit(1);
        }
    }
    return matriz;
}

void libera_vetor(int *vetor)
{
    free(vetor);
}

void libera_vetor(vector<int> *vetor)
{
    delete[] vetor;
}

void libera_matriz_float(float **matriz, int nlinhas)
{
    int i;

    for (i = nlinhas - 1; i >= 0; i--)
        free((float *)matriz[i]);
    free((float *)matriz);
}

void imprime_solucao(int n, vector<int> &s)
{
    for (int i = 0; i < n && s[i] != -1; i++)
        cout << "Pilha " << i + 1 << ": " << s[i] << endl;
}

void imprime_concentracoes(vector<float> resultado, vector<string> nomes)
{
    for (int i = 0; i < resultado.size(); i++)
        cout << nomes[i] << ": " << resultado[i] * 100 << "%    ";
    cout << endl;
}

void imprime_distancia(vector<float> resultado, vector<string> nomes, vector<float> meta)
{
    for (int i = 0; i < resultado.size(); i++)
    {
        cout << nomes[i] << ": ";
        printf("%.3f%%      ", fabs(meta[i] - (resultado[i] * 100)));
    }
    cout << endl;
}

float calcula_fo(int n, vector<int> &s, float *custo)
{
    float fo = 0;

    for (int i = 0; i < n; i++)
        fo += s[i] * custo[i];

    return fo;
}
