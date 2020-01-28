// #include <graph_input.h>
#include <bits/stdc++.h>
using namespace std;
void print_vector(vector<int>& x);



// class to maintain graph structure
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
};




// class to maintain bags 
class bags
{
public:
	bags(int b)
	{
		width = b;
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



// function to check if (T,B) is a tree decompositon
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

	for (int i = 0; i < g.v; ++i)                 		//For each vertex i
	{
		bool mark[t.v];
		for (int j = 0; j < t.v; ++j)					//Marking all the bags containing i 
		{
			mark[j] = false;
		}
		for (int j = 0; j < t.v; ++j)			  	
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


		for (int j = 0; j < t.v; ++j)			 		// Searching for a bag containing i
		{
			for (auto k : b.bag_list[j])
			{
				if (i == k)								// Starting bfs with bag j containing i 
				{
					bool visited[t.v];
					for (int l = 0; l < t.v; ++l)
					{
						visited[l] = false;
					}
					list<int> queue;

					visited[j] = true;					// bag j is visited
					queue.push_back(j);

					while(!queue.empty())
					{
						int s = queue.front();
						queue.pop_front();
						for (int m = 0; m < t.v; ++m)  	// Exploring the child m
						{
							if (t.matrix[s][m] == 1 && !visited[m])
							{
								for (auto n : b.bag_list[m])
								{
									if (n == i)      	// If child m contains i then push it to queue
									{
										visited[m] = true;
										queue.push_back(m);
										break;
									}
								}
							}
						}
					}

					for (int l = 0; l < t.v; ++l)		// If all marked vertex are not visited then return false
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

	
	for (int i = 0; i < t.v; ++i)     			
	{
		for (int j = 0; j < t.v; ++j)			// every bag combination
		{
			if (i != j)
			{
				flag = false;
				map <int,int> m;
			    for(auto k : b.bag_list[j])		// noting the second bag elements
			    {
			        m[k]++;
			    }
			    for(auto k : b.bag_list[i])		// checking if first bag is subset of second bag
			    {
			        if(m.find(k)==m.end()) 		// if a element is not found in second bag then not a suvhset
			        {
			        	flag = true;
			        	break;
			        }
			    }
			    if (!flag)						// if every element of first set is found in second then it is subset
			    {
			    	return false;
			    }
			}
		}
	}

	return true;
}


int main(int argc, char const *argv[])
{
	fstream file;
	string line, word;

	graph g(0, 0);
	graph t(0, 0);
	bags b(0);

	file.open("g1.txt", ios::in);
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
		cout << "no of bags : \t" << no_of_edges << endl << endl;

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

	file.open("decomposition.txt", ios::in);
	cout << "###########Tree##########" << endl;

	if (file.is_open())
	{
		getline(file, line); //First line is comment line
		file >> word;   //Reads character "s"

		file >> word;
		int no_of_bags = stoi(word);
		file >> word;
		int width = stoi(word);
		file >> word;
		cout << "v : \t\t" << no_of_bags << endl;
		cout << "width : \t" << width << endl;

		t.v = no_of_bags;
		b.width = width;

		getline(file, line); // to finish prev line 
		for (int i = 0; i < no_of_bags; ++i)
		{
			getline(file, line);
			istringstream parse(line);
			vector<int> x;
			parse >> word;
			parse >> word;
			while(parse >> word)
			{
				x.push_back(stoi(word));	
			}
			b.add_bag(x);
			// break;
		}

		while(getline(file, line))
		{
			string a, b;
			istringstream parse(line);
			parse >> a;
			parse >> b;
			t.add_edge(stoi(a), stoi(b));
		}

	}
	
	file.close();

	t.print_matrix();
	b.print_baglist();
	cout<<endl;

	if (check_std(g, t, b))
	{
		cout<< "(T,B) is a simple tree decomposition of G" << endl;
	}
	else
	{
		cout<< "(T,B) is not a simple tree decomposition of G" << endl;
	}
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