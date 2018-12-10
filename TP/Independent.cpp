#include "Independent.h"

ofstream outfile("sets.txt");

Independent::Independent(int vert): verts(vert)
{
	counter = 0;
	found = false;
	min = verts + 1;
}

Independent::~Independent()
{
}

bool Independent::removable(vector<int> neighbor, vector<int> cover)
{
	bool check = true;
	for (int i = 0; i < neighbor.size(); i++)
		if (cover[neighbor[i]] == 0)
		{
			check = false;
			break;
		}
	return check;
}

int Independent::max_removable(vector<vector<int>> neighbors, vector<int> cover)
{
	int r = -1, max = -1;
	for (int i = 0; i < cover.size(); i++)
	{
		if (cover[i] == 1 && removable(neighbors[i], cover) == true)
		{
			vector<int> temp_cover = cover;
			temp_cover[i] = 0;
			int sum = 0;
			for (int j = 0; j < temp_cover.size(); j++)
				if (temp_cover[j] == 1 && removable(neighbors[j], temp_cover) == true)
					sum++;
			if (sum > max)
			{
				max = sum;
				r = i;
			}
		}
	}
	return r;
}

vector<int> Independent::procedure_1(vector<vector<int>> neighbors, vector<int> cover)
{
	vector<int> temp_cover = cover;
	int r = 0;
	while (r != -1)
	{
		r = max_removable(neighbors, temp_cover);
		if (r != -1) temp_cover[r] = 0;
	}
	return temp_cover;
}

vector<int> Independent::procedure_2(vector<vector<int>> neighbors, vector<int> cover, int k)
{
	int count = 0;
	vector<int> temp_cover = cover;
	for (int i = 0; i < temp_cover.size(); i++)
	{
		if (temp_cover[i] == 1)
		{
			int sum = 0, index;
			for (int j = 0; j < neighbors[i].size(); j++)
				if (temp_cover[neighbors[i][j]] == 0) { index = j; sum++; }
			if (sum == 1 && cover[neighbors[i][index]] == 0)
			{
				temp_cover[neighbors[i][index]] = 1;
				temp_cover[i] = 0;
				temp_cover = procedure_1(neighbors, temp_cover);
				count++;
			}
			if (count > k) break;
		}
	}
	return temp_cover;
}

int Independent::cover_size(vector<int> cover)
{
	int count = 0;
	for (int i = 0; i < cover.size(); i++)
		if (cover[i] == 1) count++;
	return count;
}

void Independent::setK(int K)
{
	k = verts - K;
}

void Independent::encontraIndepedentes(Grafo grafo)
{
	
	//Find Independent Sets
	bool found = false;
	cout << "Finding Independent Sets..." << endl;
	min = verts + 1;
	vector<vector<int> > covers;
	vector<int> allcover;
	for (auto i = 0; i < grafo.getMatriz().size(); i++)
		allcover.push_back(1);
	for (auto i = 0; i < allcover.size(); i++)
	{
		if (found) break;
		counter++; cout << counter << ". ";  outfile << counter << ". ";
		vector<int> cover = allcover;
		cover[i] = 0;
		cover = procedure_1(grafo.getViz(), cover);
		s = cover_size(cover);
		if (s < min) min = s;
		if (s <= k)
		{
			outfile << "Independent Set (" << verts - s << "): ";
			for (auto j = 0; j < cover.size(); j++) if (cover[j] == 0) outfile << j + 1 << " ";
			outfile << endl;
			cout << "Independent Set Size: " << verts - s << endl;
			covers.push_back(cover);
			found = true;
			break;
		}
		for (auto j = 0; j < verts - k; j++)
			cover = procedure_2(grafo.getViz(), cover, j);
		s = cover_size(cover);
		if (s < min) min = s;
		outfile << "Independent Set (" << verts - s << "): ";
		for (auto j = 0; j < cover.size(); j++) if (cover[j] == 0) outfile << j + 1 << " ";
		outfile << endl;
		cout << "Independent Set Size: " << verts - s << endl;
		covers.push_back(cover);
		if (s <= k) { found = true; break; }
	}

	/*cout << "Finding independent Sets..." << endl;
	
	
	for (auto i = 0; i < grafo.getMatriz().size(); i++)
		allcover.push_back(1);
	for(auto i = 0; i<allcover.size(); i++)
	{
		if (found)
			break;

		counter++;
		cout << counter << ". ";
		vector<int> cover = allcover;
		cover[i] = 0;
		cover = procedure_1(grafo.getViz(), cover);
		s = cover_size(cover);
		if (s < min)
			min = s;
		if(s <= k)
		{
			cout << "Independent Set(" << verts - s << "): ";
			for (auto j = 0; j < cover.size(); j++)
				if (cover[j] == 0)
					cout << j + 1 << " ";
			cout << endl;
			cout << "Independent set Size: " << verts - s << endl;
			covers.push_back(cover);
			found = true;
			break;
		}
		for(auto j = 0; j < verts - k; j++)
			cover = procedure_2(grafo.getViz(), cover, j);
		s = cover_size(cover);
		if (s < min)
			min = s;
		cout << "Independent Set(" << verts - s << "): ";
		for (auto j = 0; j < cover.size(); j++)
			if (cover[j] == 0)
				cout << j + 1 << " ";
		cout << endl;
		cout << "Independent set Size: " << verts - s << endl;
		covers.push_back(cover);
		if(s <= k)
		{
			found = true;
			break;
		}
	}*/
}

