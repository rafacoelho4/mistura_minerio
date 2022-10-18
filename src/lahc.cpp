#include "lahc.h"

float LAHC(int pilhas, vector<int> &s, float *custos, float **concentracoes,
           vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha, int l, int m)
{
    // fo da solucao corrente e da solucao vizinha
    // distancia da meta de concentração
    float fo, fo_viz, distance;
    int r, p, valido, massa = 6000;

    // cpu time
    clock_t inicio_CPU, fim_CPU;

    // funcao objetiva
    fo = calcula_fo(pilhas, s, custos);
    // distance to desired concentration for all elements
    distance = proximo_meta(resultado.size(), resultado, meta);
    // não adicionando multiplicador alpha na primeira iteração ou valores serão muito altos
    // distance *= alpha;

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

    s_star = s;
    // posição p começa no 0 assim como iterador r
    p = r = 0;

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

        if (!valido)
            continue;

        // we want to reach the concentration goal values
        fo_viz += distance;

        if ((fo_viz <= fo || fo_viz <= F[p]) && valido)
        {
            if (fo_viz > fo)
            {
                r = 0;
                // cout << "fo_viz: " << fo_viz << " menor que fo: " << fo << " ou F[p]: " << F[p] << endl;
            }

            s = s_viz;
            fo = calcula_fo(pilhas, s, custos);

            // calcula a concentração de cada elemento no produto final
            calcula_concentracoes(pilhas, s, resultado.size(), concentracoes, resultado);

            distance = proximo_meta(resultado.size(), resultado, meta);
            distance *= alpha;

            fo += distance;

            if (fo < fo_star)
                s_star = s;
        }

        // cout << "colocando " << fo << " em F[p] na posicao " << p << endl;
        F[p] = fo;
        // avançando no vetor de soluções
        p = (p + 1) % l;
        // incremento
        r++;

        imprime_fo((char *)"output/lahc.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, r, distance / alpha);
    }

    calcula_concentracoes(pilhas, s, resultado.size(), concentracoes, resultado);
    distance = proximo_meta(resultado.size(), resultado, meta);
    distance *= alpha;

    return fo - distance;
}
