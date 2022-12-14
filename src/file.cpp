#include "file.h"

/* le um arquivo no formato i, valor */
void le_arq_vetor(char nomearq[], float *vetor)
{
    int i = 0;
    float valor;
    FILE *arquivo;

    arquivo = fopen(nomearq, "r");
    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%f\n", &valor);
        vetor[i] = valor;
        i++;
    }
    fclose(arquivo);
}

void le_arq_vetor_matriz(char nomearq[], int m, vector<int> &vetor, int n, float **matriz)
{
    int i = 0, qtd;
    float valor;
    FILE *arquivo;

    arquivo = fopen(nomearq, "r");
    if (!arquivo)
    {
        cout << "O Arquivo " << nomearq << "nao pode ser aberto.\n";
        getchar();
        exit(1);
    }

    while (i < m)
    {
        fscanf(arquivo, "%d", &qtd);
        vetor[i] = qtd;
        for (int j = 0; j < n; j++)
        {
            fscanf(arquivo, "%f", &valor);
            matriz[i][j] = valor;
        }

        i++;
    }

    fclose(arquivo);
}

void le_arq_vetor_string(char nomearq[], vector<string> &vetor)
{
    int i = 0;
    FILE *arquivo;
    char buf[100];

    arquivo = fopen(nomearq, "r");
    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%s\n", buf);
        vetor.push_back(buf);

        i++;
    }
    fclose(arquivo);
}

void le_arq_tres_vetores(char nomearq[], int n, vector<float> &vetor1, vector<float> &vetor2, vector<float> &vetor3)
{
    int i = 0;
    float valor1, valor2, valor3;
    FILE *arquivo;

    arquivo = fopen(nomearq, "r");
    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%f %f %f\n", &valor1, &valor2, &valor3);
        vetor1.push_back(valor1);
        vetor2.push_back(valor2);
        vetor3.push_back(valor3);
        i++;
    }
    fclose(arquivo);
}

void limpa_arquivo(char nomearq[])
{
    FILE *arquivo;
    arquivo = fopen(nomearq, "w");
    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }
    fclose(arquivo);
}

void imprime_fo(char nomearq[], float tempo, float fo, int iteracao, float distance)
{
    FILE *arquivo;
    arquivo = fopen(nomearq, "a+");

    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }
    fprintf(arquivo, "%8.5f\t  %4d\t  %7.2f\t %7.2f\n", tempo, iteracao, fo, distance);
    fclose(arquivo);
}

void imprime_s(char nomearq[], int pilhas, int elementos, vector<int> s, float fo,
               vector<float> resultado, vector<string> nomes, float distance)
{
    FILE *arquivo;
    arquivo = fopen(nomearq, "a+");

    if (!arquivo)
    {
        cout << "O arquivo " << nomearq << "nao pode ser aberto";
        getchar();
        exit(1);
    }

    int qtd;
    for (int i = 0; i < pilhas && s[i] != -1; i++)
        fprintf(arquivo, "Pilha %d: %5d\n", i + 1, s[i]);

    fprintf(arquivo, "Funcao objetivo: %5.2f\n", fo);

    for (int i = 0; i < elementos && s[i] != -1; i++)
        fprintf(arquivo, "%s: %5.4f\t\t", nomes[i].c_str(), resultado[i] * 100);

    fprintf(arquivo, "\nDistancia para meta: %5.2f\n", distance);

    fclose(arquivo);
}