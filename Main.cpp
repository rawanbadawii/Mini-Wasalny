#include<iostream>
#include<unordered_map>
#include<fstream>
#include <string>
#include <vector>
#include <queue>
#include"Graph.h"
using namespace std;


//void EnterGraph(bool bi)
//{
//    bool flag = false;
//    int n = 0;
//    Graph g(flag);
//    string c, d;
//    string s, e;
//    int w = 0;
//    cout << "Enter the number of vertices :" << endl;
//    cin >> n;
//    cout << endl;
//    for (int i = 0; i < n; i++)
//    {
//        cout << "Enter the source : ";
//        cin >> c;
//        cout << "Enter the distenation : ";
//        cin >> d;
//        cout << "The distance between them is : ";
//        cin >> w;
//        g.addEdge(c, d, w);
//        cout << "----------------------------" << endl;
//    }
//}
//reads the data from the file and puts it in the graph
Graph LoadData(ifstream& read , string fileName , Graph& g)
{
    read.open(fileName);
    string curr , dest ,line;
    int w;
    string arr[2];
   
    cout << "ana hena"<<endl;
    //vector<string> savedData; //this will store the data of the file to be put in the graph later
    for(int i=0; i<3 ;i++)
    {
        cout << "da5alt"<<endl;
        getline(read, line);
        for (int i = 0; i < 3; i++)
        {
            cout << "in";
            if (i == 2)
            {
                arr[i] = line;
                w = stoi(arr[i]);
            }
            else
            {
                arr[i] = line;
                if (i == 0)
                    curr = arr[i];
                else
                    dest = arr[i];
            }
        }
        g.addEdge(curr, dest, w);
    }
    cout << endl << "ana 5alast" << endl;
    g.display();
    return g;
}





void saveData(Graph g , string file)
{
    ofstream changes;
    changes.open(file);
    for (auto i = g.graph.begin(); i != g.graph.end(); i++)
    {
        changes<< "start point : " << i->first << endl;

        for (auto j = g.graph[i->first].begin(); j != g.graph[i->first].end(); j++)
        {
            changes << "\t\t=> " << j->first << ", distance : " << j->second << endl;
        }
    }
    changes.close();

}

