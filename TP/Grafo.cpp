#include "Grafo.h"

Grafo::Grafo(vector<vector<int>> m, int v, int a)
	: matriz(move(m)), vertices(v), arestas(a)
{

}

int Grafo::get_arestas() const
{
	return this->arestas;
}

Grafo::~Grafo()
{
}
