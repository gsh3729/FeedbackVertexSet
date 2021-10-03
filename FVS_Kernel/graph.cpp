#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

graph :: graph(int a, int b)
{
	v = a;
	no_of_edges = b;
}

graph :: graph(const graph &g1) 
{	v = g1.v;
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			matrix[i][j] = g1.matrix[i][j];
		}
	}
	no_of_edges = g1.no_of_edges;
}

void graph :: add_edge(int a, int b)
{
	matrix[a][b] = 1;
	matrix[b][a] = 1;
}

void graph :: print_matrix()
{
	cout << "------Adjacent matrix-------" << endl;
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void graph :: shift_matrix(int x)
{
	while (x < v)
	{ 
        for (int y = 0; y < v; ++y) 
        { 
            matrix[y][x] = matrix[y][x + 1]; 
        } 

        for (int y = 0; y < v; ++y) { 
            matrix[x][y] = matrix[x + 1][y]; 
        } 
        x++; 
    }
    v--;
}

int get_degree(int x)
{
	int degree = 0;
	for (int i = 0; i < v; ++i)
	{
		if (matrix[x][i] >= 1)
		{
			degree = degree + matrix[x][i];
		}
		
	}
	return degree;
}

int double_edges(int x)
{
	int num=0;
	for (int i = 0; i < v; ++i)
	{
		if (matrix[x][i] == 2)
		{
			num++;
		}
		
	}
	return num;
}

vector<int> neighbours(int x)
{
	vector<int> ngbrs;
	for (int i = 0; i < v; ++i)
	{
		if (matrix[x][i] >= 1)
		{
			ngbrs.push_back(i);
		}
	}
	return ngbrs;
}

void graph :: delete_vertices(vector<int> x)
{
	for (auto i:x)
	{
		for (int j = 0; j < v; ++j)
		{
			matrix[i][j] = 0;
			matrix[j][i] = 0;
		}
	}

}

bool graph :: is_empty()
{
	if (v <= 0)
	{
		return true;
	}

	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (matrix[i][j] == 1)
			{
				return false;
			}
		}
	}

	return true;
}


