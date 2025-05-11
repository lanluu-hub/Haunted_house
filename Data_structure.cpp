// FILE: DATA_STRUCTURE.CPP
// Author: Lan Luu
// Create: 10/14/2024
// SUMAMRY: Implementation file for data_structure.h

#include <iostream>
#include <cstring>
#include <iomanip>
#include <cassert>
#include "Data_structure.h"
using namespace std;

///////////////////////////////////////////////////////////////
/// KidNode class: derived from Kid
//////////////////////////////////////////////////////////////

// Constructor
KidNode::KidNode(const string a_name, const string a_description, const string a_monster, const int candy, KidNode * a_next):Kid(), room_name(a_name), room_description(a_description),
	monster(a_monster), candy_reward(candy), next(a_next)
{
}

// Destructor
KidNode::~KidNode()
{
}

KidNode::KidNode(const Kid & source): Kid(source), next(nullptr)
{
}

// Display fucntion
// precondition:
// postcondition: display the current room information to the user
void KidNode::display() const
{
	cout << "\nRoom Name: " << room_name << endl;
	cout << setfill('-');
	cout << left << setw(20) << '-' << endl;
	cout << "Detail: " << room_description << endl;
	cout << "There is a(n) " << monster << " here." << endl;
	if (candy_reward > 0)	
		cout << "He is holding " << candy_reward << " candy in his hand.\n";
	cout << setfill('-');
	cout << left << setw(40) << '-' << endl;
}

// function: set_next
// precondition: new_next is not the same as current next
// postcondition: modify the current "next" to "new_next"
// Argument to pass: new_next, a KidNode pointer.
void KidNode::set_next(KidNode * new_next)
{
	next = new_next;
}

// function: get_room_name
// precondition:
// postcondition: return the current "room_name" value
string& KidNode::get_room_name()
{
	return room_name;
}

// function: get_next
// precondition:
// postcondition: return the current "next" value 
KidNode* KidNode::get_next()
{
	return next;
}

// Constant version of the get_next function
const KidNode* KidNode::get_next() const
{
	return next;
}

// function: get_candy
// precondition:
// postcondition: return the current "candy_reward" value 
int KidNode::get_candy() const
{
	return candy_reward;
}



///////////////////////////////////////////////////////////////
/// CLL_Maze class: 
//////////////////////////////////////////////////////////////

// Constructor
CLL_Maze::CLL_Maze(): rear(nullptr), current(nullptr)
{
}

// Destructor
CLL_Maze::~CLL_Maze()
{
	remove_all();
	rear = nullptr;
	current = nullptr;
}

// Copy Constructor
CLL_Maze::CLL_Maze(const CLL_Maze & source): rear(nullptr)
{
	if (source.rear == nullptr)
		return;
	// Implement copy
}


// function: wrapper function for insert
// precondition:
// postcondition: A new node is being insert into the rear of CLL with the passing value
// Argument to pass: 	a_name: const string, for a room name
// 			a_description: const string, for room detail
// 			a_monster: const string, for monster reside in that room
// 			candy: const int, number of candy in that room
void CLL_Maze::insert( const string a_name, const string a_description, const string a_monster, const int candy)
{
	// need validation
	insert(rear, a_name, a_description, a_monster, candy);
}

// function: insert
// precondition: "rear" is a pointer to the rear of the CLL
// postcondition: a new node is being insert to the rear of the CLL
// Argument to pass: 	a_name: const string, for a room name
// 			a_description: const string, for room detail
// 			a_monster: const string, for monster reside in that room
// 			candy: const int, number of candy in that room
void CLL_Maze::insert(KidNode *& rear, const string a_name, const string a_description, const string a_monster, const int candy)
{
	if (rear == nullptr)
	{
		rear = new KidNode( a_name, a_description, a_monster, candy);
		rear->set_next(rear);	
	}
	else 
	{
		KidNode * newNode = new KidNode (a_name, a_description, a_monster, candy);
		newNode->set_next(rear->get_next());
		rear->set_next(newNode);
		rear = newNode;
	}
}

// function: list_length
// precondition: 
// postcondition: an int will be return equal to the number of node currently in the CLL
int CLL_Maze::list_length() const
{
	if (rear == nullptr)
		return 0;
	return list_length(rear->get_next()); 	// Pass the rear->get_next() as the start of the CLL
}

