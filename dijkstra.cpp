#include<iostream>
#include<cstdlib>
#include<climits>
#include<random>

//For vector
#include<vector>

using namespace std;


/*****************************
 * Generate the Graph G(V,E)
 *****************************/
void CreateRandomGraph(int **graph, const int& size,const float& density, const int& dist_range)
{
	//Create random probabilistic graph G(V,E)
	std::random_device rd;
	std::mt19937 gen(rd());
	//uniform distribution between 0 and 1
	std::uniform_real_distribution<> dis(0, 1);

	//uniform distribution between 0 and dist_range
	std::uniform_real_distribution<> disrange(0, dist_range);
	
	for (int i=0;i<size;i++)
	{
		for (int j=0;j<size;j++)
		{
			if(i==j)//No self loops pls
				graph[i][j]=0;
			else
			{
				if(dis(gen)<density)//add an edge b/w (i,j)
					graph[i][j]=graph[j][i]=disrange(gen);
			}
		}
	}
/*
	for (int i=0;i<size;i++)
		{
		    for (int j=0;j<size;j++)
		        cout << graph[i][j];
		    cout << endl;
		}
	cout <<endl;	
*/
}


/**************************************************************************** 
 * Function that implements Dijkstra's single source shortest path algorithm 
 * for a graph represented using adjacency matrix representation 
 ***************************************************************************/
void dijkstra(int** graph, const int& n, const int& src,vector <int>& dist) 
{ 
	// sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized
    bool sptSet[n];  
    
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < dist.size(); i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0;
    
    // Find shortest path for all vertices 
    for (int count = 0; count < n - 1; count++) 
	{ 
        int min = INT_MAX, min_index; 
  
        for (int v = 0; v < n; v++) 
            if (sptSet[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
                
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = min_index;
        
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        int v;
        for (v = 0; v < n; v++) 
        {
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && (dist[u] + graph[u][v] < dist[v]) ) 
                dist[v] = dist[u] + graph[u][v]; 
        }
    }
} 
 
/**************
 * Test Code
 **************/			
int main()
{
	const int size=50;
	const int dist_range=10;
	const float density=0.20;
	int **graph=NULL;
	
	//Create a 2D matrix for storing undirected graph G(V,E)
	srand(time(0));
	graph=new int*[size];
	for (int i=0;i<size;i++)
		graph[i]=new int[size]; 
	
	
	//SP will hold shortest path from source to each V-1 nodes
	//Initiaze it to 0
	vector <int> sp(size,-1);
	
	//1. Create Graph
	CreateRandomGraph(graph, size, density, dist_range);
	
	//2. Call Dijkstra Algo on G with start node=0
	dijkstra(graph, size, 0, sp);
	
	//3. Calculate average shortest path for G(V,E)
	float avgsp=0.0;
	count=0;
	for (int i=0;i<sp.size();i++)
	{	if(sp[i]!=0)
		{
			count++;
			avgsp+=sp[i];
		}
	}	
	//4. Print Avg Shortest path
	avgsp=avgsp/count;
	cout<<"Average SP len for graph with "<<size<<" nodes, node density as "<<density<<" and distance range as (0,"<<dist_range<<") is "<<avgsp<<endl;
	
	//5. Free memory
	for (int i=0;i<size;i++)
		delete (graph[i]);
	delete (graph);	
}