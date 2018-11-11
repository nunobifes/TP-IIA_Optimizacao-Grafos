#include <iostream>
#include <string>
#include <vector>
#include "Funcoes.h"
#include "Grafo.h"

using namespace std;

int main()
{
	string nomeficheiro;
	int vert, edges;
	vector< vector<int> > mat;
	cout << "Nome do ficheio: ";
	getline(cin, nomeficheiro);
	Funcoes::le_dados(nomeficheiro, &vert, &mat, &edges);
	Grafo grafo(mat, vert, edges);
	mat.clear();
	getchar();
}

