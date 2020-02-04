#include <graph_input.h>
#include <randomised_fvs.h>
#include <graph.h>
#include <bits/stdc++.h>


int find_max_degree(graph g)
{
	int max_degree=-1;
	for (int i = 0; i < g.v; ++i)
	{
		degree=0;
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j]==1)
			{
				degree++;
			}
		}
		max_degree = max(max_degree, degree);
	}
	return max_degree;
}

void branching(graph g, int k)
{
	int max_degree = find_max_degree(g);

	if (max_degree==0 && k>=0)
	{
		return true;
	}

	if (k<0)
	{
		return false;
	}

	graph g_1 = g;
	g_1.shift_matrix(v);
	branching(g_1, k-1);

	graph g_2 = g;
	int degree = 0;
	for (int i = 0; i < g.v; ++i)
	{
		if (g.matrix[v][i] == 1)
		{
			g_2.shift_matrix(i);
			degree++;
		}
	}
	branching(g_2,k-degree);
}



bool branching_vc(graph g, int k)
{
	graph g_1, g_2;
	tie(g_1, g_2) = preprocessing_rules(g);
	return branching(g_1,k) || branching(g_2,k);
}


int main(int argc, char const *argv[])
{
	graph g = read_file();
	g.print_matrix();

	int k=4;

	branching_vc(g,k);

	return 0;
}

tuple<graph, graph> preprocessing_rules(graph g)
{
	int number_of_vertices_deleted=0;

	delete_isolated_vertices(&g);     // degree as input 0 and 1
	number_of_vertices_deleted = delete_high_degree_vertices(&g,k);
	k = k-number_of_vertices_deleted;
	number_of_vertices_deleted = add_ngbrs_degree_one(&g);
	k = k-number_of_vertices_deleted;
	number_of_vertices_deleted = degree_two_vertices(g);
	k = k-number_of_vertices_deleted;
}

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

int delete_high_degree_vertices(graph g, int k)
{
	int degree=0;
	int number_of_vertices_deleted = 0;
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
		if (degree >= k+1)								// check k+1
		{
			g.shift_matrix(i);
			number_of_vertices_deleted++;
		}
	}

	return number_of_vertices_deleted;
}


int add_ngbrs_degree_one(graph g)
{
	int degree=0;
	int number_of_vertices_deleted=0;
	for (int i = 0; i < g.v; ++i)						// g.v is getting changed down
	{
		degree = 0;
		vector<int> adj_vertices;										// note all degree 0 vertices
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
			number_of_vertices_deleted++;
			g.shift_matrix(i);						// check to delete or not
		}
	}
	return number_of_vertices_deleted;
}


tuple<int,vector<graph>> degree_two_vertices(graph g)
{
	int degree=0;
	vector<graph> graph_reductions;
	for (int i = 0; i < g.v; ++i)						// g.v is getting changed down
	{
		degree = 0;										// note all degree 0 vertices
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
				number_of_vertices_deleted = number_of_vertices_deleted+2;
			}
			else
			{
				graph g_dash = g;
				vector<int> ngbrs;
				for (int x = 0; x < g.v; ++x)
				{
					if (g_dash.matrix[adj_vertices[1]][x] == 1 && x!=i)
					{
						ngbrs.push_back(x);
					}
				}
				for (auto x: ngbrs)
				{
					g_dash.matrix[adj_vertices[0]][x] = 1;
					g_dash.matrix[x][adj_vertices[0]] = 1;
				}
				g_dash.shift_matrix(i);	
				g_dash.shift_matrix(adj_vertices[1]);	
				number_of_vertices_deleted = number_of_vertices_deleted+1;			// reduced by 1 only
				graph_reductions.push_back(g_dash);		// will g_dash be see outside as its scope is over


			}
		}
	}
}


