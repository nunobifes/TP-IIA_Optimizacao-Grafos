#include "TrepaColinas.h"


TrepaColinas::TrepaColinas(const Grafo& grafo, int iter): grafo(grafo), vert(grafo.get_verts()), n_iter(iter)
{
	custo = 0;
	mbf = 0.0;
	best_custo = 0;
	
	Funcoes::inicializector(&best, vert);
}

vector<int> TrepaColinas::gera_sol_inicial()
{
	
	vector<int> sol;
	for (int i = 0; i < vert; ++i)
		sol.push_back(Funcoes::bynarit());
	
	return sol;
}

void TrepaColinas::escreve_sol(vector<int> sol, int vert)
{
	cout << "\nSet de Vertices Independentes: ";
	for (auto i = 0; i < vert; i++)
		if (sol[i] == 1)
			cout << i+1 << " ";
	
	cout << "\n";
}

void TrepaColinas::substitui(vector<int> *sol1, vector<int> *sol2, int vert)
{
	for (int i = 0; i < vert; ++i)
			sol1->at(i) = sol2->at(i);
}

int TrepaColinas::trepa_colinas(vector<int> *sol, Grafo g, int vert, int num_iter)
{
	vector<int> nova_sol;
	Funcoes::inicializector(&nova_sol, vert);
	int custo, custo_viz;

	custo = calcula_fit(*sol, g.get_matriz(), vert);
	for (auto i = 0; i < num_iter; i++)
	{
		gera_vizinho(sol, &nova_sol, vert);
		//gera_vizinho2(sol, &nova_sol, vert);
		custo_viz = calcula_fit(nova_sol, g.get_matriz(), vert);
		if(custo_viz > custo)
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
	int total = 0, conta = 0;

	for (auto i = 0; i < vert; i++)
	{
		if(sol[i] == 1)
		{
			for (int j = 0; j < vert; ++j)
				if (sol[j] == 1 && mat[i][j] == 1)
					total++;
			
		}
	}

	if(total == 0)
	{
		for(int i = 0; i < vert; i++)
		{
			if (sol[i] == 1)
				conta++;
		}
		return conta;
	}
	else
	{
		return -total;
	}
}

void TrepaColinas::gera_vizinho(vector<int> *sol1, vector<int> *sol2, int n)
{
	int p1;
	
	for (int i = 0; i < n; ++i)
		sol2->at(i) = sol1->at(i);
		
	
	p1 = Funcoes::random_l_h(0, n - 1);
	
	sol2->at(p1) = !sol2->at(p1);
	
}




void TrepaColinas::run()
{
	int k;
	for(k = 0; k < 20; k++){
		sol = gera_sol_inicial();
		escreve_sol(sol, vert);
		custo = trepa_colinas(&sol, grafo, vert, n_iter);
		cout << "\nRepeticao: " << k;
		escreve_sol(sol, vert);
		cout << "Custo Final " << custo << endl;
		mbf += custo;
		if(k == 0 || best_custo < custo)
		{
			best_custo = custo;
			substitui(&best, &sol, vert);
		}
	}
	cout << "\n\nMBF: " << setprecision(3) << mbf / k << endl;
	cout << "\nConjunto Maximo de Vertices Independentes: ";
	escreve_sol(best, vert);
	cout << "Custo final: " << best_custo << endl;

}
