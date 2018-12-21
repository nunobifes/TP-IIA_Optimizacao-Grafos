#include <iostream>
#include <string>
#include <vector>
#include "Funcoes.h"
#include "Grafo.h"
#include "TrepaColinas.h"
#include "TrepaColinasV2.h"

using namespace std;

#define DEFAULT_RUNS 20
#define NUM_ITER 100

int main(int argc, char *argv[])
{

	string nomeficheiro;
	int vert, edges, runs;
	vector< vector<int> > mat;

	Funcoes::init_rand();
	while (1) {
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

		cout << endl << "TrepaColinas" << endl;

		TrepaColinas *alg = new TrepaColinas(grafo, runs);
		alg->run();
		delete alg;

		cout << endl << "TrepaColinasV2" << endl;

		TrepaColinas *alg2 = new TrepaColinasV2(grafo, runs);
		alg2->run();
		delete alg2;
		getchar();
		cout << endl;
	}
	return 0;
}

