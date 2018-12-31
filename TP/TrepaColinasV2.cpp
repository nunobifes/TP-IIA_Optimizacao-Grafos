#include "TrepaColinasV2.h"



TrepaColinasV2::TrepaColinasV2(Grafo* grafo, int iter, int testes, string outputFile): TrepaColinas(grafo, iter, testes, outputFile)
{
}


TrepaColinasV2::~TrepaColinasV2()
{
}

void TrepaColinasV2::gera_vizinho(vector<int>* sol1, vector<int>* sol2, int n)
{
	int p1, p2;


	for (int i = 0; i < n; ++i)
		sol2->at(i) = sol1->at(i);


	p1 = Funcoes::random_l_h(0, n - 1);

	sol2->at(p1) = !sol2->at(p1);

	do
		p2 = Funcoes::random_l_h(0, n - 1);
	while (p2 == p1);

	sol2->at(p2) = !sol2->at(p2);
}
