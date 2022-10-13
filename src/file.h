#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include "util.h"
using namespace std;

void ler_custo();

void le_arq_vetor(char nomearq[], float *vetor);

// n: quantidade de elementos analisados
// m: quantidade de pilhas de minério
void le_arq_vetor_matriz(char nomearq[], int m, vector<int> &vetor, int n, float **matriz);

#endif