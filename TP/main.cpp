#include <iostream>
#include <string>
#include <vector>
#include "Funcoes.h"
#include "Grafo.h"
#include "Independent.h"

using namespace std;



int main()
{
	
	Funcoes::init_rand();
	string nomeficheiro;
	int vert, edges;
	vector< vector<int> > mat;
	cout << "Nome do ficheio: ";
	getline(cin, nomeficheiro);
	Funcoes::le_dados(nomeficheiro, &vert, &mat, &edges);
	Grafo grafo(mat, vert, edges);
	mat.clear();

	while(1){
		Independent alg(vert);
		int K;
		cout << "introduzir k: ";
		cin >> K;
		alg.setK(K);
		alg.encontraIndepedentes(grafo);
		alg.pairwiseIntercecoes(grafo);
	
		getchar();
	}
	return 0;
}