int main()
{
	////to create new file with each runtime.
    cout << "Welcome to mini wasalny app!!"<<endl<<"------------------------"<<endl;
    cout << "Would you like to load a saved file?" << endl << "if yes type 1 and if no type 0"<<endl;
    bool load_file_flag = 0;
    cin >> load_file_flag;
    cout << "-------------------------------" << endl;

if (load_file_flag == 1)
{
        cout << "please type the number of the saved file:"<<endl;

        unsigned int numFile;
        cin >> numFile; //then load the file

        ifstream ReadsavedFile;
        string savedFileName= "afile" + to_string(numFile) + ".txt";
        cout << "your file name is " << savedFileName << endl;
        cout << "if it is undirected type 1 and if it is directed type 0 " << endl;
        bool bi;
        cin >> bi;
        int num;
        cout << "enter the number of nodes:";
        cin >> num;
        Graph savedGraph(bi , num);

        savedGraph=LoadData(ReadsavedFile, savedFileName , savedGraph);
        savedGraph.display();
        //there are two options 
        //1-> read data 3alatool(yetala3 el shortest path) 
        //2-> update the data then read

        bool update_saved;
        cout << "would you like to update on or display your data?" << endl << "if yes type 1 and if no type 0:" << endl; //law 0 el loop hy break lwa7do
        cin >> update_saved;
        while (update_saved==1)
        {
            
            //(here) update data w ama ye5alas ye type 0 w el loop hy break
            int flag = 0;
            cout << "choose the number of your option:"<<endl<<" 1 - to add edge "<<endl<<"2 - to remove a node"<<endl<<"3 - add node"<<endl<<" 4 - update weight"<<endl<<"5 - to display the shortes path"<<endl;
            cin >> flag;
            switch (flag)
            {
            case 1:
            {
                string current, destination;
                int weight;
                cout << "enter the current location:" << endl;
                cin >> current;
                cout << "enter the destination:";
                cin >> destination;
                cout << "enter the distance between them:";
                cin >> weight;
                savedGraph.addEdge(current, destination, weight);
                break;
            }
            case 2:
            {
                string Deletnode;
                cout << "enter the name of the node you want to remove" << endl;
                cin >> Deletnode;
                savedGraph.removeNode(Deletnode);
                break;
            }
            case 3:
            {
                string node3, node4;
                int w;
                map<string, int> mp;
                cout << "Enter the node name:" << endl;
                cin >> node3;
                cout << "Enter the destination:" << endl;
                cin >> node4;
                cout << "Enter the weight:";
                cin >> w;
                mp.insert({ node4 , w });
                savedGraph.addNode(node3, mp);
                break;
            }
            case 4:
            {
                string start, end;
                int newWeight;
                cout << "Enter start node:" << endl;
                cin >> start;
                cout << "Enter end node:" << endl;
                cin >> end;
                cout << "Enter new weight:" << endl;
                cin >> newWeight;
                savedGraph.updateWeight(start, end, newWeight);
                break;
            }
            case 5:
            {
                /*string src, dest;
                cout << "enter the source:" << endl;
                cin >> src;
                cout << "enter the destination" << endl;
                cin >> dest;
                cout << "Shortest path:" << endl;
                savedGraph.printshortestPath(src, dest);*/
                savedGraph.display();

            }
            case 0: break;
            }
            if (flag == 0)
            {
                break;
            }
            //cout << "Would you like to continue editing? if yes type 1 else typ 0" << endl;
            //cin >> update_saved;

            //(here) ne5alyh yetala3 el shortest path w keda

            
            cout << "--------------------------" << endl;
        }
        // ba3d keda ...save changes?
        bool save = 0;
        cout << "would you like to save changes?" << "1->yes ... 0->no" << endl;
        cin >> save;
        if (save)
        {
            saveData(savedGraph, savedFileName);
        }
}
    
    
    //creating new file

else
{

    ifstream seqFileIn;
    ofstream seqFileOut;
    unsigned int fileSeq;
    seqFileIn.open("sequeceFile.txt", ios::in);//the file that saves the sequence of the files.
    if (seqFileIn.is_open())                  //el 7eta dy to save the number of the latest file
    {
        seqFileIn >> fileSeq;
        fileSeq++;
    }
    else
    {
        fileSeq = 1; // if it does not exist, start from sequence 1.
    }

    ofstream CreatedFile;
    string CreatedFileName = "afile" + to_string(fileSeq) + ".txt";
    

    cout << "undirected -> 1"<<endl<<" directed -> 0"<<endl;
    bool bi;
    cin >> bi;
    int num1;
    cout << "enter the number of :";
    cin >> num1;
    Graph CreatedGraph(bi ,num1);
    string first, second;
    int weight;
    for (int i = 0; i < CreatedGraph.numOfNodes; i++)
    {
        cout << "Please Enter your towns:" << endl;
        cout << "Enter the name of the first town" << endl;
        cin >> first;
        cout << "Enter the name of the second town" << endl;
        cin >> second;
        cout << "Enter the distance between " << first << " and " << second << ":" << endl;
        cin >> weight;
        CreatedGraph.addEdge(first, second, weight);
    }
    cout << "show options??" << endl<<"yes->1"<<endl<<"no -> 0"<<endl;
    int d;
    cin >> d;
        while (d==1) {
            cout << "I. If you want to print the graph press '1'." << endl;
            cout << "II. If you want to make updates to the graph press '2'." << endl;
            int x = 1;
            cin >> x;
            if (x == 1) {
                CreatedGraph.display();
                int z;
                cout << "would you like to terminate programe?....type 1 for yes." << endl;
                cin >> z;
                if (z == 1)
                    break;
                else
                    continue;
            }
            else if (x == 2) {
                int y;
                string Node, destNode;
                long Weight;
                cout << "I. If you want to add node to the graph press '1'." << endl;
                cout << "II. If you want to remove node from the graph press '2'." << endl;
                cout << "III. If you want to update edge in the graph press '3'." << endl;
                cout << "IV. If you want to add edge to the graph press '4'." << endl;
                cout << "V. If you want to calculate the shortest path to the graph press '5'." << endl;
                cin >> y;
                if (y == 1) {
                    int adjNodes;
                    cout << "Enter the name of the new node." << endl;
                    cin >> Node;
                    cout << "Enter the number of adjacent nodes." << endl;
                    cin >> adjNodes;
                    cout << "Enter the name and weight of adjacent nodes." << endl;
                    map<string, int> adjacentNodes;
                    for (int i = 0; i < adjNodes; i++) {
                        cin >> destNode >> Weight;
                        adjacentNodes.insert({ destNode, Weight });
                    }
                    CreatedGraph.addNode(Node, adjacentNodes);
                }
                else if (y == 2) {
                    cout << "Enter the name of the node." << endl;
                    cin >> Node;
                    CreatedGraph.removeNode(Node);
                }
                else if (y == 3) {
                    cout << "Enter the name of the source node." << endl;
                    cin >> Node;
                    cout << "Enter the name of the destination node." << endl;
                    cin >> destNode;
                    cout << "Enter the new weight ." << endl;
                    cin >> Weight;
                    CreatedGraph.updateWeight(Node, destNode, Weight);
                }
                else if (y == 4) {
                    cout << "Enter the name of the source node." << endl;
                    cin >> Node;
                    cout << "Enter the name of the destination node." << endl;
                    cin >> destNode;
                    cout << "Enter the weight ." << endl;
                    cin >> Weight;
                    CreatedGraph.addEdge(Node, destNode, Weight);
                }
                else if (y == 5)
                {
                    cout << "Enter the source node:" << endl;
                    cin >> Node;
                    cout << "Enter the destinationg node:" << endl;
                    cin >> destNode;
                    int j=CreatedGraph.shortestPath(Node, destNode);
                    cout <<"min distance is: "<< j << endl;
                }
                else {
                    cout << "Data is Not Valid." << endl;
                    break;
                }
            }
            else {
                cout << "Data is Not Valid." << endl;
                break;
            }

            cout << "would you like to terminate programe?" << endl<<"if no type 1 if yes type 2";
            cin >> d;

        }
    

        saveData(CreatedGraph, CreatedFileName);






    //string line;// el mafrood da el line el hytketeb fel file (hyt7at badalo el current w el dest w el weight)
    //while (CreatedFile)
    //{
    //    //enter the graph
    //    getline(cin, line);

    //    if (line == "-1")
    //        break;

    //    CreatedFile << line << "\n";
    //    CreatedFile.close();
    //}
    //// reading data
    //string text;
    //ifstream reading;
    //reading.open(CreatedFileName);
    //while (getline(reading, text)) {

    //    // Output the text from the file
    //    cout << text << " ";
    //}
    //reading.close();


    // Before you exit your program, do not forget to store the last file sequence in "sequeceFile.txt".
    seqFileOut.open("sequeceFile.txt", ios::out);
    seqFileOut << fileSeq;

}



}