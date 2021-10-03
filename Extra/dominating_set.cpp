#include <bits/stdc++.h>
using namespace std;

class node
{
	public:
	int data;
	vector<node *> child;
	int a;
	int b;
	int c;
};

node *newNode(int key) 
{ 
   node *temp = new node; 
   temp->data = key; 
   temp->a = 0;
   temp->b = 0;
   temp->c = 0;
   return temp; 
}


// function to calculate minimum dominating set 
int min_dominating_set(node* root)
{
	if (root->child.empty())
	{
		root-> a = root->data;
		return root->a;
	}

	int a=0,b=0,c=0;
	

	for (auto i : root->child)
	{
		int temp = min_dominating_set(i);

		c = c + i->c;
		b = b + i->b;
		a = a + i->a;
	}

	root->c = 1+b;
	root->b = min(a, 1+b);

	for (auto i : root->child)
	{
		c = min(c, i->c + a - i->a);
	}

	root->a = min(1+b, root->data + b) ;

	return root->a;
}

int main(int argc, char const *argv[])
{
	
	node *root = newNode(4);
	(root->child).push_back(newNode(1)); 
   	(root->child).push_back(newNode(1)); 
   	// (root->child).push_back(newNode(1));
   	(root->child[0]->child).push_back(newNode(1)); 
   	(root->child[0]->child).push_back(newNode(1));
 //   	(root->child[2]->child).push_back(newNode(32)); 
	// (root->child[2]->child).push_back(newNode(18)); 
 //   	(root->child[2]->child).push_back(newNode(12));

   	int result = min_dominating_set(root);

   	cout << "Minimum dominating set size : " << result << endl;
	return 0;
}