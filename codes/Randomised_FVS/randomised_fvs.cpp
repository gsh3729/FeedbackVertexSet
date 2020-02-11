#include <bits/stdc++.h>
using namespace std;
#include "graph.h"
#include "graph_input.h"
#include "randomised_fvs.h"

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
	}
}

void preprocessing_rules(graph& g, int& k)
{
	int number_of_vertices_deleted=0;
	delete_isolated_vertices(g);     // degree as input 0 and 1
	delete_degree_one_vertices(g);
	number_of_vertices_deleted = delete_loops(g);
	k = k-number_of_vertices_deleted;
	short_circuit_degree_two_vertices(g);
}


vector<vector<int>> find_cycles(graph g)
{
	vector<vector <int>> cycles;
	vector<int> cycle; 
	stack <int> included_in_tree_not_explored;
	map<int, int> parent;
	map<int, set<int>> included_in_tree;

	included_in_tree_not_explored.push(0);
	parent.insert(pair<int,int> {0,0});
	included_in_tree.insert(pair<int, set<int>>(0,set<int> {0}));
	while (!included_in_tree_not_explored.empty())
	{
		int z = included_in_tree_not_explored.top();
		// cout << "exploring " << z << endl;
		included_in_tree_not_explored.pop();
		for (int i = 0; i < g.v; ++i)
		{
			if (g.matrix[i][z]==1)
			{
				if (i==z)
				{
					cycles.push_back(vector<int> {z});
				}
				else if (included_in_tree.find(i)==included_in_tree.end())   //new node //avoids parent(already in tree)
				{
					// cout << "new node found " << i << endl; 
					included_in_tree.insert(pair<int, set<int>>(i,set<int> {z}));
					included_in_tree_not_explored.push(i);
					parent.insert(pair<int, int>(i,z));
				}
				else if (included_in_tree[z].find(i)==included_in_tree[z].end()) // found a cycle //only parent and virtual parent 
				{
					// cout << "found cycle bcoz of edge " << z << i << endl; 
					cycle.push_back(i);
					cycle.push_back(z);
					int p = parent[z];
					while (included_in_tree[i].find(p)==included_in_tree[i].end()) // till parent of i is reached
					{
						cycle.push_back(p);
						p = parent[p];
					}
					cycle.push_back(p);
					cycles.push_back(cycle);
					cycle.clear();
					included_in_tree[i].insert(z);
				}
			}
		}
	}
	return cycles;
}

void printing_cycles(graph g)
{
	vector<vector<int>> cycles = find_cycles(g);
	for (auto i : cycles)
	{
		for (auto j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	return;
}

bool check_fvs(graph g, vector<int> fvs)
{
	map<int,int> fvs_map;
	for(auto i:fvs)
	{
		fvs_map[i]++;
	} 

	vector<vector<int>> cycles = find_cycles(g);
	
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

	return true;
}

void test_fvs(graph g)
{
	vector<int> fvs;
	// fvs.push_back(0);
	fvs.push_back(1);
	// fvs.push_back(2);
	if(check_fvs(g,fvs))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

}

tuple<int,int> pick_edge(graph g)
{
	int x = rand() % g.no_of_edges;
	return g.edge_map[x];
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
	return x;
}

void randomised_fvs(graph g, int k)
{
	int u=0, v=0, x=0;
	int parameter = k;
	for (int i = 0; i < pow(4,k); ++i)
	{
		cout << i << endl;
		vector<int> fvs;
		for (int j = 0; j < parameter; ++j) 		// k will change so need to keep it unupdated
		{
			preprocessing_rules(g, k);
			g.print_matrix();
			tie(u,v) = pick_edge(g);
			x = pick_vertex(u, v);
			fvs.push_back(x);
			g.shift_matrix(x);
		}
		// cout << "fvs" << fvs[0] << endl;
		if(check_fvs(g, fvs))
		{
			cout << "Feedback vertex set size : " << fvs.size() << endl;
			return;		
		}	
	}
	cout << "No instance" << endl;
	return;
}


int main(int argc, char const *argv[])
{
	graph g = read_file();

	int k=1;
	
	randomised_fvs(g,k);

	return 0;
}


