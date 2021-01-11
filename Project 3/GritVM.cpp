#include <fstream>
#include <iostream>
#include "GritVM.hpp"

    GritVM::GritVM()
    :machineStatus(WAITING), accumulator(0) {}

    
    //does the actual accumulator or dataMem maths, mostly returns 1 unless its a jump
    long GritVM::evaluate(Instruction ins)
    {
        switch (ins.operation) 
            {
                case CLEAR:    
                    accumulator=0; 
                    return 1;
                    break;
                
                case AT:        
                    accumulator=dataMem.at(ins.argument);
                    return 1;
                    break;
                
                case SET:       
                    dataMem.at(ins.argument)=accumulator;
                    return 1;
                    break;
                
                case INSERT:    
                    dataMem.insert(ins.argument, accumulator);
                    return 1;
                    break;
                    
                case ERASE:     
                    dataMem.erase(ins.argument);
                    return 1;
                    break;
                case ADDCONST: 
                    accumulator = accumulator + ins.argument;
                    return 1;
                    break;

                case SUBCONST:  
                    accumulator = accumulator - ins.argument;
                    return 1;
                    break;

                case MULCONST:  
                    accumulator = accumulator * ins.argument;
                    return 1;
                    break;

                case DIVCONST:  
                    accumulator = accumulator / ins.argument;
                    return 1;
                    break;

                case ADDMEM:    
                    accumulator = accumulator + dataMem.at(ins.argument);
                    return 1;
                    break;

                case SUBMEM:    
                    accumulator = accumulator - dataMem.at(ins.argument);
                    return 1;
                    break;

                case MULMEM:    
                    accumulator = accumulator * dataMem.at(ins.argument);
                    return 1;
                    break;

                case DIVMEM:    
                    accumulator = accumulator / dataMem.at(ins.argument);
                    return 1;
                    break;

                case JUMPREL:   
                    return ins.argument;
                    break;

                case JUMPZERO:  
                    if(accumulator==0)
                        return ins.argument;
                    else return 1;                    
                    break;

                case JUMPNZERO: 
                    if(accumulator!=0)
                        return ins.argument;
                    else return 1;
                    break;
                    
                case NOOP:      
                    return 1;
                    break;

                case HALT:      
                    machineStatus=HALTED;
                    return 1;
                    break;

                case OUTPUT: 
                    std::cout << accumulator << std::endl;   
                    return 1;
                    break;

                case CHECKMEM:  
                    if(dataMem.size()<ins.argument)
                    machineStatus = ERRORED;
                    return 1;
                    break;
                default:        
                    return 0;
            }
    }
    
    //moves instruction iterator, if jump dis is negative, moves it backward
    void GritVM::advance(long jumpdis)
    { 
            int i = jumpdis;
            while(i!=0)
                {
                    if(i<0)
                        {
                            --currentInstruct;
                            i++;
                        }
                    else 
                        {
                            ++currentInstruct;
                            i--;
                        }
                }
    }

//loads file
STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory)
    {
        //bool printData = true;
        //bool printInstruction = true;
        //printVM( printData,printInstruction);
        //if status is anyhting other than waiting, return that
        if(machineStatus!=WAITING)
            {
                return machineStatus;   
            }
        else
            {   
                std::ifstream file;
                file.open (filename);
                std::string line;

                if (file.is_open())
                    {
                        while (getline (file, line, '\n'))
                        {
                            if (!line.empty()&&line.at(0)!='#')
                                {
                                    //open file, get all lines and use helper method to read in instruction
                                    Instruction curr = GVMHelper::parseInstruction(line);
                                    //if instruction is unrecognized
                                    if(curr.operation==UNKNOWN_INSTRUCTION)
                                        {
                                            machineStatus = ERRORED;
                                            return machineStatus;
                                        }
                                    //otherwise, add it to the instruction set
                                    else 
                                        instructMem.insertBack(curr);
                                }
                        }
                        file.close();
                        //initialize memory
                        dataMem = initialMemory;
                        //if there are no instructions, set status to waiting, otherwise, ready to run the instructions
                        if(instructMem.size()==0)
                            machineStatus=WAITING;
                        else
                          machineStatus=READY;  
                    }

                //if file could not be opened
                else throw std::runtime_error ("Could not open file");
            }
            //printVM(true, true);
            
            return machineStatus;

    }

STATUS GritVM::run()
    {
        //bool printData = true;
        //bool printInstruction = true;
        //printVM( printData,printInstruction);
        //  if we're ready to get instructions, set status to running, 
        //  iterator to the beginning of the instruction list, and enter the while loop
        if(machineStatus==READY)
            {
                machineStatus =RUNNING;
                currentInstruct=instructMem.begin();
            }
        
        while(machineStatus == RUNNING) 
            {       
                // Evaluate the current instruction
                long jumpDistance = evaluate(*currentInstruct);
                // Advance the current instruction based on the last evaluation
                advance(jumpDistance);
                
                //if we get to the end of instructions, status to HALTED
                if(currentInstruct==instructMem.end())
                    machineStatus=HALTED;
            } 
            //otherwise, return final status of program, which should still be HALTED
            //printVM(true, true);
            return machineStatus;
            
    }

std::vector<long> GritVM::getDataMem()
    {
        //just returns dataMem
        std::vector<long> temp;
        for(int i =0; i< dataMem.size(); i++)
            temp.push_back(dataMem.at(i));
        return temp;
    }

STATUS GritVM::reset()
    {
        //status to WAITING, AC to 0, and clear dataMem/instructMem
        machineStatus=WAITING;
        accumulator=0;
        dataMem.clear();

        while(!instructMem.empty())
            {
                instructMem.eraseBack();
            }
        
        return machineStatus;
    }

//destructor, uses reset method
GritVM::~GritVM()
    {
       reset();
    }

   //printer function given from instructions
   void GritVM::printVM(bool printData, bool printInstruction) 
   {
        std::cout << "****** Output Dump ******" << std::endl;
        std::cout << "Status: " <<
                GVMHelper::statusToString(machineStatus) << std::endl;
        std::cout << "Accumulator: " << accumulator << std::endl; 
        
        if (printData) 
        {
            std::cout << "*** Data Memory ***" << std::endl;
            int index = 0;
            //std::vector<long>::iterator it = dataMem.begin();
            int mover = 0;
            
            while(mover != dataMem.size())
            {
                long item = dataMem.at(mover);
                std::cout << "Location " << index++ << ": " << item << std::endl;
                mover++;
            }
        }
        
        if (printInstruction) 
        {
            std::cout << "*** Instruction Memory ***" << std::endl;
            int index = 0;
            NodeList::Iterator it = instructMem.begin();
            
            while(it != instructMem.end()) 
            {
                Instruction item = (*it);
                std::cout << "Instruction " <<
                index++ << ": " <<
                GVMHelper::instructionToString(item.operation) <<
                " " << item.argument << std::endl;
                ++it;
            }
        }
    }
