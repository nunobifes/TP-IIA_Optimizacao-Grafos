#include "Hibrido.h"



Hibrido::Hibrido(Grafo* grafo, float pr, float pm, int ger, int popSize, int iter, string outputfile) : Evolutivo(grafo, pr, pm, ger, popSize, iter, outputfile)
{
}


Hibrido::~Hibrido()
{
}

void Hibrido::Run()
{
	time_t start, end;
	time(&start);
	int k, kk, invv;

	CSVFile *csvFile = new CSVFile();
	csvFile->Write(0, 0, outputFile);
	csvFile->addCabecalhoE();
	for (k = 0; k < iter; k++)
	{
		//cout << "Repeticao: " << k << endl;
		pop = init_pop(EA_param);
		evaluate(pop, EA_param, grafo->get_matriz());
		best_run = *pop[0];
		best_run = get_best(pop, EA_param, best_run);
		parents = init_vector(EA_param);

		int gen_actual = 1;
		while (gen_actual <= EA_param.numGenerations)
		{
			tournament_geral(pop, EA_param, parents);
			genetic_operators(parents, EA_param, pop);
			evaluate(pop, EA_param, grafo->get_matriz());
			trepa_colinas(pop, EA_param, grafo->get_matriz());
			best_run = get_best(pop, EA_param, best_run);
			gen_actual++;
		}
		int inv = 0;
		for (int i = 0; i < EA_param.popsize; i++)
			if (pop[i]->valido == 0)
				inv++;
/*
		cout << endl << "Repeticao: " << k << endl;
		write_best(best_run, EA_param);
		cout << "Percentagem Invalidos: " << 100 * (inv / EA_param.popsize) << endl;
		*/
		mbf += best_run.fitness;
		if (k == 0 || best_run.fitness > best_ever.fitness)
		{
			best_ever = best_run;
			kk = k;
			invv = inv;
		}

		csvFile->addHipoteseE(k, (mbf / k), (100 * (inv / EA_param.popsize)), best_run, EA_param);

		for (Individual* element : parents)
			delete element;
		for (auto i = 0; i < parents.size(); i++)
			parents.erase(parents.begin() + i);


		for (Individual* element : pop)
			delete element;
		for (auto i = 0; i < pop.size(); i++)
			pop.erase(pop.begin() + i);


	}
	//cout << endl << endl << "MBF: " << mbf / k << endl;
	//cout << endl << "Melhor Solucao encontrada: " << endl;
	//write_best(best_ever, EA_param);
	csvFile->addBestE(kk, (mbf / k), (100 * (invv / EA_param.popsize)), best_ever, EA_param);
	csvFile->toFile(outputFile);
	time(&end);

	cout << "Terminado - " << outputFile << ": " << difftime(end, start) << " segundos" << endl;

}

void Hibrido::gera_vizinho(vector<int> *sol, vector<int>* solViz, const vector<vector<int>>& ises, int nGenes)
{
	int p1, p2;


	for (int i = 0; i < nGenes; i++)
		solViz->push_back(sol->at(i));


	p1 = Funcoes::random_l_h(0, nGenes - 1);

	solViz->at(p1) = !solViz->at(p1);

	do
		p2 = Funcoes::random_l_h(0, nGenes - 1);
	while (p2 == p1);

	solViz->at(p2) = !solViz->at(p2);
}

void Hibrido::trepa_colinas(vector<Individual*> pop, const Info& info, const vector<vector<int>>& ises)
{
	Individual* vizinho;
	for (int i = 0; i < info.popsize; i++)
	{
		for (int j = 0; j < GENERATIONS_TC; j++)
		{
			vizinho = new Individual;
			gera_vizinho(&pop[i]->p, &vizinho->p, ises, info.numGenes);
			vizinho->fitness = eval_individual(vizinho->p, info, ises, &vizinho->valido);
			if (vizinho->fitness >= pop[i]->fitness)
				pop[i] = vizinho;
		}
	}
}
