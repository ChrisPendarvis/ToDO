#ifndef HMS_h
#define HMS_h

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Assignment.h"

class HMS {

public:
	std::unordered_map<int, Assignment> homework_Map;
	std::unordered_set<int> in_Progress;

	std::unordered_multimap<int, int> assignments_Due; // Due date first int, id second int
	std::unordered_multimap<std::string, int> courses_Map;
	
	void add_In_Progress(int); // Adds the Assignment ID to the in_Progress set
	void add_Due_Date(int, int); // Adds the due date and the Assignment ID to the assignments_Due multimap
	void add_Course_Name(std::string, int); // Adds the course to the 
	
	void add_Assignment(int, Assignment);
	void update_Name(int, std::string); // Updates the Assignment name
	void update_Due_Date(int, int); // Updates the Assignment due date

	HMS(int, Assignment);
	HMS();

	void update_Started(int, bool); // Updates the Assignment to started/not started
	void update_Estimate(int, int); // Updates the estimated time for completion
	void remove_Assignment(int); //Removes Assignment based on the Assignment ID.

	void print_All();

	void print_Due_Date(int); // Prints all Assignments with the argument as their due date
	void print_Course(std::string); // Prints all Assignments with the argument as the course name
	void print_In_Progress(); // Prints all Assignments in progress
};

#endif