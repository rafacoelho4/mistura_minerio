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