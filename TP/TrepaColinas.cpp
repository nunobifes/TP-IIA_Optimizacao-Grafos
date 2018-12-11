#include "TrepaColinas.h"


TrepaColinas::TrepaColinas(const Grafo& grafo, int vert, int iter): grafo(grafo), vert(vert), n_iter(iter)
{
	custo = 0;
	mbf = 0.0;
	best_custo = 0;
	sol = gera_sol_inicial();
}

vector<int> TrepaColinas::gera_sol_inicial()
{
	int x;
	vector<int> sol;
	for (int i = 0; i < vert; ++i)
		sol.push_back(0);
	for (int i = 0; i < vert/2; ++i)
	{
		do
			x = Funcoes::random_l_h(0, vert - 1);
		while (sol[x] != 0);
		sol[x] = 1;
	}
	return sol;
}

void TrepaColinas::escreve_sol(vector<int> sol, int vert)
{
	cout << "\nConjunto A: ";
	for (auto i = 0; i < vert; i++)
		if (sol[i] == 0)
			cout << i << " ";
	cout << endl << endl << "Conjunto B: ";
	for (auto i = 0; i < vert; i++)
		if (sol[i] == 1)
			cout << i << " ";
	cout << "\n";
}

void TrepaColinas::substitui(vector<int> *sol1, vector<int> *sol2, int vert)
{
	if (sol1->empty())
		for (auto i = 0; i < vert; ++i)
			sol1->push_back(sol2->at(i));
	else
		for (auto i = 0; i < vert; ++i)
			sol1->at(i) = sol2->at(i);
}

int TrepaColinas::trepa_colinas(vector<int> *sol, Grafo g, int vert, int num_iter)
{
	vector<int> nova_sol;
	int custo, custo_viz;

	custo = calcula_fit(*sol, g.get_matriz(), vert);
	for (auto i = 0; i < num_iter; i++)
	{
		gera_vizinho(sol, &nova_sol, vert);
		custo_viz = calcula_fit(nova_sol, g.get_matriz(), vert);
		if(custo_viz < custo)
		{
			substitui(sol, &nova_sol, vert);
			custo = custo_viz;
		}
	}
	nova_sol.clear();
	return custo;
}

int TrepaColinas::calcula_fit(vector<int> sol, vector<vector<int>> mat, int vert)
{
	int total = 0;

	for (auto i = 0; i < vert; i++)
	{
		if(sol[i] == 0)
		{
			for (int j = 0; j < vert; ++j)
				if (sol[j] == 1 && mat[i][j] == 1)
					total++;
			
		}
	}
	return total;
}

void TrepaColinas::gera_vizinho(vector<int> *sol1, vector<int> *sol2, int n)
{
	int p1, p2;

	for (int i = 0; i < n; ++i)
		sol2->push_back(sol1->at(i));

	do
		p1 = Funcoes::random_l_h(0, n - 1);
	while (sol2->at(p1) != 0);
	do
			p2 = Funcoes::random_l_h(0, n - 1);
	while (sol2->at(p2) != 0);
	
	sol2->at(p1) = 1;
	sol2->at(p2) = 0;
}


void TrepaColinas::run()
{
	int k;
	for(k = 0; k < 10; k++){
		escreve_sol(sol, vert);
		custo = trepa_colinas(&sol, grafo, vert, n_iter);
		cout << "\nRepeticao: " << k;
		escreve_sol(sol, vert);
		cout << "Custo Final" << custo << endl;
		mbf += custo;
		if(k == 0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(&best, &sol, vert);
		}
	}
	cout << "\n\nMBF: " << mbf / k << endl;
	cout << "\nMelhor Solucao Encontrada: ";
	escreve_sol(best, vert);
	cout << "Custo final: " << best_custo << endl;

}
