#ifndef UTIL_H
#define UTIL_H

#define UNIDADE 10
#define MIN_MOVER 100

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int *cria_vetor(int tam);
float *cria_vetor_float(int tam);
float **cria_matriz_float(int nlinhas, int ncolunas);

void libera_vetor(vector<int> *vetor);
void libera_matriz_float(float **matriz, int nlinhas);

float calcula_fo(int n, vector<int> &s, float *custo);

void imprime_solucao(int n, vector<int> &s);
void imprime_concentracoes(vector<float> resultado, vector<string> nomes);
void imprime_distancia(vector<float> resultado, vector<string> nomes, vector<float> meta);

#endif