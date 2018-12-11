#include "Grafo.h"

Grafo::Grafo(vector<vector<int>> m, int v, int a)
	: matriz(move(m)), vertices(v), arestas(a)
{

}

int Grafo::get_arestas() const
{
	return this->arestas;
}

vector<vector<int>> Grafo::get_matriz() const
{
	return matriz;
}


Grafo::~Grafo()
{
}
