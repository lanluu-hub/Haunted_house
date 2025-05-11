// File: Driver file for Prog1
// Author: Lan Luu
// Create: 10/10/2024
// Course: CS302-001
// Summary: A program to generate 3 type of maze base on the type of attendees. 
// 
// TODO:	generateAdultMaze - implement a maze for adult using ARR
// 		need implement RNG mechanic 
// 		need include std::vector --DONE 
//		need implement adult_maze GameFlow, Adult_menu, . . . 
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Attendees.h"
#include "Data_structure.h"

using namespace std;

const int MAX_ROOM_SIZE = 3;

void Intro( );
char CharacterSelection ( );
char getOption ();
char InitializeMaze (const char, CLL_Maze & kid_maze, ARR_Maze & adult_maze, vector<AnimalNode> &  pet_mazer);
void generateKidMaze(CLL_Maze & kidMaze);
void generateAdultMaze(ARR_Maze & adultMaze);
void generateAnimalMaze( vector<AnimalNode> & pet_maze);
void kidMenu();
void PetMenu();
char KidGameFlow( Kid & player, CLL_Maze & maze, const char choice);
char petGameFlow( Animal & player, vector<AnimalNode>::iterator it, const char choice);

int main()
{
	CLL_Maze kid_maze;
	ARR_Maze adult_maze(MAX_ROOM_SIZE);
	vector<AnimalNode> pet_maze;
	char maze_type;

	Kid kid1("default kid", 8, 0, "spider");
	Adult adult1("default adult", 28, 10);
	Animal pet1("Pepper", 4, "cat", 0);

	Intro( );

	maze_type = InitializeMaze(CharacterSelection( ), kid_maze, adult_maze, pet_maze);	
	
	switch (maze_type)
	{
		case '1': do 
			{ 
				kid_maze.get_current()->display();
				kidMenu();
			} while ( KidGameFlow(kid1, kid_maze, getOption()) == 'r');
			
			break;

		case '2': // NEED IMPLEMENT ARR MAZE	
			for (auto idx = 0; idx < MAX_ROOM_SIZE; ++idx)
			{
				adult_maze.display(idx);
			}

			break;

		case '3': 	 
			for (auto it = pet_maze.begin(); it != pet_maze.end( ); )
			{
				it->display( );	// display current room
				
				PetMenu();	

				if ( petGameFlow(pet1, it, getOption()) == 'm') 
				{
					++it;
					if (it == pet_maze.end())
						cout << "\nYou reach the end of the maze!\n";	
					else
					{		
						cout << "\nYou follow the smell of treat to the next room.\n";
					}	
				}
			}

			break;
		default: cout << "These type of maze is not yet ready for public.\n";
	}	
		
/**
TEST	kid_maze.start( );	
	kid_maze.get_current()->display();
 	kid_maze.advance(); // Not Work as expected
	kid_maze.remove_all();

	kid_maze.get_current()->display();
	kid_maze.get_current()->get_next()->display();
**/


/*
Test	AdultNode room1;
	LLL list;

	cout << list.list_length() << endl;
	list.list_head_insert(list.head, "test 1", "detail detail", "Evtn vent", 2);
	list.list_head_insert(list.head, "test 1", "detail detail", "Evtn vent", 2);
	list.list_head_insert(list.head, "test 2", "detail detail", "Evtn vent", 2);
	list.list_head_insert(list.head, "test 1", "detail detail", "Evtn vent", 2);
	cout << list.list_length() << endl;
	
	if ( list.retrieval("test 3") != nullptr)
		cout << list.retrieval("test 3")->get_room_name();
	else 
		cout << "Room Not Found!";
	
	list.list_remove_all( );
	cout << list.list_length() << endl;
	*/
/*	
TEST	ARR_Maze AdultMaze(10);
	AdultMaze.add_room(0, "test 1", "this is blank room", "Nothing happend here", 2);
	AdultMaze.add_room(0, "test 1", "this is blank room", "Nothing happend here", 2);
	AdultMaze.add_room(0, "test 1", "this is blank room", "Nothing happend here", 2);

	AdultMaze.display(0);	
	AdultMaze.remove_room(0);
*/
	
	return 0;
}


////////////////////////////////////////////////////////
/// FUNCTION IMPLEMENTATION
///////////////////////////////////////////////////////

void Intro( )
{
	cout << "\t\t HAUNTED HOUSE PROGRAM\n\n";
	cout << "\tThis is a simple Haunted house simulation (WIP)\n";
}

char CharacterSelection () 
{
	cout << "What are you? \n Enter: 1 for Kid, 2 for Adult, 3 for Animal\n >> ";
	return getOption();
}

char getOption()
{
	char option {};
	cout << "Your choice: ";
	while (!(cin >> option))
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please enter a valid option.\n >> ";
	}

	return option;
}