void Independent::pairwiseIntercecoes(Grafo grafo)
{
	for (auto p = 0; p < covers.size(); p++)
	{
		if (found) break;
		for (auto q = p + 1; q < covers.size(); q++)
		{
			if (found) break;
			counter++; cout << counter << ". ";  outfile << counter << ". ";
			vector<int> cover = allcover;
			for (auto r = 0; r < cover.size(); r++)
				if (covers[p][r] == 0 && covers[q][r] == 0) cover[r] = 0;
			cover = procedure_1(grafo.getViz(), cover);
			s = cover_size(cover);
			if (s < min) min = s;
			if (s <= k)
			{
				outfile << "Independent Set (" << verts - s << "): ";
				for (auto j = 0; j < cover.size(); j++) if (cover[j] == 0) outfile << j + 1 << " ";
				outfile << endl;
				cout << "Independent Set Size: " << verts - s << endl;
				found = true;
				break;
			}
			for (auto j = 0; j < k; j++)
				cover = procedure_2(grafo.getViz(), cover, j);
			s = cover_size(cover);
			if (s < min) min = s;
			outfile << "Independent Set (" << verts - s << "): ";
			for (auto j = 0; j < cover.size(); j++) if (cover[j] == 0) outfile << j + 1 << " ";
			outfile << endl;
			cout << "Independent Set Size: " << verts - s << endl;
			if (s <= k) { found = true; break; }
		}
	}
	if (found) cout << "Found Independent Set of size at least " << verts - k << "." << endl;
	else cout << "Could not find Independent Set of size at least " << verts - k << "." << endl
		<< "Maximum Independent Set size found is " << verts - min << "." << endl;
	cout << "See sets.txt for results." << endl;


	/*for(auto p = 0; p<covers.size(); p++)
	{
		if (found)
			break;
		for(auto q = p + 1; q<covers.size(); q++)
		{
			if (found)
				break;
			counter++;
			cout << counter << ". ";
			vector<int> cover = allcover;
			for (auto r = 0; r < cover.size(); r++)
				if (covers[p][r] == 0 && covers[q][r])
					cover[r] = 0;
			cover = procedure_1(grafo.getViz(), cover);
			s = cover_size(cover);
			if (s < min)
				min = s;
			if (s <= k)
			{
				cout << "Independent Set(" << verts - s << "): ";
				for (auto j = 0; j < cover.size(); j++)
					if (cover[j] == 0)
						cout << j + 1 << " ";
				cout << endl;
				cout << "Independent set Size: " << verts - s << endl;
				covers.push_back(cover);
				found = true;
				break;
			}
			for (auto j = 0; j <k; j++)
				cover = procedure_2(grafo.getViz(), cover, j);
			s = cover_size(cover);
			if (s < min)
				min = s;
			cout << "Independent Set(" << verts - s << "): ";
			for (auto j = 0; j < cover.size(); j++)
				if (cover[j] == 0)
					cout << j + 1 << " ";
			cout << endl;
			cout << "Independent set Size: " << verts - s << endl;
			if (s <= k)
			{
				found = true;
				break;
			}
		}
	}
	if (found)
		cout << "Found Independent Set of size at least " << k + verts << "." << endl;
	else
		cout << "Could not find Independent Set of size at least " << k + verts << "." << endl << "Maximum Independent Set size found is " << verts - min << "." << endl;
	*/
}
