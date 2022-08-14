#include<bits/stdc++.h>
using namespace std;

bool flag = true;//To check when to come out of the loop of hashing
int countCollisions = 0;//Collision counter
void ReadTextFile(vector<string>& temp)
{
    //Method to read text file
    fstream openfile;
    string inputString;
    openfile.open("football.txt",ios::in);//opens the file
    if(openfile.is_open())
       {
           while(getline(openfile,inputString))//TO input a line in the file and copy it to a string
               temp.push_back(inputString);
       }

}
 int DoCollisionResolution(vector<string>& finalTable,int& countCollisions,int val,int tableSize)
 {
     //Mehod of open addressing using quadrating method
     int j = 1;
      int quadProb = 1;
		int squareVal = 1;
        int newValue;
        newValue = (val + squareVal ) % tableSize;
     //This loop runs until we find a empty slot , uses quadratic method
        while(finalTable[newValue] != "")
        {
             quadProb++;
             countCollisions++;
             squareVal+= (2 * quadProb) - 1;
             newValue = (val + squareVal) % tableSize;
        }
        
        return newValue;
 }

 float  FindLoadFactor(int countLoadFactor,int tableSize)
 {
     //TO check whether load factor is more than 0.5
       return (float(countLoadFactor)/(float)(tableSize));
 }
void DoHashing(vector<string> store,vector<string>finalTable)
{
    //We first use 31 size and if the load factor increases we up the table size and do this again
    int tableSize = finalTable.size();
    int val;
    int countLoadFactor = 0;
    hash<string>hashin;//cpp inbuilt has function
    for(int i=0;i<store.size();i++)
    {
        countLoadFactor++;
        val = hashin(store[i]) % tableSize;//TO get place value
        if(finalTable[val] == "") //IF empty store the value
          finalTable[val] = store[i];
        else
        {
            countCollisions++;
            int newVal = DoCollisionResolution(finalTable,countCollisions,val,tableSize);
            finalTable[newVal] = store[i];
        }
        float factr = FindLoadFactor(countLoadFactor,tableSize);
        if(factr > 0.5)
        {
            cout<<"Outputting collision count before rehashing is  "<<countCollisions<<endl;
            flag = true;
            return;
        }

    }
    flag = false;
}

int main()
{
    int tblSize = 31;
    vector<string>store;
     ReadTextFile(store);
    cout<<"Input text"<<endl;
    for(int i=0;i<store.size();i++)
    cout<<store[i]<<" ";
    cout<<endl;
    int itt =1;
    vector<string> finalTable(tblSize*itt,"");
    while(flag)
    {
      countCollisions = 0;
      finalTable.resize(tblSize*itt,"");
      DoHashing(store,finalTable);
      itt++;
    }
    cout<<endl;
    cout<<"Table Size is   "<<finalTable.size()<<endl;
    cout<<"Final Collision count is  "<<countCollisions<<endl;
}