#include<bits/stdc++.h>
using namespace std;
#define vertices 14

unordered_map<string,vector<string>>connections;
unordered_map<string,bool> visit;
vector<string>vertexList;
unordered_map<string,int>InwardDegree;
vector<vector<string>> edgeList;


void LinkEdges(string from,string to)
{
    connections[from].push_back(to);
    InwardDegree[to]++;
} 

void TopologicalSortBFS()
{
   //For BFS ordering we need to check inward degree
    for(auto itr:vertexList)
      visit[itr] = false;
      
    queue<string> store;
    vector<string> BFSorder;
    string temp;
    for(auto itr:vertexList)
    {
        if(InwardDegree[itr] == 0)
        {
            store.push(itr);
            visit[itr] = true;
        }
    } //store in queue all the nodes visited
    while (store.empty() == false)
	{
		 temp = store.front();
		BFSorder.push_back(temp);
		store.pop();

		for (auto itr : connections[temp])
		{
			InwardDegree.at(itr)--; 
			if (visit[itr] == false && InwardDegree[itr] == 0)
			{
				store.push(itr); 
				visit[itr] = true; 
			}
		}
	}
	if (BFSorder.size() < vertices) 
		{
            cout << "BFS can only be done for directed acyclic graph thus no topological sorting can be done";
            return;
        }
    cout<<"BFS Topological sort is"<<endl;
	for(auto itr : BFSorder)
      cout<<itr<<" ";
      cout<<endl;
}



void DFSOrder(string node, unordered_map<string, bool>& visited, unordered_map<string, bool>& finished, stack<string>& store, bool& flag)
{
	if (flag) 
		return;

	visited[node] = true; 
	finished[node] = false; 
   //Recurisvely calling the function
	for (auto itr : connections[node])
	{
		if (!finished[itr]) 		
			flag = true; 		
			
		 
		if (!visited[itr])
			DFSOrder(itr, visited, finished, store, flag);
	}

	store.push(node); 
	finished[node] = true; 
}



void TopologicalSortDFS()
{
	unordered_map<string, bool> visited;
	unordered_map<string, bool> finished;	
	stack<string>store;	
    bool flag = false; 

	for (auto it : vertexList)
	{
		visited[it] = false; 
		finished[it] = true; 
	}

	//check for cycle in DFS
	for (auto it : vertexList)
	{
		if (flag) 
		{
			cout << "There's a cycle, topological order cannot be found";
			return;
		}
		if (!visited[it]) //If no cycle recursively call the function
			DFSOrder(it, visited, finished, store, flag);
	}

	cout<<"DFS Toplogical order is"<<endl;//print output
	while (!store.empty())
	{
		cout << store.top() << " ";
		store.pop();
	}

}



int main()
{ // store them as vertices and edges as this is string
    vertexList = { "m","n","o","p","q","r","s","t","u","v","w","x","y","z" }; 
	edgeList = {{"m","q"},{"m","r"},{"m","x"},{"n","o"},{"n","q"},{"n","u"},{"o","r"},{"o","s"},
									{"o","v"},{"p","o"},{"p","s"},{"p","z"},{"q","t"},{"r","u"},{"r","y"},{"s","r"},
									{"u","t"},{"v","w"},{"v","x"},{"w","z"},{"y","v"}};
    

    for(int i=0;i<edgeList.size();i++)
      LinkEdges(edgeList[i][0],edgeList[i][1]);//Link the edges one by one

  for(int i=0;i<vertices;i++)
      InwardDegree[vertexList[i]] = 0;
    TopologicalSortBFS();
    TopologicalSortDFS();
}

		


