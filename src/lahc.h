#ifndef LAHC_H
#define LAHC_H

#include <ctime>
#include "util.h"
#include "file.h"
#include "construcao.h"

// l: tamanho do vetor de soluções F
// m: máximo de rejeições seguidas
float LAHC(int pilhas, vector<int> &s, int massa, float *custos, float **concentracoes,
           vector<float> &resultado, vector<float> limInf, vector<float> limSup, vector<float> meta, int alpha, int l, int m);

#endif