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

// METHOD USED TO INITIALIZE THE Lqueue CLASS.
template <class T>
Lqueue<T>::Lqueue() {

	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

// THE DESTRUCT METHOD
template <class T>
Lqueue<T>::~Lqueue() {

	while (!IsEmpty()) {

		Clear();
	}
}

// THE COPY CONSTRUCTOR METHOD
template <class T>
Lqueue<T>::Lqueue(const Lqueue& q) {

	// ASSIGN THE HEAD OF THE SOURCE TO A NEW NODE POINTER, THEN
	// AS LONG AS THE TEMP VARIABLE IS DIFFERENT FROM ZERO, PUSH
	// VALUE OF THE SOURCE TO THE NEW CALLER Lqueue.
	Node<T>* temp = q.m_head;

	while (temp != nullptr) {

		Push(temp->GetData());
		temp = temp->GetNext();
	}
}

// THE OVERLOADED ASSIGNMENT OPERATOR METHOD.
template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& q) {

	// ASSIGN THE HEAD OF THE SOURCE TO A NEW NODE POINTER, THEN
	// AS LONG AS THE TEMP VARIABLE IS DIFFERENT FROM ZERO, PUSH
	// VALUE OF THE SOURCE TO THE NEW CALLER Lqueue.
	if (this == &q) {
		return *this; // CHECKING FOR SELF ASSIGNMENT. IF IT IS, RETURN ITSELF.
	}

	Node<T>* temp = q.m_head;

	while (temp != nullptr) {

		Push(temp->GetData());
		temp = temp->GetNext();
	}

	return *this;
}

// THE PUSH METHOD
template <class T>
void Lqueue<T>::Push(const T& q) {

	// PUSH THE ELEMENT THAT IS PASSED TO THIS METHOD TO A NODE
	// THAT EXISTS, OR CREATE A NEW NODE THEN POINT ITSELF AS THE
	// HEAD AND TAIL.
	
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

// THE POP METHOD
template <class T>
T Lqueue<T>::Pop() {

	// POP THE ELEMENT THAT IS LOCATED AT THE FRONT OF THE QUEUE,
	// THEN RETURN THE DATA OF THAT POPPED ELEMENT
	
	Node<T>* temp = nullptr;
	T temp2;

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
			temp2 = temp->GetData();
			delete temp;
			return temp2;
		}
		else {

			temp = m_head;
			m_head = m_head->GetNext();
			m_size--;
			temp2 = temp->GetData();
			delete temp;
			return temp2;
		}
	}
}

// THE DISPLAY METHOD.
template <class T>
void Lqueue<T>::Display() {

	// DISPLAY THE QUEUE AS LONG AS THE QUEUE/NODE
	// ISN'T EMPTY

	int counter = 1;
	if (IsEmpty()) {

		cout << "\nYou have no heroes yet! You should try to acquire some first!" << endl;
	}
	else {

		Node<T>* temp = m_head;

		while (temp != nullptr) {

			cout << counter << ". " << *temp->GetData();
			temp = temp->GetNext();
			counter++;
		}

	}
}

// THE FRONT METHOD: RETURNS THE FRONT OF THE QUEUE
template <class T>
T Lqueue<T>::Front() {

	return m_head->GetData();
}

// THE ISEMPTY METHOD: CHECKS IF THE QUEUE IS EMPTY
template <class T>
bool Lqueue<T>::IsEmpty() {

	if (m_head == nullptr && m_tail == nullptr) {

		return true;
	}

	return false;
}

// THE SIZE METHOD: RETURNS THE SIZE OF THE QUEUE
template <class T>
int Lqueue<T>::size() {

	return m_size;
}

// THE FIND METHOD
template <class T>
int Lqueue<T>::Find(T& q) {

	// CHECK FOR THE ELEMET THAT WAS PASSED TO THIS METHOD
	// IF IT EXISTS. IF IT DOES, RETURN THE INDEX OF THAT
	// ELEMENT. IF IT DOESN'T RETURN -1

	Node<T>* temp = m_head;

	for (int i = 0; i < m_size; i++) {

		if (temp->GetData() == q) {
			return i;
		}
		temp = temp->GetNext();
	}
	return -1;
}

// THE SWAP METHOD: UNCHECKED METHOD
template <class T>
void Lqueue<T>::Swap(int x) {

	// SWAP THE DATA OF THE ELEMENT THAT WAS PASSED
	// TO THIS METHOD WITH THE DATA OF THE ELEMENT THAT
	// THE DATA THAT'S LOCATED PRIOR TO THE PASSED ELEMENT
	
	Node<T>* temp = operator[](x);
	Node<T>* temp2 = operator[](x - 1);
	Node<T>* tempT = temp2;

	temp2->SetData(temp->GetData());
	temp->SetData(tempT->GetData());
}

// THE CLEAR METHOD
template <class T>
void Lqueue<T>::Clear() {

	// AS LONG AS THE TEMPORARY VARIABLE ISN'T A NULL POINTER,
	// DELETE THE ELEMENT THATS REFERENCED TO IT, THEN SET THE
	// TEMPORARY VARIBLE TO THE NEXT OF THE CURRENT ELEMENT

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

// THE OVERLOADED [] METHOD
template <class T>
T& Lqueue<T>::operator[] (int x) {

	// RETURN THE DATA OF THE ELEMENT LOCATED AT POSITION "x"

	Node<T>* temp = m_head;

	for (int i = 0; i < m_size; i++) {
		if (i == x) {
			return temp->GetData();
		}
		temp = temp->GetNext();
	}
}

#endif