/**
* Ben LeVeque, 2013
* common.cpp
*
* Includes definitions of common functions used throughout the project
**/

#include "common.h"

void printinfo(bigint b, string s) 
{
    /* makes it easy to print bigints */
    cout << s << " = " << b << "\n";
}
bigint GCD(bigint a, bigint b)
{
    /* computes the greatest common divisor of a and b using mpz_gcd */
    bigint c;
    mpz_gcd(c.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
    return c;
}
bigint MOD(bigint a, bigint m)
{
    /* computes a mod b using mpz_mod, giving a non-negative result */
    bigint r;
    mpz_mod(r.get_mpz_t(),a.get_mpz_t(),m.get_mpz_t());
    return r;
}
bigint NEXTPRIME(bigint after)
{
    /* uses mpz_nextprime to find the next prime number after the input */
    bigint r;
    mpz_nextprime(r.get_mpz_t(),after.get_mpz_t());
    return r;
}
bigint NTHROOT_CEIL(bigint b, int n)
{
    /* Returns the ceiling of the nth root of b */
    bigint r;
    int t;
    t=mpz_root(r.get_mpz_t(),b.get_mpz_t(),n);
    if(t)
        return r;
    else
        return r+1;
}
bigint POW(bigint base, bigint exp)
{
    /* computes base^exp using mpz_pow_ui */
    bigint r;
    mpz_pow_ui(r.get_mpz_t(),base.get_mpz_t(),mpz_get_ui(exp.get_mpz_t()));
    return r;
}
bigint POWMOD(bigint base, bigint exp, bigint m)
{
    /* computes base^exp mod m using mpz_powm */
    bigint r;
    mpz_powm(r.get_mpz_t(),base.get_mpz_t(),exp.get_mpz_t(),m.get_mpz_t());
    return r;
}
bigint RAND(bigint bound, bigint lbound)
{
    /* computes a random integer in [lbound,bound) */
    assert(lbound<=bound);
    bigint r(rand());
    while(r<bound)
        r=r*rand()+rand(); //want to avoid things like rand being a multiple of 5, so r will always be a multiple of 5 thereafter
    return MOD(r,bound-lbound)+lbound;
}
bigint RAND(bigint bound)
{
    /* calls RAND with lbound=0 */
    return RAND(bound,bigint(0));
}
bigint RAND()
{
    /* calls RAND with bound=10000 and lbound=0 */
    return RAND(bigint(10000),bigint(0));
}
bigint SQRT(bigint b)
{
    bigint r;
    mpz_sqrt(r.get_mpz_t(),b.get_mpz_t());
    return r;
}
bigint XGCD(bigint a, bigint b, bigint &ainv, bigint &binv)
{
    /* computes the extended gcd of a and b using mpz_gcdext
       the output g and variables ainv and binv satisfy
          g = a*ainv + b*binv
       The variables ainv and binv are so called for the
       specific case when g=1.
     */
    bigint g;
    mpz_gcdext(g.get_mpz_t(),ainv.get_mpz_t(),binv.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
    return g;
}