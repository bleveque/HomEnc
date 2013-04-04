#ifndef LLIST_H
#define LLIST_H

#include <fstream>
#include "common.h"

/* doubly linked list for representing 
   two-variable polynomials (inspired by Knuth 270-5)  */

typedef struct node
{
	struct node * prev;
	struct node * next;
	bigint coeff;
	int xdeg;
	int ydeg;
} node;

class llist
{
	public:
		llist(){head=new node;head->prev=NULL;head->next=NULL;head->coeff=bigint(0);head->xdeg=-1;head->ydeg=-1;};
		//-1 as suggested in Knuth
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