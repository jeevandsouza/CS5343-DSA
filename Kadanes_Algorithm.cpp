#include<bits/stdc++.h>
using namespace std;

int KadanesAlgorithm(int array[],int arr_Len)
{
    int max_Sum=0,curr_Sum=0;
    for(int i=0;i<arr_Len;i++)
    {
        curr_Sum = curr_Sum + array[i];
        if(curr_Sum > max_Sum)
        max_Sum = curr_Sum;
        else if(curr_Sum < 0)
        curr_Sum = 0;
        else
        continue;
    }
    return max_Sum;
}

int main()
{
    int array [] = {2,-1,4,2,-5,6,-3,2}; //Answer should be 8 where we get this by adding 6,-3,2
    int arr_Len = sizeof(array)/sizeof(array[0]);
    int max_Sum = KadanesAlgorithm(array,arr_Len);
    cout<<max_Sum;
}