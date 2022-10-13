#include "construcao.h"
#include "busca_local.h"
#include "util.h"
#include "file.h"

/*
    SOLUÇÃO
        formato:
        vetor onde cada posição diz respeito a massa retirada da pilha na posição i do vetor
        [0 100 300 0 200]
        massa total: 600

        validação da solução:
        concentração dos 5 elementos deve estar dentro dos limites

        valor da função objetiva:
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
    // n: quantidade de elementos analisados
    // m: quantidade de pilhas de minério
    int n = 5, m = 15;
    // c: vetor de custo
    // fo: valor da função objetiva (custo da solução)
    float *custos, fo;
    // s: vetor solução
    vector<int> s;

    // criando vetor de custo
    custos = cria_vetor_float(m);
    // lendo valores dos custos de cada pilha
    le_arq_vetor((char *)"input/custo.txt", custos);

    // construção de solução inicial
    for (int i = 0; i < n; i++)
        s.push_back(i * 10);

    // calculando valor da solução atual
    fo = calcula_fo(n, s, custos);

    printf("\nSolucao:\n");
    imprime_solucao(n, s);
    printf("Funcao objetivo = %f\n", fo);

    // conentracoes dos elementos em cada pilha
    float **concentracoes;
    // m pilhas, n elementos
    concentracoes = cria_matriz_float(m, n);

    // quantidade de material disponível em cada pilha
    vector<int> qtd(m);

    // lendo quatidades e concentrações
    le_arq_vetor_matriz((char *)"input/pilhas.txt", m, qtd, n, concentracoes);

    // nomes dos elementos
    vector<string> nomes;

    // lendo nomes do arquivo txt
    le_arq_vetor_string((char *)"input/nomes.txt", nomes);

    // concentração ideal do elemento no produto final, limites aceitaveis inferior e superior
    vector<float> meta;
    vector<float> limInf;
    vector<float> limSup;

    // lendo limites das concentracoes dos elementos no produto final
    le_arq_tres_vetores((char *)"input/limites.txt", n, limInf, meta, limSup);

    return 1;
}