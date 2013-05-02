/**
* Ben LeVeque, 2013
* llist.cpp
*
* Definitions of the functions declared in llist.h.
**/

#include "llist.h"

llist::llist(const llist& L)
{
    /* Copy constructor for linked lists. */
    head=new node;
    head->next=NULL; //head->next = NULL is equivalent to the list being empty
    head->coeff=bigint(0);
    head->xdeg=-1;
    head->ydeg=-1;
    
    node * ptr=L.head->next;
    while(ptr)
    {
        insert(ptr->coeff,ptr->xdeg,ptr->ydeg);
        ptr=ptr->next;
    }
}

llist::~llist()
{
    /* Destructor. Deletes all nodes. */
    node * ptr=head;
    node * next=head->next;
    while(ptr)
    {
        delete ptr;
        ptr=next;
        if(next)
            next=next->next;
    }
}

llist& llist::operator=(llist L)
{
    /* Assignment operator overload. */
    llist temp(L);
    std::swap(head,temp.head);
}

llist llist::operator+(const llist& L)
{
    /* Addition operator overload. Creates a new list
       and inserts each node of *this and L. Since node
       insertion handles combining like terms, this is
       all that's necessary. In case we have term cancellation,
       we trim out the zero terms at the end.
     */
    llist ret;
    node * ptr=head->next;
    node * Lptr=L.head->next;
    while(ptr)
    {
        ret.insert(ptr->coeff,ptr->xdeg,ptr->ydeg);
        ptr=ptr->next;
    }
    while(Lptr)
    {
        ret.insert(Lptr->coeff,Lptr->xdeg,Lptr->ydeg);
        Lptr=Lptr->next;
    }
    ret.trim_zeros();
    return ret;
}

llist llist::operator-(const llist& L)
{
    /* Subtraction operator overload. Analogous to operator+. */
    llist ret;
    node * ptr=head->next;
    node * Lptr=L.head->next;
    while(ptr)
    {
        ret.insert(ptr->coeff,ptr->xdeg,ptr->ydeg);
        ptr=ptr->next;
    }
    while(Lptr)
    {
        ret.insert(-Lptr->coeff,Lptr->xdeg,Lptr->ydeg);
        Lptr=Lptr->next;
    }
    ret.trim_zeros();
    return ret;
}

llist llist::operator*(const llist& L)
{
    /* Multiplication operator overload. Inserts each product of pairs
       of terms from *this and L. Node insertion handles combining
       like terms.
     */
    llist ret;
    node * ptr=head->next;
    int i=0,j=0;
    while(ptr)
    {
        i++;
        node * Lptr=L.head->next;
        j=0;
        while(Lptr)
        {
            j++;
            bigint coeffprod(ptr->coeff*Lptr->coeff);
            int xdegsum=ptr->xdeg+Lptr->xdeg;
            int ydegsum=ptr->ydeg+Lptr->ydeg;
            ret.insert(coeffprod,xdegsum,ydegsum);
            Lptr=Lptr->next;
        }
        ptr=ptr->next;
    }
    ret.trim_zeros();
    return ret;
}

llist llist::eval_y(bigint z)
{
    /* De facto evaluation at y. Changes each coefficient to
       be the product of the existing coefficient and z^ydeg
       and then changes the y-degree to 0.
     */
    llist ret;
    node * ptr=head->next;
    while(ptr)
    {
        ret.insert(ptr->coeff*POW(z,ptr->ydeg),ptr->xdeg,0);
        ptr=ptr->next;
    }
    return ret;
}

bigint llist::get_lead_coeff(void)
{
    /* Returns LC(*this). */
    node * ptr=head->next;
    if(!ptr)
        return bigint(0);
    return ptr->coeff;
}

int llist::get_xdeg(void)
{
    /* Returns the x-degree of *this. */
    node * ptr=head->next;
    if(!ptr)
        return 0;
    return ptr->xdeg;
}

