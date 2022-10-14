#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include <ctime>
#include "util.h"
#include "file.h"

float vizinho_aleatorio(int n, vector<int> &s, float *custos);
float descidaRandomica(int n, vector<int> &s, float *custos, int iterMax);

#endif