// function: list_length
// precondition: 
// postcondition: an int will be return equal to the number of node currently in the CLL
// Argument to pass:	start: KidNode *, a pointer to the front node in the CLL
int CLL_Maze::list_length(KidNode * current) const
{
	if (current == this->rear) 	// BASE CASE: if current node equal to the front node
		return 1;
	return 1 + list_length(current->get_next());	// Recursive call	
}

// function: remove (wrapper)
// precondition: list is not empty 
// postcondition: remove the node that have "room_name" equal to "target". return 1 if successfully remove, 0 if not.
// argument to pass: 	target, const string, room_name that need to be remove
bool CLL_Maze::remove( const string target)
{
	if ( rear == nullptr)
		return false;
	
	bool remove_check{false};

	remove(rear->get_next(), rear, remove_check, target);

	return remove_check;	
}

// function: remove 
// precondition:  "current" is pointer to current node, "prev" is pointer to the previous node of "current" 
// postcondition: remove the node that have "room_name" equal to "target". Set "remove_check" to 1 if node is removed, 0 if not. return "remove_check".
// argument to pass: 	current, KidNode *, pointer to current node
// 			prev, KidNode * , pointer to the previous node in CLL
// 			remove_check, bool &, flag to check if node is being remove from CLL	
// 			target, const string, room_name that need to be remove
bool CLL_Maze::remove(KidNode * current, KidNode *& prev, bool & remove_check, const string target)
{
	if ( current == this->rear || remove_check)
	{
		if (current->get_room_name() == target)
		{
			remove_check = true;
			KidNode * tempNode = current;

			if (current == current->get_next())	// Only one node left inside the CLL
			{
				delete tempNode;
				this->rear = nullptr;
			}
			else	// There is more than 1 node, and the node need remove is rear node 
			{
				prev->set_next(current->get_next());
				this->rear = prev;
				delete tempNode;
				current = prev->get_next();
			}
		}

	       	return remove_check;	
	}

	if (current->get_room_name() == target)
	{
		remove_check = true;
		KidNode * tempNode = current;

		if (current == current->get_next())	// Only one node left inside the CLL
		{
			delete tempNode;
			this->rear = nullptr;
		}

		prev->set_next(current->get_next());
		delete tempNode;
		current = prev->get_next();
	}

	return remove(current->get_next(), current, remove_check, target);
}

/* function: remove_all (wrapper)
* precondition: 
* postcondition: remove all node currently in the CLL and return the number of node removed.
**/
int CLL_Maze::remove_all()
{
	if (rear == nullptr)
		return 0;
	return remove_all(rear->get_next(), rear);	// Pass rear->get_next() as the front node
}

/* function: remove_all
 * precondition: list cannot be null 
 * postcondition: remove all node currently in CLL and return the numbers of node removed
 * argument to pass: 	current, KidNode *, pointer to the current node in the CLL
 * 			prev, KidNode*, pointer to the previous node before current.
 **/
int CLL_Maze::remove_all(KidNode * current, KidNode * prev)
{
	if (current == this->rear)
	{
		KidNode * tempNode = current;

		if ( current == current->get_next())	// check if current was the last node in CLL
		{
			this->rear = nullptr;
		} 
		else 
		{
			this->rear = prev;		// if last node was remove and there is more node in
							// the CLL, we have to move the CLL rear to the prev
		}

		prev->set_next(current->get_next());
		current = prev->get_next();
		delete tempNode;

		return 1;
	}

	KidNode * tempNode = current;
	prev->set_next(current->get_next());
	current = prev->get_next();
	delete tempNode;
	return 1 + remove_all(current, prev);

}

/* function: retrieval (wrapper)
 * precondition: list cannot be null
 * postcondition: retrieve the data from the CLL with "target" as it value.
 * argument to pass: 	target, const string, target value for retrieve
 * return: 	KidNode*, a pointer to the node containing the "target"
 **/
KidNode* CLL_Maze::retrieval ( const string target ) const
{
	if ( rear == nullptr )
		return nullptr;
	return retrieval(rear->get_next(), target);
}

/* function: retrieval 
 * precondition: list cannot be null
 * postcondition: retrieve the data from the CLL with "target" as it value.
 * argument to pass: 	current, KidNode *, a pointer to the current node
 * 			check, bool &, a flag to check if the target was in the CLL
 * 			target, const string, target value for retrieve
 **/
