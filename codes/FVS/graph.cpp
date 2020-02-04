#include <bits/stdc++.h>

class graph
{
  public:
	graph(int a, int b)
	{
		v = a;
		no_of_edges = b;
	}
	int v;
	int no_of_edges;
	int matrix[100][100];
	void add_edge(int a, int b)
	{
		matrix[a][b] = 1;
		matrix[b][a] = 1;
	}
	void print_matrix()
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
	void shift_matrix(int x)
	{
		while (x < t.v)
		{ 
            for (int y = 0; y < t.v; ++y) 
            { 
                t.matrix[y][x] = t.matrix[y][x + 1]; 
            } 
  
            for (int y = 0; y < t.v; ++y) { 
                t.matrix[x][y] = t.matrix[x + 1][y]; 
            } 
            x++; 
        }
        g.v--;
	}
};
