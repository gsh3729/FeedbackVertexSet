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


vector<node*> connectedComponents(graph g) 
{ 
    bool *visited = new bool[g.v]; 
    for(int i = 0; i < g.v; i++)
    {
        visited[i] = false; 
    }
  
  	vector<node*> components;
    for (int i=0; i<g.v; i++) 
    { 
        if (visited[i] == false) 
        { 
            node* root = new node();
            root->data = i;
            DFSUtil(g, root, i, visited);  // root is already pointer is it req to send &root?? 
  			components.push(root);
        } 
    }

    return components; 
} 
  
void DFSUtil(graph g, node root, int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 

    for (int i = 0; i < g.v; ++i)
    {
    	if (g.matrix[v][i]>=1)
    	{
    		if(!visited[*i]) 
	        {
	        	node* child = new node();
	        	child->data = i;
	        	root->child.push_back(child);
	            DFSUtil(g, child, *i, visited); 
	        }
    	}
    }
    return;
}

vector<int> two_approximation_fvs(graph g, int k)
{
	return vector<int> ();
}

int lca(node* root, int i, int j)
{


	return 0;
}


tuple<vector<int>, vector<node>> flower_lemma_return_fvs3k(graph g, int v, int k)
{
	vector<int> solution_2k;
	solution_2k = two_approximation_fvs(g,k);
	graph g1 = g;
	forest = g1.delete_vertices(solution_2k);

	if (solution_2k.size()> 2*k)
	{
		return make_tuple(vector<int>(), vector<node>());
	}
	else if (find(solution_2k.begin(), solution_2k.end(), v) == solution_2k.end())
	{
		return solution_2k;
	}
	else
	{
		vector<node*> trees = connected_components(g1);
		for(auto tree : trees)
		{
			tuple<int, int, pair<int,int>> ancestor_pairs;
			vector<int> ngbrs_v = g1.neighbours(v);
			for (int i = 0; i < ngbrs_v.size(); ++i)
			{
				for (int j = 0; j < ngbrs_v.size(); ++j)
				{
					if (i!=j)
					{
						int ancestor = lca(tree, i, j);
						ancestor_pairs.insert(ancestor, depth, make_pair(i,j));
					}
				}
			}

			for (auto temp : ancestor_pairs)
			{
				tie(ancestor,depth,pair) = temp;
				if (search_node(tree, pair.first) && search_node(tree, pair.second))
				{
					parent_ancestor = find_parent_node(tree, ancestor);
					ancestor_node = find_node(tree, ancestor);
					parent_ancestor.child.erase(remove(parent_ancestor.child.begin(), parent_ancestor.child.end(), ancestor_node), parent_ancestor.child.end());
					final_ancestors.append(ancestor);
				}
			}

			solution_2k.erase(remove(solution_2k.begin(), solution_2k.end(), v), solution_2k.end());
			solution_2k.insert(solution_2k.end(), final_ancestors.begin(), final_ancestors.end());
			return make_tuple(solution_2k,trees); // returning here is not crct check once with loop
		}
	}
}

tuple<vector<int>, vector<int>> expansion_lemma(graph g, vector<int> solution_3k)
{
	bool flag = true;
	for (auto i : solution_3k)
	{
		if (g.degree(i)<2)
		{
			flag = false;
		}
	}


	if (flag)
	{
		vector<int> ngbrs;
		for (auto i : solution_3k)
		{
			ngbrs.push_back(g.ngbrs(i));
		}
		return make_tuple(solution_3k,ngbrs) ;
	}
	else
	{
		int pow_set_size = pow(2, solution_3k.size());

		vector<vector <int>> power_set;
		for(int counter = 1; counter < pow_set_size; counter++) 
	    { 
	    	vector<int> v;
		    for(int j = 0; j < solution_3k.size(); j++) 
		    { 
		        if(counter & (1 << j)) 
		        {
		        	v.push_back(solution_3k[j]);
		        }
		    }
		    power_set.push_back(v); 
	    }

	    for (auto i: power_set)
	    {
	    	vector<int> ngbrs;
	    	for (auto j : i)
	    	{
	    		ngbrs.push_back(g.ngbrs(j));
	    	}
	    	if (ngbrs.size()<2*i.size())
	    	{
	    		graph g1 = g;
	    		g.delete_vertices(i); // i may have neibhbours in i 
	    		g.delete_vertices(ngbrs);
	    		solution_3k.delete(i);
	    		return expansion_lemma(g, solution_3k);
	    	}
	    }

	}
}

bool check_for_flower(graph g, int v)
{
	int petals = 0;
	vector<vector<int>> cycles = find_cycles(g);
	for(auto cycle : cycles)
	{
		if (find(cycle.begin(), cycle.end(), v) != cycle.end())
		{
			petals++;
		}
	}
	if (petals >= k+1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}


void further_reduction(graph g, int k)
{
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < g.v; ++i)						
		{
			if (g.get_degree(i)>10*k)
			{
				if(check_for_flower(g,i))
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
				if(g.double_edges(i)>2*k)
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
				solution_3k = flower_lemma_return_fvs3k(g, v);
				tie(solution_3k_expansion, ngbrs_3k_expansion) = expansion_lemma(g, solution_3k);

				for (auto j : solution_3k_expansion)
				{
					g.matrix[j][v] = 2;
					g.matrix[v][j] = 2;					
				}

				for (int j = 0; j < g.v; ++j)
				{
					if (g.matrix[j][v] >= 1)
					{
						for (auto : )
						{

						}
					}
				}
			}
		}
	}while(flag);



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