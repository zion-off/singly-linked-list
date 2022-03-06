//============================================================================
// Name         : lab3.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 22-09-2020
// Date Modified: 02-01-2021 
// Copyright    : All rights are reserved
// Description  : Singly Linked-List implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
using namespace std;
//====================================
class Node
{
	private:
		int elem; //data element 
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int elem) : elem(elem), next(NULL)
		{}
		friend class MyLinkedList ;
};
//=====================================
class MyLinkedList
{
	private:
		Node* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		void addFront(int elem); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		unsigned int countElem(int elem); //count frequency of an element in the list
		int getIndexOf(int elem); //returns first index of an element in the list, -1 if the element is not present
		void display() const;
		void loadData(string); //read a file and load it into the linked list
		void dumpData(string) const; //write the linked list to a file
		void sort();  // sort the elements of the list
};
//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Linked List"<<endl
		<<"addFront <element> : Add <element> to the front of the Linked List"<<endl
		<<"removeFront        : Remove the front node of the Linked List"<<endl
		<<"count <element>    : count frequency of an element in the list"<<endl
		<<"indexOf <element>  : return first index of an elemenent in the list (-1 of not present)"<<endl
		<<"load <file_name>   : Load the data from <file> and add it into the Linked List"<<endl
		<<"dump <file_name>   : Dump the contents of the Linked list to <file>"<<endl
		<<"sort               : Sort the Linked List using Bubble Sort Algorithm"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{

	MyLinkedList myList;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);
		
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		
		
		if(command=="display") 				myList.display();
		else if(command=="addFront" or command=="add")				myList.addFront(stoi(parameter)),myList.display();
		else if(command=="removeFront" or command=="remove")		myList.removeFront(),myList.display();
		else if(command=="count")			cout<<parameter<<" occurs "<<myList.countElem(stoi(parameter))<<" time(s) in the list"<<endl;
		else if(command=="indexOf")         cout<<"First index of "<<parameter<<" in the list is: "<<myList.getIndexOf(stoi(parameter))<<endl;
		else if(command=="load")			myList.loadData(parameter),myList.display();
		else if(command == "dump")			myList.dumpData(parameter);
		else if(command == "sort")			myList.sort(),myList.display();
		else if(command == "help")			listCommands();
		else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	}while(command!="exit");

	return EXIT_SUCCESS;
}
//====================================
// constructor
MyLinkedList::MyLinkedList ()
{
	this->head = NULL;
}
//====================================
// destructor to clean up all nodes
MyLinkedList::~MyLinkedList () 
{
	while(!empty())
		removeFront();
	this->head = NULL;
}
//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const 
{
	return this->head == NULL;
}
//====================================
// add a node at the front of list
void MyLinkedList::addFront(int elem)
{
	Node *tmp = this->head;
	this->head = new Node(elem);
	this->head->next = tmp;
}
//====================================
// remove the first node from the list
void MyLinkedList::removeFront()
{
	if(!empty())
	{
		Node *tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}

}
//====================================
// count frequency of an element in the list
unsigned int MyLinkedList::countElem(int elem)
{
	unsigned int count = 0;
	Node *curr = this->head;
	while(curr!=NULL)
	{
		if(curr->elem == elem)
			count++;
		curr=curr->next;
	}
	return count;
}
//==============================================
// get first index of an element in the the list.
// returns -1 if the element is not present
int MyLinkedList::getIndexOf(int elem)
{
	int index = 0;
	Node *curr = this->head;
	while(curr != nullptr)
	{
		if(curr->elem == elem)
			return index; 
		curr = curr->next;
		index++;
	}
	return -1; //element not found
}
//==============================================
// display all nodes of the linked list
void MyLinkedList::display() const
{
	Node *ptr=head;
	cout<<"Head->";
	while(ptr!=NULL)
	{
		cout<<ptr->elem<<"->";
		ptr=ptr->next;
	}
	cout<<"Null"<<endl;
}
//====================================
// sort the elments of the list using bubble_sort
void MyLinkedList::sort()
{
	if(head==NULL) return;

	Node *curr;
	bool swapped;
	do
	{
		curr = head;		//reset current to the head (for next round)
		swapped = false;
		while(curr->next!=NULL)
		{
			if(curr->elem > curr->next->elem)   //swap if the element of current node is bigger thant the elment of next node
			{
				int tmp = curr->elem;
				curr->elem = curr->next->elem;
				curr->next->elem = tmp;
				swapped = true;
			}
			curr = curr->next;    //move the current node
		}
	}while(swapped);
}
//==============================================
//Load data from a file and add it to the Linked List
void MyLinkedList::loadData(string path)
{
	ifstream fin(path);
	if(!fin)
	{
		cout<<"Can't open fil1e.txt"<<endl;
		return;
	}

	while(true)
	{
		int data;
		fin>>data;
		if(fin.eof()) break;
		
		addFront(data);
	}

	fin.close();

}
//=============================================
//Dump/write the contents of the list to a file
void MyLinkedList::dumpData(string path) const
{
	ofstream fout(path);
	if(!fout)
	{
		cout<<"Can't open file: "<<endl;
		return;
	}
	Node *ptr = head;

	while(ptr!=NULL)
	{
		fout<<(ptr->elem)<<endl;
		ptr = ptr->next;
	}
	fout.close();
}
//==================================================

