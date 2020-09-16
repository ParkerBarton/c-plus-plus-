//
//  Graph.cpp
//  
//
//  Created by Parker Barton on 11/18/19.
//

#include "Graph.hpp"
#include <queue>
#include <iostream>

using namespace std;

void Graph::printPath(map<string, string> parent, string j, vector<std::string> &path){ //utility  function to  get path string
    if (parent[j]== "")
        return;
    
    printPath(parent, parent[j], path);
    path.push_back(j);
}

void Graph::addVertex(std::string label){
    if(lookup.empty()){ // if graph is empty, create  new vertex  and add it tot  the graph
        Vertex *v = new Vertex(label);
        lookup.insert(make_pair(label, v));
    }
    else if (lookup.find(label) == lookup.end()){ // if the label doesn not alredy exist in the graph then add it
        Vertex *v = new Vertex(label);
        lookup.insert(make_pair(label, v));
    }
    else{
        cout << "/nThat vertex is already in the graph./n";
    }
}
void Graph::removeVertex(std::string label){
    if(lookup.find(label) == lookup.end())
        return;
    lookup.erase(lookup.find(label));
}
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    Vertex *t1 = nullptr;
    Vertex *t2 = nullptr;
    if(label1 != label2){
        if(lookup.find(label1) != lookup.end()){
            if(lookup.find(label2)!= lookup.end()){ // checks if the verticies exist in  the  graph
                t1 = lookup[label1];
                t2 = lookup[label2];
                for (auto i : t1->adjacent) { // checks if an edge between the  two verticies alreay  existes
                    if(i.first == t2){
                        cout << "/nThat  edge already exists./n";
                        }
                }
                for (auto i : t2->adjacent) {
                    if(i.first == t1){
                        cout << "/nThat  edge already exists./n";
                        }
                }
            }
            }
        
        }
    
    t1->adjacent.push_back(make_pair(t2, weight)); // adds the verticies in the  list
    t2->adjacent.push_back(make_pair(t1, weight));
}
void Graph::removeEdge(std::string label1, std::string label2){
   int count = 0;
    for(auto i : lookup){
        count = 0;
        if(i.first == label1){ // find  first vertex
            for(auto p : i.second->adjacent){
                count++; // counter to identify  second vertex
                if(p.first->label == label2){ // find second vertex
                    i.second->adjacent.erase(i.second->adjacent.begin()+count);
                }
            }
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    typedef pair<unsigned long, Vertex*> Pair;
    priority_queue <Pair, vector<Pair>, greater<Pair> > q;
    map<string, unsigned long> dist; // map of distances mapped to the corresponding label
    
    map<string, string> paths;
    paths[startLabel] = "";
    
    for(auto i : lookup)
        dist.insert(make_pair(i.first, 0x3f3f3f3f)); //initialize to infinity for all verticies
    q.push(make_pair(0, lookup[startLabel]));
    dist[startLabel] = 0;
    
    while (!q.empty()) {
        Vertex* v = q.top().second;
        q.pop();
        
        for(auto i : v->adjacent){ // check all verticies connected
            Vertex* temp = i.first;
            unsigned long w = i.second; // get weight of all edges
            if (dist[temp->label] > dist[v->label] + w)
            {
                dist[temp->label] = dist[v->label] + w;
                paths[temp->label] = v->label;
                q.push(make_pair(dist[temp->label], temp));
            }
        }
    }
    path.push_back(startLabel);

    findSoultion(dist, endLabel, paths, path); // call function to find path string
    return dist[endLabel];
}

int Graph::findSoultion(map<string, unsigned long> dist, string n, map<string, string> parent, vector<std::string> &path){
    printPath(parent, n, path);
    return dist[n];
}

