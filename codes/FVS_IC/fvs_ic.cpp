#include <bits/stdc++.h>
using namespace std;
#include "graph.h"
#include "graph_input.h"
#include "fvs_ic.h"

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

void delete_degree_one_vertices(graph& g)
{
	int degree=0;
	vector<int> vertex_to_delete;
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
		if (degree == 1)
		{
			vertex_to_delete.push_back(i);			
		}
	}
	g.delete_vertices(vertex_to_delete);
}


int delete_loops(graph& g)
{
	int number_of_loops=0;
	for (int i = 0; i < g.v; ++i)
	{
		if (g.matrix[i][i] == 1)
		{
			number_of_loops++;
			g.shift_matrix(i);							
			i--;
		}
	}

	return number_of_loops;
}


void preprocessing_rules(graph& g, int& k)								
{
	int reduce_parameter=0;
	delete_isolated_vertices(g); 
	reduce_parameter = delete_loops(g);
	k = k-reduce_parameter;
	g.print_matrix();    
}

void get_intersection(vector<int> big_solution, int i, vector<int> left, vector<int> right, vector<tuple<vector<int>, vector<int>>>& result)
{
	if (i==big_solution.size())
	{
		if (left.empty() || right.empty())				// verify this once
		{
			return;
		}
		result.push_back(make_tuple(left, right));
		return;
	}

	left.push_back(big_solution[i]);
	get_intersection(big_solution,i+1,left,right,result);

	left.pop_back();
	right.push_back(big_solution[i]);
	get_intersection(big_solution,i+1,left,right,result);

}

void get_subgraph(graph& g, vector<int> subgraph_vertices)
{
	vector<int> vertex_to_delete;
	for (int i = 0; i < g.v; ++i)
	{
		if (find(subgraph_vertices.begin(), subgraph_vertices.end(), i) == subgraph_vertices.end())
		{
			vertex_to_delete.push_back(i);
		}
	}

	g.delete_vertices(vertex_to_delete);
}

int find_leaf(graph g, vector<int> x_forest, vector<int> y_forest)
{
	graph g1 = g;
	g1.delete_vertices(x_forest);

	for (int i = 0; i < g1.v; ++i)
	{
		int y_degree = 0;
		for (int j = 0; j < g1.v; ++j)
		{
			if (g1.matrix[i][j] == 1)
			{
				y_degree++;
			}
		}

		int x_degree=0;
		for (auto j : x_forest)
		{
			if (g.matrix[i][j]==1)
			{
				x_degree++;
			}
		}

		if (y_degree <= 1 && x_degree >= 2)
		{
			return i;
		}
	}
}


bool branching_fvs_ic(graph g, int k, vector<int>& solution, vector<int> x_forest, vector<int> y_forest)
{
	if (k<0)
	{
		return false;
	}

	if (g.is_empty() && k>=0)
	{
		return true;
	}

	int v = find_leaf(g, x_forest, y_forest);

	graph g1 = g;
	g1.shift_matrix(v);
	y_forest.erase(remove(y_forest.begin(), y_forest.end(), v), y_forest.end());
	bool flag1 = branching_fvs_ic(g, k-1, solution, x_forest, y_forest);


	x_forest.push_back(v);	
	bool flag2 = branching_fvs_ic(g, k, solution, x_forest, y_forest);

	if (flag1 || flag2)
	{
		if (flag1)
		{
			solution.push_back(v);
		}
	}

	return flag1 || flag2;
}

