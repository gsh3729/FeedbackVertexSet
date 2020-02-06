#include <bits/stdc++.h>
using namespace std;
#include "graph.h"
#include "graph_input.h"
#include "branching_vc.h"	

void delete_isolated_vertices(graph& g)
{
	int degree=0;
	for (int i = 0; i < g.v; ++i)						
	{
		degree = 0;										 
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

int delete_high_degree_vertices(graph& g, int k)
{
	int degree=0;
	int number_of_vertices_deleted = 0;
	for (int i = 0; i < g.v; ++i)						
	{
		degree = 0;										
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
			}
		}
		if (degree >= k+1)								
		{
			g.shift_matrix(i);
			i--;
			number_of_vertices_deleted++;
		}
	}

	return number_of_vertices_deleted;
}


int add_ngbrs_degree_one(graph& g)
{
	int degree=0;
	int number_of_vertices_solution=0;
	int number_of_vertices_deleted=0;
	for (int i = 0; i < g.v; ++i)						
	{
		degree = 0;
		vector<int> adj_vertices;										
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
				adj_vertices.push_back(j);
			}
		}
		if (degree == 1)
		{
			number_of_vertices_solution++;			// add ngbr to soln and delete vertex
			g.shift_matrix(adj_vertices[0]);		// check to delete or not // if nbr is removed then edge with i is removed
			if (i>adj_vertices[0])
			{
				i--;
			}
		}
	}
	return number_of_vertices_solution;
}


int degree_two_vertices(graph& g)
{
	int degree=0;
	int number_of_vertices_solution=0;	
	for (int i = 0; i < g.v; ++i)						
	{
		degree = 0;										
		vector<int> adj_vertices;						// check scope
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
			if (g.matrix[adj_vertices[0]][adj_vertices[1]]==1)
			{
				g.shift_matrix(adj_vertices[0]);
				g.shift_matrix(adj_vertices[1]);
				g.shift_matrix(i);	
				if (i<adj_vertices[0] && i<adj_vertices[1])
				{
					i--;
				}
				else if ((i>adj_vertices[0] && i<adj_vertices[1]) || (i>adj_vertices[1] && i<adj_vertices[0]))
				{
					i=i-2;
				}
				else if (i>adj_vertices[0] && i>adj_vertices[1])
				{
					i=i-3;
				}
				number_of_vertices_solution = number_of_vertices_solution+2;
			}
			else
			{
				for (int x = 0; x < g.v; ++x)
				{
					if (g.matrix[adj_vertices[1]][x]==1 && x!=i)
					{
						g.matrix[adj_vertices[0]][x] = 1;
						g.matrix[x][adj_vertices[0]] = 1;
					}
				}	
				g.shift_matrix(i);	
				g.shift_matrix(adj_vertices[1]);
				if (i<adj_vertices[1])
				{
					i--;
				}
				else if (i>adj_vertices[1])
				{
					i=i-2;
				}
				number_of_vertices_solution = number_of_vertices_solution+1;			
			}
		}
	}

	return number_of_vertices_solution;
}


void preprocessing_rules(graph& g, int& k)
{
	int number_of_vertices_deleted=0, number_of_vertices_solution=0;

	delete_isolated_vertices(g);     
	number_of_vertices_deleted = delete_high_degree_vertices(g,k);
	k = k-number_of_vertices_deleted;
	number_of_vertices_solution = add_ngbrs_degree_one(g);
	k = k-number_of_vertices_solution;
	number_of_vertices_solution = degree_two_vertices(g);
	k = k-number_of_vertices_solution;
}										

tuple<int,int> find_max_degree(graph g)
{
	int max_degree=-1, max_degree_vertex=-1;
	for (int i = 0; i < g.v; ++i)
	{
		int degree=0;
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
			}
		}
		if (degree > max_degree)
		{
			max_degree = degree;
			max_degree_vertex = i;
		}
	}
	return make_tuple(max_degree, max_degree_vertex);
}

bool branching(graph g, int k)
{
	int max_degree, max_degree_vertex;
	tie(max_degree, max_degree_vertex) = find_max_degree(g);

	if (max_degree==0 && k>=0)
	{
		return true;
	}

	if (k<0)
	{
		return false;
	}

	graph g_1 = g;
	g_1.shift_matrix(max_degree_vertex);
	// g_1.print_matrix();


	graph g_2 = g;
	int degree = 0;

	for (int i = 0; i < g_2.v; ++i)
	{
		if (g_2.matrix[max_degree_vertex][i] == 1)
		{
			g_2.shift_matrix(i);
			i--;
			degree++;
		}
	}
	// g_2.print_matrix();
	
	return branching(g_1, k-1) || branching(g_2,k-degree);
}


 
bool branching_vc(graph g, int k)
{
	preprocessing_rules(g,k);
	// cout << "preprocessing done : " << k <<endl;
	// g.print_matrix();
	return branching(g,k);
}


int main(int argc, char const *argv[])
{
	graph g = read_file();

	for (int k = 2*g.v/3; k>0; --k)
	{
		// k=3;
		if (branching_vc(g,k))
		{
			cout << "Given G has a vertex cover of size " << k << endl;
		}
		else
		{
			cout << "Given G does not has a vertex cover of size " << k << endl;
		}
		// break;
	}
	return 0;
}





