#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated Node class used in templated linked list
template <class T>
class Node {
public:
	Node(const T& data); //Constructor
	T& GetData(); //Gets data from node
	void SetData(const T& data); //Sets data in node
	Node<T>* GetNext(); //Gets next pointer
	void SetNext(Node<T>* next); //Sets next pointer
private:
	T m_data;
	Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node(const T& data) {
	m_data = data;
	m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
	return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data) {
	m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
	return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext(Node<T>* next) {
	m_next = next;
}

template <class T>
class Lqueue {
public:
	// Name: Lqueue() (Linked List Queue) - Default Constructor
	// Desc: Used to build a new linked queue (as a linked list)
	// Preconditions: None
	// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
	Lqueue();
	// Name: ~Lqueue() - Destructor
	// Desc: Used to destruct a Lqueue
	// Preconditions: There is an existing lqueue with at least one node
	// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
	//                 to have no memory leaks!
	~Lqueue();
	// Name: Lqueue (Copy Constructor)
	// Preconditions: Creates a copy of existing LQueue
	//                Requires a Lqueue
	// Postconditions: Copy of existing Lqueue
	Lqueue(const Lqueue&);
	// Name: operator= (Overloaded Assignment Operator)
	// Preconditions: Copies an Lqueue into an existing Lqueue
	//                Requires a Lqueue
	// Postconditions: Copy of existing Lqueue
	Lqueue<T>& operator= (Lqueue&);
	// Name: Push
	// Preconditions: Takes in data. Creates new node. 
	//                Requires a Lqueue
	// Postconditions: Adds a new node to the end of the lqueue.
	void Push(const T&);
	// Name: Pop
	// Preconditions: Lqueue with at least one node. 
	// Postconditions: Removes first node in the lqueue, returns data from first node.
	T Pop();
	// Name: Display
	// Preconditions: Outputs the lqueue.
	// Postconditions: Displays the data in each node of lqueue
	void Display();
	// Name: Front
	// Preconditions: Requires a populated lqueue
	// Postconditions: Returns whatever data is in front 
	T Front();
	// Name: IsEmpty
	// Preconditions: Requires a lqueue
	// Postconditions: Returns if the lqueue is empty.
	bool IsEmpty();
	// Name: size
	// Preconditions: Requires a lqueue
	// Postconditions: Returns m_size
	int size();
	// Name: Find()
	// Preconditions: Requires a lqueue
	// Postconditions: Iterates through lqueue and if it finds the thing, returns index, else -1
	int Find(T&);
	// Name: Swap(int)
	// Preconditions: Requires a lqueue
	// Postconditions: Swaps the nodes at the index with the node prior to it.
	void Swap(int);
	// Name: Clear
	// Preconditions: Requires a lqueue
	// Postconditions: Removes all nodes in a lqueue
	void Clear();
	//Name: Overloaded [] operator
	//Precondition: Existing Lqueue
	//Postcondition: Returns object from Lqueue using []
	//Desc: Iterates to node x and returns data from Lqueue
	T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
	Node <T>* m_head; //Node pointer for the head
	Node <T>* m_tail; //Node pointer for the tail
	int m_size; //Number of nodes in queue
};
//***********IMPLEMENT LQUEUE HERE***********************

template <class T>
Lqueue<T>::Lqueue() {

	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

template <class T>
Lqueue<T>::~Lqueue() {

	while (!IsEmpty()) {

		Clear();
	}
}

template <class T>
Lqueue<T>::Lqueue(const Lqueue& q) {

	Node<T>* temp = q.m_head;

	while (temp != nullptr) {

		Push(temp->GetData());
		temp = temp->GetNext();
	}
}

template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& q) {

	if (this == &q) {
		return *this;
	}

	Node<T>* temp = q.m_head;

	while (temp != nullptr) {

		Push(temp->GetData());
		temp = temp->GetNext();
	}

	return *this;
}

template <class T>
void Lqueue<T>::Push(const T& q) {

	Node<T>* temp = new Node<T>(q);

	if (m_head == nullptr) {

		m_head = m_tail = temp;
		m_size++;
	}
	else {

		m_tail->SetNext(temp);
		m_tail = temp;
		m_size++;
	}
}

template <class T>
T Lqueue<T>::Pop() {

	Node<T>* temp = nullptr;

	if (IsEmpty()) {

		cout << "The queue is empty, nothing left to pop." << endl;
		return NULL;
	}
	else {
		if (m_head == m_tail) {

			temp = m_head;
			m_head = nullptr;
			m_tail = nullptr;
			m_size--;
			delete temp;
			return m_head->GetData();
		}
		else {

			temp = m_head;
			m_head = m_head->GetNext();
			m_size--;
			delete temp;
			return m_head->GetData();
		}
	}
}

template <class T>
void Lqueue<T>::Display() {

	int counter = 1;
	if (IsEmpty()) {

		cout << "You have no heroes yet! You should try to acquire some first!" << endl;
	}
	else {

		Node<T>* temp = m_head;
		cout << "\nThe values in the queue are: " << endl;

		while (temp != nullptr) {

			cout << counter << ". " << *temp->GetData() << endl;
			temp = temp->GetNext();
			counter++;
		}

	}
}

template <class T>
T Lqueue<T>::Front() {

	return m_head->GetData();
}

template <class T>
bool Lqueue<T>::IsEmpty() {

	if (m_head == nullptr && m_tail == nullptr) {

		return true;
	}

	return false;
}

template <class T>
int Lqueue<T>::size() {

	return m_size;
}

template <class T>
int Lqueue<T>::Find(T& q) {

	Node<T>* temp = m_head;

	for (int i = 0; i < m_size; i++) {

		if (temp->GetData() == q) {
			return i;
		}
		temp = temp->GetNext();
	}
	return -1;
}

// UNTESTED FUNCTION
template <class T>
void Lqueue<T>::Swap(int x) {

	Node<T>* temp = operator[](x);
	Node<T>* temp2 = operator[](x - 1);
	Node<T>* tempT = temp2;

	temp2->SetData(temp->GetData());
	temp->SetData(tempT->GetData());
}

template <class T>
void Lqueue<T>::Clear() {

	Node<T>* temp = nullptr;
	while (m_head != nullptr) {
		temp = m_head;

		if (m_head->GetNext() == nullptr) {

			m_head = m_tail = nullptr;
		}
		else {

			m_head = m_head->GetNext();
		}

		m_size--;
		delete temp;
	}
}

// UNTESTED FUNCTION.
template <class T>
T& Lqueue<T>::operator[] (int x) {

	Node<T>* temp = m_head;

	for (int i = 0; i < m_size; i++) {
		if (i == x) {
			return temp->GetData();
		}
		temp = temp->GetNext();
	}
}

#endif