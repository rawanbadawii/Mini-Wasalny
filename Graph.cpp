
#include"Graph.h"
#include <iostream>
#include <set>
#include <queue>
using namespace std;

// constructor sets the graph as: -
//      true -> undirected
//      false -> directed
Graph::Graph(bool bi , int numOfNodes) {

    this->bi = bi;
    this->numOfNodes = numOfNodes;
}

//addes {destination} as an adjacent node of {current} with {weight} .... building the graph
void Graph::addEdge(string current, string destination, int weight)
{
    // if directed add from src to dest
    graph[current].insert(make_pair(destination, weight));

    // if undirected also add from dest to src
    if (bi == true)
    {
        graph[destination].insert(make_pair(current, weight));
    }
}

// removes {node} from the graph and all adj lists of other nodes
void Graph::removeNode(string node)
{
    // removes {node} from the graph
    graph.erase(node);

    // checks adjacents of all other nodes 
    //to remove the edges connected to this node??
    for (auto i = graph.begin(); i != graph.end(); i++) {

        // if {node} was found as adjacent
        if (graph[i->first].find(node) != graph[i->first].end()) {

            //remove it
            graph[i->first].erase(node);
        }
    }


}

// addes {node} with its {adj} into the graph
//map adj -> destination as key and the weight as value
void Graph::addNode(string node, map<string, int> adj)
{
    // if directed add {node} and connections from {node} to other nodes
    graph.insert({ node, adj });

    // if undirected also add connection to {node} from other nodes
    if (bi) {

        for (auto i = adj.begin(); i != adj.end(); i++) {
            // hyda5al adj.first(i->first) as current loacetion w el node as destination w el adj.second(i->second) as weight
            addEdge(i->first, node, i->second );
        }

    }
}

// updates weight between {start} and {end} as {newWeight}
void Graph::updateWeight(string start, string end, int newWeight)
{
    // if directed update weight from {start} to {end} 
    //graph[start].at(end) = newWeight;
    graph[start][end] = newWeight;

    // if undirected also update weight from {end} to {start} 3ashan yeb2a nafs el weight raye7 gai
    if (bi) {

        //graph[end].at(start) = newWeight;
        graph[end][start] = newWeight;
    }
}


// dijkstra 
int Graph::shortestPath(string src, string dest)
{

    map<string, int> distance;//string->nodes ... int->weight
    set<string> visited; //visited nodes

    queue<string> q;//??

    //putting all the distances of all the nodes be infinity
    for (auto i = graph.begin(); i != graph.end(); i++) {
        distance.insert({ i->first, INT32_MAX }); //INTMAX_32??..infinity
        q.push(i->first); //i->first el hya el current location...hane3ml push le kol el nodes
        if (bi==false)
        {
            if (distance.find(dest) == distance.end())
            {
                //cout << endl<<"in"<<endl;
                distance.insert({ dest, INT32_MAX });
                q.push(dest);
            }
        }
    }
   
    distance[src] = 0; //7ateina el distance beta3et el node el e7na 3andaha be 0

    while (!q.empty())
    {
        
        string min = findMin(distance, visited); //findMin dy function fel graph class betraga3 esm el node el 3andaha el min path
        //cout << "min is " << min << endl;
        visited.insert(min); // inserts the name of the node with the min distance 3ashan teb2a marked as visited

        for (auto j = graph[min].begin(); j != graph[min].end(); j++) {
            // el condition : hwa wa2ef 3and node mo3ayena w bykaren bein el weights ely ma benha w mabein el adjacent nodes
            if ((distance[min] + j->second) < distance[j->first]) {
                distance[j->first] = (distance[min] + j->second);
                parents[j->first] = min; //hyb2a fyha kol el parents el leehom weights so8ayara??//
            }
        }
        //cout << q.front() << " ";
        q.pop();
    }

    printshortestPath(src, dest);

    return distance[dest];
}

// displays the graph as an adjacency list
void Graph::display()
{
    // loop over every node in the graph
    for (auto i = graph.begin(); i != graph.end(); i++) {

        // print current node
        cout << "start point : " << i->first << endl;

        // loop over its adjacents and print them
        for (auto j = graph[i->first].begin(); j != graph[i->first].end(); j++) {
            cout << "\t\t=> " << j->first << ", distance : " << j->second << endl;
        }

        // 5at lzoom el sheaka
        cout << endl << "=============================" << endl << endl;
    }
}

// finds node with min distance (and not visited) and returns it
string Graph::findMin(map<string, int> distance, set<string> visited)
{
    int minVal = INT32_MAX;
    string minStr = "";

    // loop over all distances
    for (auto i = distance.begin(); i != distance.end(); i++)
    {
       // cout << "inloop"<<endl;
        // if you find a value with lower disatnce that is not visited before
        if (i->second < minVal && visited.find(i->first) == visited.end()) {
            // save it
            //cout << "it works?" << endl;
            minVal = i->second; //the smallest weight
            minStr = i->first; // the node of smallest weight(path)
        }
    }
    // return name of node with min distance 
    return minStr;
}

// prints the shortest path as a string
void Graph::printshortestPath(string src, string dest)
{
    // if map of parents is empty
    // there is no path to print
    if (parents.size() == 0) {
        return;
    }
    else {

        // this function starts from the dest and backtrakes to the source
        // we set the start point as the dest

        string startPoint = dest;

        // this will be our final output string
        string output = "";

        // we stop when we reach a node with no parent 
        // aka the src
        while (parents.find(startPoint) != parents.end()) {

            // we insert the current node at the beginning of the string 
            output.insert(0, " => " + startPoint);

            // then we update the start point to be the parent of the current node
            // aka going one step up form dest to src
            startPoint = parents[startPoint];

        }

        // we insert the src as it is not inserted in the while loop
        output.insert(0, startPoint);

        // and print the output string
        cout << "shortest path between " + src + " and " + dest + " is : " << output << endl << endl;

    }



}