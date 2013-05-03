/**
* Ben LeVeque, 2013
* main.cpp
*
* A collection of tests using the functions defined in
* nt_funcs.cpp.
**/

#include "vec.h"
#include "llist.h"
#include "nt_funcs.h"

void testinfo(string s)
{
    /* Prints the name of a test */
    cout << "\n=== " << s << " ===\n";
}

void functest(void)
{
    /* Sanity checks for the correctness of some of
       the functions defined in vec.cpp, llist.cpp, and
       nt_funcs.cpp.
     */
     
    //test vector arithmetic
    vec a(4), b(4), c, d, e, B(2), C, K(2), J(2), S(4);
    testinfo("vecs");
    a.set_val(3,3234);
    a.set_val(0,323);
    a.printinfo("a = (323,0,0,3234)");
    C=a*3;
    C.printinfo("3a");
    b.set_val(0,432);
    b.set_val(1,4323);
    b.printinfo("b = (432,4323)");
    c=a+b;
    c.printinfo("c = a+b");
    a=b-c;
    a.printinfo("a = b-c");
    printinfo(a[0],"a[0]");
    
    //test the SUM and ARRSUM functions
    testinfo("SUM");
    bigint sum(SUM(a));
    a.printinfo("a");
    printinfo(sum,"SUM(a)");
    
    testinfo("ARRSUM");
    a.printinfo("a");
    c.printinfo("c");
    S.set_val(1,4);
    S.set_val(2,7);
    S.printinfo("S");
    vec * ac=new vec[3];
    ac[0]=a;
    ac[1]=c;
    ac[2]=S;
    b=ARRSUM(ac,3);
    b.printinfo("b=a+c+S");
    delete[] ac;
    
    //print the standard deviation function
    testinfo("STDDEVNUM");
    a.printinfo("a");
    bigint dev(STDDEVNUM(a));
    cout << "stddev(a) = sqrt(" << dev << "," << (a.get_len()*a.get_len()*(a.get_len()-1)) << ")\n";
    
    //test component-wise vector multiplication
    testinfo("COMPWISEPROD");
    a.printinfo("a");
    c.printinfo("c");
    b=COMPWISEPROD(a,c);
    b.printinfo("b = a*c");
    
    //test taking the product of all vector entries
    testinfo("prod");
    B.set_val(0,2);
    B.set_val(1,4);
    printinfo(B.prod(),"B.prod() = 8");
    
    //test reduction and component-wise vector reduction
    testinfo("ARRMOD");
    vec Bmod(ARRMOD(B,2));
    Bmod.printinfo("Bmod = (0,0)");
    
    testinfo("ARRMODARR");
    J.set_val(0,5);
    J.set_val(1,6);
    K.set_val(0,2);
    K.set_val(1,3);
    vec JmodK(ARRMODARR(J,K));
    JmodK.printinfo("(5,6) mod (2,3) = (1,0)");
    
    //test a circuit application
    testinfo("APPLYCIRC_ENC");
    a.printinfo("a");
    b.printinfo("b");
    vec circ(2);
    circ.set_val(0,3);
    circ.set_val(1,4);
    vec res(CBE_APPLYCIRC_ENC(circ,a,b));
    res.printinfo("res = 3a+b^4");
    
    //test the greatest common divisor and extended gcd functions
    testinfo("GCD");
    printinfo(GCD(2064846799,10011991),"GCD(2064846799,10011991) = 43");
    
    testinfo("XGCD");
    bigint s,t,g(2064846799),h(10011991);
    printinfo(XGCD(g,h,s,t),"XGCD(2064846799,10011991)");
    bigint l(g*s+h*t);
    cout << "inverses: "<< g << "*(" << s << ") + " << h << "*(" << t << ") = " << l << "\n";
    
    //test reduction
    testinfo("MOD");
    bigint modtest=MOD(101,82);
    printinfo(modtest,"MOD(101,82) = 19");
    
    //test integer powers
    testinfo("POW");
    bigint BI(POW(bigint(39),bigint(19)));
    printinfo(BI,"39^19");
    
    //test the Chinese Remainder Theorem implementation
    testinfo("CRT");
    vec Plist(2);
    Plist.set_val(0,3);
    Plist.set_val(1,5);
    vec vallist(2);
    vallist.set_val(0,2);
    vallist.set_val(1,3);
    a=Plist;
    bigint crt=CRT(vallist,a,1);
    printinfo(crt,"CRT([2,3],[3,5]) = 8");
    
    //test the random number functions
    testinfo("RAND");
    printinfo(RAND(50),"RAND(50)");
    printinfo(RAND(20000),"RAND(20000)");
    
    testinfo("RANDARR");
    a=RANDARR(10);
    a.printinfo("RANDARR()");
    
    //test built-in string -> bigint conversion
    testinfo("bigint via string");
    bigint bi("1023023002332");
    printinfo(bi,"1023023002332");
    
    //test finding the next prime after a given integer
    testinfo("NEXTPRIME");
    printinfo(NEXTPRIME(100),"nextprime(100) = 101");
    
    //test linked list functionality
    testinfo("linked list functionality");
    llist L1;
    L1.insert(bigint(3),5,6);
    L1.insert(bigint(2),4,10);
    L1.insert(bigint(2000),6,3);
    L1.insert(bigint(1),6,4);
    L1.insert(bigint(1),6,2);
    L1.insert(bigint(-2342),4,10);
    L1.insert(bigint(-2333),4,10);
    L1.insert(bigint(1),5,0);
    L1.printinfo("L");
    llist M1(L1);
    M1.printinfo("M");
    llist K1=M1+L1;
    K1.printinfo("K := M+L");
    llist R1=K1*L1;
    R1.printinfo("K*L");
    llist S1;
    S1.insert(bigint(3),3,3);
    S1.insert(bigint(4),5,2);
    S1.printinfo("S");
    llist T1(S1.eval_y(2));
    T1.printinfo("T := S(x,2)");
    T1.insert(0,20,20);
    T1.listprint("T + 0*x^20*y^20");
    T1.trim_zeros();
    T1.listprint("trimmed T");
    
    llist A1;
    A1.insert(1,0,0);
    A1.insert(1,1,0);
    llist B1;
    B1.insert(-1,0,0);
    B1.insert(1,1,0);
    llist C1(A1*B1+T1);
    C1.printinfo("C := A*B+T = ");
    llist D1(C1.quot_x(A1));
    A1.printinfo("A");
    T1.printinfo("T");
    D1.printinfo("C/A");
    llist RND1(RAND_MVAR_POLY(4, bigint(1000)));
    RND1.printinfo("random");
    (C1.reduce_x(T1)).printinfo("C mod T");
    
    cout << "\n";
}

