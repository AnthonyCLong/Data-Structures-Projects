/*#ifndef HASHMAPADT_H
#define HASHMAPADT_H

#include <vector>
#include <list>
#include <iostream>
//#include "Entry.hpp"


template <typename K, typename V, typename H>
class HashMap 
    {       
    public:
        class Entry 
            {
                public:
                // constructor
                Entry(const K& k = K(),const V& v = V()) :_key(k),_value(v) {}
                const K& key() const { return _key; } // get key
                const V& value() const { return _value; } // get value
                void setKey(const K& k) { _key = k; } // set key
                void setValue(const V& v) { _value = v; } // set value
                private:
                K _key; // key
                V _value; // value
                friend class HashMap; // give HashMap access
            };
        protected:
        typedef std::list<Entry> Bucket; // a bucket of entries
        typedef std::vector<Bucket> BktArray; // a bucket array
    
            protected:
        typedef typename BktArray::iterator BItor; // bucket iterator
        typedef typename Bucket::iterator EItor; // entry iterator
    //-------------------------------------------------------------------------------------------------------------------------------------------------------
    public:
        class Iterator 
        { // an iterator (& position)
            private:
            EItor ent; // which entry
            BItor bkt; // which bucket
            const BktArray* ba; // which bucket array
            public:
            Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
            : ent(q), bkt(b), ba(&a) { }
            Entry& operator*() const{ return *ent; } // get entry
            bool operator==(const Iterator& p) const 
                {
                    if (ba != p.ba || bkt != p.bkt) return false; // ba or bkt differ?
                    else if (bkt == ba->end()) return true; // both at the end?
                    else return (ent == p.ent); // else use entry to decide
                }
// are iterators equal?
            Iterator& operator++() // advance to next entry
            {
                ++ent; // next entry in bucket
                if (endOfBkt(*this)) { // at end of bucket?
                ++bkt; // go to next bucket
                while (bkt != ba->end() && bkt->empty()) // find nonempty bucket
                ++bkt;
                if (bkt == ba->end()) return *this; // end of bucket array?
                ent = bkt->begin(); // first nonempty entry
                }
                return *this; // return self
            }
            friend class HashMap; // give HashMap access
            
        };
    //-------------------------------------------------------------------------------------------------------------------------------------------------------
        protected:
        //typedef typename BktArray::iterator BItor; // bucket iterator
        //typedef typename Bucket::iterator EItor; // entry iterator

    //public:
        //class Iterator; // a iterator/position
        //class Entry;
        //typedef Entry <const K,V> Entry; // a (key,value) pair

        
    public:
        HashMap(int capacity = 100)
        : n(0), B(capacity) { } // constructor
        Iterator find(const K& k) // find entry key k
        {
            Iterator p = finder(k); // look for k
            if (endOfBkt(p)) // didn’t find it?
            return end(); // return end iterator
            else
            return p; // return its position
        }
        Iterator put(const K& k, const V& v)// insert/replace
        {
            Iterator p = finder(k); // search for k
            if (endOfBkt(p)) 
                { // k not found?
                    return inserter(p, Entry(k, v)); // insert at end of bucket
                }
            else 
                { // found it?
                    p.ent->setValue(v); // replace value with v
                    return p; // return this position
                }
        }

        void erase(const K& k) // remove entry key k
        {
            Iterator p = finder(k); // find k
            if (endOfBkt(p)) // not found?
            throw std::runtime_error("Erase of nonexistent"); // . . .error
            eraser(p); // remove it
        }
        
        void erase(const Iterator& p){ eraser(p); } // erase entry at p
        Iterator begin() 
            {
                if (empty()) return end(); // emtpty - return end
                BItor bkt = B.begin(); // else search for an entry
                while (bkt->empty()) ++bkt; // find nonempty bucket
                return Iterator(B, bkt, bkt->begin()); // return first of bucket
            }
        Iterator end(){ return Iterator(B, B.end()); }
        int size()const{ return n; }
        bool empty() const{ return size() == 0; }
        // Some functions left out and utilities (next slide)
    protected:

        Iterator finder(const K& k) // find utility
        {
            int i = hash(k) % B.size(); // get hash index i
            BItor bkt = B.begin() + i; // the ith bucket
            Iterator p(B, bkt, bkt->begin()); // start of ith bucket
            while (!endOfBkt(p) && (*p).key() != k) // search for k
            nextEntry(p);
            return p; // return final position
        }
        Iterator inserter(const Iterator& p, const Entry& e)
        {
            EItor ins = p.bkt->insert(p.ent, e); // insert before p
            n++; // one more entry
            return Iterator(B, p.bkt, ins); // return this position
        } // insert utility
        void eraser(const Iterator& p) // remove utility
        {
            p.bkt->erase(p.ent); // remove entry from bucket
            n--; // one fewer entry
        }

        static void nextEntry(Iterator& p) { ++p.ent; } // bucket's next entry
        static bool endOfBkt(const Iterator& p) { return p.ent == p.bkt->end();}
    private:
        int n; // number of entries
        H hash(K k)
        {
             int hashValue = 0;
            const stringTypeKey = `${key}${typeof key}`;

            for (let index = 0; index < stringTypeKey.length; index++) {
            const charCode = stringTypeKey.charCodeAt(index);
            hashValue += charCode << (index * 8);
            }

            return hashValue;
        }; // the hash comparator
        BktArray B; // bucket array

    };


#endif*/