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
	}													// continous short circuit cascading updates
}

void preprocessing_rules()								// check whether all rules are applied exhaustively
{
	int reduce_parameter=0;
	delete_isolated_vertices(&g);     // degree as input 0 and 1
	delete_degree_one_vertices(&g);
	reduce_parameter = delete_loops(&g);
	k = k-reduce_parmater;
	short_circuit_degree_two_vertices(&g);
}

bool check_fvs(graph g, vector<int> fvs)
{
	map<int,int> fvs_map;
	for(auto i:fvs)
	{
		fvs_map[i]++;
	} 

	vector<vector<int>> cycles = find_cycles();
	
	bool flag;
	for(auto i: cycles)
	{
		flag = false;
		for(auto j: i)
		{
			if(fvs_map.find(j) != fvs_map.end())
			{
				flag =  true;
				break;
			}
		}
		if(!flag)
		{
			return false;
		}
	}
}

vector<int> find_vertex_order(graph g, int k)
{
	vector<int> degree;
	for (int i = 0; i < g.v; ++i)
	{
		v_degree = 0;
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j] == 1)
			{
				v_degree++;
			}
		}
		degree.push_back(degree);
	}

	sort(degree, degree+g.v);

	pair<int, char> pairt[n]; 
    for (int i = 0; i < g.v; i++)  
    { 
        pairt[i].first = degree[i]; 
        pairt[i].second = i; 
    } 
    sort(pairt, pairt + g.v, greater<int>());
    degree.clear();
    for (int i = 0; i < 3*k; i++)  
    { 
        degree.push_back(pairt[i].second); 
    }

    return degree;
}

bool fvs(graph g, int k)				// should we branch at every step
{
	int parameter = k; 
	int u=0, v=0, x=0;

	preprocessing_rules(&g, k);					// graph g has min degree 3

	vector<int> vertex_order = find_vertex_order(g);

	for (auto i: vertex_order)
	{
		graph g_dash = g;				// check whether declaration is crct while iterating
		g_dash.shift_matrix(i);
		fvs(g_dash, k-1);
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
