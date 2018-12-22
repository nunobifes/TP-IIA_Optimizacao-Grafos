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
	Info EA_param;
	Individual best_run, best_ever;
	Individual *pop, *parents;
	Grafo grafo;
	float mbf;
public:

	int flip();
	Individual *init_pop(Info d);

	explicit Evolutivo(const Grafo& grafo);


	float eval_individual(int is[], const Info& info, const vector<vector<int>>& ises, int* valido);
	void evaluate(Individual* pop, const Info& info, const vector<vector<int>>& ises);
	Individual& get_best(Individual* pop, const Info& info, Individual& individual);
	void tournament(Individual* pop, const Info& info, Individual* parents);
	void tournament_geral(Individual* pop, const Info& info, Individual* parents);
	void crossover(Individual* parents, const Info& info, Individual* pop);
	void mutation(Individual* pop, const Info& info);
	void genetic_operators(Individual* parents, const Info& info, Individual* pop);
	void write_best(const Individual& individual, const Info& info);
	void Run();
	~Evolutivo();
};