int CBE_test(void)
{
    /* Tests encryption, circuit application,
       and decryption using CBE.
     */
    cout << "\n\nCBE_test" << "\n==========================================\n";
    vec p,q,pq;
    bigint P(-1);
    bigint M(100); // at least M operations should be well-defined
    bigint K(-1);
    int N=60;
    CBE_KEYGEN(p,q,P,M,K,N);
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
    vec enc(CBE_ENCRYPT(m,p,q,P,K));
    cout << "enc = ";
    enc.printr();
    NWLN;
    bigint dec(CBE_DECRYPT(enc,p,P));
    cout << "dec = " << dec << "\n";
    cout << "m = " << m << "\n";
    cout << "dec = m?  ";
    if(dec==m)
        cout << "yes\n\n\n";
    else
        cout << "no\n\n\n";
        
    cout << "CIRCUIT TEST\n===============================\n";
    bigint m2(RAND(1000));
    vec enc2(CBE_ENCRYPT(m2,p,q,P,K));
    int i=1, well_def=1;
    while(well_def)
    {
        vec circ(2);
        circ.set_val(0,0);//RAND(100000,1000));
        circ.set_val(1,i+1); //just computing powers of the second encryption
        vec applied_enc(CBE_APPLYCIRC_ENC_MODpq(circ,enc,enc2,pq));
        bigint decapplied(CBE_DECRYPT(applied_enc,p,P));
        bigint applied_m=MOD(CBE_APPLYCIRC_M(circ,m,m2),P);
        cout << "test " << i << ": " << decapplied << " ?= " << applied_m;
        if(decapplied==applied_m)
        {
            cout << "    yes\n";
            i++;
        }
        else
        {
            cout << "    no\n";
            well_def=0;
            cout << "well-defined up to " << i-1 << " multiplications\n";
            cout << "the key M guarantees at least " << M << " homomorphic operations\n\n";
        }
    }
}

