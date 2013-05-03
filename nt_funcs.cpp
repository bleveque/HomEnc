/**
* Ben LeVeque, 2013
* nt_funcs.cpp
*
* Defines the functions declared in nt_funcs.h.
**/

#include "nt_funcs.h"

vec ARRMOD(vec arr, bigint m)
{
    /* Computes a vector modulo m. */
    int i, N=arr.get_len();
    vec ret(N);
    for(i=0;i<N;i++)
        ret.set_val(i,MOD(arr[i],m));
    return ret;
}
vec ARRMODARR(vec arr, vec marr)
{
    /* Computes the component-wise reduction of
       arr modulo marr.
     */
    int i, N=arr.get_len();
    assert(N==marr.get_len());
    vec ret(N);
    for(i=0;i<N;i++)
        ret.set_val(i,MOD(arr[i],marr[i]));
    return ret;
}
vec ARRSUM(vec * arrs, int N)
{
    /* Computes the component-wise sum of all N vectors
       in arrs.
     */
    int i, len=arrs[0].get_len();
    vec ret(len);
    for(i=0;i<N;i++)
    {
        ret=ret+arrs[i];
    }
    return ret;
}

vec CBE_APPLYCIRC_ENC(vec circ, vec enc1, vec enc2)
{
    /* Applies a simple circuit to the input encryptions
       enc1 and enc2. Namely, the component-wise power
       enc2^circp[1] is added to enc1*circ[0]. This can
       be used to give an indication of the well-definition
       of homomorphic operations in the choice-based scheme.
     */
    int N=enc2.get_len();
    assert(circ.get_len()==2);
    vec med(N);
    int i;
    for(i=0;i<N;i++)
        med.set_val(i,POW(enc2[i],circ[1]));
    vec ret(enc1*circ[0]+med);
    return ret;
}
vec CBE_APPLYCIRC_ENC_MODpq(vec circ, vec enc1, vec enc2, vec pq)
{
    /* Applies the same circuit as CBE_APPLYCIRC_ENC, though now we
       can reduce each i-th component by the corresponding number
       pq[i] (as we would in the choice-based scheme) in order to
       keep the components relatively small.
     */
    int N=enc2.get_len();
    assert(circ.get_len()==2);
    vec med(N);
    int i;
    for(i=0;i<N;i++)
        med.set_val(i,POWMOD(enc2[i],circ[1],pq[i]));
    vec ret(ARRMODARR(enc1*circ[0]+med,pq));
    return ret;
}
bigint CBE_APPLYCIRC_M(vec circ, bigint m1, bigint m2)
{
    /* Applies the same circuit as above, but the inputs now are integers
       rather than vectors. This allows us to check the well-definition of
       homomorphic operations in the choice-based scheme by comparing the
       results of applying circuits to messages (integers) and to encryptions
       (vectors).
     */
    bigint ret;
    ret=circ[0]*m1+POW(m2,circ[1]);
    return ret;
}
bigint CBE_DECRYPT(vec enc, vec p, bigint P)
{
    /* The choice-based decryption function. It first reduces each
       component modulo the corresponding p[i], and then it applies the
       Chinese Remainder Theorem and reduces the result modulo P to
       recover the message.
       Inputs:
         enc: encryption vector
         p: vector of primes p
         P: secret prime P
     */
    return MOD(CRT(ARRMODARR(enc,p),p,1),P);
}
vec CBE_ENCRYPT(bigint m, vec p, vec q, bigint P, bigint K)
{
    /* The choice-based encryption function. It encrypts the message
       m by creating a vector
          e(m) := (m + a_ip_i + kP mod p_iq_i)
       using the secret vectors of primes p and q, where each a_i is
       random (here chosen less than 1000000) and k<K.
       Inputs:
         m: integer message to be encrypted
         p: secret vector of primes
         q: secret vector of primes
         P: secret prime
         K: sectret number of ways we can mask a message with multiples of P
     */
    int N=p.get_len(), i;
    assert(N==q.get_len());
    bigint k=RAND(K);
    vec a(RANDARR(N,1000000)); // a has N entries less than 1000000
    vec ret(N);
    for(i=0;i<N;i++)
        ret.set_val(i,MOD(m+a[i]*p[i]+k*P,p[i]*q[i]));
    return ret;
}
void CBE_KEYGEN(vec &p, vec &q, bigint &P, bigint &M, bigint &K, int &N)
{
    /* The choice-based key generation function. It uses the inputs P, M,
       K, and N (unless they are passed in as <0, in which case these values
       are generated as well) to create secret vectors p and q such that
           ((K+1)P)^(M+1) < prod(p_i)
       Inputs:
         p: passed by reference, will be a vector of primes
         q: passed by reference, will be a vector of primes
         P: secret prime
         M: number of allowed operations
         K: number of ways to mask a message with multiples of P
         N: number of components in p and q
     */
    if(P<0)
        P=NEXTPRIME(RAND(10000,1000));
    if(M<0)
        M=RAND(100,1);
    if(K<0)
        K=RAND(100,10);
    if(N<0)
        N=128;
    p=vec(N);
    q=vec(N);
    
    bigint prodplb(POW((K+1)*P,M+1));
    bigint eachpi(NTHROOT_CEIL(prodplb,N));
    int i;
    bigint nwp, nwq;
    for(i=0;i<N;i++)
    {
        nwp=NEXTPRIME(RAND(2*eachpi,eachpi));
        int ctr=0;
        while(IN(p,nwp))
        {
            // if nwp is already in p, choose a new prime, extend the range for RAND just in case
            ctr++;
            nwp=NEXTPRIME(RAND(POW(2,ctr)*eachpi,eachpi));
        }
        p.set_val(i,nwp);
        
        ctr=0;
        nwq=NEXTPRIME(RAND(2*eachpi,eachpi));
        while(IN(q,nwq) || IN(p,nwq))
        {
            ctr++;
            nwq=NEXTPRIME(RAND(POW(2,ctr)*eachpi,eachpi));
        }
        q.set_val(i,nwq);
    }
}

