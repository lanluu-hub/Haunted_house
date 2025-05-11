/**
 * FILE: DATA_STRUCTURE.H
 * Author: Lan Luu
 * Create: 10/14/2024
 *
 * SUMMARY: Contain the header file of data_structure for Progam 1. 
 */

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H
#include "Attendees.h"

using std::string;

class KidNode: public Kid
{
	public:
		KidNode(const string init_room_name = "Blank Room", const string init_description = "It's just a room.",
				const string init_monster = "staff", const int init_candy = 0, KidNode * init_next = nullptr);
		~KidNode();
		KidNode(const Kid & source);


		void set_next(KidNode * new_next);	
		void display() const;
		
		// FUNCTION TO GET NEXT POINTER	
		string& get_room_name();
		KidNode * get_next();
		const KidNode * get_next() const;

		// NAVIGATE METHOD
		//void move(const KidNode * current); 	// Actually a copy method
		int get_candy() const;

	protected:
		// Room info
		string 	room_name;
		string 	room_description;
		string	monster;
		int 	candy_reward;
		
		KidNode * next;
};

class AdultNode: public Adult
{
	public:
		// CONTRUCTOR	
		AdultNode(const string init_r_name = "Blank", const string init_r_description = "None", 
				const string init_event= "Nothing Unusual", const int init_sanity_penalty = 0, AdultNode * init_next = nullptr);
		~AdultNode();

		void set_next(AdultNode * a_next);		

		AdultNode* get_next() const;
		string get_room_name() const;

		void display() const;
		
	protected:
		// Room info
		string 	room_name;
		string 	room_description;
		string 	room_event;
		int 	sanity_penalty;

		AdultNode * next;
};

class AnimalNode: public Attendees
{
	public:
	// CONSTRUCTOR & DESTRUCTOR
		AnimalNode(const string init_name = "blank room", const string init_desc = "Just a blank room for hanging out!", const int init_treat = 0);
		~AnimalNode( );

	// PUBLIC METHOD
		void display ( ) const;
		int get_treat_reward( ) const;

	protected:
		// Room info
		string 	room_name;
		string 	room_description;
		int	treat_reward;
};

class CLL_Maze
{
	public:
		CLL_Maze();
		~CLL_Maze();
		CLL_Maze(const CLL_Maze & source);

		// METHOD
		void insert(const string a_name, const string a_description, const string a_monster, const int candy);
		int list_length() const;
		bool remove(const string target);
		int remove_all();
		KidNode* retrieval(const string target) const;
		void display() const;
		KidNode * get_current() const;
		// TESTING
		void start ( );
		bool advance( );	

	private:
		KidNode * rear;
		KidNode * current;


		// Private Method
		void insert(KidNode *& rear, const string a_name, const string a_description, const string a_monster, const int candy);
		int list_length(KidNode * current) const;
		bool remove(KidNode * current, KidNode *& prev, bool & check, const string target);
		int remove_all(KidNode * current, KidNode * prev);
		KidNode* retrieval( KidNode * current, const string target) const;
		void display(KidNode * current) const;
};

// LLL class
class LLL 
{
	public:
		// CONSTRUCTOR 
		LLL();
		~LLL();	
		LLL(const LLL & source);

		// PUBLIC METHOD
		AdultNode * get_head ( ) const;
		int list_length( ) const;
		// insert
		bool list_head_insert ( const string & a_room_name, const string & a_room_description, const string & a_room_event,
				const int & a_sanity_penalty);
		
		bool list_insert (AdultNode * prev, const string & a_room_name, const string & a_room_description, const string & a_room_event,
				const int & a_sanity_penalty );

		// remove
		bool list_remove ( AdultNode * prev );
		// remove_all
		int list_remove_all ();
		bool list_head_remove (AdultNode *& head );
		// retrieval
		AdultNode* retrieval( const string & target_room_name );
		
		//display
		void display( ) const;
		
		
		//AdultNode * head; 	// this for the purpose of testing
	protected:
		AdultNode * head;

		// PRIVATE METHOD	
		int list_length( AdultNode * head ) const;
		AdultNode* retrieval( AdultNode * current, const string & target_room_name );
		int list_remove_all (AdultNode *& head);
		bool list_head_insert ( AdultNode *& head, const string & a_room_name, const string & a_room_description, const string & a_room_event,
				const int & a_sanity_penalty );
		void display(const AdultNode* head ) const;
};

// TODO Implement ARR
class ARR_Maze
{
	public:	
	// CONSTRUCTOR
	ARR_Maze(const int init_room_count = 0);
	~ARR_Maze( );

	bool add_room(const int index, const string room_name, const string room_desc, const string room_event, const int sanity_penaltyl);

	int remove_room(const int index);	

	bool display(const int index) const;

	private:
		LLL ** room_list;
		int number_of_room;

	// Private/ helper function

};

#endif
