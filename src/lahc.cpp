#include "lahc.h"

float LAHC(int pilhas, vector<int> &s, int massa, float *custos, float **concentracoes, vector<int> qtd,
           vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha, int l, int m)
{
    // fo da solucao corrente e da solucao vizinha
    // distancia da meta de concentração
    float fo, fo_viz, distance;
    // posição p começa no 0 assim como iterador r
    int r = 0, p = 0, valido;

    int chosen_i, chosen_j, chosen_qtd;

    vector<float> intervalo;
    for (int i = 0; i < limInf.size(); i++)
        intervalo.push_back(limSup[i] - limInf[i]);

    // cpu time
    clock_t inicio_CPU, fim_CPU;

    // funcao objetiva
    fo = calcula_fo(pilhas, s, custos);
    // distance to desired concentration for all elements
    distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
    // cout << "Inicio do LAHC" << endl;
    // cout << "distancia: " << distance << " e alpha " << alpha << " = " << distance * alpha << endl;
    distance *= alpha;

    // cout << "fo: " << fo << " + " << distance << " = " << fo + distance << endl;

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
    s_star = s_viz = s;
    int it = 0;

    // while (r <= m && it < 10000)
    while (r <= m)
    {
        // gerar vizinho aleatório
        get_random_neighbor(pilhas, s, custos, qtd, &chosen_i, &chosen_j, &chosen_qtd);

        s_viz = s;
        s_viz[chosen_i] -= chosen_qtd;
        s_viz[chosen_j] += chosen_qtd;

        // funcao objetiva
        fo_viz = calcula_fo(pilhas, s_viz, custos);

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(pilhas, s_viz, resultado.size(), concentracoes, resultado);

        // checa se a solução possui valores aceitaveis de concentracoes
        valido = solucao_valida(resultado, limInf, limSup);

        it++;

        // só trabalhando com soluções com concentrações aceitaveis
        if (!valido)
            continue;

        // calculando distancia da solução atual ate a meta estabelecida
        distance = proximo_meta(resultado.size(), resultado, meta, intervalo);
        distance *= alpha;

        fo_viz += distance;

        // solução vizinha precisa ser melhor que a solução corrente ou que a solução na posição p de F
        if ((fo_viz <= fo) || (fo_viz <= F[p]))
        {
            // cout << fo_viz << " melhor que " << fo << " ou " << F[p] << endl;
            // se houver melhora, reiniciar iterador
            if (fo_viz < fo)
                r = it = 0;

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

        fim_CPU = clock();
        imprime_fo((char *)"output/lahc.txt", (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, fo, r, distance / alpha);
    }

    // calculando valor da funcao objetiva para melhor solução
    fo_star = calcula_fo(pilhas, s_star, custos);

    // retorna apenas custo de retomar das pilhas
    return fo_star;
}
