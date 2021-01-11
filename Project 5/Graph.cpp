#include "Graph.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <climits>

void Graph::addVertex(std::string label)
    {
        //edge is an empty map of destination verticies and weights
        edge ed;
        if (verticies.find(label)==verticies.end())
        verticies.insert(std::pair<std::string, edge>(label, ed));
        else {throw std::runtime_error ("Error: vertex already exists");}
    }

void Graph::removeVertex(std::string label)
    {
        //erase the vertex specified and all of its edges, and any egdes with the vertex as one of the points on the edge
        verticies.erase(label);
        for(auto it = verticies.begin(); it!=verticies.end(); it++)
        {
            auto it2 = it->second.find(label);
            if(it2!=it->second.end())
            removeEdge(it->first,it2->first);
        }   
        
    }

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
        if(label1==label2)
        {throw std::runtime_error ("Error: cannot add edge to same vertex");}

        if(verticies.find(label1)==verticies.end()||verticies.find(label2)==verticies.end())
            {throw std::runtime_error ("Error: both verticies do not exist");}

        if(verticies.find(label1)->second.find(label2)!=verticies.find(label1)->second.end())
            {throw std::runtime_error ("Error: Edge already exists");}
    
    //adds an edge with 2 verticies, one to the 1st vertex and one to the 2nd 
    auto it = verticies.find(label1);  
    it->second.insert(std::pair<std::string, unsigned long >(label2, weight));

    it = verticies.find(label2);
   it->second.insert(std::pair<std::string, unsigned long >(label1, weight));
    
}

void Graph::removeEdge(std::string label1, std::string label2)
    {        
        //removes an edge from 2 verticies, one tht starts with label 1 and one that starts with label 2
        auto it = verticies.find(label1);
        if(it!=verticies.end())
        it->second.erase(label2);
        
        it = verticies.find(label2);
        if(it!=verticies.end())
        it->second.erase(label1);
    }

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
    {
        //"infinity"
        unsigned long inf = ULONG_MAX;
        //keeps track of each vertex and the node that gets you to it with the shortest weight
        std::map<std::string, std::string> previous;
        //each vertex and its length from the starting point
        std::map<std::string, unsigned long> pweight;
        //hold the vertex to reset at the end of the method
        vertex ver = verticies;
        
        //fill all verticies' weights with infinity, and all previous nodes with null
        for(auto i: verticies)
        {
            pweight.insert(std::pair <std::string, unsigned long> (i.first,inf));
            previous.insert(std::pair<std::string, std::string>(i.first,"\0"));
        }
        
        //distance from start is 0
        pweight.at(startLabel)=0;
        auto it = verticies.find(startLabel);
        
        //while we havent visited every node
        while (verticies.size()!=0)
        {
            std::string current = it->first;
            
            //if the distance from current node + the edge to the compared vertex is less than the current vertex value,
            //then set the node to this
            for(auto i: it->second)
            {
                if((pweight.at(it->first) + (i.second))<(pweight.at(i.first)))
                {
                    pweight.at(i.first)=pweight.at(it->first) + (i.second);
                    previous.at(i.first) = (current);
                }

            }
            //"add" vertex to visited list    
            removeVertex(current);
            
            //select the next-lowest-unvisited node
            unsigned long shortest = inf;
            for(auto i: verticies)
            {
                if((pweight.at(i.first))<shortest)
                {
                    it = verticies.find(i.first);
                    shortest = pweight.at(i.first);
                            
                }
            }
        }
        
        //add the ending point to the path
        path.push_back(endLabel);
        auto i = endLabel;
        //go through the previous node map, selecting each nodes shortest path from the start point 
        //by means of the node beofre it, until you return to the starting point
        while(i != startLabel)
        {    
            i = previous.at(i);
            path.insert(path.begin(),i);
        }
        
        //reset the graph and return the length from the end point thats the shortest path
        verticies = ver;
        return pweight.at(endLabel);
    }

Graph::~Graph()
{
    //uses removeVertex in order to delete graph 
    auto it = verticies.begin();
    while(!verticies.empty())
    {
        removeVertex(it->first);
        it = verticies.begin();
    }
}
