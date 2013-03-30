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


bigint GCD(bigint a, bigint b)
{
    bigint c;
    mpz_gcd(c.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
    return c;
}
bigint MOD(bigint a, bigint m)
{
    //result is non-negative
    bigint r;
    mpz_mod(r.get_mpz_t(),a.get_mpz_t(),m.get_mpz_t());
    return r;
}
bigint NEXTPRIME(bigint after)
{
    bigint r;
    mpz_nextprime(r.get_mpz_t(),after.get_mpz_t());
    return r;
}
bigint POW(bigint base, bigint exp)
{
    // bigint ret;
    //     bigint mod(0);
    //     mpz_powm(ret.get_mpz_t(),base.get_mpz_t(),exp.get_mpz_t(),mod.get_mpz_t());
    //     return ret;
    assert(exp>=0);
    if(exp==0)
        return bigint(1);
    else if(exp==1)
        return base;
    else
    {
        long xp=exp.get_si();
        int i;
        bigint ret(base);
        for(i=0;i<xp-1;i++)
        {
            ret*=base;
        }
        return ret;
    }
}

bigint POWMOD(bigint base, bigint exp, bigint m)
{
    assert(exp>=0);
    if(exp==0)
        return MOD(1,m);
    else if(exp==1)
        return MOD(base,m);
    else
    {
        long xp=exp.get_si();
        int i;
        bigint ret(base);
        for(i=0;i<xp-1;i++)
        {
            ret*=base;
            ret=MOD(ret,m);
        }
        return ret;
    }
}

bigint RAND(bigint bound, bigint lbound)
{
    assert(lbound<=bound);
    bigint r1(rand());
    bigint r2(rand());
    bigint r3(rand());
    while(r1*r2*r3==0)
    {
        r1=rand();
        r2=rand();
        r3=rand();
    }
    bigint r=r1*r2*r3;
    return MOD(r,bound-lbound)+lbound;
}
bigint RAND(bigint bound)
{
    return RAND(bound,bigint(0));
}
bigint RAND()
{
    return RAND(bigint(10000),bigint(0));
}

bigint RANDODD(bigint bound=bigint(10000), bigint lbound=bigint(0))
{
    assert(lbound<=bound);
    bigint b2=bound/2;
    bigint r=RAND(b2-1);
    bigint ret=2*r+1;
    return ret;
}
bigint RANDODD()
{
    return RANDODD(bigint(10000),bigint(0));
}
bigint XGCD(bigint a, bigint b, bigint &ainv, bigint &binv)
{
    bigint g;
    mpz_gcdext(g.get_mpz_t(),ainv.get_mpz_t(),binv.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
    return g;
}