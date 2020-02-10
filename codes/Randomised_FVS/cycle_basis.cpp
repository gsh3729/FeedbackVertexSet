#include <bits/stdc++.h>

int main(int argc, char const *argv[])
{
	vector<vector <int>> cycles;
	vector<int> cycle; 
	stack <int> included_in_tree_not_explored;
	included_in_tree.push(0);
	map<int, int> parent;
	map<int, set<int>> included_in_tree;

	while (included_in_tree_not_explored.empty())
	{
		z = included_in_tree_not_explored.pop();
		for (int i = 0; i < g.v; ++i)
		{
			if (g.matrix[i][z]==1)
			{
				if (i==z)
				{
					cycle.push_back(z);
					cycles.push_back(cycle);
					cycle.clear();
				}
				else if (included_in_tree.find(i)==included_in_tree.end())   //new node //avoids parent(already in tree)
				{
					set <int> temp;
					temp.insert(z);
					included_in_tree.insert(pair<int, set<int>>(i,temp));
					included_in_tree_not_explored.push(i);
					parent.insert(pair<int, int>(i,z));
				}
				else if (included_in_tree[z].find(i)==included_in_tree[z].end()) // found a cycle //only parent and virtual parent 
				{
					cycle.push_back(i);
					cycle.push_back(z);
					int p = parent[z];
					while (included_in_tree[i].find(p)==included_in_tree.end()) // till parent of i is reached
					{
						cycle.push_back(p);
						p = parent[p];
					}
					cycles.push_back(cycle);
					included_in_tree[i].insert(z);
				}
			}
		}
	}
	return 0;
}