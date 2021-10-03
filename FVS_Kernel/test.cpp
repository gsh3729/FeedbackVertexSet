#include <bits/stdc++.h>
using namespace std;
void get_intersection(vector<int> big_solution, int i, vector<int> left, vector<int> right, vector<tuple<vector<int>, vector<int>>>& result)
{
	if (i==big_solution.size())
	{
		if (left.empty() || right.empty())
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

int main(int argc, char const *argv[])
{
	vector <int> big_solution;
	big_solution.push_back(1);
	big_solution.push_back(2);
	big_solution.push_back(3);
	
	std::vector<int> left,right;

	vector<tuple<vector<int>, vector<int>>> result;
	get_intersection(big_solution, 0, left, right, result);
	for (auto i : result)
	{
		tie(left, right) = i;
		for (auto j:left)
		{
			cout << j << " ";
		}
		cout << "\t" ;
		for (auto j:right)
		{
			cout << j << " ";
		}
		cout << "\n" ;
			
	}
	return 0;
}