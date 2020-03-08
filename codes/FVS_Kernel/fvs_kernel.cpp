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

void reduce_multiplicity_2(graph& g)
{
	for (int i = 0; i < g.v; ++i)
	{
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j] > 2)
			{
				number_of_loops++;
				g.matrix[i][j] = 2;
				g.matrix[j][i] = 2;
			}
		}
	}
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

void preprocessing_rules(graph& g, int& k)								
{
	int reduce_parameter=0;
	delete_isolated_vertices(g); 
	reduce_parameter = delete_loops(g);
	reduce_multiplicity_2(g);
	short_circuit_degree_two_vertices(g);
	k = k-reduce_parameter;
	g.print_matrix();    
}

connected_components()
{

}

connectedComponents() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[g.v]; 
    for(int i = 0; i < g.v; i++)
    {
        visited[i] = false; 
    }
  
    for (int i=0; i<g.v; i++) 
    { 
        if (visited[i] == false) 
        { 
            // print all reachable vertices 
            // from v 
            DFSUtil(g, root, i, visited); 
  
            cout << "\n"; 
        } 
    } 
} 
  
DFSUtil(graph g, node root, int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    cout << v << " "; 
  
    // Recur for all the vertices 
    // adjacent to this vertex 
    for (int i = 0; i < g.v; ++i)
    {
    	if (g.matrix[v][i]>=1)
    	{
    		if(!visited[*i]) 
	        {
	            DFSUtil(*i, visited); 
	        }
    	}
    }
}

vector<int> flower_lemma_return_fvs3k(graph g, int v)
{
	vector<int> solution_2k;
	solution_2k = two_approximation_fvs(g);
	graph g1 = g;
	forest = g1.delete_vertices(solution_2k);

	if (solution_2k.size()> 2*k)
	{
		return ;
	}
	else if(!solution_2k.find(v))
	{
		return solution_2k;
	}
	else
	{
		trees = connected_components(g1);
		for(auto tree : trees)
		{
			tuple<int, int> ancestor_pairs;
			vector<int> ngbrs_v = g1.neighbours(v);
			for (int i = 0; i < ngbrs_v.size(); ++i)
			{
				for (int j = 0; j < ngbrs_v.size(); ++j)
				{
					if (i!=j)
					{
						int ancestor = lca(tree, i, j);
						ancestor_pairs.insert(ancestor, depth);
					}
				}
			}

			for (auto  : ancestor_pairs)
			{
				if (search(i) && search(j))
				{
					parent_ancestor = find(tree, ancestor);
					parent_ancestor.remove(ancestor);
					final_ancestors.append(ancestor);
				}
			}

			solution_2k.remove(v);
			solution_2k.append(final_ancestors);
			return solution_2k;
		}
	}
}

void further_reduction()
{
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < g.v; ++i)						
		{
			if (g.get_degree(i)>10*k)
			{
				if(check_for_flower())
				{
					flag=true;
					k--;
					g.shift_matrix(i); //restart loop
				}
			}
		}
	}while(flag);
	

	do
	{
		flag = false;
		for (int i = 0; i < g.v; ++i)						
		{
			if (g.get_degree(i)>10*k)
			{
				if(g.double_edges(v)>2*k)
				{
					flag=true;
					k--;
					graph.shift_matrix(i); //restart loop
				}
			}
		}
	}while(flag);

	do
	{
		flag = false;
		for (int i = 0; i < g.v; ++i)						
		{
			if (g.get_degree(i)>10*k)
			{
				solution_3k = flower_lemma(g, v);

			}
		}
	}while(flag);



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