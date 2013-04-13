#include "array.h"

using namespace std;

//printinfo here?

array::array(const array& arr)
{
    len=arr.len;
    vals=new bigint[arr.len];
    int i;
    for(i=0;i<len;i++)
    {
        vals[i]=arr.vals[i];
    }
}

array::array(int size)
{
    len=size;
    vals=new bigint[size];
    int i;
    for(i=0;i<len;i++)
    {
        vals[i]=bigint(0);
    }
}

array::array(int size, bigint initval)
{
    len=size;
    vals=new bigint[size];
    int i;
    for(i=0;i<len;i++)
    {
        vals[i]=initval;
    }
}

array::~array()
{
    delete[] vals;
}

array& array::operator=(array arr)
{
    array temp(arr);
    std::swap(len,temp.len);
    std::swap(vals,temp.vals); //right??
}

array array::operator+(const array& arr1)
{
    int maxlen=max(len,arr1.len);
    array ret(maxlen);
    int i;
    for(i=0;i<maxlen;i++)
    {
        if(i<len)
            ret.vals[i]=ret.vals[i]+vals[i];
        if(i<arr1.len)
            ret.vals[i]=ret.vals[i]+arr1.vals[i];
    }
    return ret;
}

array array::operator-(const array& arr1)
{
    array temp(arr1);
    int i;
    for(i=0;i<temp.len;i++)
        temp.vals[i]=temp.vals[i]*(-1);
    return operator+(temp);
}

array array::operator*(bigint b)
{
    array ret(len);
    int i;
    for(i=0;i<len;i++)
    {
        ret.vals[i]=vals[i]*b;
    }
    return ret;
}

// array array::operator*(const array& arr) //ambiguous overloading
// {
//     assert(len==arr.len);
//     int i;
//     array ret;
//     for(i=0;i<len;i++)
//     {
//         ret.append(vals[i]*arr.vals[i]);
//     }
//     return ret;
// }

bigint array::operator[](int i)
{
    bigint ret(0);
    if(i>=len)
    {
        cout << "i = " << i << ", len = " << len << "\n";
        assert(0 && "out of bounds error");
    }
    else
    {
        ret=vals[i];
    }
    return ret;
}

void array::append(bigint val)
{
    if(len==0)
    {
        vals=new bigint[1];
        vals[0]=val;
        len=1;
    }
    else
    {
        bigint * temp=new bigint[len];
        int i;
        for(i=0;i<len;i++)
        {
            temp[i]=vals[i];
        }
        delete[] vals;
        vals=new bigint[len+1];
        for(i=0;i<len;i++)
            vals[i]=temp[i];
        delete[] temp;
        vals[len]=val;
        len++;
    }
}

void array::appendv(bigint vec[], int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        append(vec[i]);
    }
}

void array::clear(void)
{
    //clears an array
    delete[] vals;
    vals=NULL;
    len=0;
}

int array::get_len(void)
{
    return len;
}

void array::printr(void)
{
    int i;
    std::cout << "[";
    for(i=0;i<len;i++)
    {
        std::cout << vals[i].get_mpz_t() << ",";
    }
    std::cout << "]\n";
}

void array::printinfo(string name)
{
    cout << name << " = ";
    printr();
}

bigint array::prod(void)
{
    bigint r(1);
    int i;
    for(i=0;i<len;i++)
        r=r*vals[i];
    return r;
}
