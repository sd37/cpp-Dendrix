#include "util.h"

void lsplit(string line,list<string>&v)
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

