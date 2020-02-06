#ifndef BRANCHING_VC_H
#define BRANCHING_VC_H

tuple<int,int> find_max_degree(graph g);
bool branching(graph g, int k);
bool branching_vc(graph g, int k);
void preprocessing_rules(graph& g, int& k);
void delete_isolated_vertices(graph& g);
int delete_high_degree_vertices(graph& g, int k);
int add_ngbrs_degree_one(graph& g);
int degree_two_vertices(graph& g);

#endif 