KidNode* CLL_Maze::retrieval ( KidNode * current, const string target ) const
{
	if ( current == this->rear )
	{
		if ( current->get_room_name() == target )
		{
			return current;
		}
	}

	if ( current->get_room_name() == target )
	{
		return current;
	}

	return retrieval ( current->get_next(), target);
}

/* function: display (wrapper)
 * precondition: list cannot be null
 * postcondition: display all node current in the CLL
 **/
void CLL_Maze::display() const
{
	if ( rear == nullptr )
		return;
	return display ( rear->get_next());
}

/* function: display 
 * precondition: list cannot be null
 * postcondition: display all node current in the CLL
 * argument to pass: 	current, KidNode *, pointer to the current node in CLL
 **/
void CLL_Maze::display( KidNode * current) const
{
	if (current == this->rear)
	{
		current->display();
		return;
	}

	current->display();
	return display(current->get_next());
}

/* function: get_current
 * precondition: list must not be empty
 * postcondition: return the current/front node 
 **/
KidNode * CLL_Maze::get_current() const
{
	assert(current != nullptr);
	return current;
}

void CLL_Maze::start ( ) 
{
	assert(rear);
	current =  rear->get_next();
}

bool CLL_Maze::advance( )
{
	assert(rear);
	if (current == nullptr)
		return false;

	if (current == this->rear)
	{
		cout << "You have reach the exit!\n";
		return false;
	}

	current = current->get_next(); // check on gdb
	
	return true;
}


///////////////////////////////////////////////////////////////
/// AdultNode Class: Derived from Adult 
//////////////////////////////////////////////////////////////

/**
	CONTRUCTOR
**/
AdultNode::AdultNode(const string a_room_name, const string a_room_description, const string a_event, const int a_sanity_penalty, AdultNode * a_next): Adult(), 
			room_name(a_room_name), room_description(a_room_description), room_event(a_event), sanity_penalty(a_sanity_penalty), next(a_next)
{
}

/**
	DESTRUCTOR
**/
AdultNode::~AdultNode()
{
}

/**
	SETTER
**/	
void AdultNode::set_next( AdultNode * a_next )
{
	next = a_next;
}

/**
	GETTER
**/
AdultNode* AdultNode::get_next() const
{
	return next;
}

string AdultNode::get_room_name( ) const
{
	return room_name;
}

/**
	DISPLAY
**/
void AdultNode::display( ) const
{
	cout << "\nRoom Name: " << room_name << endl;
	cout << setfill('-');
	cout << left << setw(20) << '-' << endl;
	cout << "Detail: " << room_description << endl;
	cout << "Event: " << room_event << endl;
	cout << setfill('-');
	cout << left << setw(40) << '-' << endl << endl;
}


///////////////////////////////////////////////////////////////
/// LLL Class: Simple Linear Link List 
//////////////////////////////////////////////////////////////
/**
CONSTRUCTOR
**/
LLL::LLL( ):head(nullptr)
{
}

/**
DESTRUCTOR
**/
LLL::~LLL( )
{
	delete head;
	head = nullptr; 
}

/**
COPY CONSTRUCTOR
[Pending implemment. . .]
**/
LLL::LLL(const LLL & source)
{
}

AdultNode* LLL::get_head ( ) const
{
	return head;
}

/**
LIST_LENGTH
@precondition:
@postcondition: return the total node currently in the LLL
@param: head, head pointer of the LLL
**/
int LLL::list_length( ) const
{
	if (head == nullptr)
		return 0;

	return list_length( head );
}

int LLL::list_length(AdultNode * head ) const
{
	if (head == nullptr)
		return 0;
	
	return 1 + list_length( head->get_next());
}

/**
LIST_HEAD_INSERT
@precondition:
@postcondition: a new node is being add to the head of the LLL
@param: head, AdultNode*, head pointer of the LLL
	other data belong to the AdultNode class.
**/
bool LLL::list_head_insert ( const string & a_room_name, const string & a_room_description, const string & a_room_event,
			const int & a_sanity_penalty ) 
{
	return list_head_insert (head, a_room_name, a_room_description, a_room_event, a_sanity_penalty);
}

bool LLL::list_head_insert ( AdultNode *& head, const string & a_room_name, const string & a_room_description, const string & a_room_event,
			const int & a_sanity_penalty )
{
	head = new AdultNode(a_room_name, a_room_description, a_room_event, a_sanity_penalty, head);
	return true;
}

