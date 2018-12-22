#include "Evolutivo.h"


#define DEFAULT_RUNS 10


int Evolutivo::flip()
{
	if (( static_cast<float>( rand() )) / RAND_MAX < 0.5)
		return 0;
	else
		return 1;
}



Evolutivo::Evolutivo(const Grafo& grafo): grafo(grafo)
{
	mbf = 0.0;
	pop = nullptr;
	parents = nullptr;
	EA_param.ro = 0;
	EA_param.popsize = 100;
	EA_param.pm = 0.001f;
	EA_param.pr = 0.7f;
	EA_param.capacity = grafo.get_arestas();
	EA_param.tsize = 2;
	EA_param.numGenerations = 2500;
	EA_param.numGenes = grafo.get_verts();
}

Individual* Evolutivo::init_pop(Info d)
{
	Individual *indiv = new Individual[d.popsize];

	for (int i = 0; i < d.popsize; i++)
	{
		for (int j = 0; j < d.numGenes; j++)
			indiv[i].p[j] = flip();
	}
	return indiv;
}

float Evolutivo::eval_individual(int is[], const Info & info, const vector<vector<int>>& ises, int * valido)
{
	float sum_weight, sum_profit;

	sum_profit = sum_weight = 0.0;

	for(int i = 0; i < info.numGenes; i++)
	{
		if(is[i] == 1)
		{
			sum_weight += ises[i][0];
			sum_profit += ises[i][1];
		}
	}
	if(sum_weight > info.capacity)
	{
		*valido = 0;
		return 0;
	}
	else
	{
		*valido = 1;
		return sum_profit;
	}

}

void Evolutivo::evaluate(Individual* pop, const Info& info, const vector<vector<int>>& ises)
{
	for (int i = 0; i < info.popsize; i++)
	{
		pop[i].fitness = eval_individual(pop[i].p, info, ises, &pop[i].valido);
	}
}

Individual& Evolutivo::get_best(Individual* pop, const Info& info,  Individual& individual)
{
	for (int i = 0; i < info.popsize; i++)
		if (individual.fitness < pop[i].fitness)
			individual = pop[i];
	
	return individual;
}

void Evolutivo::tournament(Individual* pop, const Info& info, Individual* parents)
{
	int x1, x2;
	for(int i = 0; i < info.popsize; i++)
	{
		x1 = Funcoes::random_l_h(0, info.popsize - 1);
		do
			x2 = Funcoes::random_l_h(0, info.popsize - 1);
		while (x1 == x2);
		if (pop[x1].fitness > pop[x2].fitness)
			parents[i] = pop[x1];
		else
			parents[i] = pop[x2];
	}
}

void Evolutivo::tournament_geral(Individual* pop, const Info& info, Individual* parents)
{
	int *pos = new int;
	int sair, best, i, j, k;

	for(i = 0; i < info.popsize; i++)
	{
		for (j=0; j < info.tsize; j++)
		{
			do
			{
				pos[j] = Funcoes::random_l_h(0, info.popsize - 1);
				sair = 0;
				for (k = 0; k < j; k++)
					if (pos[k] == pos[j])
						sair = 1;
			}
			while (sair);
			if (j == 0 || pop[pos[j]].fitness > pop[pos[best]].fitness)
				best = j;
		}
		parents[i] = pop[pos[best]];
	}
	delete pos;
}

void Evolutivo::crossover(Individual* parents, const Info& info, Individual* pop)
{
	int i, j, point;

	for (i = 0; i < info.popsize; i+=2)
	{
		if(Funcoes::rand_01() < info.pr)
		{
			point = Funcoes::random_l_h(0, info.numGenes - 1);
			for (j = 0; j < point; j++)
			{
				pop[i].p[j] = parents[i].p[j];
				pop[i+1].p[j] = parents[i+1].p[j];
			}
			for (j = point; j < info.numGenes; j++)
			{
				pop[i].p[j] = parents[i+1].p[j];
				pop[i + 1].p[j] = parents[i].p[j];
			}
		}
		else
		{
			pop[i] = parents[i];
			pop[i + 1] = parents[i + 1];
		}
	}
}

void Evolutivo::mutation(Individual* pop, const Info& info)
{
	int i, j;
	for (i = 0; i < info.popsize; i++)
		for (j = 0; j < info.numGenes; j++)
			pop[i].p[j] = !(pop[i].p[j]);
}

void Evolutivo::genetic_operators(Individual* parents, const Info& info, Individual* pop)
{
	crossover(parents, info, pop);
	mutation(pop, info);
}

void Evolutivo::write_best(const Individual& individual, const Info& info)
{
	cout << endl << "Best Individual: " << fixed << setprecision(1) << individual.fitness << endl;
	for (int i = 0; i < info.numGenes; i++)
		if(individual.p[i] == 1)
			cout << " " <<i + 1 << " ";
	
		
	cout << endl;
}

void Evolutivo::Run()
{
	int k;
	for(k = 0; k < DEFAULT_RUNS; k++)
	{
		//cout << "Repeticao: " << k << endl;
		pop = init_pop(EA_param);
		evaluate(pop, EA_param, grafo.get_matriz());
		best_run = pop[0];
		best_run = get_best(pop, EA_param, best_run);
		parents = new Individual[EA_param.popsize];

		int gen_actual = 1;
		while(gen_actual <= EA_param.numGenerations)
		{
			tournament(pop, EA_param, parents);
			genetic_operators(parents, EA_param, pop);
			evaluate(pop, EA_param, grafo.get_matriz());
			best_run = get_best(pop, EA_param, best_run);
			gen_actual++;
		}
		int inv = 0;
		for (int i = 0; i < EA_param.popsize; i++)
			if (pop[i].valido == 0)
				inv++;

		cout << endl <<"Repeticao: " << k << endl;
		write_best(best_run, EA_param);
		cout << "Percentagem Invalidos: " << 100*static_cast<float>(inv/EA_param.popsize) << endl;
		mbf += best_run.fitness;
		if (k == 0 || best_run.fitness > best_ever.fitness)
			best_ever = best_run;
		delete parents;
		delete pop;
	}
	cout << endl << endl << "MBF: " << mbf / k << endl;
	cout << endl << "Melhor Solucao encontrada: " << endl;
	write_best(best_ever, EA_param);
}

Evolutivo::~Evolutivo()
{
}
