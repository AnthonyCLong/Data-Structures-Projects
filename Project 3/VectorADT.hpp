#ifndef VECTORADT_H
#define VECTORADT_H

#include <stdexcept>
#include <algorithm>
#include <vector>


typedef long VElem;                                 // base element type

class ArrayVector 
{
    public:
        ArrayVector();                              // constructor
        int size() const;                           // number of elements
        bool empty() const;                         // is vector empty?
        VElem& operator[ ](int i);                  // element at index
        VElem& at(int i) throw(std::out_of_range);  // element at index
        void erase(int i);                          // remove element at index
        void clear();
        void insert(int i, const VElem& e);         // insert element at index
        void reserve(int N);                        // reserve at least N spots
        ArrayVector& operator=(const std::vector<long> &invec);
    private:
        int capacity;                               // current array size
        int n;                                      // number of elements in vector
        VElem* A;                                   // array storing the elements
};

#endif