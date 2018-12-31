#pragma once
#include "TrepaColinas.h"
class TrepaColinasV2 :
	public TrepaColinas
{
public:
	TrepaColinasV2(Grafo* grafo, int iter, int testes, string outputFile);
	virtual ~TrepaColinasV2();
	void gera_vizinho(vector<int>* sol1, vector<int>* sol2, int n) override;
};

