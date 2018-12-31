#include "CSVFile.h"



CSVFile::CSVFile()
{

}

void CSVFile::Write(int x, int y, string cont)
{
	if (y == -1)
		y = ++lastLine;
	while(matriz.size() <= y)
	{
		vector<string> v;
		matriz.push_back(v);
	}
	while (matriz[y].size() <= x)
	{
		matriz[y].emplace_back("");
	}
	matriz[y][x] = cont;
}

int CSVFile::addCabecalhoTC(int x)
{
	if (x == 0)
		++lastLine;
	Write(x++, lastLine, "Iteracao");
	Write(x++, lastLine, "Solucao");
	Write(x++, lastLine, "MBF");
	Write(x++, lastLine, "Custo");
	Write(x++, lastLine, "Best");
	return x;
}
int CSVFile::addHipoteseTC(vector<int> sol, int custo, float mbf, int iter, int x)
{
	string tmp = "";
	if (x == 0)
		++lastLine;

	Write(x++, lastLine, to_string(iter));
	for (auto i = 0; i < sol.size(); ++i)
	{
		if (sol[i] == 1) 
			tmp += (to_string(i + 1) + " ");
		
		
	}
	Write(x++, lastLine, tmp);
	Write(x++, lastLine, to_string(mbf/iter));
	Write(x++, lastLine, to_string(custo));
	Write(x++, lastLine, to_string(0));
	return x;
}
int CSVFile::addBestTC(vector<int> sol, int custo, float mbf, int iter, int x)
{
	string tmp = "";
	if (x == 0)
		++lastLine;
	
	Write(x++, lastLine, to_string(iter));
	for (auto i = 0; i < sol.size(); ++i)
	{
		if (sol[i] == 1){
			if (i < sol.size() - 1)
				tmp += (to_string(i + 1) + " ");
			else
				tmp += to_string(i + 1);
		}
	}
	Write(x++, lastLine, tmp);
	Write(x++, lastLine, to_string(mbf / iter));
	Write(x++, lastLine, to_string(custo));
	Write(x++, lastLine, to_string(1));
	return x;
}

int CSVFile::addCabecalhoE(int x)
{
	if (x == 0)
		++lastLine;
	Write(x++, lastLine, "Iteracao");
	Write(x++, lastLine, "Probbilidade de mutacao");
	Write(x++, lastLine, "Probabilidade de crossover");
	Write(x++, lastLine, "Tamanho da populacao");
	Write(x++, lastLine, "Maximo Geracoes");
	Write(x++, lastLine, "Solucao");
	Write(x++, lastLine, "MBF");
	Write(x++, lastLine, "Percentagem de Invalidos");
	Write(x++, lastLine, "Melhor");
	return x;
}

int CSVFile::addHipoteseE(int iter, float mbf, float percInv, Individual run, Info info, int x)
{
	string tmp = "";
	if (x == 0)
		++lastLine;
	Write(x++, lastLine, to_string(iter));
	Write(x++, lastLine, to_string(info.pm));
	Write(x++, lastLine, to_string(info.pr));
	Write(x++, lastLine, to_string(info.popsize));
	Write(x++, lastLine, to_string(info.numGenerations));
	for (auto i = 0; i < run.p.size(); ++i)
	{
		if (run.p[i] == 0)
			tmp += (to_string(i + 1) + " ");
	}
	Write(x++, lastLine, tmp);
	Write(x++, lastLine, to_string(mbf));
	Write(x++, lastLine, to_string(percInv));
	Write(x++, lastLine, to_string(0));
	return x;
}

int CSVFile::addBestE(int iter, float mbf, float percInv, Individual run, Info info, int x)
{
	string tmp = "";
	if (x == 0)
		++lastLine;
	Write(x++, lastLine, to_string(iter));
	Write(x++, lastLine, to_string(info.pm));
	Write(x++, lastLine, to_string(info.pr));
	Write(x++, lastLine, to_string(info.popsize));
	Write(x++, lastLine, to_string(info.numGenerations));
	for (auto i = 0; i < run.p.size(); ++i)
	{
		if (run.p[i] == 0)
			tmp += (to_string(i + 1) + " ");
	}
	Write(x++, lastLine, tmp);
	Write(x++, lastLine, to_string(mbf));
	Write(x++, lastLine, to_string(percInv));
	Write(x++, lastLine, to_string(0));
	return x;
}
void CSVFile::toFile(string filename)
{
	ofstream *file = new ofstream(filename + ".csv");
	for (auto y : matriz)
	{
		for(auto x : y)
		{
			*file << x << ",";
		}
		*file << endl;
	}
	
}

CSVFile::~CSVFile()
{
}
