/**
* Ben LeVeque, 2013
* vec.cpp
*
* Function definitions for the the vector class.
**/

#include "vec.h"

/* Constructors and destructor */

vec::vec(const vec& arr)
{
    /* copy constructor */
    len=arr.len;
    vals=new bigint[arr.len];
    int i;
    for(i=0;i<len;i++)
    {
        vals[i]=arr.vals[i];
    }
}
vec::vec(int size)
{
    /* constructs a size-length vector
       with entries initialized to 0
     */
    len=size;
    vals=new bigint[size];
    // int i;
    //     for(i=0;i<len;i++)
    //     {
    //         vals[i]=bigint(0);
    //     }
}
vec::vec(int size, bigint initval)
{
    /* constructs a size-length vector
       with entries equal to initval
     */
    len=size;
    vals=new bigint[size];
    int i;
    for(i=0;i<len;i++)
    {
        vals[i]=initval;
    }
}
vec::~vec()
{
    /* destructor */
    delete[] vals;
}

/* Operator overloads */

vec& vec::operator=(vec arr)
{
    /* assignment operator overload using std::swap */
    vec temp(arr);
    std::swap(len,temp.len);
    std::swap(vals,temp.vals);
}
vec vec::operator+(const vec& arr1)
{
    /* component-wise vector addition */
    int maxlen=max(len,arr1.len);
    vec ret(maxlen);
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
vec vec::operator-(const vec& arr1)
{
    /* component-wise vector subtraction */
    vec temp(arr1);
    int i;
    for(i=0;i<temp.len;i++)
        temp.vals[i]=temp.vals[i]*(-1);
    return operator+(temp);
}
vec vec::operator*(bigint b)
{
    /* multiplies the vector by the scalar b */
    vec ret(len);
    int i;
    for(i=0;i<len;i++)
    {
        ret.vals[i]=vals[i]*b;
    }
    return ret;
}
bigint vec::operator[](int i)
{
    /* access i-th vector entry */
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

/* Miscellaneous class methods */

void vec::clear(void)
{
    /* deletes underlying array and sets it to null */
    delete[] vals;
    vals=NULL;
    len=0;
}
int vec::get_len(void)
{
    /* returns length */
    return len;
}
void vec::printr(void)
{
    /* prints the vector in a user-friendly way */
    int i;
    std::cout << "[";
    for(i=0;i<len;i++)
    {
        std::cout << vals[i].get_mpz_t() << ",";
    }
    std::cout << "]\n";
}
void vec::printinfo(string name)
{
    /* prints the vector, using the input name */
    cout << name << " = ";
    printr();
}
bigint vec::prod(void)
{
    /* returns the product of all vector entries */
    bigint r(1);
    int i;
    for(i=0;i<len;i++)
        r=r*vals[i];
    return r;
}
void vec::set_val(int index, bigint v)
{
    /* set the i-th entry to v */
    if(len<=index)
        assert(0 && "index out of bounds, not setting value");
    else
        vals[index]=v;
}