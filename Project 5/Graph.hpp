#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <list>
#include <map>
#include <iostream>



typedef std::map<std::string,unsigned long > edge;
typedef std::map<std::string, edge> vertex;

class Graph: public GraphBase {
  public:
    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;
    ~Graph();
  
  private:
    vertex verticies;
};

#endif

//g++ -std=gnu++17 -Wall *.cpp