#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
#define MAX_OBJ 1000
#define DEFAULT_RUNS 10

class Funcoes
{
public:

	void static le_dados(string nome, int *vert, vector< vector<int> > *mat, int *edges);
	void static init_rand();
	int static bynarit();
	int static random_l_h(int min, int max);
	float static rand_01();
	void static inicializector(vector<int>* v, int vert);
};

