// #include <graph_input.h>
#include <bits/stdc++.h>
using namespace std;

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
	void clear_matrix()
	{
		for (int i = 0; i < v; ++i)
		{
			for (int j = 0; j < v; ++j)
			{
				matrix[i][j]=0;
			}
		}
	}
};



class bags
{
public:
	bags(int a)
	{
		width = a;
	}
	int width;
	vector< vector<int> > bag_list;

	void add_bag(vector<int>& line)
	{
		bag_list.push_back(line);
	}
	void print_baglist()
	{
		cout << "###########Bags##########" << endl;
		for (int i = 0; i < bag_list.size(); i++)
		{
		    for (int j = 0; j < bag_list[i].size(); j++)
		    {
		        cout << bag_list[i][j] << " ";
		    }
		    cout << endl;
		}
	}
};

void print_vector(vector<int>& x);
bool check_std(graph g, graph t, bags b);



void combination(vector<int> v, int data[], int start, int end, int index, int n, vector< vector <int>> &result)
{
	if (index == n)  
    {  
    	vector<int> row;
        for (int j = 0; j < n; j++)
        {
            row.push_back(data[j]);          	
        }  
        result.push_back(row);
        return;  
    }

	for (int i = start; i <= end && end - i + 1 >= n - index; i++)  
    {  
        data[index] = v[i];  
        combination(v, data, i+1, end, index+1, n, result);  
    }
}

vector<vector<int>> get_combinations(int n)
{
	vector<int> v;
	for (int i = 1; i <= (n*(n-1))/2; ++i)
	{
		v.push_back(i);
	}

	int data[n];
	vector< vector <int>> result;
	combination(v, data, 0, v.size()-1, 0, n-1, result);

	return result;
}

void combs_repeat(vector<int> v, int data[], int end, int index, int n, vector< vector <int>> &result)
{
	if (index == n)  
    {  
    	vector<int> row;
        for (int j = 0; j < n; j++)
        {
            row.push_back(data[j]);          	
        }  
        result.push_back(row);
        return;  
    }

	for (int i = 0; i <= end; i++)  
    {  
        data[index] = v[i];  
        combs_repeat(v, data, end, index+1, n, result);  
    }
}

vector<vector<int>> get_combs_repeat(int n, int m)
{
	vector<int> v;
	for (int i = 1; i < pow(2,n); ++i)
	{
		v.push_back(i);
	}

	int data[n];
	vector< vector <int>> result;
	combs_repeat(v, data, v.size()-1, 0, m, result);

	return result;
}



vector<vector<vector<int>>> generate_bags(int n, int m)
{
	int pow_set_size = pow(2, n);

	vector<vector <int>> power_set;
	for(int counter = 1; counter < pow_set_size; counter++) 
    { 
    	vector<int> v;
	    for(int j = 0; j < n; j++) 
	    { 
	        if(counter & (1 << j)) 
	        {
	        	v.push_back(j);
	        }
	    }
	    power_set.push_back(v); 
    }

	vector<vector<int>> result = get_combs_repeat(n,m);

	vector<vector<vector<int>>> bag_combs;
	for (auto i : result)
	{
		vector<vector<int>> temp;
		for (auto j : i)
		{
			temp.push_back(power_set[j-1]);
		}
		bag_combs.push_back(temp);			
	}

	return bag_combs;
}

int compute_width(vector<vector<int>> v)
{
	int result=0;
	for (auto i: v)
	{
		int temp = i.size();
		result = max(result, temp);
	}	
	return result-1;
}

bool is_cycle(graph t, int v, bool visited[], int parent)
{
	visited[v] = true;

	for (int i = 0; i < t.v; ++i)
	{
		if (t.matrix[v][i]==1)
		{
			if (!visited[i])
			{
				if (is_cycle(t,i,visited,v))
				{
					return true;
				}
			}
			else if (i != parent)
			{
				return true;
			}
		}
	}

	return false;
}

bool check_tree(graph t)
{
	bool *visited = new bool[t.v];
	for (int i = 0; i < t.v; ++i)
	{
		visited[i] = false;
	}

	if (is_cycle(t, 0, visited, -1))
	{
		return false;
	}

	for (int i = 0; i < t.v; ++i)
	{
		if (!visited[i])
		{
			return false;
		}
	}

	return true;
}

int opt_tree_decomposition(graph g)
{
	cout << "Enumeration starts" << endl << endl;
	tuple<int, int> e;
	int no_of_edges=0;

	graph t(0,0);
	bags b(0);

	int tree_width=10000;

	int x,y;

	map<int, tuple <int, int>> edge_map;
	for (int i = 0; i < g.v; ++i)					// i is the tree size for graph g
	{
		if (i==0)
		{
			t.v = 1;
			vector<vector<int>> temp;
			vector<int> a;
			for (int j = 0; j < g.v; ++j)
			{
				a.push_back(j);
			}
			temp.push_back(a);
			b.bag_list = temp;
			int r = compute_width(b.bag_list);
			tree_width = min(tree_width, r);
			cout << "Tree 0 width :" << tree_width << endl; 
			continue;
		}
		t.v = i+1;

		cout << "Adding new edges " << i << " th vertex" << endl;
		for (int j = 0; j < i; ++j)
		{
			e = make_tuple(j, i);
			no_of_edges++;
			edge_map.insert(pair<int, tuple <int, int>>(no_of_edges, e)); 
		}

		vector<vector<int>>  tree_edges = get_combinations(t.v);   // sending no of vertex //require edges 123 124 125 126

		for (auto j :tree_edges)
		{
			for (auto k : j)    
			{
				tie(x, y) = edge_map[k];							
				t.add_edge(x, y);
			}					// a tree is formed

			if (check_tree(t))
			{
				t.clear_matrix();
				continue;
			}

			cout << "A tree is formed from selecting the edges" << endl;

			vector<vector<vector<int>>> bag_combs = generate_bags(g.v, t.v);   
			cout << "Bags are generated for a particular tree" << endl;

			for (auto k : bag_combs)  //all possible bags of a tree
			{
				b.bag_list = k;
				if(check_std(g,t,b))
				{
					int temp = compute_width(b.bag_list);
					if (temp < tree_width)
					{
						cout << "width " << temp << endl; 
						b.print_baglist();
						t.print_matrix();
					}
					tree_width = min(tree_width, temp);
				}
			}

			cout << "Evaluation of all bags is done" << endl << endl;
			t.clear_matrix();
		}
		cout << "now size gonna increase" << endl << endl;
	}

	return tree_width;
}




