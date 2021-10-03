#ifndef FVS_H
#define FVS_H

void delete_isolated_vertices(graph& g);
void delete_degree_one_vertices(graph& g);
int delete_loops(graph& g);
void preprocessing_rules(graph& g, int& k);								// check whether all rules are applied exhaustively
void get_intersection(vector<int> big_solution, int i, vector<int> left, vector<int> right, vector<tuple<vector<int>, vector<int>>>& result);
void get_subgraph(graph& g, vector<int> subgraph_vertices);
int find_leaf(graph g, vector<int> x_forest, vector<int> y_forest);
bool branching_fvs_ic(graph g, int k, vector<int>& solution, vector<int> x_forest, vector<int> y_forest);
vector<int> reduction(graph g, vector<int>big_intersect_small, vector<int>& x_forest, vector<int>& y_forest, int k);
vector<int> compression(graph g, int k, vector<int> big_solution, vector<int> subgraph_vertices);
bool fvs_ic(graph g, int k);				
vector<vector<int>> find_cycles(graph g);

#endif