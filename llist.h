/**
* Ben LeVeque, 2013
* llist.h
*
* Header file for a linked list class. This class will allow us
* to represent (possibly) sparse multivariate polynomials without
* the need to keep track of zero terms. Terms/nodes are represented
* as a structure containing a pointer to the next term, a bigint
* coefficient, an x-degree, and a y-degree. Addition and mulitplication
* of polynomials are very straightforward, relying on an implementation
* of node insertion that combines like terms. The linked list has a set
* head node that has x and y degree -1 to avoid empty list problems.
*
* Idea from Knuth's Art of Computer Programming.
**/

#ifndef LLIST_H
#define LLIST_H

#include <fstream>
#include "common.h"

typedef struct node
{
	struct node * next;
	bigint coeff;
	int xdeg;
	int ydeg;
} node;

class llist
{
	public:
		llist(){head=new node;head->next=NULL;head->coeff=bigint(0);head->xdeg=-1;head->ydeg=-1;};
		llist(const llist& L);
		virtual ~llist();
		
		llist& operator=(llist L);
		llist operator+(const llist& L);
		llist operator-(const llist& L);
		llist operator*(const llist& L);
		
		llist eval_y(bigint z);
		void insert(bigint coeff, int xdeg, int ydeg);
		int get_xdeg(void);
		bigint get_lead_coeff(void);
		void listprint(string s);
		void printinfo(string s);
		void print_to_file(ofstream * file);
		llist quot_x(const llist& L);
		llist reduce_x(const llist& L);
		void trim_zeros(void);
		
	private:
		node * head;
};


#endif