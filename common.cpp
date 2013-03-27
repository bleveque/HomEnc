#include "common.h"

void printinfo(bigint b, string s)
{
    cout << s << " = " << b << "\n";
}

void split(string s, char c, string * ret)
{
    //assume that ret has not been allocated
    int i=0, num_match=0;
    while(s[i]!=0)
    {
        if((s[i]==c) && (i!=0) && (s[i+1]!=0))
        {
            num_match++;
        }
        i++;
    }
    ret=new string[num_match+1];
    i=0;
}