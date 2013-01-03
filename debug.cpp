#include "util.h"

void printSet(const set<string> &s)
{
    int i =0;
    tr(s,it)
	{
	    
	    cout <<"e[" << i <<  "]"<< ":" << "\"" << *it << "\"" << "\n";
	    i++;
	}

}

void printDict(const DictSetInt &d)
{
    tr(d,it)
	{
	    printf("{\nKey:\n");
	    printSet(it->first);
	    printf("Value:\n");
	    printf("%d\n}\n",it->second) ;
	}
}
