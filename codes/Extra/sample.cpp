#include <bits/stdc++.h>
using namespace std;
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

	for (int i = 0; i <= end ; i++)  
    {  
        data[index] = v[i];  
        combs_repeat(v, data, end, index+1, n, result);  
    }
}

vector<vector<int>> get_combs_repeat(int n, int m)
{
	vector<int> v;
	for (int i = 1; i < pow(2, n); ++i)
	{
		v.push_back(i);
	}

	int data[n];
	vector<vector<int>> result;
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

    cout << "Powerset" << power_set.size() << endl;
    for(auto i: power_set)
    {
    	for(auto j:i)
    	{
    		cout<<j<<" ";
    	}
    	cout << endl;
    }
    cout << "Powerset done" << endl;

	vector<vector<int>> result = get_combs_repeat(n, m);

	for(auto i: result)
	{
		for(auto j: i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	cout << "result done" << endl;

	vector<vector<vector<int>>> bag_combs;
	for (auto i : result)
	{
		// bool flag = true;
		vector<vector<int>> temp;
		for (auto j : i)
		{
			// if (j==pow(2,n))
			// {
			// 	flag = false;
			// 	continue;
			// }
			temp.push_back(power_set[j-1]);
		}
		// if (flag)
		// {
			bag_combs.push_back(temp);			
		// }
	}

	return bag_combs;
}

int main(int argc, char const *argv[])
{
	vector<vector<int>> tree_edges = get_combinations(5);
	cout << "Combinations" << endl;
	for(auto i: tree_edges)
	{
		for(auto j: i)
		{
			cout << j << " ";
		}
		cout << endl;
	}

	cout << endl;

		
	// vector<vector<vector<int>>>  t = generate_bags(5, 2); // 3 vertices on graph , 2 bag
	// for(auto i: t)              	//all combs
	// {
	// 	for(auto j: i)				//bag
	// 	{
	// 		for(auto k:j)           //powerset bag
	// 		{
	// 			cout << k << " ";
	// 		}
	// 		cout << "\t" ;
	// 	}
	// 	cout << endl;
	// }
	return 0;
}