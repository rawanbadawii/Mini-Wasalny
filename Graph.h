#include <string>
#include <unordered_map>
#include<map>
#include<set>
using namespace std;
class Graph
{
private:
    // map of every node and its parent
    map<string, string> parents; //parent->el node el abl el e7na wa2feen 3andaha(back tracking to print the path)

    // finds node with min distance (and not visited) and returns it
    string findMin(map<string, int> distance, set<string> visited);

    // prints the shortest path as a string
    

public:
    // the graph
    // the first string is the node name
    // the map is the list of adjacent nodes with the weight
    unordered_map<string, map<string, int>> graph;

    // if the graph is undirected this is set to true
    // this variable takes a value in the constructor
    bool bi;
    int numOfNodes;

    // constructor
    Graph(bool , int);

    // adds a new connection between nodes(builds the graph)
    void addEdge(string current, string destination, int weight);

    void printshortestPath(string src, string dest);

    // takes a node and removes it from the graph
    void removeNode(string node);

    // adds a node into the graph 
    // takes the node and a map of its adjacent nodes
    void addNode(string node, map<string, int>);

    // updates weight of an edge between 2 nodes
    void updateWeight(string start, string end, int newWeight);

    // dijkstra
    int shortestPath(string src, string dest);

    // displays the graph as an adjacency list
    void display();




  


};