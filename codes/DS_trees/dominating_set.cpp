#include <bits/stdc++.h>
using namespace std;

class node
{
	public:
	int data;
	vector<node *> child;
	int gamma;
	int lambda;
	int delta;
};

node *newNode(int key) 
{ 
   node *temp = new node; 
   temp->data = key; 
   temp->gamma = 0;
   temp->lambda = 0;
   temp->delta = 0;
   return temp; 
}


// function to calculate minimum dominating set 
int min_dominating_set(node* root)
{
	if (root->child.empty())
	{
		root->gamma = 1;
		root->lambda = 0;
		root->delta = 1;

		return root->gamma;
	}

	int gamma_sum=0,lambda_sum=0,delta_sum=0;

	for (auto i : root->child)
	{
		min_dominating_set(i);

		delta_sum = delta_sum + i->delta;
		lambda_sum = lambda_sum + i->lambda;
		gamma_sum = gamma_sum + i->gamma;
	}

	root->delta = 1+lambda_sum;                    
	root->lambda = min(gamma_sum, 1+lambda_sum);    

	int temp=100000;
	for (auto i : root->child)
	{
		temp = min(temp, i->delta + gamma_sum - i->gamma);
	}

	root->gamma = min(1+lambda_sum, temp) ;

	return root->gamma;
}

int main(int argc, char const *argv[])
{
	
	node *root = newNode(4);
	(root->child).push_back(newNode(1)); 
   	(root->child).push_back(newNode(1)); 
   	(root->child).push_back(newNode(1));
   	// (root->child[0]->child).push_back(newNode(1)); 
   	// (root->child[0]->child).push_back(newNode(1));
 //   	(root->child[2]->child).push_back(newNode(32)); 
	// (root->child[2]->child).push_back(newNode(18)); 
 //   	(root->child[2]->child).push_back(newNode(12));

   	int result = min_dominating_set(root);

   	cout << "Minimum dominating set size : " << result << endl;
	return 0;
}