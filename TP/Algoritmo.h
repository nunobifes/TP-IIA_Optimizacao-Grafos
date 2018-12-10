#pragma once
#include <vector>
#include "Funcoes.h"
using namespace std;

class Algoritmo
{
	vector<int> sol;
	vector<int> best;
	int vertices;
public:
	Algoritmo(int vert);
	~Algoritmo();
	vector<int> getSol() const;
	vector<int> getBest() const;
	void setSol(vector<int> s);
	void setBest(vector<int> b);
	void geraSolInicial(vector<int> sol, int vert);
	void escreveSol(vector<int> sol, int vert);
	

};



Algoritmo::Algoritmo(int vert):
	vertices(vert)
{

}

inline void Algoritmo::setSol(vector<int> s)
{
	sol = s;
}

inline void Algoritmo::setBest(vector<int> b)
{
	best = b;
}

inline void Algoritmo::geraSolInicial(vector<int> sol, int vert)
{
	int x, i;
	for (i = 0; i < vertices; i++)
		sol.push_back(0);
	for(i = 0; i < vertices/2; i++)
	{
		do
			x = Funcoes::random_l_h(0, vertices - 1);
		while (sol[x] != 0);
		sol[x] = 1;
	}
}

inline void Algoritmo::escreveSol(vector<int> sol, int vert)
{

}

inline vector<int> Algoritmo::getSol() const
{
	return sol;
}

inline vector<int> Algoritmo::getBest() const
{
	return best;
}

Algoritmo::~Algoritmo()
{
}


