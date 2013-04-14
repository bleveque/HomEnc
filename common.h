#ifndef COMMON_H
#define COMMON_H

#include <gmp.h>
#include <gmpxx.h>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

#define RAND_BD 100
#define COEFF_BD 10000000
#define RLEN 50 //length of the arrays in the EXTresultant function
#define STD_DEG 5
#define NEWLINE "\n"
#define NUMCOMP 3
#define NWLN (cout << "\n")
#define BIGINTSIZE (sizeof(mpz_class))
#define Z0_SIZE 100000
#define MULTICRYPT_DEGREE 5

typedef mpz_class bigint;
typedef mpz_class mpz;

void printinfo(bigint b, string s);
void split(string s, char c, string * ret);

bigint GCD(bigint a, bigint b);
bigint MOD(bigint a, bigint m);
bigint NEXTPRIME(bigint after);
bigint POW(bigint base, bigint exp);
bigint POWMOD(bigint base, bigint exp, bigint m);
bigint RAND();
bigint RAND(bigint bound);
bigint RAND(bigint bound, bigint lbound);
bigint RAND2(bigint bound, bigint lbound);
bigint RANDODD();
bigint RANDODD(bigint bound, bigint lbound);
bigint XGCD(bigint a, bigint b, bigint &ainv, bigint &binv);

#endif