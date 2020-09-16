//
//  Graph.hpp
//  
//
//  Created by Parker Barton on 11/18/19.
//

#ifndef Graph_hpp
#define Graph_hpp
#include "GraphBase.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::pair;
using std::vector;

class Vertex {
public:
    string label;
    vector<pair<Vertex *, unsigned long>> adjacent;
    Vertex(string l){ this->label = l;};
};

class Graph : GraphBase {
private:
    std::map<string, Vertex*> lookup;
public:
    ~Graph(){
        for(auto i : lookup)
            delete i.second;
        lookup.clear();
    }
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    int findSoultion(std::map<string, unsigned long> dist, string n, std::map<string, string> parent, vector<std::string> &path);
    void printPath(std::map<string, string> parent, string j, vector<std::string> &path);
};

#endif /* Graph_hpp */
