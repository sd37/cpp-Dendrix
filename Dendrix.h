#include "util.h"

void lsplit(string line,list<string>& v);
void vsplit(string line,vector<string>& v);
void random_samples(list<string> g,int K,list<string>& sol);
string random_sample_sel(const set<string> &g);
void cNumVisits(DictSetInt &num_visits,set<string> &frozen_tmp,const set<string> &solution_Set);


vector<string> convertListToVector(const list<string> &l);
set<string> convertVectortoSet(const vector<string> &v);
set<string> convertListToSet(const list<string> &l);

double measure(set<string>& genes_collection1,set<string>& genes_collection2,DictStringSet& sample_mutatedGenes);
