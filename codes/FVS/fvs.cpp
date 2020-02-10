#include <bits/stdc++.h>
using namespace std;
#include "graph.h"
#include "graph_input.h"
#include "fvs.h"

void delete_isolated_vertices(graph& g)
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
			i--;
		}
	}
}

void delete_degree_one_vertices(graph& g)
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
			i--;
		}
	}
}

int delete_loops(graph& g)
{
	int number_of_loops=0;
	for (int i = 0; i < g.v; ++i)
	{
		if (g.matrix[i][i] == 1)
		{
			number_of_loops++;
			g.shift_matrix(i);							// what about edges incident to v
			i--;
		}
	}

	return number_of_loops;
}

void short_circuit_degree_two_vertices(graph& g)
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
			i--;
		}
	}													// continous short circuit cascading updates
}

void preprocessing_rules(graph& g, int& k)								// check whether all rules are applied exhaustively
{
	int reduce_parameter=0;
	delete_isolated_vertices(g); 
	cout << "iso" << endl;
	g.print_matrix();    
	delete_degree_one_vertices(g);
	cout << "one" << endl;
	g.print_matrix();    
	reduce_parameter = delete_loops(g);
	k = k-reduce_parameter;
	cout << "dl" << endl;
	g.print_matrix();    
	short_circuit_degree_two_vertices(g);
	cout << "sc" << endl;
	g.print_matrix();    
}

bool sortinrev(const pair<int,int> &a, const pair<int,int> &b) 
{ 
       return (a.first > b.first); 
} 

vector<int> find_vertex_order(graph g, int k)
{
	vector<int> degree;
	for (int i = 0; i < g.v; ++i)
	{
		int v_degree = 0;
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j] == 1)
			{
				v_degree++;
			}
		}
		degree.push_back(v_degree);
	}

	vector<pair<int, int>> pairt;
    for (int i = 0; i < g.v; i++)  
    { 
    	pairt.push_back(make_pair(degree[i], i));
    } 
    sort(pairt.begin(), pairt.end(), sortinrev);   // check whether sorting is happening to first vertex

    degree.clear();
    for (int i = 0; i < 3*k; i++)  
    { 
        degree.push_back(pairt[i].second); 
    }

    return degree;
}

bool branching_fvs(graph g, int k)
{
	if (k<0)
	{
		return false;
	}

	if (g.is_empty() && k>=0)
	{
		return true;
	}

	bool result=false;
	vector<int> vertex_order = find_vertex_order(g,k);

	for (auto i: vertex_order)
	{
		graph g_dash = g;				
		g_dash.shift_matrix(i);
		result = result || branching_fvs(g_dash, k-1);
	}

	return result;
}


bool fvs(graph g, int k)				// should we branch at every step
{  
	preprocessing_rules(g, k);					// graph g has min degree 3
	cout << "processing done : " << k << endl; 
	g.print_matrix();

	return branching_fvs(g,k);	
}


int main(int argc, char const *argv[])
{
	graph g = read_file();

	int k=3;

	if (fvs(g,k))
	{
		cout << "Given G has a fvs of size " << k << endl;
	}
	else
	{
		cout << "Given G does not has a fvs of size " << k << endl;
	}

	return 0;
}
