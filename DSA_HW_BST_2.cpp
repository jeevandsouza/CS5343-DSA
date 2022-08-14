#include<bits/stdc++.h>
using namespace std;

class BinarySearchTree{
	public:
	int data;
	 BinarySearchTree* left_Child,*right_Child;

};

void BST_Inorder_Traversal(BinarySearchTree* BST_Root)
{
	//Inorder Traversal will give ordered output
	if(BST_Root == NULL)
	return;
	if(BST_Root->left_Child != NULL)
	 BST_Inorder_Traversal(BST_Root->left_Child);
	 cout<<BST_Root->data<<" ";
	 if(BST_Root->right_Child != NULL)
	 BST_Inorder_Traversal(BST_Root->right_Child);
}

BinarySearchTree* BST_Insert(BinarySearchTree* BST_Root,BinarySearchTree* new_Node)
{
	if(BST_Root == NULL)
	  return new_Node;

    else
    {
    	//Need to traverse the loop 
    	BinarySearchTree* BST_Curr_Ptr = BST_Root;
    	BinarySearchTree* BST_Prev_Ptr = NULL;
    	while(BST_Curr_Ptr != NULL)
    	{
    		if(BST_Curr_Ptr->data > new_Node->data)
    		{
    			BST_Prev_Ptr = BST_Curr_Ptr;
				BST_Curr_Ptr = BST_Curr_Ptr->left_Child;
			}
			else
			{
				BST_Prev_Ptr = BST_Curr_Ptr;
				BST_Curr_Ptr = BST_Curr_Ptr->right_Child;
			}
		}
	//	cout<<new_Node->data<<" ";
			if(BST_Prev_Ptr->data > new_Node->data)
			   BST_Prev_Ptr->left_Child = new_Node;
			else
			   BST_Prev_Ptr->right_Child = new_Node;
		}
		return BST_Root;
}

BinarySearchTree* FindMaxLeftAncestor(BinarySearchTree* temp)
{
	// I need to find the rightmost leaf to get the maximum element on the on the left subtree
    while(temp != NULL && temp->right_Child != NULL)
       temp = temp->right_Child;

       return temp;
}

BinarySearchTree* BST_Delete(BinarySearchTree* BST_Root,int num_To_Delete)
{
	//There are in total 3 cases when it comes to deletion
	//1) If it'a leaf node, which is easy, just remove the reference from it's ancestor
	//2) The node to be deleted has only one child then the node's child will be connected to the node's ancestor
	//3)If it has two children, here in this third case we first have to make it into any of the first to case, there are two possibilities either we have to take the max element
	//from the left subtree of the node to be deleted or min element from the right subtree.
	//In the first case we need to delete 40 which is the root node in our tree, I am going to find the max element from the left subtree that would be 35 and make it the root.
	//Then delete 35, which is the leaf node, like condition 1 mentioned above
	
    BinarySearchTree* temp_Node;

	//First case or base case if root is null then just return
	if(BST_Root == NULL)
    return BST_Root;

    //If root has no left or right child, i,e it is a leaf ( In 2nd case when we need to delete 15)
    if(BST_Root->left_Child == NULL && BST_Root->right_Child == NULL && BST_Root->data == num_To_Delete)
    return NULL;

    // For thenext 2 else if statements,If root has only right child or only left child i,e case 2
    else if(BST_Root->left_Child == NULL && BST_Root->data == num_To_Delete)
    {
            temp_Node = BST_Root->right_Child;
            free(BST_Root);//freeing the space by deleting the link
            return temp_Node;
    }

    else if(BST_Root->right_Child == NULL && BST_Root->data == num_To_Delete)
    {
            temp_Node = BST_Root->left_Child;
            free(BST_Root);
            return temp_Node;
    }
    // here to get to the node which I want tp delete , i need to traverse
    else if(num_To_Delete > BST_Root->data)
    BST_Root->right_Child = BST_Delete(BST_Root->right_Child,num_To_Delete);

    else if(num_To_Delete < BST_Root->data)
	BST_Root->left_Child = BST_Delete(BST_Root->left_Child,num_To_Delete);

   // This is the case 3 where node to be deleted has both left and right child 
    else
    {
        //Get the max value from the left subtree assign value and then call delete to delete the value
        temp_Node = FindMaxLeftAncestor(BST_Root->left_Child);

        //If I consider case 1 of deleting 40 , 35 is what I will be copying to  40 node 
        BST_Root->data = temp_Node->data;

        //So I have copied root to 35 in the first case and now I need to delete 35 so I call delete method and 35.
        BST_Root->left_Child = BST_Delete(BST_Root->left_Child,temp_Node->data);
    }
	
	return BST_Root;
	
}

int main()
{
	BinarySearchTree* BST_Root = NULL;
	int array_of_BST_Nodes [] = {40,60,20,80,50,10,30,15,5,35,25,45,55,70,90,32,33,48,46};
	int length_Of_Array = sizeof(array_of_BST_Nodes)/sizeof(array_of_BST_Nodes[0]);
	for(int i=0;i<length_Of_Array;i++)
	{
		BinarySearchTree* new_Node = new BinarySearchTree();
		new_Node->data = array_of_BST_Nodes[i];
		BST_Root = BST_Insert(BST_Root,new_Node);
	}
    cout<<"BST Inorder Traversal after Insertion"<<endl;
	BST_Inorder_Traversal(BST_Root);
	cout<<endl;
	
	
   BST_Root = BST_Delete(BST_Root,40);
   cout<<"BST Inorder Traversal after after deleting node 40"<<endl;
   BST_Inorder_Traversal(BST_Root);
   cout<<endl;
    
    BST_Root = BST_Delete(BST_Root,20);
    cout<<"BST Inorder Traversal after  deleting node 20"<<endl;
    BST_Inorder_Traversal(BST_Root);
   cout<<endl;
}