void user_CBE_test(void)
{
    /* Test the CBE scheme using user input for N, P, K, and M. */
     
    //get patameters and run key generation
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
    vec p, q;
    vec pq;
    CBE_KEYGEN(p,q,P,M,K,N);
    p.printinfo("  p");
    q.printinfo("  q");
    pq=COMPWISEPROD(p,q);
    bigint prodp(p.prod());
    cout << "  prod(p_i) = " << prodp << "\n";
    NWLN;
    
    // test circuit application on encryptions of user-inputted messages
    cout << "Enter a message m1 <" << P << ": ";
    getline(cin,input);
    bigint m1(input);
    vec enc1(CBE_ENCRYPT(m1,p,q,P,K));
    enc1.printinfo("  e(m1)");
    cout << "Enter a message m2 <" << P << ": ";
    getline(cin,input);
    bigint m2(input);
    vec enc2(CBE_ENCRYPT(m2,p,q,P,K));
    enc2.printinfo("  e(m2)");
    cout << "Enter a message m3 <" << P << ": ";
    getline(cin,input);
    bigint m3(input);
    vec enc3(CBE_ENCRYPT(m3,p,q,P,K));
    enc3.printinfo("  e(m3)");
    cout << "  Our circuit is C(x1,x2,x3) = x1*x2+x3\n";
    vec Cencs(ARRMODARR(COMPWISEPROD(enc1,enc2)+enc3,pq));
    Cencs.printinfo("  C(e(m1),e(m2),e(m3))");
    bigint dec(CBE_DECRYPT(Cencs,p,P));
    bigint cms(MOD(m1*m2+m3,P));
    cout << "  d(C(e(m1),e(m2),e(m3))) = " << dec << "\n";
    cout << "  C(m1,m2,m3) = " << cms << "\n";
    cout << "  equal? ";
    if(cms==dec)
        cout << "yes\n";
    else
        cout << "no\n";
}

void CBE_stddev_test(void)
{
    /* Similar to user_CBE_test above, this method
       uses user input to test the application of the
       standard deviation and mean circuits. Since these
       circuits in general return a rational number, we
       calculate the numerator and denominator separately here.
       Note that since we reduce modulo P in decryption, we
       need to be careful to choose messages that will not
       cause the circuit to overflow P if we want well-definition.
     */
    string input;
    vec p,q,pq;
    bigint P(-1);
    int N;
    cout << "Enter N: ";
    getline(cin,input);
    stringstream(input) >> N;
    bigint M(20);
    bigint K(-1);
    CBE_KEYGEN(p,q,P,M,K,N);
    pq=COMPWISEPROD(p,q);
    vec messages(N);
    vec * encs=new vec[N];
    int i;
    for(i=0;i<N;i++)
    {
        cout << "Enter message < " << P << ":  ";
        getline(cin,input);
        if(input.length()==0)
        {
            bigint m(RAND(P));
            messages.set_val(i,m);
            encs[i]=CBE_ENCRYPT(m,p,q,P,K);
        }
        else
        {
            bigint m(input);
            messages.set_val(i,m);
            encs[i]=CBE_ENCRYPT(m,p,q,P,K);
        }
    }
    messages.printinfo("messages");
    clock_t t=clock();
    testinfo("MEAN");
    vec sum(ARRSUM(encs,N));
    sum.printinfo("sum of encryptions");
    bigint dec(CBE_DECRYPT(sum,p,P));
    printinfo(dec,"decrypted sum of encrypted messages");
    printinfo(MOD(SUM(messages),P),"sum of messages modulo P");
    cout << "the mean is returned as a pair (" << dec << "," << N << ")\n";
    
    testinfo("STANDARD DEVIATION");
    vec nsumarr(STDDEVNUMARR(encs,N));
    bigint ndec(CBE_DECRYPT(nsumarr,p,P));
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
    cout << "keygen, encryption, circuit application, and decryption took " << t << " clock ticks, or " << ((float)t)/CLOCKS_PER_SEC << " seconds" << "\n";
	
}

