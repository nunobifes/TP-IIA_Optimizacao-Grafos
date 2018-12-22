#include <iostream>
#include <string>
#include <vector>
#include "Funcoes.h"
#include "Grafo.h"
#include "TrepaColinas.h"
#include "TrepaColinasV2.h"
#include "Evolutivo.h"

using namespace std;

#define DEFAULT_RUNS 20
#define NUM_ITER 100

int main(int argc, char *argv[])
{

	string nomeficheiro,teste;
	int vert, edges, runs;
	bool exit = 0;
	vector< vector<int> > mat;

	Funcoes::init_rand();
	while (!exit) {
		if (argc == 3) {
			runs = atoi(argv[2]);
			
			nomeficheiro = (argv[1]);
		}
		else
			// Se o numero de execucoes do processo nao for colocado nos argumentos de entrada, define-o com um valor por defeito
			if (argc == 2) {
				runs = DEFAULT_RUNS;
				nomeficheiro = (argv[1]);
			}
		//pede-o novamente
			else {
				runs = DEFAULT_RUNS;
				cout << "Nome do ficheio: ";
				getline(cin, nomeficheiro);

			}

		// Se o numero de execucoes do processo for menor ou igual a 0, termina o programa
		if (runs <= 0) {
			return 0;
		}
		

		Funcoes::le_dados(nomeficheiro, &vert, &mat, &edges);
		Grafo grafo(mat, vert, edges);
		mat.clear();


		cout << endl << "Que teste prentede fazer: ";
		getline(cin, teste);


		if(teste == "TrepaColinas" || teste == "trepacolinas" || teste == "tc" || teste == "TC")
		{
			TrepaColinas *alg = new TrepaColinas(grafo, runs);
			alg->run();
			delete alg;

		}
		else if(teste == "TrepaColinasV2" || teste == "trepacolinasv2" || teste == "trepacolinas2" || teste == "tcv2" || teste == "TCV2" || teste == "TC2" || teste == "tc2")
		{
			TrepaColinas *alg = new TrepaColinasV2(grafo, runs);
			alg->run();
			delete alg;

		}
		else if(teste == "Evolutivo")
		{
			Evolutivo *alg = new Evolutivo(grafo);
			alg->Run();
			delete alg;
		}
		else if (teste == "Hibrido")
		{
			cout << "Ainda Não Implementado." << endl;
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

