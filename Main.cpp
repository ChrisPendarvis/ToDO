#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Assignment.h"
#include "HMS.h"

HMS h1; // Making the HMS global and so the entire program can access it

void clearScreen() {
	std::cout << std::string(100, '\n'); // For clearing the screen to prevent clutter
}

void choice1() {
	std::string name;
	std::string course;
	int due;
	int id;
	bool start{};
	int est;

	std::cout << "\nEnter a unique id number to identify this Assignment: ";
	std::cin >> id;
	auto search = h1.homework_Map.find(id);
	while (search != h1.homework_Map.end()) { // Check to make sure the ID isn't already in use
		std::cout << "\nThat unique id is already being used. Enter a different one: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> id;
		search = h1.homework_Map.find(id);
	}
	std::cout << "Enter the name of the Assignment: ";
	std::cin >> name;
	std::cout << "\nEnter the course name: ";
	std::cin >> course;
	std::cout << "\nEnter the due date in amount of days: ";
	std::cin >> due;
	while ((std::cout << "\nHave you started the Assignment? Type 1 for Yes, 0 for No: ") // Check to make sure user types either 0 or 1.
		&& (!(std::cin >> start) || start < 0 || start > 1)) {
		std::cout << "\nThat's not a 0 or a 1!";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	std::cout << "\nEnter the estimated days until completion: ";
	std::cin >> est;
	Assignment a1(name, course, due, id, start, est);
	if (start == 1) {
		h1.add_In_Progress(id); // Adds the Assignment ID to the in_Progress unordered_set
	}
	h1.add_Course_Name(course, id); // Adds the course and Assignment ID to the courses_Map unordered_multimap
	h1.add_Due_Date(due, id); // Adds the due date to the assignments_Due unordered_multimap
	h1.add_Assignment(id, a1); // Adds the Assignment itself and the ID to the homework_Map
	h1.print_All(); // Prints all of the Assignments afterwards for convienence
}

void choice2() { // For updating assignments. Name / Due date / Started or not / Deleting
	clearScreen();
	h1.print_All();
	std::cout << "Enter the ID of the Assignment you would like to update: ";
	int user_Defined_ID;
	std::cin >> user_Defined_ID;
	auto search2 = h1.homework_Map.find(user_Defined_ID);
	while (search2 == h1.homework_Map.end()) { // Checking if the Assignment exists
		std::cout << "\nThat Assignment doesn't exist. Enter the ID of the Assignment you would like to update: \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> user_Defined_ID;
		search2 = h1.homework_Map.find(user_Defined_ID);
	}

	std::cout << "Please select an option... ";
	std::cout << "\n1. Update Assignment name";
	std::cout << "\n2. Update Assignment due date";
	std::cout << "\n3. Change Assignment to started/not started";
	std::cout << "\n4. Remove the Assignment\n";
	int updateChoice;
	std::cin >> updateChoice;
	do {
		if (updateChoice == 1) {
			std::cout << "Enter the new name of the Assignment: ";
			std::string new_Name;
			std::cin >> new_Name;
			h1.update_Name(user_Defined_ID, new_Name);
			break;
		}
		else if (updateChoice == 2) {
			std::cout << "Enter the new due date in amount of days for the Assignment: ";
			int new_Date;
			std::cin >> new_Date;
			h1.assignments_Due.erase(user_Defined_ID); // Updates assignments_Due
			h1.add_Due_Date(new_Date, user_Defined_ID);
			h1.update_Due_Date(user_Defined_ID, new_Date); // Updates homework_Map
			break;

		}
		else if (updateChoice == 3) {
			if (h1.homework_Map.at(user_Defined_ID).started == 0) {
				h1.homework_Map.at(user_Defined_ID).started = 1; // Changes the started value to started (1)
				std::cout << "Assignment " << user_Defined_ID << " changed to started. \n";
				h1.in_Progress.insert(user_Defined_ID); // Inserts the Assignment ID into the in_Progress unordered_set
			}
			else if (h1.homework_Map.at(user_Defined_ID).started == 1) {
				h1.homework_Map.at(user_Defined_ID).started = 0; // Changes the started value to not started (0)
				std::cout << "Assignment " << user_Defined_ID << " changed to not started. \n";
				h1.in_Progress.erase(user_Defined_ID); // Erases the started Assignment from the in_Progress unordered_set
			}
			break;
		}
		else if (updateChoice == 4) {
			h1.remove_Assignment(user_Defined_ID); // Deletes the assignment from the homework_Map.
			std::cout << "Assignment " << user_Defined_ID << " deleted. \n";
			break;
		}
		else {
			std::cout << "Please pick a choice between 1 and 4.";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> updateChoice;
		}
	} while (0 < updateChoice < 5); // Making sure user inputs a number between 1 and 4
}

void choice3() {
	int choice;
	int user_Defined_ID;
	std::string course_Name;
	std::cout << "What would you like to search by?" << std::endl;
	std::cout << "Enter 1 to search by amount of days until due." << std::endl;
	std::cout << "Enter 2 to search by course." << std::endl;
	std::cin >> choice;
	if (choice == 1) {
		std::cout << "Enter the amount of days until due: ";
		std::cin >> user_Defined_ID;
		std::cout << "Assignments due in " << user_Defined_ID << " days: \n";
		h1.print_Due_Date(user_Defined_ID);
	}
	else if (choice == 2) {
		std::cout << "Enter the course name: ";
		std::cin >> course_Name;
		std::cout << "Assignments for course " << course_Name << ":\n";
		h1.print_Course(course_Name);
	}
	else {
		std::cout << "Please enter either 1 or 2: ";
		std::cin >> choice;
	}
}

void choice4() {
	std::cout << "\nAssignments in progress: \n";
	h1.print_In_Progress();
}

void choice5() {
	int user_Defined_ID;
	h1.print_All();
	std::cout << "Enter the ID of the Assignment you'd like to remove: ";
	std::cin >> user_Defined_ID;
	auto search3 = h1.homework_Map.find(user_Defined_ID);
	while (search3 == h1.homework_Map.end()) { // Checking if the Assignment exists
		std::cout << "\nThat Assignment doesn't exist. Returning to menu . . . \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	h1.remove_Assignment(user_Defined_ID);
	std::cout << "\nAssignment " << user_Defined_ID << " deleted.\n";
}

void menu() {
	std::cout << "--------------------------------------------- \n";
	std::cout << "Homework Management System \n";
	std::cout << "--------------------------------------------- \n";
	std::cout << "1. Create a new Assigmnet \n";
	std::cout << "2. Update an existing Assignment \n";
	std::cout << "3. Search for an Assignment \n";
	std::cout << "4. Display all Assignments in progress \n";
	std::cout << "5. Remove an Assignment \n";
	std::cout << "6. Exit Program \n";
}

int main() {
	int choice;
	std::string confirm;
	do {
		std::cout << "Please select an option! \n";
		menu();
		std::cin >> choice;

		switch (choice) {
		case 1:
			choice1(); // Adding assignment
			break;
		case 2:
			choice2(); // Updating assignment
			break;
		case 3:
			choice3(); // Search function
			break;
		case 4:
			choice4(); // Print courses in progress
			break;
		case 5:
			choice5(); // Removing assignment
			break;
		case 6:
			return 0; // Exits the program
		default:
			std::cout << "Exiting . . . ";
		}
	} while (choice > 0 && choice < 6);

	return 0;
}