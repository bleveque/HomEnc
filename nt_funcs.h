/**
* Ben LeVeque, 2013
* nt_funcs.h
*
* Contains general function declarations, including those
* for the key generation, encryption, and decryption functions
* of the choice-based and multivariate encryption schemes.
**/

#ifndef FUNCS_H
#define FUNCS_H

#include "vec.h"
#include "llist.h"

vec ARRMOD(vec arr, bigint m);
vec ARRMODARR(vec arr, vec marr);
vec ARRSUM(vec * arrs, int N);
vec CBE_APPLYCIRC_ENC(vec circ, vec enc1, vec enc2);
vec CBE_APPLYCIRC_ENC_MODpq(vec circ, vec enc1, vec enc2, vec pq);
bigint CBE_APPLYCIRC_M(vec circ, bigint m1, bigint m2);
bigint CBE_DECRYPT(vec enc, vec p, bigint P);
vec CBE_ENCRYPT(bigint m, vec p, vec q, bigint P, bigint K);
void CBE_KEYGEN(vec &p, vec &q, bigint &P, bigint &M, bigint &K, int &N);
vec COMPWISEPROD(vec arr1, vec arr2);
int COPRIMECHECK(vec arr);
bigint CRT(vec rlist, vec mlist);
bigint CRT(vec rlist, vec mlist, int check);
int IN(vec arr, bigint nw);
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0);
void MULTICRYPT_KEYGEN(llist &f, llist &g, bigint &z0, int deg, bigint coeff_size);
bigint MULTICRYPT_DECRYPT(llist c, llist f, llist g, bigint z0);
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g);
llist MULTICRYPT_ENCRYPT(bigint m, llist f, llist g, int deg, bigint coeff_size);
int NEWCOPRIME(vec arr, bigint nw);
int NOTIN(vec arr, bigint nw);
vec RANDARR(int n);
vec RANDARR(int n, bigint bd);
llist RAND_MVAR_POLY(int degbd, bigint coeffbd);
bigint STDDEVNUM(vec arr);
vec STDDEVNUMARR(vec * arrs, int N);
bigint SUM(vec arr);

#endif