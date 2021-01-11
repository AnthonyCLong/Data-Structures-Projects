	#include "NotationConverter.hpp"
    #include <iomanip>
    #include <algorithm>
    #include <cstring>

    //checks if input is valid, which is when all characters are letters, operands, spaces or parentheses
    bool NotationConverter::isValid(std::string inStr)
        {
            unsigned int i=0; 
            while (i<inStr.size())
            {
                if (!isalpha(inStr[i])&&!isOperator(inStr[i])&&inStr[i]!=' '&&inStr[i]!='('&&inStr[i]!=')')
                {return false;}
                i++;
            }
            return true;
        }

    //removes whitespace from strings
    std::string NotationConverter::removewhite(std::string inStr)
        {
            unsigned int i=0;
            while(i<inStr.size())
            {
                if(inStr[i]==' ')
                {
                    inStr.erase(i,1);
                    i--;
                }
                i++;
            }
            return inStr;
        }

    //checks if a function is an operator
    bool NotationConverter::isOperator(char x) 
        { 
            switch (x) 
            { 
                case '+': 
                case '-': 
                case '/': 
                case '*': 
                return true; 
            } 
        
            return false; 
        } 

    //adds to the top, conditional for if the list has no nodes
    void NotationConverter::pushTop(std::string c) 
        {
            Node* temp = new Node;
            temp->val=c;
            if (top == nullptr) 
                bottom = top = temp; 
     
            else 
            { 
                temp->next = top; 
                top->prev = temp; 
                top = temp; 
            } 
        }
    
    //add to the bottom, smae as the top, but the bottom
    void NotationConverter::pushBottom(std::string c)
        {
            Node* temp = new Node;
            temp->val=c;
            
            if (bottom == nullptr) 
                top = bottom = temp; 
    
            // Inserts node at the bottom end 
            else 
            { 
                temp->prev = bottom; 
                bottom->next = temp; 
                bottom = temp; 
            } 
        }
    
    //removes top node, conditional for the last element vs multiple
    void NotationConverter::popTop()
        {
            if (top==nullptr) 
                {throw std::runtime_error ("empty deque");} 
     
            else 
            { 
                Node* temp = top; 
                top = top->next; 
         
                if (top == nullptr) 
                    bottom = nullptr; 
                else
                    top->prev = nullptr; 
                delete(temp);
            }
        }
   
   //removes from the bottom, smae as the top, but the bottom
    void NotationConverter::popBottom()
        {
            if (top==nullptr) 
            {throw std::runtime_error ("empty deque");} 
    
            else 
            { 
                Node* temp = bottom; 
                bottom = bottom->prev; 
        
                if (bottom == nullptr) 
                    top = nullptr; 
                else
                    bottom->next = nullptr; 
                delete(temp); 
            }
        }

    //returns top
    std::string NotationConverter::getTop() 
        {
            if (top==nullptr) 
            {throw std::runtime_error ("empty deque");}  
        
            return top->val; 
        }

    //returns bottom
    std::string NotationConverter::getBottom()  
        {
            if (top==nullptr) 
            {throw std::runtime_error ("empty deque");} 
        
            return bottom->val; 
        }
//===========================================================================================================
  std::string NotationConverter::postfixToInfix(std::string inStr)
    {
        //checks string's validity
        if(!isValid(inStr))
        {throw std::runtime_error ("invalid characters");}

        //remove whitespace
        std::string temp= removewhite(inStr);

        for (unsigned int i = 0; i<temp.size(); i++) 
            { 
                std::string hold(1, temp[i]); 
                pushTop(hold); 
                
                //when we find an operator, rearrange the operands and operator, and push it back onto the deque
                if (isOperator(temp[i])) 
                    { 
                        std::string op1 = getTop(); 
                        popTop(); 
                        std::string op2 = getTop();
                        popTop();  
                        std::string op3 = getTop();
                        popTop(); 
                        pushTop("(" + op3 +" "+ op1 +" "+ op2 + ")"); 
                    } 
                                    
            } 
        
            //returns our one string that is the required notation, and pops the deque
            std::string ret=getTop();
            popTop();
            return ret;
    } 

  std::string NotationConverter::infixToPrefix(std::string inStr)
    {
        //checks string's validity
        if(!isValid(inStr))
        {throw std::runtime_error ("invalid characters");}

        //remove whitespace
        std::string temp= removewhite(inStr);

        for (unsigned int i=0; i<temp.size(); i++) 
            { 
                std::string hold(1, temp[i]);
                pushBottom(hold); 
                     
                //when we get to the end of a quantity
                if (getBottom()==")") 
                    { 
                        //pop the '('
                        popBottom();
                            
                        //get the first var and pop
                        std::string op1=getBottom();  
                        popBottom();

                        //get sign and pop
                        std::string op2=getBottom();
                        popBottom();

                        //thrid var, pop, and pop the opening '('
                        std::string op3=getBottom();
                        popBottom();
                        popBottom();

                        //push the quantity now fixed, back onto the stack
                        pushBottom(op2 +" "+ op3+" "+ op1); 
                    } 

            } 
        
        //returns our one string that is the required notation, and pops the deque    
        std::string ret=getTop();
        popTop();
        return ret;

    }

  std::string NotationConverter::prefixToPostfix(std::string inStr)
    {
        //checks string's validity
        if(!isValid(inStr))
        {throw std::runtime_error ("invalid characters");}

        //remove whitespace
        std::string temp= removewhite(inStr);

        for (int i = temp.size() - 1; i >= 0; i--) 
            { 
        
                std::string hold(1, temp[i]); 
                pushTop(hold);
                
                // when we find an operator 
                if (isOperator(temp[i])) 
                { 
                    // get the operator and operands and pop all of them from the deque 
                    std::string op1 = getTop(); 
                    popTop(); 
                    std::string op2 = getTop(); 
                    popTop(); 
                    std::string op3 = getTop(); 
                    popTop();
                
                    // rearrange the operator and operands, and push it back to the deque 
                    std::string hold = op2 +" "+ op3 +" "+ op1;  
                    pushTop(hold); 
                } 
            
            } 
  
        // stack contains only the Postfix expression 
        std::string ret=getTop();
        popTop();
        return ret;
  }
  
  //these 3 functions use the already defined functions to go convert to the required notation
  std::string NotationConverter::prefixToInfix(std::string inStr)
  {
      return postfixToInfix(prefixToPostfix(inStr));
  }
  
  std::string NotationConverter::postfixToPrefix(std::string inStr)

  {
      return infixToPrefix(postfixToInfix(inStr));
  }

  std::string NotationConverter::infixToPostfix(std::string inStr)
  {
      return prefixToPostfix(infixToPrefix(inStr));
  }

//destructor, takes advantage of pop function from deque
NotationConverter::~NotationConverter()
{
    while(top!=nullptr)
    {
        popTop();
    }
}