/**
LIST_INSERT
@precondition:
@postcondition: a new node is being add to the next node of the LLL after prev pointer
@param: prev, AdultNode*, a pointer to the node before the target to be insert 
	other data belong to the AdultNode class.
**/
bool LLL::list_insert (AdultNode * prev, const string & a_room_name, const string & a_room_description, const string & a_room_event,
			const int & a_sanity_penalty ) 
{
	if ( head == nullptr )
	{
		list_head_insert (prev, a_room_name, a_room_description, a_room_event, a_sanity_penalty);
		return true;
	}
	
	prev = new AdultNode(a_room_name, a_room_description, a_room_event, a_sanity_penalty, prev->get_next());
	
	return true;
}

/**
LIST_HEAD_REMOVE
@precondition:
@postcondition:
@param:
**/
bool LLL::list_head_remove (AdultNode *& head )
{
	AdultNode * remove_ptr = head;
	head = head->get_next();
	delete remove_ptr;
	return true;
}

/**
LIST_REMOVE
@precondition:
@postcondition:
@param:
**/
bool LLL::list_remove ( AdultNode * prev )
{
	if (head == nullptr)
		return true;
	AdultNode * remove_ptr = prev->get_next();
	prev->set_next( remove_ptr->get_next());
	delete remove_ptr;
	return true;
}

AdultNode* LLL::retrieval( const string & target_room_name)
{
	if (head == nullptr)
		return nullptr;
	return retrieval( head, target_room_name);
}

AdultNode* LLL::retrieval ( AdultNode * current, const string & target_room_name )
{
	if (current == nullptr)
		return current;

	if (target_room_name == current->get_room_name() )
		return current;
	

	return retrieval(current->get_next(), target_room_name);
}
		
int LLL::list_remove_all () 
{
	if ( head == nullptr )
		return 0;
	return list_remove_all( head);
}

int LLL::list_remove_all (AdultNode *& head)
{
	if (head == nullptr)
		return 0;
	list_head_remove(head);
	return 1 + list_remove_all(head);
}

void LLL::display( ) const
{
	if (head == nullptr)
		return;

	display(head);
}

void LLL::display( const AdultNode * head) const
{
	if (head == nullptr)
		return;

	head->display();
	display(head->get_next());
}


///////////////////////////////////////////////////////////////
/// ARR_Maze Class: Array of  Linear Link List 
//////////////////////////////////////////////////////////////
ARR_Maze::ARR_Maze( const int room_count): number_of_room(room_count)
{
	room_list = new LLL* [room_count];	// initialize an array of LLL

	// Need convert to recursion	
	for (auto idx = 0; idx < room_count; ++idx)
		room_list[idx] = new LLL();
	
} 

ARR_Maze::~ARR_Maze( )
{
	// Need convert to recursion
	for (auto idx = 0; idx < number_of_room; idx++)
		delete room_list[idx];

	delete [] room_list;
}

bool ARR_Maze::add_room(const int index, const string room_name, const string room_desc, const string room_event, const int sanity_penalty)
{
	if (index < 0 || index >= number_of_room)
		return false;
	room_list[index]->list_head_insert( room_name, room_desc, room_event, sanity_penalty);
	return true;
}
	
int ARR_Maze::remove_room(const int index)
{
	if (index < 0 || index >= number_of_room)
		return 0;
	return room_list[index]->list_remove_all( );
}

bool ARR_Maze::display(const int index ) const
{
	
	if (index < 0 || index >= number_of_room)
		return false;
	if (room_list[index] != nullptr)
		room_list[index]->display( );
	return true;
}




///////////////////////////////////////////////////////////////
/// AnimalNode class: derived from Animal 
//////////////////////////////////////////////////////////////

AnimalNode::AnimalNode( const string a_room_name, const string a_room_desc, const int a_treat): room_name(a_room_name), room_description(a_room_desc), treat_reward(a_treat)
{
}

AnimalNode::~AnimalNode( )
{
}

void AnimalNode::display ( ) const
{
	cout << "\nRoom Name: " << room_name << endl;
	cout << setfill('-');
	cout << left << setw(20) << '-' << endl;
	cout << "Detail: " << room_description << endl;
	if (treat_reward > 0)	
		cout << "There is " << treat_reward << " treat laying on the ground.\n";
	cout << setfill('-');
	cout << left << setw(40) << '-' << endl;
	
}

int AnimalNode::get_treat_reward( ) const
{
	return treat_reward;
}
