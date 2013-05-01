#include "funcs.h"

///////// NON-MEMBER FUNCTIONS /////////

array ARRMOD(array arr, bigint m)
{
    int i, N=arr.get_len();
    array ret(N);
    for(i=0;i<N;i++)
    {
        ret.set_val(i,MOD(arr[i],m));//append(MOD(arr[i],m));
    }
    return ret;
}

array ARRMODARR(array arr, array marr)
{
    int i, N=arr.get_len();
    assert(N==marr.get_len());
    array ret(N);
    for(i=0;i<N;i++)
    {
        ret.set_val(i,MOD(arr[i],marr[i]));//.append(MOD(arr[i],marr[i]));
    }
    return ret;
}

array COMPWISEPROD(array arr1, array arr2)
{
    int i, N=arr1.get_len();
    assert(N==arr2.get_len());
    array ret(N);
    for(i=0;i<N;i++)
    {
        ret.set_val(i,arr1[i]*arr2[i]);//append(arr1[i]*arr2[i]);
    }
    return ret;
}

int NEWCOPRIME(array arr, bigint nw)
{
    //check to see if an integer is coprime to all entries of arr
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

int IN(array arr, bigint nw)
{
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

int NOTIN(array arr, bigint nw)
{
    return !IN(arr,nw);
}

array RANDARR(int n, bigint bd)
{
    array ret(n);
    int i;
    for(i=0;i<n;i++)
    {
        ret.set_val(i,RAND(bd));//append(RAND(bd));
    }
    return ret;
}
array RANDARR(int n)
{
    return RANDARR(n,bigint(10000));
}

int COPRIMECHECK(array arr)
{
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

bigint CRT(array rlist, array mlist, int check)
{
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
bigint CRT(array rlist, array mlist)
{
    return CRT(rlist,mlist,0);
}
void KEYGEN(array &p, array &q, bigint &P, bigint &M, bigint &K, int &N, int cleararrs)
{
    //generates the lists {p_i} and {q_i}
    //if you want to also generate P, M, K, or N, send them in as 0
    if(cleararrs)
    {
        p.clear();
        q.clear();
    }
    if(P==0)
        P=NEXTPRIME(RAND(10000,1000));
    if(M==0)
        M=RAND(100,1);
    if(K==0)
        K=RAND(30,10);
    if(N==0)
        N=128;
    p=array(N);
    q=array(N);
    bigint prodplb(POW((K+1)*P,M+1));
    //cout << "prod(p_i) lower bound = " << prodplb << "\n";
    bigint eachpi(NTHROOT_CEIL(prodplb,N));
        
    //assume input arrays are empty
    int i;
    bigint nwp, nwq;
    for(i=0;i<N;i++)
    {
        nwp=NEXTPRIME(RAND(2*eachpi,eachpi));
        int ctr=2;
        while(IN(p,nwp))
        {
            ctr++;
            nwp=NEXTPRIME(RAND(ctr*eachpi,eachpi));
        }
        p.set_val(i,nwp);//append(nwp);
        
        ctr=2;
        nwq=NEXTPRIME(RAND(2*eachpi,eachpi));
        while(IN(q,nwq))
        {
            ctr++;
            nwq=NEXTPRIME(RAND(ctr*eachpi,eachpi));
        }
        q.set_val(i,nwq);//append(nwq);
    }
    bigint prodp=p.prod();
    //cout << "prod(p_i) =             " << prodp << "\n";
    //P=NEXTPRIME(RAND(10000,1001));
}
void KEYGEN(array &p, array &q, bigint &P, int N, int cleararrs)
{
    if(cleararrs)
    {
        p.clear();
        q.clear();
    }
    p=array(N);
    q=array(N);
    //assume all inputted arrays are empty
    int i;
    bigint nwp, nwq;
    for(i=0;i<N;i++)
    {
        nwp=NEXTPRIME(RAND(1000000,10001));
        while(IN(p,nwp))
            nwp=NEXTPRIME(RAND(1000000,10001));
        p.set_val(i,nwp);//append(nwp);
        
        nwq=NEXTPRIME(RAND(1000000,10001));
        while(IN(q,nwq))
            nwq=NEXTPRIME(RAND(1000000,10001));
        q.set_val(i,nwq);//append(nwq);
    }
    bigint prodp=p.prod();
    P=NEXTPRIME(RAND(10000,1001));
}
void KEYGEN(array &p, array &q, bigint &P)
{
    KEYGEN(p,q,P,10,0);
}
array ENCRYPT(bigint m, array p, array q, bigint P, bigint K, int check, int print)
{
    if(print)
    {
        cout << "scheme: e(m) = [MOD(m + a[i]*p[i]+K*P , p[i]*q[i])]\n";
        NWLN;
    }
    int N=p.get_len();
    
    int i;
    if(check)
    {
        assert(N==p.get_len());
        assert(N==q.get_len());
    }
    bigint prodp=p.prod();
    bigint k=prodp/P; // # times P goes into prodp
    if(print)
    {
        printinfo(k,"prodp/P");
        NWLN;
    }
    if(print)
    {
        printinfo(K,"K");
        NWLN;
    }
    array a(RANDARR(N));
    array ret(N); //zero array
    for(i=0;i<N;i++)
    {
        ret.set_val(i,MOD(m+a[i]*p[i]+K*P,p[i]*q[i]));
    }
    return ret;
}
array ENCRYPT(bigint m, array p, array q, bigint P, int check, int print)
{
    if(print)
    {
        cout << "scheme: e(m) = [MOD(m + a[i]*p[i]+K*P , p[i]*q[i])]\n";
        NWLN;
    }
    int N=p.get_len();
    int i;
    if(check)
    {
        assert(N==p.get_len());
        assert(N==q.get_len());
    }
    bigint prodp=p.prod();
    bigint k=prodp/P; // # times P goes into prodp
    if(print)
    {
        printinfo(k,"prodp/P");
        NWLN;
    }
    bigint K=RAND(30,10);
    if(print)
    {
        printinfo(K,"K");
        NWLN;
    }
    array a(RANDARR(N));
    array ret(N);
    for(i=0;i<N;i++)
    {
        ret.set_val(i,MOD(m+a[i]*p[i]+K*P,p[i]*q[i]));
    }
    return ret;
}
array ENCRYPT(bigint m, array p, array q, bigint P)
{
    //manual default params
    return ENCRYPT(m,p,q,P,0,0);
}

bigint DECRYPT(array enc, array p, bigint P)
{
    //first reduce mod p[i], then use the CRT, then reduce mod P
    int i, N=enc.get_len();
    array modif(N);
    for(i=0;i<N;i++)
    {
        bigint t1(MOD(enc[i],p[i]));
        modif.set_val(i,t1);//append(t1);
    }
    bigint r(CRT(modif,p,1));
    bigint ret(MOD(r,P));
    return ret;
}

array APPLYCIRC_ENC(array circ, array enc1, array enc2)
{
    int N=enc2.get_len();
    assert(circ.get_len()==2);
    array med(N);
    int i;
    for(i=0;i<N;i++)
        med.set_val(i,POW(enc2[i],circ[1]));//append(POW(enc2[i],circ[1]));
    array ret(enc1*circ[0]+med);
    return ret;
}

array APPLYCIRC_ENC_MODpq(array circ, array enc1, array enc2, array pq)
{
    int N=enc2.get_len();
    assert(circ.get_len()==2);
    array med(N);
    int i;
    for(i=0;i<N;i++)
    {
        med.set_val(i,POWMOD(enc2[i],circ[1],pq[i]));//append(POWMOD(enc2[i],circ[1],pq[i]));
    }
    array ret(ARRMODARR(enc1*circ[0]+med,pq));
    return ret;
}

bigint APPLYCIRC_M(array circ, bigint m1, bigint m2)
{
    bigint ret;
    ret=circ[0]*m1+POW(m2,circ[1]);
    return ret;
}

array ARRSUM(array * arrs, int N)
{
    int i, len=arrs[0].get_len();
    array ret(len);
    for(i=0;i<N;i++)
    {
        ret=ret+arrs[i];
    }
    return ret;
}

llist RAND_MVAR_POLY(int totdeg, bigint coeffbd)
{
    int i,j;
    llist ret;
    int xdeg;
    if(totdeg>1)
        xdeg=rand()%(totdeg-1)+1;
    else
    {
        int tst=rand()%2;
        if(tst)
            xdeg=1;
        else
            xdeg=0;
    }
    int ydeg=totdeg-xdeg;
    for(i=0;i<=xdeg;i++)
    {
        for(j=0;j<=ydeg;j++)
        {
            bigint coeff;
            int test=rand()%10;
            if(test<5 && (!(i==xdeg && j==ydeg)) && (!(i==0 && j==0))) // made constant coefficients non-zero
                coeff=bigint(0);
            else
                coeff=RAND(coeffbd,bigint(1));//coeffbd/bigint(2)); //used to be between bd and bd/2
            ret.insert(coeff,i,j);
        }
    }
    return ret;
}

void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0)
{
    //generate random polynomials f, g1, set g=g1*(y-z0)
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
    //generate random polynomials f, g1, set g=g1*(y-z0)
    z0=RAND(coeff_size,coeff_size/2);
    f=RAND_MVAR_POLY(totaldeg,coeff_size);
    llist g1(RAND_MVAR_POLY(totaldeg-1,coeff_size));
    llist g2y; // will be (y-z0)
    g2y.insert(1,0,1); // term: y
    g2y.insert(-z0,0,0); // term: -z0
    g=g1*g2y;
}

bigint MULTICRYPT_DECRYPT(llist c, llist f, llist g, bigint z0)
{
    llist inter(c.eval_y(z0));
    llist ret(inter.reduce_x(f.eval_y(z0)));
    assert(ret.get_xdeg()==0);
    return ret.get_lead_coeff();
}

llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g)
{
    llist ret;
    llist M;
    M.insert(m,0,0);
    llist a(RAND_MVAR_POLY(MULTICRYPT_DEGREE,Z0_SIZE));
    llist b(RAND_MVAR_POLY(MULTICRYPT_DEGREE,Z0_SIZE));
    ret=M+a*f+b*g;
    return ret;
}

llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g, int deg, bigint coeff_size)
{
    llist ret;
    llist M;
    M.insert(m,0,0);
    llist a(RAND_MVAR_POLY(deg,coeff_size));
    llist b(RAND_MVAR_POLY(deg,coeff_size));
    ret=M+a*f+b*g;
    return ret;
}

bigint NTHROOT_CEIL(bigint b, int n)
{
    //returns ceiling of the nth root of b
    bigint r;
    int t;
    t=mpz_root(r.get_mpz_t(),b.get_mpz_t(),n);
    if(t)
        return r;
    else
        return r+1;
}

bigint SQRT(bigint b)
{
    bigint r;
    mpz_sqrt(r.get_mpz_t(),b.get_mpz_t());
    return r;
}



bigint STDDEVNUM(array arr)
{
    //returns num in stddev=sqrt(num/((arr.len^2*(arr.len-1)))
    int i, len=arr.get_len();
    bigint sum(SUM(arr));
    bigint dev(0);
    for(i=0;i<len;i++)
    {
        dev+=(arr[i]*len-sum)*(arr[i]*len-sum);
    }
    return dev;
}

array STDDEVNUMARR(array * arrs, int N)
{
    int i, len=arrs[0].get_len();
    array sum(ARRSUM(arrs,N));
    array dev(len);
    for(i=0;i<N;i++)
    {
        dev=dev+COMPWISEPROD((arrs[i]*N-sum),(arrs[i]*N-sum));
    }
    return dev;
}

bigint SUM(array arr)
{
    int i, len=arr.get_len();
    bigint sum(0);
    for(i=0;i<len;i++)
    {
        sum+=arr[i];
    }
    return sum;
}