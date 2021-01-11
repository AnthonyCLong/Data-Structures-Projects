#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"



class HuffmanTree: public HuffmanTreeBase 
{
  public:
    virtual std::string compress(const std::string inputStr) override;
    virtual std::string serializeTree() const override;
    virtual std::string decompress(const std::string inputCode, const std::string serializedTree) override;
    void createCharTable(HuffmanNode* root, std::string str, std::map<char, std::string> *charMap);
    ~HuffmanTree();
    
  private:
  std::string serializedTree;
  HeapQueue <HuffmanNode*, HuffmanNode::Compare> HQ;
};

#endif