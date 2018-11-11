#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class Funcoes
{
	Funcoes();
	~Funcoes();
public:

	void static le_dados(string nome, int *vert, vector< vector<int> > *mat, int *edges);

};