vec COMPWISEPROD(vec arr1, vec arr2)
{
    /* Computes the component-wise product of two
       vectors. This is necessary for the application
       of circuits to encryption vectors.
     */
    int i, N=arr1.get_len();
    assert(N==arr2.get_len());
    vec ret(N);
    for(i=0;i<N;i++)
    {
        ret.set_val(i,arr1[i]*arr2[i]);
    }
    return ret;
}
int COPRIMECHECK(vec arr)
{
    /* Checks if the entries in arr are pairwise coprime */
    int i, j, N=arr.get_len(), ret=1;
    for(i=0;i<N-1;i++)
    {
        for(j=i+1;j<N;j++)
        {
            if(GCD(arr[i],arr[j])!=1)
            {
                cout << "ERROR: gcd = " << GCD(arr[i],arr[j]) << "\n";
                ret=0;
                break;
            }
        }
    }
    return ret;
}
bigint CRT(vec rlist, vec mlist, int check)
{
    /* Computes the solution mod prod(mlist) to the system
         x = rlist[i] mod mlist[i]
     */
    int i, j, mlen=mlist.get_len(), rlen=rlist.get_len();
    assert(mlen==rlen);
    if(check)
    {
        //check that the moduli are pairwise coprime
        assert(COPRIMECHECK(mlist));
    }
    bigint q(mlist[0]), r(rlist[0]), qinv, binv;
    for(i=1;i<mlen;i++)
    {
        XGCD(q,mlist[i],qinv,binv);
        r=q*(qinv*(rlist[i]-r))+r;
        q=q*mlist[i];
    }
    return MOD(r,mlist.prod());
}
bigint CRT(vec rlist, vec mlist)
{
    /* Wrapper for CRT above with no coprimality checks */
    return CRT(rlist,mlist,0);
}
int IN(vec arr, bigint nw)
{
    /* checks to see if nw is an entry in arr */
    int i, N=arr.get_len(), ret=0;
    for(i=0;i<N;i++)
    {
        if(nw==arr[i])
        {
            ret=1;
            break;
        }
    }
    return ret;
}

bigint MULTICRYPT_DECRYPT(llist c, llist f, llist g, bigint z0)
{
    /* The multivariate scheme decryption function. It first evaluates
       an encryption at z0 and then reduces the result modulo f(x,z0).
       Inputs:
         c: encryption
         f: secret polynomial
         g: secret polynomial which vanishes at z0
         z0: secret integer
      */
    llist inter(c.eval_y(z0));
    llist ret(inter.reduce_x(f.eval_y(z0)));
    assert(ret.get_xdeg()==0);
    return ret.get_lead_coeff(); //converts constant polynomial --> integer
}
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g)
{
    /* The multivariate encryption function. It adds random multiples of f and
       g (by polynomials a and b of standard degree and coefficient size) to the
       input integer message m.
       Inputs:
         m: message
         f: secret polynomial
         g: secret polynomial
     */
    llist ret, M;
    M.insert(m,0,0); //convert the message to a constant polynomial
    llist a(RAND_MVAR_POLY(MULTICRYPT_DEGREE,Z0_SIZE));
    llist b(RAND_MVAR_POLY(MULTICRYPT_DEGREE,Z0_SIZE));
    ret=M+a*f+b*g;
    return ret;
}
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g, int deg, bigint coeff_size)
{
    /* The multivariate encryption function as above, with the added inputs deg
       and coeff_size, which give the total degree and coefficient size of the
       random polynomials a and b.
     */
    llist ret, M;
    M.insert(m,0,0); //convert the message to a constant polynomial
    llist a(RAND_MVAR_POLY(deg,coeff_size));
    llist b(RAND_MVAR_POLY(deg,coeff_size));
    ret=M+a*f+b*g;
    return ret;
}
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0)
{
    /* The multivariate scheme key generation function. Generates
       a random integer z0 (of standard size determined in common.h),
       a random polynomial f, and a random polynomial g which has a
       factor (y-z0).
     */
    z0=RAND(Z0_SIZE,Z0_SIZE/2);
    f=RAND_MVAR_POLY(MULTICRYPT_DEGREE,Z0_SIZE);
    llist g1(RAND_MVAR_POLY(MULTICRYPT_DEGREE-1,Z0_SIZE));
    llist g2y;
    g2y.insert(1,0,1);
    g2y.insert(-z0,0,0);
    g=g1*g2y;
}
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0, int totaldeg, bigint coeff_size)
{
    /* The multivariate scheme key generation function. The same as
       above, except it uses input degree and coefficient sizes rather
       than constants defined in common.h
       Inputs:
         f: secret polynomial to be generated
         g: secret polynomial to be generated, which satisfies g(X,z0)=0
         z0: secret integer to be generated
         totaldeg: the total degree of f and g
         coeff_size: bound on Z0 and the size of the coefficients of f and g
     */
    z0=RAND(coeff_size,coeff_size/2);
    f=RAND_MVAR_POLY(totaldeg,coeff_size);
    llist g1(RAND_MVAR_POLY(totaldeg-1,coeff_size));
    llist g2y; // will be (y-z0)
    g2y.insert(1,0,1); // term: y
    g2y.insert(-z0,0,0); // term: -z0
    g=g1*g2y;
}

