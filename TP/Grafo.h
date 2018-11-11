#pragma once
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class Grafo
{
	vector< vector<int> > matriz;
	int vertices;
	int arestas;
public:
	Grafo(vector<vector<int>> m, int v, int a);
	int get_arestas() const;
	~Grafo();
};

