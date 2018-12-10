#pragma once
#include <vector>
#include "Grafo.h"
#include <iostream>

using namespace std;
class Independent
{
	int k;
	int s;
	int verts;
	int counter;
	vector< vector<int> > covers;
	vector<int> allcover;
	bool found;
	int min;
public:
	Independent(int vert);
	~Independent();
	bool removable(vector<int> neighbor, vector<int> cover);
	int max_removable(vector<vector<int> > neighbors, vector<int> cover);
	vector<int> procedure_1(vector<vector<int> > neighbors, vector<int> cover);
	vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k);
	int cover_size(vector<int> cover);

	void setK(int K);
	void encontraIndepedentes(Grafo grafo);
	void pairwiseIntercecoes(Grafo grafo);
};

