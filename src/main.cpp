#include "construcao.h"
#include "busca_local.h"
#include "util.h"
#include "file.h"
#include "construcao.h"
#include "busca_local.h"
#include "lahc.h"
#include "menu.h"

int main()
{
    // ex1: 5 elementos, 15 pilhas, 6000 massa desejada
    // ex2: 7 elementos, 6 pilhas, 6100 massa desejada

    // numero de elementos analisados e nro de pilhas disponiveis
    int elementos = 5, pilhas = 15;
    // int elementos = 7, pilhas = 6;
    // custos: vetor que armazena valor para movimentar uma unidade da pilha i
    // fo: valor da função objetiva (custo da solução)
    float *custos, fo;
    // s: vetor solução
    vector<int> s;
    // massa desejada pro produto final
    int massa = 6000;
    // int massa = 6100;

    // criando vetor de custo
    custos = cria_vetor_float(pilhas);
    // lendo valores dos custos de cada pilha
    le_arq_vetor((char *)"input/custoigual.txt", custos);

    // conentracoes dos elementos em cada pilha
    float **concentracoes;
    // pilhas pilhas, elementos elementos
    concentracoes = cria_matriz_float(pilhas, elementos);

    // quantidade de material disponível em cada pilha
    vector<int> qtd(pilhas);
    // lendo quatidades e concentrações
    le_arq_vetor_matriz((char *)"input/pilhas.txt", pilhas, qtd, elementos, concentracoes);

    // nomes dos elementos
    vector<string> nomes;
    // lendo nomes do arquivo txt
    le_arq_vetor_string((char *)"input/nomes.txt", nomes);

    // concentração ideal do elemento no produto final, limites aceitaveis inferior e superior
    vector<float> meta;
    vector<float> limInf;
    vector<float> limSup;
    // lendo limites das concentracoes dos elementos no produto final
    le_arq_tres_vetores((char *)"input/limites.txt", elementos, limSup, meta, limInf);

    // diferenca entre limite superior e inferior para cada elemento
    vector<float> intervalo;
    for (int i = 0; i < limInf.size(); i++)
        intervalo.push_back(limSup[i] - limInf[i]);

    // concentracoes dos elementos no produto final
    vector<float> resultado;

    // valido terá valor 1 se solução apresentar concentrações finais aceitaveis
    int valido = 0, it = 0;
    // distancia relativa até a meta
    float distance;

    // seed for random numbers
    srand((unsigned)time(0));

    vector<float> old;
    float oldfo;
    float fo_viz;
    int alpha = 5;
    int iterMax;

    int escolha = 0;
    do
    {
        escolha = menu_principal();
        switch (escolha)
        {
        case 0:
            printf("\n\nBye bye!!!\n\n");
            break;

        case 1:
            switch (menu_solucao_inicial())
            {
            case 1: /* Geracao gulosa */
                printf("Nao implementado\n");
                construcao_exemplo(pilhas, s);
                fo = calcula_fo(pilhas, s, custos);
                calcula_concentracoes(pilhas, s, elementos, concentracoes, resultado);

                printf("\nSolucao: %d\n", solucao_valida(resultado, limInf, limSup));
                imprime_solucao(pilhas, s);
                printf("Funcao objetivo = %f\n", fo);
                imprime_concentracoes(resultado, nomes);
                cout << "distancia relativa: " << proximo_meta(elementos, resultado, meta, intervalo) << endl;

                old = resultado;
                oldfo = fo;
                break;
            case 2: /* Geracao aleatória */
                printf("\nSolucao construida de forma parcialmente gulosa (Vizinho Mais Proximo):\n");
                printf("Funcao objetivo = %f\n", fo);
                do
                {
                    // clearing vectors (new solution (s) will be found and new concentration results too (resultado))
                    resultado.clear();
                    s.clear();

                    // construcao da solucao inicial
                    construcao_aleatoria(pilhas, s, massa, 100, massa / 10, qtd);
                    // construcao_exemplo(pilhas, s);

                    // calculando valor da solução atual
                    fo = calcula_fo(pilhas, s, custos);

                    // calcula a concentração de cada elemento no produto final
                    calcula_concentracoes(pilhas, s, elementos, concentracoes, resultado);

                    // checa se a solução possui valores aceitaveis de concentracoes
                    valido = solucao_valida(resultado, limInf, limSup);

                    // incrementing iteration variable
                    it++;
                } while (valido == 0 && it < 800);

                valido ? cout << "solucao encontrada!" : cout << "solucao nao encontrada...";

                if (!valido)
                {
                    libera_matriz_float(concentracoes, pilhas);
                    return 1;
                }

                // Solucao antes de refinamento
                printf("\nSolucao: %d\n", solucao_valida(resultado, limInf, limSup));
                imprime_solucao(pilhas, s);
                printf("Funcao objetivo = %f\n", fo);
                imprime_concentracoes(resultado, nomes);
                cout << "distancia relativa: " << proximo_meta(elementos, resultado, meta, intervalo) << endl;

                old = resultado;
                oldfo = fo;
                break;
            }
            break;
        case 2:
            // printf("Nao implementado\n");
            fo_viz = best_improvement(pilhas, s, custos, concentracoes, resultado, limInf, limSup, meta, alpha);
            cout << "Apos descida best improvement: ";
            printf("\nSolucao: %d\n", solucao_valida(resultado, limInf, limSup));
            imprime_solucao(pilhas, s);
            printf("Funcao objetivo = %f\n", fo);
            imprime_concentracoes(resultado, nomes);
            cout << "distancia relativa: " << proximo_meta(elementos, resultado, meta, intervalo) << endl;
            break;
        case 3:
            // printf("Nao implementado\n");
            iterMax = 600;
            fo_viz = descidaRandomica(pilhas, s, custos, iterMax, concentracoes, resultado, limInf, limSup, meta, alpha);
            cout << "Apos descida randomica: ";
            printf("\nSolucao: %d\n", solucao_valida(resultado, limInf, limSup));
            imprime_solucao(pilhas, s);
            printf("Funcao objetivo = %f\n", fo);
            imprime_concentracoes(resultado, nomes);
            cout << "distancia relativa: " << proximo_meta(elementos, resultado, meta, intervalo) << endl;
            break;
        case 4:
            // LAHC
            int l = 40, m = 60, alphaLAHC = 1000;
            fo_viz = LAHC(pilhas, s, massa, custos, concentracoes, qtd, resultado, limInf, limSup, meta, alphaLAHC, l, m);
            cout << "Apos LAHC: ";

            // Solucao apos refinamento
            calcula_concentracoes(pilhas, s, elementos, concentracoes, resultado);
            printf("\nSolucao: %d\n", solucao_valida(resultado, limInf, limSup));
            imprime_solucao(pilhas, s);
            printf("Funcao objetivo = %f\n", fo_viz);
            imprime_concentracoes(resultado, nomes);
            cout << "distancia relativa: " << proximo_meta(elementos, resultado, meta, intervalo) << endl;
            break;
        }
    } while (escolha != 0);

    // comparando concentracoes da primeira solucao e a ultima solucao encontrada
    vector<float> novo = resultado;
    vector<string> melhores;
    float novofo = fo_viz;

    cout << "\nfo da primeira solucao e depois refinamento: " << endl;
    cout << oldfo << " - " << novofo << endl;

    if (oldfo < novofo)
        cout << "\tsolucao anterior e melhor em custo" << endl;
    else if (oldfo == novofo)
        cout << "\tcustos iguais antes e depois";
    else
        cout << "\tcustos novo e menor por " << oldfo - novofo << endl;

    cout << "\ndistancia ate meta na primeira solucao e depois refinamento: " << endl;
    imprime_distancia(old, nomes, meta);
    imprime_distancia(novo, nomes, meta);
    for (int i = 0; i < meta.size(); i++)
        if ((fabs(meta[i] - (novo[i] * 100))) <= (fabs(meta[i] - (old[i] * 100))))
            melhores.push_back(nomes[i]);

    if (melhores.size() == 0)
        cout << "\tsolucao anterior e melhor em todas os elementos";
    else
    {
        cout << "\tsolucao nova e melhor em (" << melhores.size() << "): ";
        for (int i = 0; i < melhores.size(); i++)
            cout << melhores[i] << ", ";
    }

    limpa_arquivo((char *)"output/solucao.txt");
    imprime_s((char *)"output/solucao.txt", pilhas, elementos, s, fo_viz, resultado, nomes, distance);

    libera_matriz_float(concentracoes, pilhas);
    return 0;
}