//By Alan Kokaev
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <map>
#include "BSTClasses.h"
using namespace std;

struct CounterOfLetters
{
	int key, keyForHash;
	char letter;
	CounterOfLetters()
	{
		key = 1, keyForHash = 0;
		letter = ' ';
	}
};

void InitTable(CounterOfLetters *table, int size);
void insert(CounterOfLetters *table, int size, int no);
void printTable(CounterOfLetters *table, int size);

void ForHash(char* line, int myiter)
{
	cout << "\n\nHash-Table: \n";

	CounterOfLetters* C1 = new CounterOfLetters[myiter];

	for (int i = 0; i < myiter; i++)
		C1[i].letter = line[i];

	InitTable(C1, myiter);

	int no = 0;

	for (int i = 0; i < myiter; i++)
	{
		no = rand();
		insert(C1, myiter, no);
	}
	printTable(C1, myiter);
}

void ForBBST(char* line, int myiter)
{
	map<char, int> Balance;

	for (int i = 0; i < myiter; i++)
		Balance.insert(pair<char, int>(line[i], i));
	cout << endl << "Balanced BST: ";
	for (auto it = Balance.begin(); it != Balance.end(); ++it)
		cout << (*it).first << "  ";
}
void ForBST(char* line, int myiter)
{
	Tree Object;
	Object.SetSize(myiter);

	for (int i = 0; i<myiter; i++)
		Object.insert_node((char)line[i]);

	cout << "BST: ";
	Object.inorder_walk(Object.get_root()); cout << endl;
}

int main()
{	
	ifstream fin("text.txt");
	char count[50];
	for (int i = 0; i < 50; i++)
		count[i] = 'h';

	int k = 0, myiter = 0;
	while (!fin.eof())
	{
		fin >> count[k];
		k++;
	}

	for (int i = 0; i < 50; i++)
		if (count[i] != 'h')
			myiter++;

	char* line = new char[myiter];
	for (int i = 0; i < myiter; i++)
		line[i] = count[i];

	fin.close();

	ForBST(line, myiter);
	ForBBST(line, myiter);
	ForHash(line, myiter);
	
	_getch();
}

void InitTable(CounterOfLetters *table, int size)
{
	for (int i = 0; i < size; i++)
		table[i].keyForHash = -999;
}
void insert(CounterOfLetters *table, int size, int no)
{
	bool inserted = false;
	int k = no % size;

	while (!inserted)
	{
		if (table[k].keyForHash == -999)
		{
			table[k].keyForHash = no;
			inserted = true;
		}
		else {
			k++;
			k %= size;
		}
	}
}
void printTable(CounterOfLetters *table, int size)
{
	for (int i = 0; i < size; i++)
		if (!(table[i].keyForHash == -999))
			cout << "Hash: " << table[i].keyForHash << "\tnumber: " << table[i].letter << endl;
}