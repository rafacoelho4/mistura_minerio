#include "lahc.h"

float LAHC(int pilhas, vector<int> &s, int massa, float *custos, float **concentracoes,
           vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha, int l, int m)
{
    // fo da solucao corrente e da solucao vizinha
    // distancia da meta de concentração
    float fo, fo_viz, distance;
    // posição p começa no 0 assim como iterador r
    int r = 0, p = 0, valido;

    vector<float> intervalo;
    for (int i = 0; i < limInf.size(); i++)
        intervalo.push_back(limSup[i] - limInf[i]);

    // cpu time
    clock_t inicio_CPU, fim_CPU;

    // funcao objetiva
    fo = calcula_fo(pilhas, s, custos);
    // distance to desired concentration for all elements
    distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
    // não adicionando multiplicador alpha na primeira iteração

    fo += distance;

    // vetor das l-ésimas ultimas soluções
    vector<float> F;
    // começa tudo com valor inicial de fo
    for (int i = 0; i < l; i++)
        F.push_back(fo);

    // melhor solução
    vector<int> s_star(s);
    // solução vizinha
    vector<int> s_viz(s);
    // valor da melhor função objetiva
    float fo_star = fo;

    limpa_arquivo((char *)"output/lahc.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo((char *)"output/lahc.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, r, distance / alpha);

    // melhor solução ate agora é a inicial
    s_star = s;

    while (r <= m)
    {
        // random neighbor
        construcao_aleatoria(pilhas, s_viz, massa);

        // funcao objetiva
        fo_viz = calcula_fo(pilhas, s_viz, custos);

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(pilhas, s_viz, resultado.size(), concentracoes, resultado);

        // checa se a solução possui valores aceitaveis de concentracoes
        valido = solucao_valida(resultado, limInf, limSup);

        // só trabalhando com soluções com concentrações aceitaveis
        if (!valido)
            continue;

        // calculando distancia da solução atual ate a meta estabelecida
        distance = proximo_meta(resultado.size(), resultado, meta, intervalo);

        fo_viz += distance;

        // solução vizinha precisa ser melhor que a solução corrente ou que a solução na posição p de F
        if ((fo_viz <= fo) || (fo_viz <= F[p]))
        {
            // se houver melhora, reiniciar iterador
            if (fo_viz < fo)
                r = 0;

            // atualizando solução corrente
            s = s_viz;
            fo = fo_viz;

            // se for melhor que a melhor solução encontrada, atualizar solução estrela
            if (fo < fo_star)
                s_star = s;
        }

        // inserindo solução na posição p
        F[p] = fo;
        // avançando no vetor de soluções
        p = (p + 1) % l;
        // incremento
        r++;

        imprime_fo((char *)"output/lahc.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, r, distance / alpha);
    }

    // calculando valor da funcao objetiva para melhor solução
    fo_star = calcula_fo(pilhas, s_star, custos);

    // retorna apenas custo de retomar das pilhas
    return fo_star;
}