void llist::insert(bigint coeff, int xdeg, int ydeg)
{
    /*  Node insertion. Takes in a node, allocates a pointer to it,
        inserts it in the list in decreasing order of x-degree, then
        decreasing order of y-degree. Like terms are combined if necessary.
        As an example of the ordering, consider the following:
          x^n(y^m+....+y+7) + x^(n-1)(y^2+y+9) + ... + x(y^7+y^3) + (y^3+y) + 9
    */
    node * ptr=head->next;
    node * pptr=head;
    int done=0;
    while(ptr && (ptr->xdeg>xdeg))
    {
        pptr=ptr;
        ptr=ptr->next;
    }
    if((ptr==NULL) || (ptr->xdeg<xdeg))
    {
        node * ndptr=new node;
        ndptr->coeff=coeff;
        ndptr->xdeg=xdeg;
        ndptr->ydeg=ydeg;
        ndptr->next=pptr->next;
        pptr->next=ndptr;
        return;
    }
    //now we assume that ptr->xdeg==xdeg
    while(ptr && (ptr->xdeg==xdeg) && (ptr->ydeg>ydeg))
    {
        pptr=ptr;
        ptr=ptr->next;
    }
    if((ptr==NULL) || (ptr->xdeg<xdeg) || (ptr->ydeg<ydeg))
    {
        node * ndptr=new node;
        ndptr->coeff=coeff;
        ndptr->xdeg=xdeg;
        ndptr->ydeg=ydeg;
        ndptr->next=pptr->next;
        pptr->next=ndptr;
        return;
    }
    //now we assume that the xdegs and ydegs are the same, so add
    ptr->coeff=ptr->coeff+coeff;
    return;
}

void llist::listprint(string s)
{
    /* Friendly linked list printing. */
    node * ptr=head;
    cout << s << " = ";
    while(ptr)
    {
        cout << "(" << ptr->coeff.get_mpz_t() << "," << ptr->xdeg << "," << ptr->ydeg << ")";
        cout << " --> ";
        ptr=ptr->next;
    }
    if(!ptr)
        cout << "NULL\n";
}

void llist::printinfo(string s)
{
    /* Prints *this as a polynomial. */
    trim_zeros();
    node * ptr=head->next;
    cout << s << " = ";
    if(!ptr)
        cout << "0";
    while(ptr)
    {
        if(ptr->coeff != 0)
        {
            cout << "(" << ptr->coeff;
            if(ptr->xdeg != 0)
                cout << "*x^" << ptr->xdeg;
            if(ptr->ydeg != 0)
                cout << "*y^" << ptr->ydeg;
            cout << ")";
            if(ptr->next)
                cout << "+";
        }
        ptr=ptr->next;
    }
    cout << "\n";
}

void llist::print_to_file(ofstream * file)
{
    /* Saves a polynomial to a file. This is helpful for running
       Grobner basis tests.
     */
    trim_zeros();
    node * ptr=head->next;
    if(!ptr)
        *file << "0";
    while(ptr)
    {
        if(ptr->coeff != 0)
        {
            *file << "(" << ptr->coeff;
            if(ptr->xdeg != 0)
                *file << "*x^" << ptr->xdeg;
            if(ptr->ydeg != 0)
                *file << "*y^" << ptr->ydeg;
            *file << ")";
            if(ptr->next)
                *file << "+";
        }
        ptr=ptr->next;
    }
}

llist llist::quot_x(const llist& L)
{
    /* Returns *this / L using polynomial long division.
       We assume that zeros have been trimmed from L.
     */
    node * Lptr=L.head->next;
    if(!Lptr)
    {
        cout << "division by zero error";
        return L;
    }
    llist T(*this);
    T.trim_zeros();
    llist R(*this);
    R.trim_zeros();
    llist Q;
    int lxdeg=Lptr->xdeg;
    bigint ldcoeff(Lptr->coeff);
    while(R.get_xdeg()>=lxdeg)
    {
        bigint rldcoeff(R.get_lead_coeff());
        int rdeg=R.get_xdeg();
        bigint q=rldcoeff/ldcoeff;
        int degdiff=rdeg-lxdeg;
        Q.insert(q,degdiff,0);
        R=T-(Q*L);
        if(R.get_xdeg()>=rdeg)
        {
            cout << "failure\n";
            llist failure; //empty list
            return failure;
        }
    }
    Q.trim_zeros();
    R.trim_zeros();
    return Q;
}

llist llist::reduce_x(const llist& L)
{
    /* Reduces *this modulo L, assuming that both are polynomials
       only in x (i.e. ydeg=0 for all terms). This uses the quot_x
       method above.      
     */
    llist Q(quot_x(L));
    llist T(*this);
    llist ret(T-Q*L);
    return ret;
}

void llist::trim_zeros(void)
{
    /* Delete any 0-coefficient terms. */
    node * ptr=head->next;
    node * pptr=head;
    while(ptr)
    {
        if(ptr->coeff==bigint(0))
        {
            pptr->next=ptr->next;
            node * temp=ptr;
            ptr=ptr->next;
            delete temp;
        }
        else
        {
            pptr=ptr;
            ptr=ptr->next;
        }
    }
}