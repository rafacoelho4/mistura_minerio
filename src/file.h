#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include "util.h"
using namespace std;

void ler_custo();

void le_arq_vetor(char nomearq[], float *vetor);

void le_arq_vetor_string(char nomearq[], vector<string> &vetor);

void le_arq_tres_vetores(char nomearq[], int n, vector<float> &vetor1, vector<float> &vetor2, vector<float> &vetor3);

// n: quantidade de elementos analisados
// m: quantidade de pilhas de minério
void le_arq_vetor_matriz(char nomearq[], int m, vector<int> &vetor, int n, float **matriz);

void limpa_arquivo(char nomearq[]);

void imprime_fo(char nomearq[], float tempo, float fo, int iteracao);

#endif