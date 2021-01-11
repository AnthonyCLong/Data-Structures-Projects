#ifndef GRITVM_H
#define GRITVM_H

#include <iostream>
#include <string>
#include <list>
#include "GritVMBase.hpp" 
#include "ListADT.hpp" 
#include "VectorADT.hpp" 

class  GritVM: public GritVMInterface
{
    public:
        virtual STATUS              load(const std::string filename, const std::vector<long> &initialMemory) override;
        virtual STATUS              run() override;
        virtual std::vector<long>   getDataMem() override;
        virtual STATUS              reset() override;
        GritVM();
        ~GritVM();
        void printVM(bool printData, bool printInstruction);



    private:
        long evaluate(Instruction);
        void advance(long);

        ArrayVector dataMem;
        NodeList instructMem;
        NodeList::Iterator currentInstruct;
        STATUS machineStatus;
        long accumulator; 
};

#endif
