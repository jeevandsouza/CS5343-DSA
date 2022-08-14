#include<bits/stdc++.h>
using namespace std;
#define vertices 8

list<int>connections[vertices];
bool visit [vertices+1];
bool store [vertices+1];

void LinkEdges(int from, int to)
{
    //Function to create a graph using adjacency list
    connections[from].push_back(to);
}

bool CheckCycle(int node)
{
    if(visit[node] == false)
    {
        visit[node] = true;
        store[node] = true;

        for(auto itr = connections[node].begin();itr != connections[node].end();itr++)
        {
            if(visit[*itr] == false && CheckCycle(*itr))
              return true;
            else if (store[*itr])
            return true;
        }
    }
    store[node] = false;
    return false;
}

bool IsGraphCyclic()
{
    //To check if the graph is cyclic, if it is then return true
   for(int i=1;i<vertices+1;i++)
   {
       visit[i] = false;
       store[i] = false; 
   }
   for(int i=1;i<vertices+1;i++)
   {
       if(visit[i] == false)
       {
          bool chk = CheckCycle(i);
          if(chk)
          return true;
       }
   }
   return false;
}

void SortTheGraphByDFS(int node,stack<int>& temp)
{
    //To sort DFS DAG in a recursive manner
   visit[node] = true;
   for(auto itr = connections[node].begin();itr!=connections[node].end();itr++)
   {
       if(visit[*itr] == false)
       SortTheGraphByDFS(*itr,temp);
   }
   temp.push(node);
}

void PrintDFSSorting(stack<int>& temp)
{
    //To output the DFS topological sort
   cout<<"DFS topological sort is"<<endl;
   while(temp.empty() == false)
   {
       cout<<temp.top()<<" ";
       temp.pop();
   }
   cout<<endl;
}
void TopologicalSortDFS()
{
   // Topological sorting can be done if the graph is DAG i,e Directed Acyclic graph
   // So first we need to check if the graph is cyclic or not,  if cyclic then it cannot be done
    if(IsGraphCyclic())
    {
        cout<<"Topological DFS sorting cannot be done as the graph is cyclic"<<endl;
        return;
    }
    //If there is no loop then do the DFS topological sorting
    //Take all the vertices, if the vertices are not visited then add it to stack in a recursive way
     stack<int>temp;
      
        for(int i=1;i<vertices+1;i++)
        visit[i] = false;
        for(int i=1;i<vertices+1;i++)
        {
            if(visit[i] == false)
              SortTheGraphByDFS(i,temp);
        }
        PrintDFSSorting(temp);
    
}

void TopologicalSortBFS()
{
     if(IsGraphCyclic())
    {
        cout<<"Topological BFS sorting cannot be done as the graph is cyclic"<<endl;
        return;
    }
    vector<int> vertexList{1,2,3,4,5,6,7,8};//Take the vertices
    unordered_map<int,bool>visited;
    unordered_map<int,int>InDegree;//calculate in degree
    for(auto itr:vertexList)
      {
          visit[itr] = false;
          InDegree[itr] = 0;
      }
    
      
    queue<int> str;//For BFS use queue
    vector<int> BFSorder;
    int temp;
    for(auto itr:vertexList)
    {
        if(InDegree[itr] == 0)
        {
            str.push(itr);
            visited[itr] = true;
        }
    }
    while (str.empty() == false)//Output when non empty queue
	{
		 temp = str.front();
		BFSorder.push_back(temp);
		str.pop();

		for (auto itr : connections[temp])
		{
			InDegree.at(itr)--; 
			if (visited[itr] == false && InDegree[itr] == 0)
			{
				str.push(itr); 
				visited[itr] = true; 
			}
		}
	}
    cout<<"BFS Topological sort is"<<endl;
	for(auto itr : BFSorder)
      cout<<itr<<" ";
      cout<<endl;
}

int main(){

    LinkEdges(1,2);
    LinkEdges(1,5);
    LinkEdges(1,6);
    LinkEdges(2,3); 
    LinkEdges(2,5);
    LinkEdges(2,7);
    LinkEdges(3,4);
    LinkEdges(4,5);
    LinkEdges(5,7);
    LinkEdges(5,8);
    LinkEdges(6,5);
    LinkEdges(6,8);
    LinkEdges(7,4);
    LinkEdges(7,8);
    TopologicalSortDFS();
    TopologicalSortBFS();

}