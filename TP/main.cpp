#include <iostream>
#include <string>
#include <vector>
#include "Funcoes.h"
#include "Grafo.h"
#include "TrepaColinas.h"

using namespace std;

int main()
{

	Funcoes::init_rand();
	
	
	
	string nomeficheiro;
	int vert, edges;
	vector< vector<int> > mat;
	
	while(1){
		cout << "Nome do ficheio: ";
		getline(cin, nomeficheiro);
		Funcoes::le_dados(nomeficheiro, &vert, &mat, &edges);
		Grafo grafo(mat, vert, edges);
		mat.clear();


		TrepaColinas *alg = new TrepaColinas(grafo, vert, 100);
		alg->run();
		delete alg;
		getchar();
		cout << endl;
	}
	return 0;
}

