#include "array.h"
#include "funcs.h"

using namespace std;

void testinfo(string s)
{
    cout << "\n=== " << s << " ===\n";
}

void functest(void)
{
    array a, b, c, d, e, B, C, K, J, S;
    testinfo("arrays");
    a.append(3);
    a.append(33);
    a.printinfo("a = (3,33)");
    C=a*3;
    C.printinfo("3a");
    b.append(432);
    b.append(4323);
    b.printinfo("b = (432,4323)");
    c=a+b;
    c.printinfo("c = a+b");
    a=b-c;
    a.printinfo("a = b-c");
    printinfo(a[0],"a[0]");
    
    testinfo("SUM");
    bigint sum(SUM(a));
    a.printinfo("a");
    printinfo(sum,"SUM(a)");
    
    testinfo("ARRSUM");
    a.printinfo("a");
    c.printinfo("c");
    S.append(4);
    S.append(7);
    S.printinfo("S");
    array * ac=new array[3];
    ac[0]=a;
    ac[1]=c;
    ac[2]=S;
    b=ARRSUM(ac,3);
    b.printinfo("b=a+c+S");
    delete[] ac;
    
    testinfo("STDDEVNUM");
    a.printinfo("a");
    bigint dev(STDDEVNUM(a));
    cout << "stddev(a) = sqrt(" << dev << "," << (a.get_len()*a.get_len()*(a.get_len()-1)) << ")\n";
    
    testinfo("COMPWISEPROD");
    a.printinfo("a");
    c.printinfo("c");
    b=COMPWISEPROD(a,c);
    b.printinfo("b = a*c");
    
    testinfo("appendv");
    bigint A[10]={3,4,5,6,7,8,9,10,1,2};
    d.appendv(A,10);
    d.printinfo("d = (3,4,5,6,7,8,9,10,1,2)");
    
    testinfo("prod");
    B.append(2);
    B.append(4);
    printinfo(B.prod(),"B.prod() = 8");
    
    testinfo("ARRMOD");
    array dmod(ARRMOD(d,2));
    dmod.printinfo("dmod = (1,0,1,0,1,0,1,0,1,0)");
    
    testinfo("ARRMODARR");
    J.append(5);
    J.append(6);
    K.append(2);
    K.append(3);
    array JmodK(ARRMODARR(J,K));
    JmodK.printinfo("(5,6) mod (2,3) = (1,0)");
    
    testinfo("APPLYCIRC_ENC");
    a.printinfo("a");
    b.printinfo("b");
    array circ;
    circ.append(3);
    circ.append(4);
    array res(APPLYCIRC_ENC(circ,a,b));
    res.printinfo("res = 3a+b^4");
    
    testinfo("GCD");
    printinfo(GCD(2064846799,10011991),"GCD(2064846799,10011991) = 43");
    
    testinfo("XGCD");
    bigint s,t,g(2064846799),h(10011991);
    printinfo(XGCD(g,h,s,t),"XGCD(2064846799,10011991)");
    bigint l(g*s+h*t);
    cout << "inverses: "<< g << "*(" << s << ") + " << h << "*(" << t << ") = " << l << "\n";
    
    testinfo("MOD");
    bigint modtest=MOD(101,82);
    printinfo(modtest,"MOD(101,82) = 19");
    
    testinfo("POW");
    bigint BI(POW(39,19));
    printinfo(BI,"39^19");
    
    testinfo("CRT");
    array Plist;
    Plist.append(3);
    Plist.append(5);
    array vallist;
    vallist.append(2);
    vallist.append(3);
    a=Plist;
    bigint crt=CRT(vallist,a,1);
    printinfo(crt,"CRT([2,3],[3,5]) = 8");
    
    testinfo("RAND");
    printinfo(RAND(50),"RAND(50)");
    printinfo(RAND(20000),"RAND(20000)");
    
    testinfo("bigint via string");
    bigint bi("1023023002332");
    printinfo(bi,"1023023002332");
    

    testinfo("RANDARR");
    a=RANDARR(10);
    a.printinfo("RANDARR()");
    
    testinfo("NEXTPRIME");
    printinfo(NEXTPRIME(100),"nextprime(100) = 101");
    
    cout << "\n";
}