char InitializeMaze (const char selection, CLL_Maze & kid_maze, ARR_Maze & adult_maze, vector<AnimalNode> & pet_maze) 
{
	switch (selection)
	{
		case '1': generateKidMaze(kid_maze);
			break;

		case '2': generateAdultMaze(adult_maze);
			cout << "NOT READY YET!! PLEASE COME BACK LATER!\n\n";
			break;

		case '3': generateAnimalMaze(pet_maze);
			break;

		default: cout << "That is not a valid Option!\n";
			cin.clear();
			cin.ignore(1024, '\n');
			InitializeMaze(getOption(), kid_maze, adult_maze, pet_maze);
	}
	
	return selection;
}

void generateKidMaze(CLL_Maze & kidMaze)
{
	kidMaze.insert("Entrance", "This is the Entrance to the Haunted House", "Staff", 0);
	kidMaze.insert("Skeleton Room", "The room is filled with funky Skeleton...", "Skeleton", 2);
	kidMaze.insert("Spider Room", "The room is filled with fluffy spider...", "spider", 3);
	kidMaze.insert("Exit", "The Exit of the Haunted House", "staff", 0);
	
	kidMaze.start( );	// set the current_ptr to head_ptr
	cout <<	"The friendly kid maze have " << kidMaze.list_length() << " rooms.\n";
}

void generateAnimalMaze( vector<AnimalNode> & pet_maze)
{
	pet_maze.emplace_back("Entrance", "This is the entrance to the haunted house. You smell a trace of treat behind the entrance door.", 0);
	pet_maze.emplace_back("Room 2", "This is the second room in the haunted house", 2);
	pet_maze.emplace_back("Room 3", "This is the third room in the haunted house", 1);
	pet_maze.emplace_back("Room 4", "This is the fourth room in the haunted house", 3);
	pet_maze.emplace_back("Room exit", "This is the exit to the haunted house", 0);
}

void generateAdultMaze(ARR_Maze & adultMaze)
{
	adultMaze.add_room(0, "Entrance", "This is the entrance to the maze!", "None", 0);

	adultMaze.add_room(0, "Enchanted Library", "A vast library filled with ancient tomes and glowing manuscripts. The air smells of old paper and magic.", 
				"A mischievous spirit rearranges the books, making it difficult to find your way.", 3);
	adultMaze.add_room(0, "Dark Cavern", "A dimly lit cave with echoing drips of water. Shadows dance across the walls, creating eerie shapes.", 
				"You stumble over loose rocks, causing a minor fall.", 5);

	adultMaze.add_room(1, "Crystal Garden", "A beautiful garden filled with shimmering crystal flowers that reflect light in mesmerizing patterns.", 
				"A sudden gust of wind knocks over a crystal, creating a sharp sound.", 2);
	adultMaze.add_room(1, "Haunted Gallery", "An art gallery filled with paintings that seem to watch you. The air is thick with tension.", 
				"One of the portraits whispers a warning, startling you.", 4);
	adultMaze.add_room(1, "Alchemist’s Workshop", "A cluttered workshop filled with bubbling potions and strange ingredients. The smell is overwhelming.", 
				"A potion accidentally spills, creating a slippery floor.", 3);

	adultMaze.add_room(2, "Abandoned Kitchen", "An old kitchen with rusted utensils and a large fireplace. The silence is unsettling.", 
				"A rat scurries past, causing a minor scare.", 2);
	adultMaze.add_room(2, "Mystic Observatory", "An observatory filled with star charts and telescopes, offering a stunning view of the night sky.", 
				"A sudden meteor shower briefly distracts you, causing disorientation.", 3);
	adultMaze.add_room(2, "Exit", "A murky marshland enveloped in thick fog, with the sound of croaking frogs in the background.", 
				"You lose your footing in the mud, making you     stumble.", 4);

}


void kidMenu () 
{
	vector<string> kid_menu {"1. advance", "2. Pick up candy", "3. Status"};
	for ( auto it = kid_menu.begin(); it != kid_menu.end(); ++it)
		cout << *it << endl;
}



char KidGameFlow( Kid & player, CLL_Maze & maze, const char choice)
{
	switch (choice)
	{
		case '1':if (maze.advance( ))
			 	cout << "\nYou move to the next room.\n";
			 else
			{
				cout << "\nNo more path to go.\n";
				return 'q';
			}						 
		  	break;	  

		case '2': cout << "\nYou Picked Up candy.\n";
			  player.pick_up_candy(maze.get_current()->get_candy());
			  break;

		case '3': cout << "\nHere is you Status:\n";
			  player.display();
			  break;

		default: cout << "\nThat not an options.\n";
			 kidMenu();
			 KidGameFlow(player, maze, getOption());
	} 
	return 'r';
}

void PetMenu()
{
	vector<string> pet_menu {"1. sniff", "2. Eat the treat", "3. Status"};
	for ( auto it = pet_menu.begin(); it != pet_menu.end(); ++it)
		cout << *it << endl;
}


char petGameFlow( Animal & player, vector<AnimalNode>::iterator it, const char choice)
{
	switch (choice)
	{
		case '1': cout << "You move on!\n";
			return 'm';		
			break;

		case '2': player.eat_treat(it->get_treat_reward());
			break;

		case '3': player.display( );
			break;

		default: cout << "That is not an valid options.\n";
			PetMenu( );
			petGameFlow(player, it, getOption( ) );
	}
	return ' ';
}
