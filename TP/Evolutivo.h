#pragma once
#include <iostream>
#include <iomanip>
#include "Info.h"
#include "Individual.h"
#include "Funcoes.h"
#include "Grafo.h"
using namespace std;


/*

*/
class Evolutivo
{
protected:
	Info EA_param;
	Individual best_run, best_ever;
	//Individual *pop, *parents;
	vector<Individual*> pop;
	vector<Individual*> parents;
	Grafo *grafo;
	int iter;
	float mbf;
	string outputFile;
public:

	int flip();
	vector<Individual*> init_pop(Info d);

	explicit Evolutivo(Grafo * grafo, float pr, float pm, int ger, int popSize, int iter, string outputfile);
	vector<Individual*> init_vector(Info d);


	float eval_individual(vector<int> is, const Info& info, const vector<vector<int>>& ises, int* valido);
	void evaluate(vector<Individual*> pop, const Info& info, const vector<vector<int>>& ises);
	Individual &get_best(vector<Individual*> pop, const Info& info, Individual &individual);
	void tournament(vector<Individual*> pop, const Info& info, vector<Individual*> parents);
	void tournament_geral(vector<Individual*> pop, const Info& info, vector<Individual*> parents);
	void crossover(vector<Individual*> parents, const Info& info, vector<Individual*> pop);
	void mutation(vector<Individual*> pop, const Info& info);
	void genetic_operators(vector<Individual*> parents, const Info& info, vector<Individual*> pop);
	void write_best(const Individual& individual, const Info& info);
	void virtual Run();
	~Evolutivo();
};


