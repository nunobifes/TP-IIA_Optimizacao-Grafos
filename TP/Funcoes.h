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
	
public:

	void static le_dados(string nome, int *vert, vector< vector<int> > *mat, int *edges);
	int static random_l_h(int min, int max);
	void static init_rand();
	float static rand_01();
};

