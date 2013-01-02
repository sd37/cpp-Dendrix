#include "util.h"
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define sz(a) int((a).size()) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end()) 

void lsplit(string line,list<string>& v);
void vsplit(string line,vector<string>& v);