int main(int argc, char const *argv[])
{
	fstream file;
	string line, word;

	graph g(0, 0);
	graph t(0, 0);
	bags b(0);

	file.open("g3.txt", ios::in);
	cout << "###########Graph##########" << endl;

	if (file.is_open())
	{
		getline(file, line);
		file >> word;

		file >> word;
		int v = stoi(word);
		file >> word;
		int no_of_edges = stoi(word);

		cout << "v : \t\t" << v << endl;
		cout << "no of edges : \t" << no_of_edges << endl << endl;

		g.v = v;
		g.no_of_edges = no_of_edges;

		getline(file, line); // to finish prev line 
		while(getline(file, line))
		{
			string a, b;
			istringstream parse(line);
			parse >> a;
			parse >> b;
			g.add_edge(stoi(a), stoi(b));
		}
	}

	g.print_matrix();
	cout << endl;
	file.close();

	int result = opt_tree_decomposition(g);
	
	cout << "Tree width :" << result << endl;

	return 0;
}


void print_vector(vector<int>& x)
{
	for (int i = 0; i < x.size(); ++i)
	{
		cout << x[i] << " ";
	}
	cout << endl;
}


bool check_std(graph g, graph t, bags b)
{
	bool flag, flag1, flag2;
	for (int i = 0; i < g.v; ++i)                    // For each vertex i
	{
		flag = false;
		for (int j = 0; j < t.v; ++j)                // Searching for a bag containing i
		{
			for (auto k : b.bag_list[j])
			{
				if (i == k)
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				break;
			}
		}
		if (!flag)                                   // If i is not found in any bag then return false
		{
			return false;
		}
	}

	for (int i = 0; i < g.v; ++i)
	{
		for (int j = 0; j < g.v; ++j)
		{
			if (g.matrix[i][j] == 1)             	// For each edge i,j
			{
				flag = false;
				for (int k = 0; k < t.v; ++k)       // Searching for a bag containing both i,j
				{
					flag1 = false;
					flag2 = false;
					for (auto l : b.bag_list[k])
					{
						if (i == l)
						{
							flag1 = true;
						}
						if (j == l)
						{
							flag2 = true;
						}
					}
					if (flag1 && flag2)
					{
						flag = true;
					}
				}
				if (!flag)							// If i is not found in any bag then return false
				{
					return false;
				}
			}
		}
	}

	for (int i = 0; i < g.v; ++i)                 	//For each vertex i
	{
		bool mark[t.v];
		for (int j = 0; j < t.v; ++j)
		{
			mark[j] = false;
		}
		for (int j = 0; j < t.v; ++j)			  	//Marking all the bags containing i 
		{
			for (auto k : b.bag_list[j])
			{
				if (k==i)
				{
					mark[j] = true;
					break;
				}
			}
		}

		for (int j = 0; j < t.v; ++j)			 	// Starting bfs with bag j containing i 
		{
			for (auto k : b.bag_list[j])
			{
				if (i == k)
				{
					bool visited[t.v];
					for (int l = 0; l < t.v; ++l)
					{
						visited[l] = false;
					}
					list<int> queue;

					visited[j] = true;				// bag j is visited
					queue.push_back(j);

					while(!queue.empty())
					{
						int s = queue.front();
						queue.pop_front();
						for (int m = 0; m < t.v; ++m)  // Exploring the child m
						{
							if (t.matrix[s][m] == 1 && !visited[m])
							{
								for (auto n : b.bag_list[m])
								{
									if (n == i)      // If child m contains i then push it to queue
									{
										visited[m] = true;
										queue.push_back(m);
										break;
									}
								}
							}
						}
					}

					for (int l = 0; l < t.v; ++l)
					{
						if (mark[l] != visited[l])
						{
							return false;
						}
					}
					break;
				}
			}
		}
	}


	for (int i = 0; i < t.v; ++i)     			// For each bag 
	{
		for (int j = 0; j < t.v; ++j)
		{
			if (i != j)
			{
				flag = false;
				map <int,int> m;
			    for(auto k : b.bag_list[j])
			    {
			        m[k]++;
			    }
			    for(auto k : b.bag_list[i])
			    {
			        if(m.find(k)==m.end()) 
			        {
			        	flag = true;
			        	break;
			        }
			    }
			    if (!flag)
			    {
			    	return false;
			    }
			}
		}
	}

	return true;
}