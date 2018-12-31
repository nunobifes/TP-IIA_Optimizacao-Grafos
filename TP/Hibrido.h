#pragma once
#include "Evolutivo.h"
#include "CSVFile.h"

#define GENERATIONS_TC  100
#define PROBGERAVIZ     1.0
class Hibrido :
	public Evolutivo
{
public:
	Hibrido(Grafo* grafo, float pr, float pm, int ger, int popSize, int iter, string outputfile);
	~Hibrido();

	void Run() override;
	void gera_vizinho(vector<int> *sol, vector<int> *solViz, const vector<vector<int>>& ises, int nGenes);
	void trepa_colinas(vector<Individual*> pop, const Info& info, const vector<vector<int>>& ises);
};

