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
