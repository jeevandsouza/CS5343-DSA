//Student Name: Randy Suarez Rodes
//Course: CS 5343
//Assignment #6
//August 2nd, 2020
//This program was written on c++, run on Visual Studio Community 2019 on Windows 10.

#include <iostream> 
#include <string> 
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//Hash Table class
class Hash_Table
{
public:
	int table_size; //size of the table
	vector<string> hash_table; //hash table
	int count;	//variable to hold the number of words inserted
	int collisions; //variable to track the number of collisions
	float load_factor; //variable to hold the load factor
	hash<string> hashfunc; //hash function from std library

	//class constructor
	Hash_Table(int n)
	{
		table_size = n;
		hash_table.assign(n, ""); //we initialize the table with empty strings, representing empty entries
		count = 0;
		collisions = 0;
		load_factor = 0;
	}

	//collision resolution function, quadratic probing strategy
	int collision_func(int hash_val) //it receives the hash value that resulted in a collision and the word to be inserted
	{
		int k = 1;
		int squares = 1;
		int newhash = (hash_val + squares) % table_size; //recalculating the new index using quadratic probing

		while (hash_table[newhash] != "") //we loop until we find an available index
		{
			collisions++;
			k++;
			squares += 2 * k - 1; //iteratively we calculate the next square from the previous square
			newhash = (hash_val + squares) % table_size; //recalculating the new index using quadratic probing
		}

		return newhash; //we return the found available index
	}

	//insert function, it receives a string value, the name of the file to be read, CSV .txt file
	void insert(string textfile)
	{
		int hash_val;	//variable to hold the hash value
		ifstream myfile;
		myfile.open(textfile); //opening file with the list of words to insert
		string temp;
		
		while (getline(myfile, temp)) //reading each line of the file
		{	
			stringstream linestream(temp);
			string word;

			while (getline(linestream, word, ',')) //tokenizing each word from the line
			{
				hash_val = hashfunc(word) % table_size; //finding the hash value and the index to insert

				if (hash_table[hash_val] == "") //if we do not have a collision we insert, otherwise we handle the collision
					hash_table[hash_val] = word;
				else
				{
					collisions++;
					hash_table[collision_func(hash_val)]=word; //inserting the word at the found index
				}

				count++; //updating the number of inserted words
				load_factor = (float)count / (float)table_size; //updating the load factor

				if (load_factor > 0.5) //if we reach a load factor greater than 0.5 we rehash
				{
					cout << "Collisions before rehashing: " << collisions << endl; //printing the number of collisions before rehashing
					
					//reseting class variables
					table_size *= 2; //doubling table size
					hash_table.assign(table_size, ""); //reseting the table to empty
					count = 0;
					collisions = 0;
					load_factor = 0;
					myfile.close(); //closing the file
					this->insert(textfile); //recursively calling insert to rehash with the new table
					return;
				}
			}
		}
		myfile.close(); //closing the file
		return;
	}	
};

int main()
{
	Hash_Table H(31); //initialazing a hash_table of size 31

	H.insert("Football.txt"); //inserting from the CSV .txt file, please include the file extension (".txt")

	cout << "Collisions in the final table: "<<H.collisions;

	return 0;
}