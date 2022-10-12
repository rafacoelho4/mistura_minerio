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
    float *c, fo;
    // s: vetor solução
    vector<int> s;

    // criando vetor de custo
    c = cria_vetor_float(m);
    // lendo valores dos custos de cada pilha 
    le_arq_vetor((char *)"input/custo.txt", c);

    // construção de solução inicial 
    for (int i = 0; i < n; i++) s.push_back(i*10);

    // calculando valor da solução atual 
    fo = calcula_fo(n, s, c);

    printf("\nSolucao:\n");
    imprime_solucao(n, s);
    printf("Funcao objetivo = %f\n", fo);

    return 1;
}