int ENCRYPTtest(void)
{
    cout << "\n\nENCRYPTtest" << "\n==========================================\n";
    array p,q,pq;
    bigint P;
    int N=60;
    KEYGEN(p,q,P,N,0);
    pq=COMPWISEPROD(p,q);
    printinfo(N,"N");
    NWLN;
    p.printinfo("p");
    NWLN;
    q.printinfo("q");
    NWLN;
    pq.printinfo("pq");
    NWLN;
    cout << "P = " << P << "\n";
    NWLN;
    assert(P<p.prod());
    
    bigint bound("100000");
    bigint m(RAND(1000));
    array enc(ENCRYPT(m,p,q,P,1,0));
    cout << "enc = ";
    enc.printr();
    NWLN;
    bigint dec(DECRYPT(enc,p,P));
    cout << "dec = " << dec << "\n";
    cout << "m = " << m << "\n";
    cout << "dec = m?  ";
    if(dec==m)
        cout << "yes\n\n\n";
    else
        cout << "no\n\n\n";
        
    cout << "CIRCUIT TEST\n===============================\n";
    bigint m2(RAND(1000));
    array enc2(ENCRYPT(m2,p,q,P,1,0));
    int i=1, well_def=1;
    while(well_def)
    {
        array circ;
        circ.append(RAND(100000,1000));
        circ.append(i);
        array applied_enc(APPLYCIRC_ENC_MODpq(circ,enc,enc2,pq));
        bigint decapplied(DECRYPT(applied_enc,p,P));
        bigint applied_m=MOD(APPLYCIRC_M(circ,m,m2),P);
        if(decapplied==applied_m)
        {
            //cout << "Applying circuit is well-defined with " << i << " multiplications\n";
            i++;
        }
        else
        {
            well_def=0;
            cout << "well-defined up to " << i-1 << " multiplications\n\n\n";
        }
    }
}

void user_encryption_test(void)
{
    string input;
    array p,q,pq;
    bigint P;
    int N;
    cout << "Enter N: ";
    getline(cin,input);
    stringstream(input) >> N;
    KEYGEN(p,q,P,N,0);
    pq=COMPWISEPROD(p,q);
    array messages;
    array * encs=new array[N];
    int i;
    for(i=0;i<N;i++)
    {
        cout << "Enter message < " << P << ":  ";
        getline(cin,input);
        if(input.length()==0)
        {
            bigint m(RAND(P));
            messages.append(m);
            encs[i]=ENCRYPT(m,p,q,P,1,0);
        }
        else
        {
            bigint m(input);
            messages.append(m);
            encs[i]=ENCRYPT(m,p,q,P,1,0);
        }
    }
    messages.printinfo("messages");
    clock_t t=clock();
    testinfo("MEAN");
    array sum(ARRSUM(encs,N));
    sum.printinfo("sum of encryptions");
    bigint dec(DECRYPT(sum,p,P));
    printinfo(dec,"decrypted sum of encrypted messages");
    printinfo(MOD(SUM(messages),P),"sum of messages modulo P");
    cout << "the mean is returned as a pair (" << dec << "," << N << ")\n";
    
    testinfo("STANDARD DEVIATION");
    array nsumarr(STDDEVNUMARR(encs,N));
    bigint ndec(DECRYPT(nsumarr,p,P));
    printinfo(ndec,"decrypted numerator of std dev of encryptions");
    printinfo(N*N*(N-1),"decrypted denominator of std dev of encryptions");
    bigint messdevnum(STDDEVNUM(messages));
    int denom=N*N*(N-1);
    printinfo(MOD(messdevnum,P),"numerator of std dev of messages (modulo P)");
    printinfo(MOD(denom,P),"denominator of std dev of messages (modulo P)");
    cout << "the std dev is returned as a pair (" << ndec << "," << denom << ")\n";
    cout << "need to take the square root of " << ndec << "/" << denom << "\n";
    NWLN;
    cout << "note that reducing mod P does not give the true standard deviation;\n";
    cout << "the real standard deviation is: sqrt(" << messdevnum << "/" << denom << ")\n";
    
    delete[] encs;
    cout << "\n";
    cout << "this whole process took " << t << " clock ticks, or " << ((float)t)/CLOCKS_PER_SEC << " seconds" << "\n";
	
}

int main(void)
{
    srand(time(NULL));
    //functest();
    //ENCRYPTtest();
    user_encryption_test();
	return 0;
}