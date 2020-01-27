#include <bits/stdc++.h>
using namespace std;

class node
{
	public:
	int data;
	vector<node *> child;
	int a;
	int b;
};

node *newNode(int key) 
{ 
   node *temp = new node; 
   temp->key = key; 
   temp->a = 0;
   temp->b = 0;
   return temp; 
}



int max_weight(node* root)
{

	if (root->child == )
	{
		root-> a = root->temp;
		return root->a;
	}

	int a=0,b=0;
	
	for (auto i = root->child.begin(); i != root->child.end() ; ++i)
	{
		b = b + i->b;
		a = a + i->a;
	}
	root->b = a;
	root->a = max(root->b, root->key + b) ;

	return root->a;
}

int main(int argc, char const *argv[])
{
	
	node *root = newNode(4);
	(root->child).push_back(newNode(3)); 
   	(root->child).push_back(newNode(6)); 
   	(root->child).push_back(newNode(1));
   	(root->child[0]->child).push_back(newNode(13)); 
   	(root->child[0]->child).push_back(newNode(23));
   	(root->child[2]->child).push_back(newNode(32)); 
	(root->child[2]->child).push_back(newNode(18)); 
   	(root->child[2]->child).push_back(newNode(12));

   	int result = max_weight(root);
	return 0;
}