#include "VectorADT.hpp"
#include <vector>
#include <iostream>

ArrayVector::ArrayVector()      // constructor
: capacity(0), n(0), A(nullptr) { }

int ArrayVector::size() const   // number of elements
    { 
        return n; 
    }
bool ArrayVector::empty() const // is vector empty?
    { 
        return size() == 0; 
    }
VElem& ArrayVector::operator[ ](int i) // element at index
    { 
        return A[i]; 
    }
// element at index (safe)
VElem& ArrayVector::at(int i) throw (std::out_of_range)
{
    if (i < 0 || i >= n)
    throw std::out_of_range("illegal index in function at()");
    return A[i];
}

void ArrayVector::erase(int i) 
    {                                   // remove element at index
        for (int j = i+1; j < n; j++)   // shift elements down
            {
                A[j - 1] = A[j];
            }
            n--;                        // one fewer element
    }

void ArrayVector::clear()
    {   
        while(!empty()) erase(n-1);     //clear all the nodes in the vector
    }

void ArrayVector::reserve(int N) 
{ // reserve at least N spots
    if (capacity >= N) 
        return;                         // already big enough
    VElem* B = new VElem[N];            // allocate bigger array
    for (int j = 0; j < n; j++)         // copy contents to new array
        B[j] = A[j];
    if (A != NULL) delete [ ] A;        // discard old array
    A = B;                              // make B the new array
    capacity = N;                       // set new capacity
}
void ArrayVector::insert(int i, const VElem& e) 
{
    if (n >= capacity)                  // overflow?
        reserve(std::max(1, 2 * capacity)); // double array size
    for (int j = n - 1; j >= i; j--)    // shift elements up
        {
            A[j+1] = A[j];
        }
        A[i] = e;                       // put in empty slot
        n++;                            // one more element
}

ArrayVector& ArrayVector::operator=(const std::vector<long> &invec)
{
    for(unsigned int i = 0; i < invec.size(); i++)
    {
        this->insert(0,invec.at(i));
    }
 
                                        // return the existing object so we can chain this operator
    return *this;
}