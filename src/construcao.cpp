#include "construcao.h"

/* exemplo do professor marcone da apostila da matéria, arquivo do excel */
void construcao_exemplo(int n, vector<int> &s)
{
    s.push_back(0);
    s.push_back(500);
    s.push_back(1480);
    s.push_back(980);
    s.push_back(0);
    s.push_back(0);
    s.push_back(0);
    s.push_back(0);
    s.push_back(0);
    s.push_back(730);
    s.push_back(0);
    s.push_back(0);
    s.push_back(1190);
    s.push_back(0);
    s.push_back(1120);
}

// m: nro de elementos
void calcula_concentracoes(int pilhas, vector<int> &s, int m, float **concentracoes, vector<float> &resultado)
{
    // sum of mass of element in total 
    vector<float> sumElementos(m);

    // sum of each element in all the piles start at 0
    for (int i = 0; i < sumElementos.size(); i++)
        sumElementos[i] = 0;

    float massatotal = 0;
    // go through every pile
    for (int i = 0; i < pilhas; i++)
    {
        // go through every element in the pile
        for (int j = 0; j < m; j++)
        {
            // add mass of element present in the pile
            // multiply how much i'm taking from the pile and the concentration of that element in that pile
            sumElementos[j] += s[i] * (concentracoes[i][j]) / 100;
        }
        // keeping total mass i'm taking from the piles
        massatotal += s[i];
    }

    // keeping the concentration of each element in the final product
    for (int i = 0; i < sumElementos.size(); i++)
        resultado.push_back(sumElementos[i] / massatotal);
}