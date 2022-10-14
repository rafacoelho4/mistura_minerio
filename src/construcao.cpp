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

void construcao_aleatoria(int n, vector<int> &s, int massa)
{
    s.clear();
    // initial state with zero
    for (int i = 0; i < n; i++)
        s.push_back(0);

    // values will vary between 500 and 2000 (if massa = 6000)
    int random, offset = 500, range = massa / 5;

    int sum = 0, resto, pos;
    while (sum < massa)
    {
        // inserting at random position
        pos = rand() % n;
        // generating random quantity to take from pile
        random = offset + (rand() % range);
        if (s[pos] != 0)
            continue;
        // se soma ultrapassa o máximo, pegar o resto até o desejado
        if (sum + random > massa)
        {
            resto = massa - sum;
            s[pos] = resto;
            break;
        }
        s[pos] = random;
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
        // cout << limInf[i] << " - " << resultado[i] * 100 << " - " << limSup[i] << endl;
        if (((resultado[i] * 100) >= limInf[i]) && ((resultado[i] * 100) <= limSup[i]))
            continue;
        else
            return 0;
    }

    return 1;
}

/*
void aleatoria(int massa, int pilhas,  float *custos, vector<int> &s, int m, float **concentracoes,
               vector<float> &resultado, vector<float> limInf, vector<float> limSup)
{
    float fo;
    int valido, it = 0;

    // seed for random numbers
    srand((unsigned)time(0));

    do
    {
        cout << "iteracao: " << it << endl;

        // clearing vectors (new solution (s) will be found and new concentration results too (resultado))
        resultado.clear();
        s.clear();

        // construcao da solucao inicial
        construcao_aleatoria(pilhas, s, massa);

        // calculando valor da solução atual
        fo = calcula_fo(pilhas, s, custos);

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(pilhas, s, m, concentracoes, resultado);

        // checa se a solução possui valores aceitaveis de concentracoes
        valido = solucao_valida(resultado, limInf, limSup);

        // incrementing iteration variable
        it++;
    } while (valido == 0 && it < 400);
}
*/