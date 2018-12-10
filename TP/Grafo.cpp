#include "Grafo.h"

Grafo::Grafo(vector<vector<int>> m, int v, int a)
	: matriz(move(m)), vertices(v), arestas(a)
{
	for(auto i = 0; i < matriz.size(); i++)
	{
		vector<int> vizinho;
		for (auto j = 0; j < matriz[i].size(); j++)
			if (matriz[i][j] == 1)
				vizinho.push_back(j);
		vizinhos.push_back(vizinho);
	}
}

int Grafo::get_arestas() const
{
	return this->arestas;
}

vector<vector<int>> Grafo::getMatriz() const
{
	return matriz;
}

vector<vector<int>> Grafo::getViz() const
{
	return vizinhos;
}

Grafo::~Grafo()
{
}
