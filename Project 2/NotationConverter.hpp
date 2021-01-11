#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <string>
#include "NotationConverterInterface.hpp"

struct Node
{
	std::string val;
	Node* next=nullptr;
	Node* prev=nullptr;
};

class NotationConverter: public NotationConverterInterface
{
public:
  virtual std::string postfixToInfix(std::string inStr) override;
  virtual std::string postfixToPrefix(std::string inStr) override;

  virtual std::string infixToPostfix(std::string inStr) override;
  virtual std::string infixToPrefix(std::string inStr) override;

  virtual std::string prefixToInfix(std::string inStr) override;
  virtual std::string prefixToPostfix(std::string inStr) override;

    void pushTop(std::string c); 
    void pushBottom(std::string c); 
    void popTop(); 
    void popBottom();
    bool isOperator(char x);
    bool isValid(std::string inStr);
	std::string getTop(); 
    std::string getBottom();
    std::string removewhite(std::string inStr);
    ~NotationConverter();



private:
	Node* top = nullptr;
	Node* bottom = nullptr;
};

#endif
