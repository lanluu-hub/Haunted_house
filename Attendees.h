// File: Attendees.h
// Author: 	Lan Luu
// Create:	10/13/204
// 
// Interface for Attendees and it derived class
// Base class 		Attendees
// Derived class	Kids , Adults , Animals
// // // // // // // // 
#ifndef ATTENDEES_H
#define ATTENDEES_H

#include <iostream>
#include <cstdlib>

class Attendees {
	public:
		// CONSTRUCTOR
		Attendees(const char * init_name = " ", int init_age = 0);
		~Attendees();
		Attendees(const Attendees & source);
		
		// MODIFICATION METHOD
		void set_name(const char * entry);
		void set_age(const int entry);
		void display() const;

	protected:
		char * 	m_name;
		int 	m_age;
};

class Kid: public Attendees {
	public:
		// CONSTRUCTOR
		Kid(const char * init_name = " ", int init_age = 0, int init_candyCount = 0, std::string init_fear = "none");
		~Kid();
		Kid(const Kid & source);
		
		// MODIFICATION METHOD
		void set_candy ( const int entry);
		void set_fear ( const std::string & entry);
		
		// Class METHOD
		void count_candy() const;			// show candy_count 
		void pick_up_candy(const int entry);		// increase candy_count	
		void display() const;

	protected:
		int 		m_candyCount;
		std::string 	fear_of;
};

class Adult: public Attendees {
	public:
		// CONSTRUCTOR
		Adult(const char* init_name = " ", int init_age = 0, int init_sanity = 10, bool init_lost = false);
		~Adult();
		Adult( const Adult & source);

		// MODIFICATION METHOD
		void set_sanity ( const int entry);
		void set_lost(); // set is_lost to true

		// CLASS METHOD
		bool react() const;	// It will simulate a dice roll 1&6 will set it to false, 2-5 will be true
					// This will determined to successful of the action to avoid jumpScare
		void decrease_sanity( const int amount );
		void sanity_check();
	
		void display() const;

	protected:
		int 	m_sanity;
		bool 	is_lost;
};

class Animal:public Attendees {
	public:
		// CONSTRUCTOR
		Animal(const char * init_name = " ", int init_age = 0, const char * init_race =  " ", int init_treat = 0);
		~Animal();
		Animal(const Animal & source);

		// MODIFICATION METHOD
		void set_race( const char * a_race);
		void set_treat( const int a_treat);	

		// CLASS METHOD
		void eat_treat(const int a_treat);	// increase treat_count
		void display() const;

	protected:
		char * m_race;
		int m_treat_count;
		//std::string m_type_of_cry;
};

#endif

