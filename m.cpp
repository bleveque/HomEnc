#include "array.h"
#include "llist.h"
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
    
    // testinfo("a*c");
    // a.printinfo("a");
    // b.printinfo("b");    
    // b=a*c;
    // b.printinfo("b = a*c");
    
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

int newENCRYPTtest(void)
{
    cout << "\n\nnewENCRYPTtest" << "\n==========================================\n";
    array p,q,pq;
    bigint P(0);
    bigint M(20);
    bigint K(0);
    int N=60;
    int cleararrs=0;
    KEYGEN(p,q,P,M,K,N,cleararrs);
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
    
    bigint m(RAND(P));
    array enc(ENCRYPT(m,p,q,P,K,1,0));
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
    array enc2(ENCRYPT(m2,p,q,P,K,1,0));
    int i=1, well_def=1;
    while(well_def)
    {
        array circ;
        circ.append(RAND(100000,1000));
        circ.append(i);
        array applied_enc(APPLYCIRC_ENC_MODpq(circ,enc,enc2,pq));
        bigint decapplied(DECRYPT(applied_enc,p,P));
        bigint applied_m=MOD(APPLYCIRC_M(circ,m,m2),P);
        cout << "test " << i << ": " << decapplied << " ?= " << applied_m;
        if(decapplied==applied_m)
        {
            //cout << "Applying circuit is well-defined with " << i << " multiplications\n";
            cout << "    yes\n";
            i++;
        }
        else
        {
            cout << "    no\n";
            well_def=0;
            cout << "well-defined up to " << i-1 << " multiplications\n\n\n";
        }
    }
}

