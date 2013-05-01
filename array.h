#ifndef ARRAY_H
#define ARRAY_H

#include "common.h"

class array
{
    public:
        array(){len=0;vals=NULL;};
        array(const array& arr);
        array(int size);
        array(int size, bigint initval);
        virtual ~array();
        
        array& operator=(array arr);
        array operator+(const array& arr);
        array operator-(const array& arr);
        array operator*(bigint b);
        //array operator*(const array& arr); //component-wise
        bigint operator[](int i);
        
        void append(bigint val);
        void appendv(bigint vec[], int size);
        void clear(void);
        int get_len(void);
        void printr(void);
        void printinfo(std::string name);
		void set_val(int index, bigint val);
        bigint prod(void);
        
    protected:
        int len;
        bigint * vals;
};

#endif