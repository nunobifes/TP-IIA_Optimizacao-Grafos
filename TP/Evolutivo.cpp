#include "Evolutivo.h"
#include "CSVFile.h"





int Evolutivo::flip()
{
	if (( static_cast<float>( rand() )) / RAND_MAX < 0.5)
		return 0;
	else
		return 1;
}



Evolutivo::Evolutivo(Grafo* grafo, float pr, float pm, int ger, int popSize, int iter, string outputfile): grafo(grafo), iter(iter), outputFile(outputfile)
{
	mbf = 0.0f;
	
	EA_param.popsize = popSize;
	EA_param.pm = pm;
	EA_param.pr = pr;
	EA_param.capacity = grafo->get_arestas();
	EA_param.tsize = 2;
	EA_param.numGenerations = ger;
	EA_param.numGenes = grafo->get_verts();
	
}

vector<Individual*> Evolutivo::init_vector(Info d)
{
	vector<Individual*> indiv;
	
	for (int i = 0; i < d.popsize; i++)
	{
		Individual * ind = new Individual;
		for (int j = 0; j < d.numGenes; j++) {
			ind->p.push_back(0);
			ind->fitness = 0;
			ind->valido = 0;
		}

		indiv.push_back(ind);
	}
	return indiv;
}

vector<Individual*> Evolutivo::init_pop(Info d)
{
	vector<Individual*> indiv;
	
	for (int i = 0; i < d.popsize; i++)
	{
		Individual * ind = new Individual;
		for (int j = 0; j < d.numGenes; j++){
			ind->p.push_back(flip());
			ind->fitness = 0;
			ind->valido = 0;
		}

		indiv.push_back(ind);
	}
	return indiv;
}

float Evolutivo::eval_individual(vector<int> is, const Info & info, const vector<vector<int>>& ises, int * valido)
{
	int tot = 0;
	int zer = 0;

	for(int i = 0; i < info.numGenes; i++)
	{
		if(is[i] == 0)
		{
			for (int j = 0; j < info.numGenes; j++)
			{
				if (is[j] == 0 && ises[i][j] == 1)
					tot++;
			}
		}
	}
	if(tot == 0)
	{
		for (int i = 0; i < info.numGenes; i++)
		{
			if (is[i] == 0)
				zer++;
		}
		*valido = 1;
		return zer;
	}
	else
	{
		*valido = 0;
		return -tot;
	}

}

void Evolutivo::evaluate(vector<Individual*> pop, const Info& info, const vector<vector<int>>& ises)
{
	for (int i = 0; i < info.popsize; i++)
	{
		pop[i]->fitness = eval_individual(pop[i]->p, info, ises, &pop[i]->valido);
	}
}

Individual &Evolutivo::get_best(vector<Individual*> pop, const Info& info,  Individual &individual)
{
	for (int i = 0; i < info.popsize; i++)
		if (individual.fitness < pop[i]->fitness)
			individual = *pop[i];
	
	return individual;
}

void Evolutivo::tournament(vector<Individual*> pop, const Info& info, vector<Individual*> parents)
{
	int x1, x2;
	for(int i = 0; i < info.popsize; i++)
	{
		x1 = Funcoes::random_l_h(0, info.popsize - 1);
		do
			x2 = Funcoes::random_l_h(0, info.popsize - 1);
		while (x1 == x2);
		if (pop[x1]->fitness > pop[x2]->fitness)
			parents[i] = pop[x1];
		else
			parents[i] = pop[x2];
	}
}

void Evolutivo::tournament_geral(vector<Individual*> pop, const Info& info, vector<Individual*> parents)
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
			if (j == 0 || pop[pos[j]]->fitness > pop[pos[best]]->fitness)
				best = j;
		}
		parents[i] = pop[pos[best]];
	}
	//delete pos;
}

void Evolutivo::crossover(vector<Individual*> parents, const Info& info, vector<Individual*> pop)
{
	int i, j, point;

	for (i = 0; i < info.popsize; i+=2)
	{
		if(Funcoes::rand_01() < info.pr)
		{
			point = Funcoes::random_l_h(0, info.numGenes - 1);
			for (j = 0; j < point; j++)
			{
				pop[i]->p[j] = parents[i]->p[j];
				pop[i+1]->p[j] = parents[i+1]->p[j];
			}
			for (j = point; j < info.numGenes; j++)
			{
				pop[i]->p[j] = parents[i+1]->p[j];
				pop[i + 1]->p[j] = parents[i]->p[j];
			}
		}
		else
		{
			pop[i] = parents[i];
			pop[i + 1] = parents[i + 1];
		}
	}
}

void Evolutivo::mutation(vector<Individual*> pop, const Info& info)
{
	int i, j;
	for (i = 0; i < info.popsize; i++)
		for (j = 0; j < info.numGenes; j++)
			if(Funcoes::rand_01() < info.pm)
				pop[i]->p[j] = !(pop[i]->p[j]);
}

void Evolutivo::genetic_operators(vector<Individual*> parents, const Info& info, vector<Individual*> pop)
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
	time_t start, end;
	time(&start);
	int k, kk, invv;

	CSVFile *csvFile = new CSVFile();
	csvFile->Write(0, 0, outputFile);
	csvFile->addCabecalhoE();
	for(k = 0; k < iter; k++)
	{
		//cout << "Repeticao: " << k << endl;
		pop = init_pop(EA_param);
		evaluate(pop, EA_param, grafo->get_matriz());
		best_run = *pop[0];
		best_run = get_best(pop, EA_param, best_run);
		parents = init_vector(EA_param);

		int gen_actual = 1;
		while(gen_actual <= EA_param.numGenerations)
		{
			tournament_geral(pop, EA_param, parents);
			genetic_operators(parents, EA_param, pop);
			evaluate(pop, EA_param, grafo->get_matriz());
			best_run = get_best(pop, EA_param, best_run);
			gen_actual++;
		}
		int inv = 0;
		for (int i = 0; i < EA_param.popsize; i++)
			if (pop[i]->valido == 0)
				inv++;

		//cout << endl <<"Repeticao: " << k << endl;
		//write_best(best_run, EA_param);
		//cout << "Percentagem Invalidos: " << 100*(inv/EA_param.popsize) << endl;
		mbf += best_run.fitness;
		if (k == 0 || best_run.fitness > best_ever.fitness)
		{
			best_ever = best_run;
			kk = k;
			invv = inv;
		}
			
		csvFile->addHipoteseE(k, (mbf/k), (100 * (inv / EA_param.popsize)),best_run, EA_param);
		
		for (Individual* element : parents)
			delete element;
		for(auto i = 0; i < parents.size(); i++)
			parents.erase(parents.begin() + i);
		

		for(Individual* element : pop)
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

Evolutivo::~Evolutivo()
{
}
