// File: Attendees.cpp
// Author: Lan Luu
// Create: 10/14/2024
// Course: cs302-001
// Implementation file for Attendees.h
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Attendees.h"

/** 
 * ATTENDEES CLASS
 *
 * void display() const
 * precondition:
 * postcondition: display attendees info.
 *
**/
Attendees::Attendees(const char * a_name, int a_age): m_age(a_age) 
{
	m_name = new char[std::strlen(a_name) + 1];
	std::strcpy(m_name, a_name);
	//srand(time(0));		// For RNG mechanism 
}

Attendees::~Attendees()
{
	delete [] m_name;
	m_name = nullptr;
}

Attendees::Attendees(const Attendees & source):m_age(source.m_age)
{
	m_name = new char[std::strlen(source.m_name) + 1];
	std::strcpy(m_name, source.m_name);
}

void Attendees::display() const
{
	std::cout << std::endl;
	std::cout << std::setfill('-');
	std::cout << std::setw(20) << '*' << std::endl;
	std::cout << "Name: " << m_name << "\t";
	std::cout << "Age: " << m_age << std::endl;
}

void Attendees::set_name(const char * entry)
{
	std::strncpy(m_name, entry, std::strlen(entry));
}

void Attendees::set_age(const int entry)
{
	m_age = entry;
}

/** 
 * KID CLASS - DERIVED FROM ATTENDEES
 * 
 * void set_candy(const int entry) 
 * precondition:
 * postcondition: modify the m_candyCount
 *
 * void set_fear(const std::string entry) 
 * precondition:
 * postcondition: modify the value of fear_of
 *
 * void count_candy() const 
 * precondition: 
 * postcondition: show the m_candyCount
 * 
 * void pick_up_candy(const int entry)	
 * precondition:
 * postcondition: increase the value of m_candyCount by "entry" amount, then 
 * 		  display the candy count.
 *
 * void display() const
 * precondition:
 * postcondition: display kid attendee info.
 *
**/
Kid::Kid(const char * a_name, int a_age, int a_candy, std::string a_fear):Attendees(a_name,a_age), m_candyCount(a_candy), fear_of(a_fear)
{
}

Kid::~Kid()
{
}

Kid::Kid(const Kid & source):Attendees(source.m_name, source.m_age), m_candyCount(source.m_candyCount), fear_of(source.fear_of)
{
}

void Kid::set_candy(const int entry)
{
	m_candyCount = entry;
}

void Kid::set_fear(const std::string & entry)
{
	fear_of = entry;
}

void Kid::count_candy() const 
{
	std::cout << m_name << " currently have " << m_candyCount << " Candies.\n";
}

void Kid::pick_up_candy(const int entry)
{
	std::cout << std::endl;	
	std::cout << m_name << " picked up " << entry << " candy.\n";
	m_candyCount += entry;
	count_candy();
}

void Kid::display() const
{
	std::cout << std::setfill('-');
	std::cout << std::left << std::setw(20) << "-" << std::endl;
	Attendees::display();
	std::cout << "Number of Candy: " << m_candyCount << std::endl;
	std::cout << "Fear of: " << fear_of << std::endl;
}


/** 
 * ADULT CLASS - DERIVED FROM ATTENDEES
 *
 * void set_sanity(const int entry)
 * precondition:
 * postcondition: modify the value of m_sanity
 *
 * void set_lost()
 * precondition:
 * postcondition: set the value of is_lost to true, anounce the attendees that he is lost
 *
 * bool react() const
 * precondition:
 * postcondition: output true if the attendees react successful, false if failed
 * 
 * void decrease_sanity( const int amount )
 * precondition:
 * postcondition: decrease "amount" from "m_sanity"
 *
 * void sanity_check()
 * precondition:
 * postcondition: check current sanity, if sanity less or equal to 0, the attendees is lost
 *
 * void display() const
 * precondition:
 * postcondition: display adult attendee info.
 *
**/
Adult::Adult(const char * a_name, int a_age, int a_sanity, bool a_lost):Attendees(a_name, a_age), m_sanity(a_sanity), is_lost(a_lost)
{
}

Adult::~Adult()
{
}

Adult::Adult(const Adult & source): Attendees(source.m_name,source.m_age), m_sanity(source.m_sanity), is_lost(source.is_lost)
{
}

void Adult::set_sanity ( const int entry)
{
	m_sanity = entry;
}

void Adult::set_lost ()
{
	is_lost = true;
	std::cout << m_name << " is lost!\n"; 
}

bool Adult::react() const
{
	bool result {true};
	int dice_roll = rand() % 6 + 1;
	
	std::cout << "A dice is throw. . .";
	std::cin.get();

	std::cout << "You got " << dice_roll << "\n";
	
	if (dice_roll < 3)
		result = false;
	
	return result;	
}

void Adult::decrease_sanity( const int amount)
{
	m_sanity -= amount;
}

void Adult::sanity_check()
{
	if (m_sanity < 1)
		set_lost();
}

void Adult::display() const
{
	Attendees::display();
	std::cout << "Your current sanity is: " << m_sanity << std::endl;
	// Dont need to display is_lost
}


/** 
 * ANIMAL CLASS - DERIVED FROM ATTENDEES
 *
 * void set_race(const char * a_race) 
 * precondition:
 * postcondition: modify the value of "m_race". 
 *
 * void set_treat(const int a_treat) 
 * precondition:
 * postcondition: modify the value of "m_treat_count".
 *
 * void eat_treat (const int a_treat)
 * precondition:
 * postcondition: increase the "m_treat_count" by "a_treat" amount
 *
 * void display() const
 * precondition:
 * postcondition: display Animal attendee info.
**/

Animal::Animal(const char * a_name, int a_age, const char * a_race, int a_treat):Attendees(a_name,a_age),m_treat_count(a_treat)
{
	m_race = new char[std::strlen(a_race) + 1];
	strcpy(m_race, a_race);
}

Animal::~Animal()
{
	delete [] m_race;
	m_race = nullptr;
}

Animal::Animal(const Animal & source):Attendees(source.m_name,source.m_age),m_treat_count(source.m_treat_count)
{
	m_race = new char[std::strlen(source.m_race) + 1];
	strcpy(m_race, source.m_race);
}

void Animal::set_race (const char * a_race)
{
	m_race = new char[std::strlen(a_race) + 1];
	strcpy(m_race, a_race);
}

void Animal::set_treat (const int a_treat)
{
	m_treat_count = a_treat;
}

void Animal::eat_treat ( const int a_treat )
{
	m_treat_count += a_treat;
	std::cout << "The " << m_race << " ate " << a_treat << " treats.\n";
}

void Animal::display() const
{
	Attendees::display();
	std::cout << "He is a(n) " << m_race << std::endl;
	std::cout << "He has eaten " << m_treat_count << " treats." << std::endl;
}
