#ifndef FUNCS_H
#define FUNCS_H

#include "array.h"
#include "llist.h"

array APPLYCIRC_ENC(array circ, array enc1, array enc2);
bigint APPLYCIRC_M(array circ, bigint m1, bigint m2);
array APPLYCIRC_ENC_MODpq(array circ, array enc1, array enc2, array pq);
array ARRMOD(array arr, bigint m);
array ARRMODARR(array arr, array marr);
array ARRSUM(array * arrs, int N);
array COMPWISEPROD(array arr1, array arr2);
int COPRIMECHECK(array arr);
bigint CRT(array rlist, array mlist);
bigint CRT(array rlist, array mlist, int check);
bigint DECRYPT(array enc, array p, bigint P);
array ENCRYPT(bigint m, array p, array q, bigint P);
array ENCRYPT(bigint m, array p, array q, bigint P, int check, int print);
int IN(array arr, bigint nw);
void KEYGEN(array &p, array &q, bigint &P);
void KEYGEN(array &p, array &q, bigint &P, int N, int cleararrs);
void KEYGEN(array &p, array &q, bigint &P, bigint &M, bigint &K, int &N, int cleararrs);
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0);
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0, int deg, bigint coeff_size);
bigint MULTICRYPT_DECRYPT(llist c, llist f, llist g, bigint z0);
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g);
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g, int deg, bigint coeff_size);
int NEWCOPRIME(array arr, bigint nw);
int NOTIN(array arr, bigint nw);
array RANDARR(int n);
array RANDARR(int n, bigint bd);
llist RAND_MVAR_POLY(int degbd, bigint coeffbd);
bigint SQRT(bigint b);
bigint STDDEVNUM(array arr);
array STDDEVNUMARR(array * arrs, int N);
bigint SUM(array arr);
//bigint XGCD(bigint a, bigint b, bigint &ainv, bigint &binv);

/// function definitions

