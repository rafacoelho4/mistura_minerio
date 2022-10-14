#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "util.h"
#include <vector>
#include <time.h>

void construcao_exemplo(int n, vector<int> &s);
void construcao_aleatoria(int n, vector<int> &s, int massa);

void calcula_concentracoes(int pilhas, vector<int> &s, int m, float **concentracoes, vector<float> &resultado);
int solucao_valida(vector<float> resultado, vector<float> limInf, vector<float> limSup);
// void aleatoria(int massa, int pilhas, float *custos, vector<int> &s, int m, float **concentracoes, vector<float> &resultado, vector<float> limInf, vector<float> limSup);

#endif