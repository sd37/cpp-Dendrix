#include "util.h"

void lsplit(string line,list<string>& v)
{
    string buf;
    stringstream ss(line);
    
    while(ss >> buf)
	v.push_back(buf);

}

void vsplit(string line,vector<string>&v)
{
    string buf;
    stringstream ss(line);
    
    while(ss >> buf)
	v.push_back(buf);

}

void random_samples(list<string> g,int K, list<string> &sol)
{
    vector<string> gg(all(g));

    srand((unsigned)time(0));
    random_shuffle(all(gg));

    int count = 0;
    tr(gg,it)
	{
	    if(count == K)
		break;
	    if(!cpresent(sol,*it))
		{
		    sol.push_back(*it);
		    count++;
      		} 
	}
}

string random_sample_sel(const set<string> &g)
{
    vector<string> gg(all(g));
    
    srand((unsigned)time(0));
    random_shuffle(all(gg));
    
    return gg[0];
}

vector<string> convertListToVector(const list<string> &l)
{
    vector<string> v(all(l));
    return v;
}

set<string> convertVectortoSet(const vector<string> &v)
{
    set<string> s(all(v));
    return s;
}

set<string> convertListToSet(const list<string> &l)
{
    vector<string> v;
    v = convertListToVector(l);
    return convertVectortoSet(v);
}

double measure(set<string>& genes_collection1,set<string>& genes_collection2,DictStringSet& sample_mutatedGenes)
{
    int out1;
    int inside1;
    int out2;
    int inside2;
    set<string> genes_in_sample;
    set<string> inside_genes1;
    set<string> inside_genes2;
    int num_ig1;
    int num_ig2;

    //coverage of genes in genes_collection1
    out1 = 0;
    //total number of mutations in genes_collection1
    inside1 = 0;
    //coverage of genes_collection2
    out2 = 0;
    //total number of mutations in genes_collection2
    inside2 = 0;
    
    tr(sample_mutatedGenes,it)
	{
	    //it->first is the sampleID
	    genes_in_sample = sample_mutatedGenes[it->first];

	    set_intersection(all(genes_collection1),all(genes_in_sample),inserter(inside_genes1,inside_genes1.end()));
	    
	    if(inside_genes1.size() > 0)
		out1 += 1;

	    num_ig1 = (int)inside_genes1.size();
	    inside1 += num_ig1;

	    set_intersection(all(genes_collection2),all(genes_in_sample),inserter(inside_genes2,inside_genes2.end()));
	    
	    if(inside_genes2.size() > 0)
		out2 += 1;
	    
	    num_ig2 = inside_genes2.size();
	    inside2 += num_ig2;
	    
	}
    
    double c = 0.5;
    return c * double(2*out1 - inside1 - (2*out2 - inside2));
}


double random01()
{
    srand((unsigned)time(0));
    return (double)rand() / (double)(RAND_MAX - 1) ;
}

void cNumVisits(DictSetInt &num_visits,set<string> &frozen_tmp,const set<string> &solution_Set)
{   
    
    if(!present(num_visits,solution_Set))
      {
	  num_visits.insert(pair<set<string>,int>(solution_Set,0));   			   
      }
    num_visits[solution_Set]++;   
}

string integerToString(int x)
{
    string result;   
    ostringstream convert;
    convert << x;    
    return  convert.str();

}

int rev_access0(list<pair<int,set<string> > > &l, int n)
{
    list<pair<int,set<string> > >::reverse_iterator rit;
    int i = 1;
    
    
	
    for (rit = l.rbegin(); rit != l.rend(); ++rit,++i)
	{
	    if(i == n)
		return (*rit).first;
	    i++;
	}
    return -1;

}

set<string> rev_access1(list<pair<int,set<string> > > &l, int n)
{
    list<pair<int,set<string> > >::reverse_iterator rit;
    int i = 1;
    
    
	
    for (rit = l.rbegin(); rit != l.rend(); ++rit,++i)
	{
	    if(i == n)
		return (*rit).second;
	    i++;
	}
    return set<string>();

}
