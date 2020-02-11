#ifndef RANDOMISED_FVS_H
#define RANDOMISED_FVS_H

void delete_isolated_vertices(graph& g);
void delete_degree_one_vertices(graph& g);
int delete_loops(graph& g);
void short_circuit_degree_two_vertices(graph& g);
void preprocessing_rules(graph& g, int& k);
vector<vector<int>> find_cycles(graph g);
void printing_cycles(graph g);
bool check_fvs(graph g, vector<int> fvs);
void test_fvs(graph g);
tuple<int,int> pick_edge(graph g);
int pick_vertex(int u, int v);
void randomised_fvs(graph g, int k);

#endif