#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <utility>
#include <ext/algorithm>

using namespace std;

#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define sz(a) int((a).size()) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end()) 

typedef map<string,set<string> > DictStringSet;
typedef map<string,double> DictStringDouble;
typedef map<const set<string>,int> DictSetInt;
double random01();
string  integerToString(int x);
