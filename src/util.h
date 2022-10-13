#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int *cria_vetor(int tam);

float *cria_vetor_float(int tam);

float **cria_matriz_float(int nlinhas, int ncolunas);

float calcula_fo(int n, vector<int> &s, float *custo);

void imprime_solucao(int n, vector<int> &s);

#endif