void user_ME_test(void)
{
    /* Test of our multivariate encryption scheme.
       Queries the user for total degrees and
       coefficient bounds for f and g. Later, it
       queries for three messages to which we will
       apply the simple circuit
           C(x1,x2,x3) = x1*x2+x3
     */
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
    /* Allows a user to generate random polynomials at will. */
    int cont=1;
    string input;
    while(cont)
    {
        cout << "Enter degree bound:   ";
        getline(cin,input);
        int totdeg;
        stringstream(input) >> totdeg;
        
        cout << "Enter bound on coefficient size: ";
        getline(cin,input);
        bigint coeffsize(input);
        
        llist a(RAND_MVAR_POLY(totdeg,coeffsize));
        a.printinfo("poly");
        
        cout << "Enter 0 to exit, <enter> to continue: ";
        getline(cin,input);
        stringstream(input) >> cont;
    }
}

void ME_test()
{
    /* Test run of the multivariate encryption scheme. */
     
    testinfo("multivariate encryption test");
    clock_t t=clock();
    llist f, g;
    bigint z0;
    MULTICRYPT_KEYGEN(f,g,z0);
    f.printinfo("keygen f");
    g.printinfo("keygen g");
    (g.eval_y(z0)).printinfo("g(x,z0)");
    cout << "z0 = " << z0 << "\n";
    bigint m(RAND(10000000));
    llist ENC(MULTICRYPT_ENCRYPT(m,f,g));
    bigint ret(MULTICRYPT_DECRYPT(ENC,f,g,z0));
    cout << "original message = " << m << "\ndecryption = " << ret << "\n";
    cout << "match? ";
    cout << ((m==ret)?"yes\n":"no\n");
    cout << "keygen/encryption/decryption took " << t << " clock ticks, or " << ((float)t)/CLOCKS_PER_SEC << " seconds" << "\n";
}

