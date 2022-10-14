#include "construcao.h"
#include "busca_local.h"
#include "util.h"
#include "file.h"
#include "construcao.h"
#include "busca_local.h"

/*
    SOLUÇÃO
        formato:
        vetor onde cada posição diz respeito a massa retirada da pilha na posição i do vetor
        [0 100 300 0 200]
        massa total: 600

        validação da solução:
        concentração dos 5 elementos deve estar dentro dos limites

        valor da função objetiva (custo):
        Si * Pi (quantidade retirada da pilha i vezes o preço do material dessa pilha)
        0 * p1 + 100 * p2 + 300 * p3 + 0 * p4 + 200 * p5
*/
/*
    PARAMETROS:
        - M: massa da mistura final em toneladas
        - m: valor mínimo de retirada de material
*/

int main()
{
    // numero de elementos analisados e nro de pilhas disponiveis
    int elementos = 5, pilhas = 15;
    // custos: vetor que armazena valor para movimentar uma unidade da pilha i
    // fo: valor da função objetiva (custo da solução)
    float *custos, fo;
    // s: vetor solução
    vector<int> s;
    // massa desejada pro produto final
    int massa = 6000;

    // criando vetor de custo
    custos = cria_vetor_float(pilhas);
    // lendo valores dos custos de cada pilha
    le_arq_vetor((char *)"input/custo.txt", custos);

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

    // concentracoes dos elementos no produto final
    vector<float> resultado;

    int valido, it = 0;

    // seed for random numbers
    srand((unsigned)time(0));

    // construção aleatória
    // aleatoria(massa, pilhas, custos, s, elementos, concentracoes, resultado, limInf, limSup);

    // // calculando valor da solução atual
    // fo = calcula_fo(pilhas, s, custos);

    do
    {
        // cout << "iteracao: " << it << endl;

        // clearing vectors (new solution (s) will be found and new concentration results too (resultado))
        resultado.clear();
        s.clear();

        // construcao da solucao inicial
        construcao_aleatoria(pilhas, s, massa);
        // construcao_exemplo(pilhas, s);

        // calculando valor da solução atual
        fo = calcula_fo(pilhas, s, custos);

        // calcula a concentração de cada elemento no produto final
        calcula_concentracoes(pilhas, s, elementos, concentracoes, resultado);

        // checa se a solução possui valores aceitaveis de concentracoes
        valido = solucao_valida(resultado, limInf, limSup);

        // incrementing iteration variable
        it++;
    } while (valido == 0 && it < 400);

    valido ? cout << "solucao encontrada!" : cout << "solucao nao encontrada...";

    if (!valido)
        return 1;

    printf("\nSolucao:\n");
    imprime_solucao(pilhas, s);
    printf("Funcao objetivo = %f\n", fo);
    imprime_concentracoes(resultado, nomes);

    float fo_viz;
    // fo_viz = vizinho_aleatorio(pilhas, s, custos);
    fo_viz = best_improvement(pilhas, s, custos);

    // int iterMax = 200;
    // fo_viz = descidaRandomica(pilhas, s, custos, iterMax);

    calcula_concentracoes(pilhas, s, elementos, concentracoes, resultado);
    printf("\nSolucao:\n");
    imprime_solucao(pilhas, s);
    printf("Funcao objetivo = %f\n", fo_viz);
    imprime_concentracoes(resultado, nomes);

    return 1;
}