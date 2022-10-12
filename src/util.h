#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
using namespace std;

float *cria_vetor_float(int tam);

float calcula_fo(int n, vector<int> &s, float *custo);

void imprime_solucao(int n, vector<int> &s);

#endif