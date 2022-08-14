#include<bits/stdc++.h>
using namespace std;
const int v = 30;

void PrintGraphMatrix(vector<vector<int>>vertices)
{
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
         cout<<vertices[i][j]<<" ";
        cout<<endl;
    }
}

bool CheckSymmetric(vector<vector<int>>vertices)
{
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++)
        {
            if(vertices[i][j] != vertices[j][i])
              return false;
        }
    }
    return true;
}

void DFSTraversal(vector<vector<int>>vertices)
{

}

void BFSTraversal(vector<vector<int>>vertices,int start)
{
     bool seen[30];
     int level[v];
     queue<int>store;
     store.push(start);
     level[start] = 0;
     seen[start] = true;
     while(!store.empty())
     {
         int temp = store.front();
         store.pop();
         cout<<temp<<" ";
         for(int i=0;i<vertices[temp].size();i++)
         {
             if(!seen[vertices[temp][i]])
             {
                 level[vertices[temp][i]] = level[temp]+1;
                 store.push(vertices[temp][i]);
                 seen[vertices[temp][i]] = true;
             }
         }
       /*  for(auto itr=vertices[temp].begin();itr!=vertices[temp].end();itr++)
         {
             if(!seen[*itr])
             {
                 seen[*itr] = true;
                 store.push(*itr);
             }
         }*/
     }
}

int main()
{
   vector<vector<int>>vertices(v); // vector having 30 vertices
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            vertices[i].push_back(rand() % 2);
        }
    }
     for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
                if(j < i)
                    vertices[i][j] = vertices[j][i] = (vertices[i][j] + vertices[j][i])/2;
                
        }
        }
     // Helper to check if matrix is symmetric or not, so as to verify it is a undirected graph

    PrintGraphMatrix(vertices);
     if( CheckSymmetric(vertices))
     cout<<"yes";
     else
     cout<<"false";
     cout<<endl;

    int start = 3;
     DFSTraversal(vertices);
     BFSTraversal(vertices,start);

}

 

