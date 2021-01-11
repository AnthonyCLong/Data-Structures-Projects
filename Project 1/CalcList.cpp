	#include "CalcList.hpp"
    #include <sstream>
    #include <iomanip>

double CalcList::total() const
{
    //returns total of operations
    return finalTotal;
}



void CalcList::newOperation(const FUNCTIONS func, const double operand)
{

    Node *temp = new Node();
    temp->next=nullptr;
    temp->prev=nullptr;
    //the operand of this operation
    temp->op=operand;
    //the total this op starts with
    temp->oldTotal=finalTotal;
    
    //if the lsit is empty, the head and tail are the now 1 node
    if(head==nullptr)
    {
        head=temp;
        tail=temp;
    }
    
    //otherwise, the tail is updated to the last node
    else
    {
        temp->prev=tail;
        tail->next=temp;
        tail=temp;
    }

    //switch for actual calculation and the sign string for tostring function
    switch(func)
    {
        case ADDITION:
            temp->sign= "+";
            finalTotal=(finalTotal + operand);
            break;

        case SUBTRACTION:
            temp->sign= "-";  
            finalTotal=(finalTotal - operand);
            break;

        case MULTIPLICATION:
            temp->sign= "*";
            finalTotal=(finalTotal * operand);
            break;

        case DIVISION:
            temp->sign= "/";
            //throw for division by 0
            if(operand==0)
            {throw std::runtime_error ("cannot divide by zero");}
            finalTotal=(finalTotal / operand);
            break;
    }

    //incriment the number of operations
    opcount++;
    //total at the end of this operation
    temp->endTotal=finalTotal;

}



void CalcList::removeLastOperation()
{
    //throw for trying to remove an op from an empty list
    if(opcount==0)
        {
            throw std::runtime_error ("cannot remove from an empty list");\
        }

    if(head==tail)
    {
        //if theres only 1 node, head and tail to null
        Node* temp = tail;
        //reset total to 0
        finalTotal=0;
        //clear head and tail
        head=tail=nullptr;
        //delete the node
        delete temp;
        //decrement the number of opertions
        opcount--;

    }
    
    //more than 1 node, delete the last node
    else
    {
        Node* temp = tail;
        //revert to the total of the previous node
        finalTotal=tail->oldTotal;
        tail = tail->prev;
        delete temp;
        opcount--;
    }
}



std::string CalcList::toString(unsigned short precision) const
{

    //for call with an empty list
    if(head == nullptr)
    return " ";

    //start from the last node
    Node* temp = tail;
    //string for output
    std::string out;
    //stream for converting numbers and strings to strings
    std::ostringstream stream;
    //set precision to passes precision
    stream<<std::setprecision(precision)<<std::fixed;
    int i=opcount;

    while(i!=0)
    {
        stream << i<<": "<< temp->oldTotal <<temp->sign <<temp->op << "=" << temp->endTotal << "\n";
        temp = temp->prev;
        i--;
    }

    //convert the stream to a string and store it in out, for return
    out = stream.str();
    return out;
}



CalcList::~CalcList()
{
    
    while(opcount>0)
    {
        removeLastOperation();
    }

}