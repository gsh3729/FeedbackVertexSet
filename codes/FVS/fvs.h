#ifndef FVS_H
#define FVS_H

void delete_isolated_vertices(graph& g);
void delete_degree_one_vertices(graph& g);
int delete_loops(graph& g);
void short_circuit_degree_two_vertices(graph& g);
void preprocessing_rules(graph& g, int& k);								// check whether all rules are applied exhaustively
bool sortinrev(const pair<int,int> &a, const pair<int,int> &b);
vector<int> find_vertex_order(graph g, int k);
bool fvs(graph g, int k);				// should we branch at every step

#endif