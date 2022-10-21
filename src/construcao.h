#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "util.h"
#include <vector>
#include <time.h>
#include <math.h>

void construcao_exemplo(int n, vector<int> &s);
void construcao_aleatoria(int n, vector<int> &s, int massa, int offset, int range, vector<int> qtd);

void calcula_concentracoes(int pilhas, vector<int> &s, int m, float **concentracoes, vector<float> &resultado);
int solucao_valida(vector<float> resultado, vector<float> limInf, vector<float> limSup);
float proximo_meta(int elementos, vector<float> resultado, vector<float> meta, vector<float> intervalo);

#endif