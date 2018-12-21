#include "Grafo.h"

Grafo::Grafo(vector<vector<int>> m, int v, int a)
	: matriz(m), vertices(v), arestas(a)
{

}

int Grafo::get_arestas() const
{
	return this->arestas;
}

int Grafo::get_verts() const
{
	return this->vertices;
}


vector<vector<int>> Grafo::get_matriz() const
{
	return matriz;
}


Grafo::~Grafo()
{
}
