#include "construcao.h"

/* exemplo do professor marcone da apostila da matéria, arquivo do excel */
void construcao_exemplo(int n, vector<int> &s)
{
    if (n != 15)
    {
        cout << "Solução exemplo deve ter 15 pilhas." << endl;
        for (int i = 0; i < n; i++)
            s.push_back(0);
        return;
    }
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

void construcao_aleatoria(int n, vector<int> &s, int massa, int offset, int range)
{
    s.clear();
    // initial state with zero
    for (int i = 0; i < n; i++)
        s.push_back(0);

    // values will vary between 500 and 2000 (if massa = 6000)
    int random;

    int sum = 0, resto, pos;
    while (sum < massa)
    {
        // inserting at random position
        pos = rand() % n;
        // generating random quantity to take from pile
        random = offset + (rand() % range);
        // sem valores quebrados, apenas multiplos de 10
        random -= random % UNIDADE;
        // if (s[pos] != 0)
        //     continue;
        // se soma ultrapassa o máximo, pegar o resto até o desejado
        if (sum + random > massa)
        {
            resto = massa - sum;
            s[pos] += resto;
            break;
        }
        s[pos] += random;
        sum += random;
    }
}

// m: nro de elementos
void calcula_concentracoes(int pilhas, vector<int> &s, int m, float **concentracoes, vector<float> &resultado)
{
    // clearing any leftover values
    resultado.clear();

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

int solucao_valida(vector<float> resultado, vector<float> limInf, vector<float> limSup)
{
    for (int i = 0; i < resultado.size(); i++)
    {
        if (((resultado[i] * 100) >= limInf[i]) && ((resultado[i] * 100) <= limSup[i]))
            continue;
        else
            return 0;
    }

    return 1;
}

float proximo_meta(int elementos, vector<float> resultado, vector<float> meta, vector<float> intervalo)
{
    float total = 0;

    for (int i = 0; i < elementos; i++)
    {
        if (intervalo[i] == 0)
            continue;
        // diferença entre concentração resultado e a meta
        // vezes 100 já que valores de meta estao em porcentagem
        // dividido pelo tamanho do intervalo limite superior e limite inferior
        // vezes 10 para tirar dos valores menores que 1
        total += ((fabs(meta[i] - (resultado[i] * 100))) / intervalo[i]) * 10;

        // cout << "difference: " << ((fabs(meta[i] - (resultado[i] * 100))) / intervalo[i]) * 10 << endl;
    }

    return total;
}