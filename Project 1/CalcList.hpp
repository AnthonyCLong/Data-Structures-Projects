#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"

struct Node
{
	std::string sign;
	double op;
	double oldTotal;
	double endTotal;
	Node* next;
	Node* prev;
};

class CalcList:public CalcListInterface {
public:
	virtual double total() const override;
	virtual void newOperation(const FUNCTIONS func, const double operand) override;
	virtual void removeLastOperation() override;
	virtual std::string toString(unsigned short precision) const override;
	~CalcList();

private:
	Node* tail = nullptr;
	Node* head = nullptr;
	double finalTotal = 0;
	int opcount = 0;
};

#endif