// bigint GCD(bigint a, bigint b)
// {
//     bigint c;
//     mpz_gcd(c.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
//     return c;
// }
// 
// bigint MOD(bigint a, bigint m)
// {
//     //result is non-negative
//     bigint r;
//     mpz_mod(r.get_mpz_t(),a.get_mpz_t(),m.get_mpz_t());
//     return r;
// }
// 
// array ARRMOD(array arr, bigint m)
// {
//     int i, N=arr.get_len();
//     array ret;
//     for(i=0;i<N;i++)
//     {
//         ret.append(MOD(arr[i],m));
//     }
//     return ret;
// }
// 
// array ARRMODARR(array arr, array marr)
// {
//     int i, N=arr.get_len();
//     assert(N==marr.get_len());
//     array ret;
//     for(i=0;i<N;i++)
//     {
//         ret.append(MOD(arr[i],marr[i]));
//     }
//     return ret;
// }
// 
// array COMPWISEPROD(array arr1, array arr2)
// {
//     int i, N=arr1.get_len();
//     assert(N==arr2.get_len());
//     array ret;
//     for(i=0;i<N;i++)
//     {
//         ret.append(arr1[i]*arr2[i]);
//     }
//     return ret;
// }
// 
// bigint XGCD(bigint a, bigint b, bigint &ainv, bigint &binv)
// {
//     bigint g;
//     mpz_gcdext(g.get_mpz_t(),ainv.get_mpz_t(),binv.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
//     return g;
// }
// 
// int NEWCOPRIME(array arr, bigint nw)
// {
//     //check to see if an integer is coprime to all entries of arr
//     int i, N=arr.get_len(), ret=1;
//     for(i=0;i<N;i++)
//     {
//         if(GCD(nw,arr[i])>1)
//         {
//             ret=0;
//             break;
//         }
//     }
//     return ret;
// }
// 
// int IN(array arr, bigint nw)
// {
//     int i, N=arr.get_len(), ret=0;
//     for(i=0;i<N;i++)
//     {
//         if(nw==arr[i])
//         {
//             ret=1;
//             break;
//         }
//     }
//     return ret;
// }
// 
// int NOTIN(array arr, bigint nw)
// {
//     return !IN(arr,nw);
// }
// 
// bigint NEXTPRIME(bigint after)
// {
//     bigint r;
//     mpz_nextprime(r.get_mpz_t(),after.get_mpz_t());
//     return r;
// }
// 
// bigint POW(bigint base, bigint exp)
// {
//     // bigint ret;
//     //     bigint mod(0);
//     //     mpz_powm(ret.get_mpz_t(),base.get_mpz_t(),exp.get_mpz_t(),mod.get_mpz_t());
//     //     return ret;
//     assert(exp>=0);
//     if(exp==0)
//         return bigint(1);
//     else if(exp==1)
//         return base;
//     else
//     {
//         long xp=exp.get_si();
//         int i;
//         bigint ret(base);
//         for(i=0;i<xp-1;i++)
//         {
//             ret*=base;
//         }
//         return ret;
//     }
// }
// 
// bigint POWMOD(bigint base, bigint exp, bigint m)
// {
//     assert(exp>=0);
//     if(exp==0)
//         return MOD(1,m);
//     else if(exp==1)
//         return MOD(base,m);
//     else
//     {
//         long xp=exp.get_si();
//         int i;
//         bigint ret(base);
//         for(i=0;i<xp-1;i++)
//         {
//             ret*=base;
//             ret=MOD(ret,m);
//         }
//         return ret;
//     }
// }
// 
// bigint RAND(bigint bound, bigint lbound)
// {
//     assert(lbound<=bound);
//     bigint r1(rand());
//     bigint r2(rand());
//     bigint r3(rand());
//     while(r1*r2*r3==0)
//     {
//         r1=rand();
//         r2=rand();
//         r3=rand();
//     }
//     bigint r=r1*r2*r3;
//     return MOD(r,bound-lbound)+lbound;
// }
// bigint RAND(bigint bound)
// {
//     return RAND(bound,bigint(0));
// }
// bigint RAND()
// {
//     return RAND(bigint(10000),bigint(0));
// }
// 
// bigint RANDODD(bigint bound=bigint(10000), bigint lbound=bigint(0))
// {
//     assert(lbound<=bound);
//     bigint b2=bound/2;
//     bigint r=RAND(b2-1);
//     bigint ret=2*r+1;
//     return ret;
// }
// bigint RANDODD()
// {
//     return RANDODD(bigint(10000),bigint(0));
// }
// 
// array RANDARR(int n, bigint bd)
// {
//     array ret;
//     int i;
//     for(i=0;i<n;i++)
//     {
//         ret.append(RAND(bd));
//     }
//     return ret;
// }
// array RANDARR(int n)
// {
//     return RANDARR(n,bigint(10000));
// }
// 
// int COPRIMECHECK(array arr)
// {
//     int i, j, N=arr.get_len(), ret=1;
//     for(i=0;i<N-1;i++)
//     {
//         for(j=i+1;j<N;j++)
//         {
//             if(GCD(arr[i],arr[j])!=1)
//             {
//                 cout << "ERROR: gcd = " << GCD(arr[i],arr[j]) << "\n";
//                 ret=0;
//                 break;
//             }
//         }
//     }
//     return ret;
// }
// 
// bigint CRT(array rlist, array mlist, int check)
// {
//     int i, j, mlen=mlist.get_len(), rlen=rlist.get_len();
//     assert(mlen==rlen);
//     if(check)
//     {
//         //check that the moduli are pairwise coprime
//         assert(COPRIMECHECK(mlist));
//     }
//     bigint q(mlist[0]), r(rlist[0]), qinv, binv;
//     for(i=1;i<mlen;i++)
//     {
//         XGCD(q,mlist[i],qinv,binv);
//         r=q*(qinv*(rlist[i]-r))+r;
//         q=q*mlist[i];
//     }
//     return MOD(r,mlist.prod());
// }
// bigint CRT(array rlist, array mlist)
// {
//     return CRT(rlist,mlist,0);
// }
// 
// void KEYGEN(array &p, array &q, bigint &P, int N, int cleararrs)
// {
//     if(cleararrs)
//     {
//         p.clear();
//         q.clear();
//     }
//     //assume all inputted arrays are empty
//     int i;
//     bigint nwp, nwq;
//     for(i=0;i<N;i++)
//     {
//         nwp=NEXTPRIME(RAND(1000000,10001));
//         while(IN(p,nwp))
//             nwp=NEXTPRIME(RAND(1000000,10001));
//         p.append(nwp);
//         
//         nwq=NEXTPRIME(RAND(1000000,10001));
//         while(IN(q,nwq))
//             nwq=NEXTPRIME(RAND(1000000,10001));
//         q.append(nwq);
//     }
//     bigint prodp=p.prod();
//     P=NEXTPRIME(RAND(10000,1001));
// }
// void KEYGEN(array &p, array &q, bigint &P)
// {
//     KEYGEN(p,q,P,10,0);
// }
// 
// array ENCRYPT(bigint m, array p, array q, bigint P, int check, int print)
// {
//     if(print)
//     {
//         cout << "scheme: e(m) = [MOD(m + a[i]*p[i]+K*P , p[i]*q[i])]\n";
//         NWLN;
//     }
//     int N=p.get_len();
//     int i;
//     if(check)
//     {
//         assert(N==p.get_len());
//         assert(N==q.get_len());
//     }
//     bigint prodp=p.prod();
//     bigint k=prodp/P; // # times P goes into prodp
//     if(print)
//     {
//         printinfo(k,"prodp/P");
//         NWLN;
//     }
//     bigint K=RAND(30,10);
//     if(print)
//     {
//         printinfo(K,"K");
//         NWLN;
//     }
//     array a(RANDARR(N));
//     array ret;
//     for(i=0;i<N;i++)
//     {
//         ret.append(MOD(m+a[i]*p[i]+K*P,p[i]*q[i]));
//     }
//     return ret;
// }
// array ENCRYPT(bigint m, array p, array q, bigint P)
// {
//     //manual default params
//     return ENCRYPT(m,p,q,P,0,0);
// }
// 
// bigint DECRYPT(array enc, array p, bigint P)
// {
//     //first reduce mod p[i], then use the CRT, then reduce mod P
//     int i, N=enc.get_len();
//     array modif;
//     for(i=0;i<N;i++)
//     {
//         bigint t1(MOD(enc[i],p[i]));
//         modif.append(t1);
//     }
//     bigint r(CRT(modif,p,1));
//     bigint ret(MOD(r,P));
//     return ret;
// }
// 
// array APPLYCIRC_ENC(array circ, array enc1, array enc2)
// {
//     int N=enc2.get_len();
//     assert(circ.get_len()==2);
//     array med;
//     int i;
//     for(i=0;i<N;i++)
//         med.append(POW(enc2[i],circ[1]));
//     array ret(enc1*circ[0]+med);
//     return ret;
// }
// 
// array APPLYCIRC_ENC_MODpq(array circ, array enc1, array enc2, array pq)
// {
//     int N=enc2.get_len();
//     assert(circ.get_len()==2);
//     array med;
//     int i;
//     for(i=0;i<N;i++)
//     {
//         med.append(POWMOD(enc2[i],circ[1],pq[i]));
//     }
//     array ret(ARRMODARR(enc1*circ[0]+med,pq));
//     return ret;
// }
// 
// bigint APPLYCIRC_M(array circ, bigint m1, bigint m2)
// {
//     bigint ret;
//     ret=circ[0]*m1+POW(m2,circ[1]);
//     return ret;
// }
// 
// array ARRSUM(array * arrs, int N)
// {
//     int i, len=arrs[0].get_len();
//     array ret(len);
//     for(i=0;i<N;i++)
//     {
//         ret=ret+arrs[i];
//     }
//     return ret;
// }
// 
// bigint SUM(array arr)
// {
//     int i, len=arr.get_len();
//     bigint sum(0);
//     for(i=0;i<len;i++)
//     {
//         sum+=arr[i];
//     }
//     return sum;
// }
// 
// bigint STDDEVNUM(array arr)
// {
//     //returns num in stddev=sqrt(num/((arr.len^2*(arr.len-1)))
//     int i, len=arr.get_len();
//     bigint sum(SUM(arr));
//     bigint dev(0);
//     for(i=0;i<len;i++)
//     {
//         dev+=(arr[i]*len-sum)*(arr[i]*len-sum);
//     }
//     return dev;
// }
// 
// array STDDEVNUMARR(array * arrs, int N)
// {
//     int i, len=arrs[0].get_len();
//     array sum(ARRSUM(arrs,N));
//     array dev(len);
//     for(i=0;i<N;i++)
//     {
//         dev=dev+COMPWISEPROD((arrs[i]*N-sum),(arrs[i]*N-sum));
//     }
//     return dev;
// }

#endif