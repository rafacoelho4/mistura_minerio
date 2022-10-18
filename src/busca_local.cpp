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
        random -= random % UNIDADE;
    } while ((s[i] - random) < MIN_MOVER);

    // taking from i and putting on j
    s[i] -= random;
    s[j] += random;

    // funcao objetivo
    fo = calcula_fo(n, s, custos);

    return fo;
}

float descidaRandomica(int n, vector<int> &s, float *custos, int iterMax, float **concentracoes,
                       vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha)
{
    int iter = 0;
    float fo, fo_viz, fo_valido;
    clock_t inicio_CPU, fim_CPU;

    // distance to goal concentration
    float distance;

    vector<float> intervalo;
    for (int i = 0; i < limInf.size(); i++)
        intervalo.push_back(limSup[i] - limInf[i]);

    // funcao objetiva da solucao corrente
    fo = calcula_fo(n, s, custos);
    // distance to desired concentration for all elements
    distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
    distance *= alpha;
    // cout << "INICIO!! fo sera: " << fo << " + " << distance << " = " << fo + distance << endl;

    fo += distance;

    // solution vector for neighbor
    vector<int> s_viz = s, s_valido = s;

    limpa_arquivo((char *)"output/descidaRandom.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char *)"output/descidaRandom.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo - distance, iter, distance / alpha);

    int valido = 0, it = 0;
    // iterations without improvement
    while (iter < iterMax)
    {
        iter++;

        // get random neighbor
        fo_viz = vizinho_aleatorio(n, s_viz, custos);

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(n, s_viz, resultado.size(), concentracoes, resultado);

        // distance to desired concentration for all elements
        distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
        distance *= alpha;

        // checa se a solução possui valores aceitaveis de concentracoes
        // valido = solucao_valida(resultado, limInf, limSup);

        // we want to reach the concentration goal values
        fo_viz += distance;

        if (!valido)
            continue;

        // if neighbor is better
        if (fo_viz < fo)
        {
            // cout << "fo sera: " << fo_viz - distance << " + " << distance << " = " << fo_viz << endl;
            s = s_viz;
            fo = fo_viz;
            fim_CPU = clock();
            imprime_fo((char *)"output/descidaRandom.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter, distance / alpha);
            // restart iteration
            iter = 0;
        }
    }

    fo = calcula_fo(n, s, custos);

    return fo;
}

float melhor_vizinho(int n, vector<int> &s, float fo, float *custos, int *melhor_i, int *melhor_j, int *melhor_qtd)
{
    float fo_melhor_viz = fo, fo_viz;
    float delta1, delta2;

    vector<int> s_viz = s;

    int random, offset = 100, range = 300;
    random = offset + (rand() % range);
    random -= random % UNIDADE;
    *melhor_qtd = random;

    for (int i = 0; i < n; i++)
    {
        // se solucao na posicao i for vazia, nao da pra tirar de la
        // se for deixar pilha com valor menor do que o mínimo, continuar procurando
        if ((s[i] == 0) || ((s[i] - random) < MIN_MOVER))
            continue;
        fo = calcula_fo(n, s_viz, custos);
        for (int j = 0; j < n; j++)
        {
            // faz o movimento
            s_viz[i] -= random;
            s_viz[j] += random;

            // calcula nova funcao objetiva
            fo_viz = calcula_fo(n, s_viz, custos);

            // refaz o movimento
            s_viz[i] += random;
            s_viz[j] -= random;

            // cout << "pilha " << i << " e " << j << "\t" << fo << " - " << fo_viz << endl;

            if (fo_viz < fo_melhor_viz)
            {
                // cout << "fo_viz menor que fo_melhor_viz: " << fo_viz << " - " << fo_melhor_viz << endl;
                // cout << "melhores i e j: " << i << " - " << j << endl
                //      << endl;
                *melhor_i = i;
                *melhor_j = j;
                fo_melhor_viz = fo_viz;
            }
        }
    }

    // cout << "melhores i e j: " << *melhor_i << " - " << *melhor_j << "\t qtd: " << *melhor_qtd << endl;

    return fo_melhor_viz;
}

float best_improvement(int n, vector<int> &s, float *custos, float **concentracoes,
                       vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha)
{

    int iter = 0, melhor_i, melhor_j, melhor_qtd, valido = 0;
    float fo, fo_viz;
    clock_t inicio_CPU, fim_CPU;
    bool melhorou;

    float distance;

    vector<float> intervalo;
    for (int i = 0; i < limInf.size(); i++)
        intervalo.push_back(limSup[i] - limInf[i]);

    // funcao objetiva da soluao corrente
    fo = fo_viz = calcula_fo(n, s, custos);

    // distance to desired concentration for all elements
    distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
    distance *= alpha;

    fo += distance;

    // solution vector for neighbor
    vector<int> s_viz = s;

    limpa_arquivo((char *)"output/descidaBestImprov.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char *)"output/descidaBestImprov.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter, distance / alpha);

    do
    {
        melhorou = false;

        fo_viz = melhor_vizinho(n, s_viz, fo, custos, &melhor_i, &melhor_j, &melhor_qtd);

        // fazer troca para ver se solução vai ser válida
        s_viz[melhor_i] -= melhor_qtd;
        s_viz[melhor_j] += melhor_qtd;

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(n, s_viz, 5, concentracoes, resultado);

        // distance to desired concentration for all elements
        distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
        distance *= alpha;

        // checa se a solução possui valores aceitaveis de concentracoes
        // valido = solucao_valida(resultado, limInf, limSup);

        // desfazendo movimentação
        s_viz[melhor_i] += melhor_qtd;
        s_viz[melhor_j] -= melhor_qtd;

        // we want to reach the concentration goal values
        fo_viz += distance;

        if (!valido)
            continue;

        if (fo_viz < fo)
        {
            // cout << "fo sera: " << fo_viz - distance << " + " << distance << " = " << fo_viz << endl;
            iter++;
            s_viz[melhor_i] -= melhor_qtd;
            s_viz[melhor_j] += melhor_qtd;
            melhorou = true;

            fo = fo_viz;
            s = s_viz;

            fim_CPU = clock();
            imprime_fo((char *)"output/descidaBestImprov.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter, distance / alpha);
        }
    } while (melhorou);

    fo = calcula_fo(n, s, custos);

    return fo;
}

float first_improvement(int n, vector<int> &s, float *custos, int iterMax)
{
    int iter = 0;
    float fo, fo_viz;
    clock_t inicio_CPU, fim_CPU;
    bool melhorou;

    // funcao objetiva da soluao corrente
    fo = calcula_fo(n, s, custos);

    // solution vector for neighbor
    vector<int> s_viz = s;

    limpa_arquivo((char *)"output/descidaFirstImprov.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char *)"output/descidaFirstImprov.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter, fo);

    do
    {
        melhorou = false;
        // fo_viz = vizinho_first_improvement(n, s, d, fo, &melhor_i, &melhor_j);
        if (fo_viz < fo)
        {
            iter++;
            // swap(s[melhor_i], s[melhor_j]);
            melhorou = true;
            s = s_viz;
            fo = fo_viz;
            fim_CPU = clock();
            imprime_fo((char *)"output/descidaRandom.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, iter, fo);

            break;
        }
    } while (melhorou);

    return fo;
}