void CBE_test(void)
{
    int N;
    string input;
    cout << "Enter N: ";
    getline(cin,input);
    stringstream(input) >> N;
    cout << "Enter P: ";
    getline(cin,input);
    bigint P(input);
    cout << "Enter K: ";
    getline(cin,input);
    bigint K(input);
    cout << "Enter M: ";
    getline(cin,input);
    bigint M(input);
    array p, q;
    array pq;
    KEYGEN(p,q,P,M,K,N,0);
    p.printinfo("  p");
    q.printinfo("  q");
    pq=COMPWISEPROD(p,q);
    bigint prodp(p.prod());
    cout << "  prod(p_i) = " << prodp << "\n";
    NWLN;
    cout << "Enter a message m1 <" << P << ": ";
    getline(cin,input);
    bigint m1(input);
    array enc1(ENCRYPT(m1,p,q,P,K,1,0));
    enc1.printinfo("  e(m1)");
    cout << "Enter a message m2 <" << P << ": ";
    getline(cin,input);
    bigint m2(input);
    array enc2(ENCRYPT(m2,p,q,P,K,1,0));
    enc2.printinfo("  e(m2)");
    cout << "Enter a message m3 <" << P << ": ";
    getline(cin,input);
    bigint m3(input);
    array enc3(ENCRYPT(m3,p,q,P,K,1,0));
    enc3.printinfo("  e(m3)");
    cout << "  Our circuit C is m1*m2+m3\n";
    array Cencs(ARRMODARR(COMPWISEPROD(enc1,enc2)+enc3,pq));
    Cencs.printinfo("  C(e(m1),e(m2),e(m3))");
    bigint dec(DECRYPT(Cencs,p,P));
    bigint cms(MOD(m1*m2+m3,P));
    cout << "  d(C(e(m1),e(m2),e(m3))) = " << dec << "\n";
    cout << "  C(m1,m2,m3) = " << cms << "\n";
    cout << "  equal? ";
    if(cms==dec)
        cout << "yes\n";
    else
        cout << "no\n";
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

void ME_test(void)
{
    string input;
    cout << "Enter bound on deg of f and g:   ";
    getline(cin,input);
    int totdeg;
    stringstream(input) >> totdeg;
    cout << "Enter bound on coefficient size: ";
    getline(cin,input);
    bigint coeffsize(input);
    llist f, g;
    bigint z0;
    MULTICRYPT_KEYGEN(f, g, z0, totdeg, coeffsize);
    f.printinfo("  f");
    g.printinfo("  g");
    cout << "  z0 = " << z0 << "\n";
    cout << "Enter a message m1: ";
    getline(cin,input);
    bigint m1(input);
    llist enc1(MULTICRYPT_ENCRYPT(m1,f,g,totdeg,coeffsize));
    enc1.printinfo("  e(m1)");
    
    cout << "Enter a message m2: ";
    getline(cin,input);
    bigint m2(input);
    llist enc2(MULTICRYPT_ENCRYPT(m2,f,g,totdeg,coeffsize));
    enc2.printinfo("  e(m2)");
    
    cout << "Enter a message m3: ";
    getline(cin,input);
    bigint m3(input);
    llist enc3(MULTICRYPT_ENCRYPT(m3,f,g,totdeg,coeffsize));
    enc3.printinfo("  e(m3)");
    
    cout << "  Our circuit C is m1*m2+m3\n";
    
    llist Cencs(enc1*enc2+enc3);
    Cencs.printinfo("  C(e(m1),e(m2),e(m3))");
    bigint dec(MULTICRYPT_DECRYPT(Cencs,f,g,z0));
    bigint cms(m1*m2+m3);
    cout << "  d(C(e(m1),e(m2),e(m3))) = " << dec << "\n";
    cout << "  C(m1,m2,m3) = " << cms << "\n";
    cout << "  equal? ";
    if(cms==dec)
        cout << "yes\n";
    else
        cout << "no\n";
}

void rmvarpolys(void)
{
    int cont=1;
    string input;
    while(cont)
    {
        cout << "Enter bound on deg of f and g:   ";
        getline(cin,input);
        int totdeg;
        stringstream(input) >> totdeg;
        
        cout << "Enter bound on coefficient size: ";
        getline(cin,input);
        bigint coeffsize(input);
        
        llist a(RAND_MVAR_POLY(totdeg,coeffsize));
        a.printinfo("poly");
        
        cout << "Enter 1 to generate another polynomial, 0 to exit: ";
        getline(cin,input);
        stringstream(input) >> cont;
    }
}

void llisttest()
{
    llist L;
    L.insert(bigint(3),5,6);
    L.insert(bigint(2),4,10);
    L.insert(bigint(2000),6,3);
    L.insert(bigint(1),6,4);
    L.insert(bigint(1),6,2);
    L.insert(bigint(-2342),4,10);
    L.insert(bigint(-2333),4,10);
    L.insert(bigint(1),5,0);
    L.printinfo("L");
    llist M(L);
    M.printinfo("M");
    llist K=M+L;
    K.printinfo("M+L");
    llist R=K*L;
    R.printinfo("K*L");
    llist S;
    S.insert(bigint(3),3,3);
    S.insert(bigint(4),5,2);
    S.printinfo("S");
    llist T(S.eval_y(2));
    T.printinfo("S(x,2) = T");
    T.insert(0,20,20);
    T.listprint("T");
    T.trim_zeros();
    T.listprint("T");
    
    llist A;
    A.insert(1,0,0);
    A.insert(1,1,0);
    llist B;
    B.insert(-1,0,0);
    B.insert(1,1,0);
    
    llist C(A*B+T);
    C.printinfo("C := A*B+T = ");
    bigint aa(bigint(50)/16);
    cout << "aa = " << aa << "\n";
    llist D(C.quot_x(A));
    A.printinfo("A");
    T.printinfo("T");
    D.printinfo("C/A");
    llist RND(RAND_MVAR_POLY(4, bigint(1000)));
    RND.printinfo("RND");
    (C.reduce_x(T)).printinfo("C mod T");
    
    clock_t t=clock();
    llist f, g;
    bigint z0;
    MULTICRYPT_KEYGEN(f,g,z0);
    f.printinfo("keygen f");
    g.printinfo("keygen g");
    (g.eval_y(z0)).printinfo("g(x,z0)");
    cout << "z0 = " << z0 << "\n";
    bigint m(45023842039482039);
    llist ENC(MULTICRYPT_ENCRYPT(m,f,g));
    bigint ret(MULTICRYPT_DECRYPT(ENC,f,g,z0));
    cout << "original message = " << m << "\ndecryption = " << ret << "\n";
    cout << "this whole process took " << t << " clock ticks, or " << ((float)t)/CLOCKS_PER_SEC << " seconds" << "\n";
    //ENC.printinfo("enc");
}

void grob_gens(int deg, bigint log_coeff_size, int num_gens)
{
    //this function saves a collection of encryptions of zero to a file M2Results.txt using the arguments as parameters
    //arguments:
    //  num_gens: the number of encryptions of zero generated (i.e. elements of (f,g))
    //  coeff_size: size of the polynomial coefficients for f and g
    //  deg: the degree of f and g
    
    int i;
    bigint coeff_size(POW(2,log_coeff_size));
    
    llist f, g;
    bigint z0;
    MULTICRYPT_KEYGEN(f,g,z0,deg,coeff_size);
    
    ofstream file;
    file.open("./Polys.txt", ios::out | ios::trunc); //file to write polynomial list to
    
    for(i=0;i<num_gens;i++)
    {//generate encryptions of zero
        llist enc=MULTICRYPT_ENCRYPT(bigint(0),f,g,deg,coeff_size);
        assert(MULTICRYPT_DECRYPT(enc,f,g,z0)==0);
        if(file.is_open())
        {
            enc.print_to_file(&file);
            if(i<num_gens-1)
                file << ",";
        }
    }
    file.close();
}

int main(int argc, char ** argv)
{
    srand(time(NULL));
    //for(int i=1;i<10;i++)
    //    cout << "RAND(10,5) = " << RAND(bigint(10),bigint(10)/bigint(2)) << "\n";
    // array p;
    // array q;
    // bigint P(0);
    // bigint M(0);
    // bigint K(0);
    // int N=0;
    // int cleararrs=0;
    // KEYGEN(p,q,P,M,K,N,cleararrs);
    char * arg=argv[1];
    if(arg==((string) "func"))
    {
        functest();
    }
    else if(arg==((string) "choice"))
    {
        ENCRYPTtest();
        user_encryption_test();
    }
    else if(arg==((string) "multi"))
    {
        llisttest();
    }
    else if(arg==((string) "nEt"))
    {
        newENCRYPTtest();
    }
    else if(arg==((string) "CBE_test"))
    {
        CBE_test();
    }
    else if(arg==((string) "ME_test"))
    {
        ME_test();
    }
    else if(arg==((string) "genpolys"))
    {
        rmvarpolys();
    }
    else if(arg==((string) "grob"))
    {
        if(argc!=5)
        {
            cout << "usage: ./enc grob <degree> <log_2 of coefficient size> <number of encryptions>\n\n";
        }
        else
        {
            grob_gens(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
        }
    }
	return 0;
}