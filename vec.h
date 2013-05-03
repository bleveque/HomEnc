/**
* Ben LeVeque, 2013
* vec.h
*
* Header for the vector class.
* This class is a wrapper for C++ arrays, adding
* arithmetic functions necessary for the choice-based
* cryptosystem.
**/

#ifndef VEC_H
#define VEC_H

#include "common.h"

class vec
{
    public:
        vec(){len=0;vals=NULL;};
        vec(const vec& v);
        vec(int size);
        vec(int size, bigint initval);
        virtual ~vec();
        
        vec& operator=(vec v);
        vec operator+(const vec& v);
        vec operator-(const vec& v);
        vec operator*(bigint b);
        bigint operator[](int i);
        
        void clear(void);
        int get_len(void);
        void printr(void);
        void printinfo(std::string name);
        bigint prod(void);
		void set_val(int index, bigint val);
        
    protected:
        int len;
        bigint * vals;
};

#endif