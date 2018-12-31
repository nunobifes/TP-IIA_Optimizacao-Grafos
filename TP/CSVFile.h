#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Individual.h"
#include "Info.h"

using namespace std;
class CSVFile
{
private:
	vector<vector<string>> matriz;
	int lastLine;
public:
	CSVFile();
	void Write(int x, int y, string cont);
	int addCabecalhoTC(int x = 0);
	int addHipoteseTC(vector<int> sol, int custo, float mbf, int iter, int x = 0);
	int addBestTC(vector<int> sol, int custo, float mbf, int iter, int x = 0);
	void toFile(string filename);
	~CSVFile();
	int addCabecalhoE(int x = 0);
	int addHipoteseE(int iter, float mbf, float percInv, Individual run, Info info, int x = 0);
	int addBestE(int iter, float mbf, float percInv, Individual run, Info info, int x = 0);
};