void grob_gens(int deg, bigint log_coeff_size, int num_gens)
{
    /* This function saves a collection of encryptions of zero to a file M2Results.txt using the arguments as parameters
       arguments:
       num_gens: the number of encryptions of zero generated (i.e. elements of (f,g))
       coeff_size: size of the polynomial coefficients for f and g
       deg: the degree of f and g
     */
    
    int i;
    bigint coeff_size(POW(2,log_coeff_size));
    
    llist f, g;
    bigint z0;
    MULTICRYPT_KEYGEN(f,g,z0,deg,coeff_size);
    
    ofstream file;
    file.open("./Polys.txt", ios::out | ios::trunc); //file to which we will write polynomial list
    
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

void time_cbe(void)
{
    ofstream file;
    file.open("./cbe_times.txt", ios::out | ios::app);
    int Plog, N;
    bigint P, M, K, iter;
    bigint coeff;
    for(Plog=1;Plog<=40;Plog+=5)
    {
        P=NEXTPRIME(POW(2,Plog));
        for(M=0;M<=40;M+=5)
        {
            for(K=5;K<=40;K+=5)
            {
                for(N=512;N<=1024;N+=512)
                {
                    for(iter=1;iter<=5;iter++)
                    {
                        clock_t t;
                        t=clock();
                        vec p,q;
                        CBE_KEYGEN(p,q,P,M,K,N);
                    
                        bigint m(RAND(P));
                        vec enc(CBE_ENCRYPT(m,p,q,P,K));
                    
                        bigint dec(CBE_DECRYPT(enc,p,P));
                        t=clock()-t;
                        assert(m==dec);
                        cout << "P = " << P << ", M = " << M << ", K = " << K << ", N = " << N << ", iteration = " << iter << ", time = " << (((float) t)/CLOCKS_PER_SEC) << "\n";
                        if(file.is_open())
                        {
                            file << P << "|" << M << "|" << K << "|" << N << "|" << (((float) t)/CLOCKS_PER_SEC) << "|\n";
                        }
                    }
                }
            }
        }
    }
    file.close();
}

void time_me(void)
{
    ofstream file;
    file.open("./me_times.txt", ios::out | ios::app);
    int deg, logcoeff, k;
    bigint coeff;
    for(deg=2;deg<=40;deg++)
    {
        for(logcoeff=2;logcoeff<=20;logcoeff++)
        {
            coeff=POW(2,logcoeff);
            for(k=1;k<=5;k++)
            {
                clock_t t;
                t=clock();
                llist f, g;
                bigint z0;
                MULTICRYPT_KEYGEN(f, g, z0, deg, coeff);
                bigint m1(RAND(100000));
                llist enc1(MULTICRYPT_ENCRYPT(m1,f,g,deg,coeff));
                bigint dec(MULTICRYPT_DECRYPT(enc1,f,g,z0));
                t=clock()-t;
                assert(m1==dec);
                cout << "deg = " << deg << ", coeff = " << coeff << ", iteration = " << k << ", time = " << (((float) t)/CLOCKS_PER_SEC) << "\n";
                if(file.is_open())
                {
                    file << deg << "|" << coeff << "|" << (((float) t)/CLOCKS_PER_SEC) << "|\n";
                }
            }
        }
    }
    file.close();
}

int main(int argc, char ** argv)
{
    /* Accept user input and call functions accordingly */
    
    srand(time(NULL)); // seed the random number generator
    char * arg=argv[1];
    if(arg==((string) "funcs"))
    {
        functest();
    }
    else if((arg==((string) "cbe")) || (arg==((string) "CBE")))
    {
        CBE_test();
    }
    else if((arg==((string) "user_cbe")) || (arg==((string) "user_CBE")))
    {   
        user_CBE_test();
    }
    else if(arg==((string) "stddev"))
    {
        CBE_stddev_test();
    }
    else if((arg==((string) "ME")) || (arg==((string) "me")))
    {
        ME_test();
    }
    else if((arg==((string) "user_ME")) || (arg==((string) "user_me")))
    {
        user_ME_test();
    }
    else if(arg==((string) "polys"))
    {
        rmvarpolys();
    }
    else if(arg==((string) "grob"))
    {
        if(argc!=5)
            cout << "usage: ./enc grob <degree> <log_2 of coefficient size> <number of encryptions>\n\n";
        else
            grob_gens(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
    }
    else if(arg==((string) "time_me"))
    {
        time_me();
    }
    else if(arg==((string) "time_cbe"))
    {
        time_cbe();
    }
    else if(arg==((string) "all"))
    {
        testinfo("funcs");
        functest();
        testinfo("cbe");
        CBE_test();
        testinfo("user_cbe");
        user_CBE_test();
        testinfo("stddev");
        CBE_stddev_test();
        testinfo("me");
        ME_test();
        testinfo("user_me");
        user_ME_test();
        testinfo("polys");
        rmvarpolys();
    }
    else
    {
        cout << "USAGE:\n";
        cout << "  ./enc all        <-- run all below (except grob)\n";
        cout << "  ./enc cbe        <-- test choice-based encryption\n";
        cout << "  ./enc funcs      <-- test vector operations\n";
        cout << "  ./enc grob       <-- save a collection of (ME) encryptions of zero to Polys.txt\n";
        cout << "  ./enc me         <-- test multivariate encryption\n";
        cout << "  ./enc polys      <-- generate random polynomials\n";
        cout << "  ./enc stddev     <-- test choice-based encryption using std deviation circuit\n";
        cout << "  ./enc user_cbe   <-- test choice-based encryption with user inputs\n";
        cout << "  ./enc user_me    <-- test multivariate encryption with user inputs\n";
    }
	return 0;
}