#include <graph_input.h>
#include <randomised_fvs.h>
#include <graph.h>
#include <bits/stdc++.h>

void delete_isolated_vertices(graph g)
{
	int degree=0;
	for (int i = 0; i < g.v; ++i)						// g.v is getting changed down // two loops two sizes might be different
	{
		degree = 0;										// note all degree 0 vertices 
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
			}
		}
		if (degree == 0)
		{
			g.shift_matrix(i);
		}
	}
}

void delete_degree_one_vertices(graph g)
{
	int degree=0;
	for (int i = 0; i < g.v; ++i)						// g.v is getting changed down
	{
		degree = 0;										// note all degree 0 vertices
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
			}
		}
		if (degree == 1)
		{
			g.shift_matrix(i);
		}
	}
}

int delete_loops()
{
	int number_of_loops=0;
	for (int i = 0; i < g.v; ++i)
	{
		if (g.matrix[i][i] == 1)
		{
			number_of_loops++;
			g.shift_matrix(i);							// what about edges incident to v
		}
	}

	return number_of_loops;
}

void short_circuit_degree_two_vertices(graph g)
{
	int degree=0;
	for (int i = 0; i < g.v; ++i)						// g.v is getting changed down
	{
		degree = 0;										// note all degree 0 vertices
		vector<int> adj_vertices;
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
				adj_vertices.push_back(j);				// check adj_vertices scope once
			}
		}
		if (degree == 2)
		{
			g.matrix[adj_vertices[0]][adj_vertices[1]] = 1;
			g.matrix[adj_vertices[1]][adj_vertices[0]] = 1;
			g.shift_matrix(i);
		}
	}
}

void preprocessing_rules()
{
	int reduce_parameter=0;
	delete_isolated_vertices(&g);     // degree as input 0 and 1
	delete_degree_one_vertices(&g);
	reduce_parameter = delete_loops(&g);
	k = k-reduce_parmater;
	short_circuit_degree_two_vertices(&g);
}

tuple<int,int> pick_edge(graph g)
{

}

int pick_vertex(int u, int v)
{
	int x = rand() % 2;
	if (x==0)
	{
		return u;
	}
	else if(x==1)
	{
		return v;
	}
}

bool check_fvs(graph g, vector<int> fvs)
{
	
}

void randomised_fvs(graph g, int k)
{
	int parameter = k; 
	int u=0, v=0, x=0;
	vector<int> fvs;
	for (int i = 0; i < parameter; ++i)
	{
		k = preprocessing_rules(&g, k);
		tie(u,v) = pick_edge(g);
		x = pick_vertex(u, v);
		fvs.push_back(x);
		g.shift_matrix(x);
	}
	if(check_fvs(g, fvs))
	{
		cout << "Feedback vertex set size : " << fvs.size() << endl;
	}
}


int main(int argc, char const *argv[])
{
	graph g = read_file();
	g.print_matrix();

	int k;

	randomised_fvs(g,k);

	return 0;
}
