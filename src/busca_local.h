#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include <ctime>
#include "util.h"
#include "construcao.h"
#include "file.h"

float vizinho_aleatorio(int n, vector<int> &s, float *custos);
float descidaRandomica(int n, vector<int> &s, float *custos, int iterMax, float **concentracoes,
                       vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha);

float melhor_vizinho(int n, vector<int> &s, float fo, float *custos, int *melhor_i, int *melhor_j, int *melhor_qtd);
float best_improvement(int n, vector<int> &s, float *custos, float **concentracoes, 
                       vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha);

#endif