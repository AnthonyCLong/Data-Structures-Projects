#include "HuffmanTree.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <stack> 


void HuffmanTree::createCharTable(HuffmanNode* root, std::string str, std::map<char, std::string> *charMap)   
  { 
    // keep going left if we can 
    if (root->left) 
      {
        createCharTable(root->left, str+"0", charMap);
      }  
    
    // keep going right if we can 
    if (root->right)
      {
        createCharTable(root->right, str+"1", charMap); 
        //if we're on a right node and we finish, visit the node--this is for SERIALIZED TREE
        serializedTree+="B";
      } 
      
    if (root->isLeaf()) 
      { 
        //if we get to a leaf, then we show we are at a node, along with what is at that node--this is for SERIALIZED TREE
        serializedTree+="L";
        serializedTree+=root->getCharacter();
        charMap->insert(std::pair<char,std::string>(root->getCharacter(),str) ); 
      } 
  } 


std::string HuffmanTree::compress(const std::string inputStr)
  {
    std::map<char, int> frequencyMap;
    //go through string, adding a char to the map, and incrimenting appropiately
    for(size_t i = 0; i < inputStr.size(); i++)
      {
        if (frequencyMap.find(inputStr.at(i)) == frequencyMap.end())
          {
            frequencyMap.insert ( std::pair<char,int>(inputStr.at(i),1) );
          }
        
        else
          frequencyMap[inputStr.at(i)]=frequencyMap[inputStr.at(i)]+1;
      }
    //using the map, create huffman nodes with their freq/char
    for (auto it=frequencyMap.begin(); it!=frequencyMap.end(); ++it)
      {
        HuffmanNode* temp =new HuffmanNode(it->first, it->second);
        HQ.insert(temp);
      }

    HuffmanNode *left, *right;
    //take the 2 min nodes, make them left and right of a new frequency only node, push it back to the stack
    while(HQ.size()!=1)
    {
      left = HQ.min();
      HQ.removeMin();
      
      right = HQ.min();
      HQ.removeMin();
      
      int topFreq = left->getFrequency() + right->getFrequency();
      HuffmanNode* top = new HuffmanNode('\0', topFreq, nullptr, left, right);
      
      HQ.insert(top);
    }
    
    std::string str,strout;
    
    //new map with char and its uniquie prefix code
    std::map<char, std::string> *charMap = new std::map<char, std::string>;
    createCharTable(HQ.min(), str, charMap);

    //compose the new, compressed string with the char/binary map
    for(unsigned int i = 0; i<inputStr.size(); i++)
      {
        strout+=(charMap->at(inputStr.at(i)));
      }
    
    return strout;
  }


std::string HuffmanTree::serializeTree() const
  {
    //just retrun what we stored from the creation of the char table
    return serializedTree;
  }


std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree)
  {
    //string to manipulate the serializedTree
    std::string str =serializedTree;
    std::string::iterator it = str.begin();
    //stack of huffmannodes to create the tree
    std::stack <HuffmanNode*> stk; 

    //creation of tree from the serialized tree string
    while(it!=str.end())
      {
        if(*it=='L')
          {
            stk.push(new HuffmanNode(*(++it), 0));
            it++;
          }

        if(*it=='B')
          {
            HuffmanNode* right = stk.top();
            stk.pop();
            
            HuffmanNode* left = stk.top();
            stk.pop();
            
            stk.push(new HuffmanNode('\0', 0, nullptr, left, right));
            it++;
          }
      }

    //map for the character using the character's variable length binary representations as the key
    std::map<char, std::string> *charMap = new std::map<char, std::string>;
    std::map<std::string, char> binaryMap;
    str = "";
    //created with our createCharTable function
    createCharTable(stk.top(), str, charMap);
          
    for (auto it=charMap->begin(); it != charMap->end(); ++it)
      {
        binaryMap.insert ( std::pair<std::string, char>(it->second,it->first) );
      }  
    
    //str to manipulate the inputCode, and one for the return 
    str = inputCode;
    std::string strout;
    int i = 1;
    
    /*because the binary representations are unique, once we dectect one from our map, 
    we can cut that part of the string out and keep doing that with a while loop until 
    we have completly converted the input string back into readable text*/
    while(str.size()>0)
    {
      if (binaryMap.find(str.substr(0,i))==binaryMap.end()) 
        {
          i++;
        }
        
        else
        {
          strout+=binaryMap[str.substr(0,i)];
          str = str.substr(i);
          i = 1;
        }
        
      }

    return strout;
  }

  HuffmanTree::~HuffmanTree()
  {
    while (!HQ.empty())
      {HQ.removeMin();}
  }