vector<int> reduction(graph g, vector<int>big_intersect_small, vector<int>& x_forest, vector<int>& y_forest, int k)
{
	vector<int> solution;
	for(auto i: big_intersect_small)
	{
		solution.push_back(i);
	}

	graph g1 = g;
	g1.delete_vertices(big_intersect_small);

	delete_degree_one_vertices(g1);	

	vector<vector<int>> cycles = find_cycles(g1);
	vector<int> vertex_to_delete;

	for(auto cycle : cycles)							// graph is modified check it //should we update x_forest and y_forest
	{
		int x_count = 0, y_count = 0, temp;
		for(auto i: cycle)
		{
			if (find(x_forest.begin(), x_forest.end(), i) != x_forest.end()) 
			{
				x_count++;
			}
			else if (find(y_forest.begin(), y_forest.end(), i) != y_forest.end())
			{
				y_count++;
				temp = i;
			}
		}
		if (y_count == 1 && x_count >= 2)
		{
			vertex_to_delete.push_back(temp);
			solution.push_back(temp);
			y_forest.erase(remove(y_forest.begin(), y_forest.end(), temp), y_forest.end());
			k--;
		}
	}
	g1.delete_vertices(vertex_to_delete);
	vertex_to_delete.clear();

	for (int i = 0; i < g1.v; ++i)
	{
		int degree = 0;
		vector<int> ngbrs;
		for (int j = 0; j < g1.v; ++j)
		{
			if (g1.matrix[i][j]==1)
			{
				degree++;
				ngbrs.push_back(j);
			}
		}
		if (degree == 2)
		{
			if (find(y_forest.begin(), y_forest.end(), i) != y_forest.end() && 
				(find(y_forest.begin(), y_forest.end(), ngbrs[0]) != y_forest.end() || 
				find(y_forest.begin(), y_forest.end(), ngbrs[1]) != y_forest.end()))  
			{
				vertex_to_delete.push_back(i);
				solution.push_back(i);
				g1.matrix[ngbrs[0]][ngbrs[1]] = 1;
				g1.matrix[ngbrs[1]][ngbrs[0]] = 1;
			}
		}
	}
	g1.delete_vertices(vertex_to_delete);

	if(branching_fvs_ic(g1, k, solution, x_forest, y_forest))
	{
		return solution;
	}
	else
	{
		return vector<int>();
	}
}

vector<int> compression(graph g, int k, vector<int> big_solution, vector<int> subgraph_vertices)
{
	vector<int> solution;
	graph g1 = g;
	get_subgraph(g1,subgraph_vertices);

	vector<int> vertices;
	for (int i = 0; i < g1.v; ++i)
	{
		vertices.push_back(i);
	}

	vector<int> small_solution;
	vector<int> left, right, big_intersect_small;
	vector<tuple<vector<int>, vector<int>>> result;
	get_intersection(big_solution, 0, left, right, result);

	for (auto i : result)
	{
		tie(big_intersect_small, right) = i;
		vector<int> x_forest, y_forest;
		sort(big_solution.begin(), big_solution.end());
		sort(big_intersect_small.begin(), big_intersect_small.end());
		set_difference(big_solution.begin(),big_solution.end(),big_intersect_small.begin(),big_intersect_small.end(),x_forest.begin());		
		set_difference(vertices.begin(), vertices.end(), big_solution.begin(), big_solution.end(), y_forest.begin());
		solution = reduction(g1,big_intersect_small,x_forest,y_forest,k);
		if (!solution.empty())
		{
			for(auto j : y_forest)
			{
				if (solution.size() == k)
				{
					break;
				}
				if (find(solution.begin(), solution.end(), j) != solution.end())
				{
					solution.push_back(j);
				}
			}
			return solution;
		}
	}

	return vector<int>();
}


bool fvs_ic(graph g, int k)				
{  
	preprocessing_rules(g,k);
	vector<int> solution, subgraph_vertices;
	for (int i = 0; i < k; ++i)
	{
		solution.push_back(i);
		subgraph_vertices.push_back(i);
	}

	for (int i = k; i < g.v; ++i)
	{
		solution.push_back(i);
		subgraph_vertices.push_back(i);
		solution = compression(g,k,solution,subgraph_vertices);
		if (solution.empty())
		{
			return false;
		}
	}

	return 	true;
}


int main(int argc, char const *argv[])
{
	graph g = read_file();

	int k=3;

	if (fvs_ic(g,k))
	{
		cout << "Given G has a fvs of size " << k << endl;
	}
	else
	{
		cout << "Given G does not has a fvs of size " << k << endl;
	}

	return 0;
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