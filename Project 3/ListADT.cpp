#include "ListADT.hpp"
#include <iostream>
#include <list>

NodeList::Iterator::Iterator()          // constructor from Node*
    { 
        v = new Node(NOOP); 
    }

NodeList::Iterator::Iterator(Node* u)   // constructor from Node*
    { 
        v = u; 
    }

Elem& NodeList::Iterator::operator*()   // reference to the element
    { 
        return v->elem; 
    }

                                        // compare positions
bool NodeList::Iterator::operator==(const Iterator& p) const
    { 
        return v == p.v; 
    }

bool NodeList::Iterator::operator!=(const Iterator& p) const
    { 
        return v != p.v; 
    }

                                        // move to next position
NodeList::Iterator& NodeList::Iterator::operator++()
    { 
        v = v->next; return *this; 
    }

                                        // move to previous position
NodeList::Iterator& NodeList::Iterator::operator--()
    { 
        v = v->prev; return *this; 
    }


NodeList::NodeList() 
    {                                       // constructor
        n = 0;                              // initially empty
        header = new Node(NOOP);            // create sentinels
        trailer = new Node(NOOP);
        header->next = trailer;             // have them point to each other
        trailer->prev = header;
    }



int NodeList::size() const                  // list size
    { 
        return n; 
    }

bool NodeList::empty() const                // is the list empty?
    { 
        return (n == 0); 
    }

NodeList::Iterator NodeList::begin() const // begin position is first item
    { 
        return Iterator(header->next); 
    }

NodeList::Iterator NodeList::end() const    // end position is just beyond last
    { 
        return Iterator(trailer); 
    }
//---------------------------------------------------------------------------------
// insert e before p

void NodeList::insert(const NodeList::Iterator& p, const Elem& e) 
    {
        Node* w = p.v;              // p’s node
        Node* u = w->prev;          // p’s predecessor
        Node* v = new Node(NOOP);   // new node to insert
        v->elem = e;
        v->next = w; w->prev = v;   // link in v before w
        v->prev = u; u->next = v;   // link in v after u
        n++;
    }

void NodeList::insertFront(const Elem& e) // insert at front
{ 
    insert(begin(), e); 
}

void NodeList::insertBack(const Elem& e) // insert at rear
{ 
    insert(end(), e); 
}

void NodeList::erase(const Iterator& p) 
    { // remove p
        Node* v = p.v;              // node to remove
        Node* w = v->next;          // successor
        Node* u = v->prev;          // predecessor
        u->next = w; w->prev = u;   // unlink p
        delete v;                   // delete this node
        n--;                        // one fewer element
    }

void NodeList::eraseFront()         // remove first
    { 
        erase(begin()); 
    }

void NodeList::eraseBack()          // remove last
    { 
        erase(--end()); 
    }