int NEWCOPRIME(vec arr, bigint nw)
{
    /* Checks to see if nw is coprime to all entries of arr. */
    int i, N=arr.get_len(), ret=1;
    for(i=0;i<N;i++)
    {
        if(GCD(nw,arr[i])>1)
        {
            ret=0;
            break;
        }
    }
    return ret;
}
int NOTIN(vec arr, bigint nw)
{
    /* Wrapper for !IN(...) */
    return !IN(arr,nw);
}
vec RANDARR(int n, bigint bd)
{
    /* Generates an n-vector with random entries less than bd */
    vec ret(n);
    int i;
    for(i=0;i<n;i++)
    {
        ret.set_val(i,RAND(bd));
    }
    return ret;
}
vec RANDARR(int n)
{
    /* Calls RANDARR above with bd=1000000 */
    return RANDARR(n,bigint(1000000));
}
llist RAND_MVAR_POLY(int totdeg, bigint coeffbd)
{
    /* Generates a random polynomial of total degree
       totdeg and with coefficients < coeffbd. Polynomials
       are represented used linked lists.
       We loop through the x- and y-degrees and for each,
       we either make the coefficient zero (about half the
       time to avoid very dense polynomials, which are expensive
       to store and manipulate) or a random value between 1 and
       coeffbd. The exceptions are the highest total degree term,
       which has nonzero coefficient to ensure that the polynomial
       has total degree totdeg as desired, and the constant term,
       which is nonzero to help mask messages (which are integers).
     */
    int i, j, xdeg;
    llist ret;
    if(totdeg>1)
        xdeg=rand()%(totdeg-1)+1;
    else
        xdeg=(rand()%2)?1:0;
    int ydeg=totdeg-xdeg;
    for(i=0;i<=xdeg;i++)
    {
        for(j=0;j<=ydeg;j++)
        {
            bigint coeff;
            int test=rand()%10;
            if(test<5 && (!(i==xdeg && j==ydeg)) && (!(i==0 && j==0)))
                coeff=bigint(0);
            else
                coeff=(coeffbd==1)?1:RAND(coeffbd,bigint(1));
            ret.insert(coeff,i,j);
        }
    }
    return ret;
}
bigint STDDEVNUM(vec arr)
{
    /* Returns the numerator squared of the standard deviation.
       The standard deviation can then be computed as
           stddev=sqrt(numerator/((arr.len^2*(arr.len-1)))
     */
    int i, len=arr.get_len();
    bigint sum(SUM(arr));
    bigint dev(0);
    for(i=0;i<len;i++)
    {
        dev+=(arr[i]*len-sum)*(arr[i]*len-sum);
    }
    return dev;
}
vec STDDEVNUMARR(vec * arrs, int N)
{
    /* Applies the standard deviation circuit to an array of vectors */
    int i, len=arrs[0].get_len();
    vec sum(ARRSUM(arrs,N));
    vec dev(len);
    for(i=0;i<N;i++)
    {
        dev=dev+COMPWISEPROD((arrs[i]*N-sum),(arrs[i]*N-sum));
    }
    return dev;
}
bigint SUM(vec arr)
{
    /* Computes the sum of the entries in arr. */
    int i, len=arr.get_len();
    bigint sum(0);
    for(i=0;i<len;i++)
    {
        sum+=arr[i];
    }
    return sum;
}