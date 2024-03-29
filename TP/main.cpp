#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Funcoes.h"
#include "Grafo.h"
#include "TrepaColinas.h"
#include "TrepaColinasV2.h"
#include "Evolutivo.h"
#include "Hibrido.h"


using namespace std;


#define DEFAULT_RUNS 20
#define NUM_ITER 100

int main(int argc, char *argv[])
{
	Funcoes::init_rand();
	string nomeficheiro,teste;
	int vert, edges, runs = DEFAULT_RUNS;
	bool exit = 0;
	vector< vector<int> > mat;
	string dest = "Instancias\\Testes\\";
	string filenameInit = "Instancia";
	string fileExtension = ".clq";
	
	while (!exit) {
		
		
		//Funcoes::le_dados(nomeficheiro, &vert, &mat, &edges);
		//Grafo grafo(mat, vert, edges);
		//mat.clear();


		cout << endl << "Que teste prentede fazer: ";
		getline(cin, teste);


		if(teste == "TrepaColinas" || teste == "trepacolinas" || teste == "tc" || teste == "TC")
		{
			time_t start, end;
			time(&start);
			vector<TrepaColinas*> test;
			for (auto i = 4; i < 5; i++)
			{
				string name = filenameInit + to_string(i+1) + fileExtension;
				Funcoes::le_dados(name, &vert, &mat, &edges);
				Grafo *grafo = new Grafo(mat, vert, edges);

				for(auto iter = 1000; iter <=1000; iter *= 10){
					for (auto j = 0; j < 2; j++)
					{
						if(j == 0)
							test.push_back(new TrepaColinas(grafo, runs, iter, dest + "Trepa-Colinas V" + to_string(j+1) + "-" + filenameInit + to_string(i+1) + "-Iter" + to_string(iter)));
						else
							test.push_back(new TrepaColinasV2(grafo, runs, iter, dest + "Trepa-Colinas V" + to_string(j + 1) + "-" + filenameInit + to_string(i+1) + "-Iter" + to_string(iter)));
					}
				}
				
			}
			
			for (TrepaColinas* t : test)
			{
				auto tr = new thread(&TrepaColinas::run, t);
				//tr->join();
			}
			
			time(&end);
			cout << endl << "Total - " << difftime(end, start) << " segundos" << endl;

		}
		
		else if(teste == "Evolutivo")
		{
			time_t start, end;
			time(&start);
			vector<Evolutivo*> test;
			for (auto i = 2; i < 4; i++)
			{
				string name = filenameInit + to_string(i+1) + fileExtension;
				Funcoes::le_dados(name, &vert, &mat, &edges);
				Grafo *grafo = new Grafo(mat, vert, edges);
				for(auto iter = 10; iter <=100; iter *= 10)
				{
					for(auto pr = 0.01; pr <= 0.25; pr *= 5)
					{
						auto pm = pr;
						for (auto ger = 10; ger <= 250; ger *= 5)
						{
							auto popSize = ger;
							test.push_back(new Evolutivo(grafo, pr, pm, ger, popSize, iter, dest + "Evolutivo " + filenameInit + "-Ins" + to_string(i + 1) + "-Pr" + to_string(pr) + "-Pm" + to_string(pr) + "-Ger" + to_string(ger) + "-Pop" + to_string(popSize) + "-Iter" + to_string(iter)));
							
						}
					}
				}
				
			}
			for (Evolutivo* t : test)
			{
				auto tr = new thread(&Evolutivo::Run, t);
				//tr->join();
			}
			time(&end);
			cout << endl << "Total - " << difftime(end, start) << " segundos" << endl;
		}
		
		else if (teste == "Hibrido")
		{
			time_t start, end;
			time(&start);
			vector<Evolutivo*> test;
			for (auto i = 0; i < 4; i++)
			{
				string name = filenameInit + to_string(i+1) + fileExtension;
				Funcoes::le_dados(name, &vert, &mat, &edges);
				Grafo *grafo = new Grafo(mat, vert, edges);
				for (auto iter = 10; iter <= 100; iter *= 10)
				{
					for (auto pr = 0.01; pr <= 0.25; pr *= 5)
					{
						auto pm = pr;
						for (auto ger = 10; ger <= 250; ger *= 5)
						{
							auto popSize = ger;
							test.push_back(new Hibrido(grafo, pr, pm, ger, popSize, iter, dest + "Hibrido " + filenameInit + "-Ins" + to_string(i + 1) + "-Pr" + to_string(pr) + "-Pm" + to_string(pr) + "-Ger" + to_string(ger) + "-Pop" + to_string(popSize) + "-Iter" + to_string(iter)));
							
						}
					}
				}
				
			}
			for (Evolutivo* t : test)
			{
				auto tr = new thread(&Evolutivo::Run, t);
				tr->join();
			}
			time(&end);
			cout << endl << "Total - " << difftime(end, start) << " segundos" << endl;
		}
		else if (teste == "Sair")
		{
			exit = 1;
		}
		else
		{
			cout << "Esse Teste nao esxiste." << endl;
		}
		getchar();
		cout << endl;
	}
	return 0;
}

