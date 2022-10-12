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