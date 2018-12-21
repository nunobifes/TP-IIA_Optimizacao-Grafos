#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include "Funcoes.h"
#include "Grafo.h"

using namespace std;

class TrepaColinas
{
public:

	TrepaColinas(const Grafo& grafo, int iter);
	vector<int> gera_sol_inicial();
	void escreve_sol(vector<int> sol, int vert);
	void substitui(vector<int> *sol1, vector<int> *sol2, int vert);
	int trepa_colinas(vector<int> *sol, Grafo g, int vert, int num_iter);
	int calcula_fit(vector<int> sol, vector< vector<int> > mat, int vert);
	void gera_vizinho(vector<int> *sol1, vector<int> *sol2, int n);
	void gera_vizinho2(vector<int>* sol1, vector<int>* sol2, int n);
	void run();

private:
	Grafo grafo;
	int vert;
	int n_iter;
	float mbf;
	int custo;
	int best_custo;
	vector<int> sol;
	vector<int> best;
	
};
