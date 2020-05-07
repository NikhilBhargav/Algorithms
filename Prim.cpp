/****************************************
 * Prim's implementation for finding MST
 ****************************************/
 
#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<set>
#include<string>
#include <sstream> //For stringstream()

using namespace std;

//Def of a node
typedef struct nodes 
{
   int dest;
   int cost;
}node;

class Graph 
{
   int n;
   list<node> *adjList;
   int total_cost;
   private:
      void showList(int src, list<node> lt) {
         list<node> :: iterator i;
         node tempNode;

         for(i = lt.begin(); i != lt.end(); i++) {
            tempNode = *i;
            cout << "Edge (" << src <<","<<tempNode.dest<<") " << "Edge cost-"<<tempNode.cost<<"\t";
         }
         cout << endl;
      }

   public:
      Graph() 
	  {
         total_cost=0;
		 n = 0;
      }

      Graph(int nodeCount) 
	  {
         total_cost=0;
		 n = nodeCount;
         adjList = new list<node>[n];
      }

      void addEdge(int source, int dest, int cost) {
         node newNode;
         newNode.dest = dest;
         newNode.cost = cost;
         adjList[source].push_back(newNode);
      }

      void displayEdges() {
         for(int i = 0; i<n; i++) {
            list<node> tempList = adjList[i];
            showList(i, tempList);
         }
         cout<<"Total most of MST is "<<this->total_cost;
      }

      friend Graph primsMST(Graph g, int start);
};

set<int> difference(set<int> first, set<int> second) 
{
   set<int> :: iterator it;
   set<int> res;

   for(it = first.begin(); it != first.end(); it++) 
   {
      if(second.find(*it) == second.end())
         res.insert(*it);    //add those item which are not in the second list
   }

   return res;    //the set (first-second)
}

Graph primsMST(Graph g, int start) 
{
   int n = g.n;
   set<int> B, N, diff;
   Graph tree(n);        //make tree with same node as graph
   B.insert(start);     //insert start node in the B set

   for(int u = 0; u<n; u++)    
      N.insert(u); //add all vertices in the N set   

   while(B != N) 
   {
      int min = INT_MAX;             //set as infinity
      int v, par;
      diff = difference(N, B);    //find the set N - B

      for(int u = 0; u < n; u++) 
	  {
         if(B.find(u) != B.end()) 
		 {
            list<node>::iterator it;
            for(it = g.adjList[u].begin(); it != g.adjList[u].end(); it++) 
			{
               if(diff.find(it->dest) != diff.end()) 
			   {
                  if(min > it->cost) 
				  {
                     min = it->cost;    //update cost
                     par = u;
                     v = it->dest;
                  }
               }
            }
         }
      }
      
	  //Add node v in closed set B	
      B.insert(v);
    
	  tree.addEdge(par, v, min);
      tree.addEdge(v, par, min);
      
      //update total MST cost till node v
      tree.total_cost+=min;
   }
   return tree;
}

int main() 
{
	/* Take input from test file */
	std::ifstream read("test.txt");
	string str;
	vector<int> vect;
	
	if (read.is_open())
	{
		while (read)
		{
			getline(read, str);
			stringstream ss(str);
			int i;
			while(ss >> i) 
			{
				vect.push_back(i);
				if(ss.peek() == ',')
					ss.ignore();
			}
		}
	}
	//Total number of nodes in Graph
	int n=vect.at(0);
	
	//Initialize Graph and MST with total number of nodes
	Graph g(n), tree(n);
	
	//Add edges as per given input 
	for(int j=1;j < vect.size();j=j+3)		
		g.addEdge(vect.at(j),vect.at(j+1),vect.at(j+2));
   
   int src=0;	
   //Call MST for g with src=0 as starting node
   tree = primsMST(g, src);
   
   //Display entire tree and total cost which is also a form of gaph 
   tree.displayEdges();
}
