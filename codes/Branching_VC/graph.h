#ifndef GRAPH_H 
#define GRAPH_H 

#include <bits/stdc++.h>
using namespace std;

class graph 													// shift matrix t.v is there check once
{
  public:
	graph(int a, int b);
	graph(const graph &g1);
	int v;
	int no_of_edges;
	int matrix[100][100];
	void add_edge(int a, int b);
	void print_matrix();
	void shift_matrix(int x);
};


#endif
