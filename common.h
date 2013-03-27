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

typedef mpz_class bigint;
typedef mpz_class mpz;

void printinfo(bigint b, string s);
void split(string s, char c, string * ret);

#endif