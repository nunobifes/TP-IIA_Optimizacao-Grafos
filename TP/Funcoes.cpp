#include "Funcoes.h"



void Funcoes::le_dados(string nome, int* vert, vector< vector<int> >* mat, int *edges)
{
	string caminho = "Instancias\\" + nome + ".clq";
	string linha;
	vector< vector<int> > matb;
	string val, lixo, lixo2, v, e;
	istringstream n;
	ifstream dados(caminho);
	do
	{ 
		
		getline(dados, linha);
		n.str(linha);
	}
	while (linha[0] != 'p');
	n >> lixo;
	n >> lixo2;
	n >> v;
	n >> e;
	*vert = atoi(v.c_str());
	*edges = atoi(e.c_str());
	for (auto i = 0; i < *vert; i++)
	{
		vector<int>novo;
		for (auto j = 0; j < *vert; j++)
		{
			novo.push_back(0);
		}
		matb.push_back(novo);
	}
	for (auto k = 0; k < *edges; k++) {
		getline(dados, linha);
		istringstream n(linha);
		string i, j;
		n >> lixo;
		n >> i;
		n >> j;
		matb[atoi(i.c_str())-1][atoi(j.c_str())-1] = 1;
	}
	*mat = matb;
}

void Funcoes::init_rand()
{
	srand((unsigned)time(NULL));
}

int Funcoes::random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float Funcoes::rand_01()
{
	return ((float)rand()) / RAND_MAX;
}
