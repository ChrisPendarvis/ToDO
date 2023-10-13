#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "HMS.h"
#include "Assignment.h"


void HMS::update_Name(int user_Defined_ID, std::string n) {
	homework_Map.at(user_Defined_ID).name = n;
}

void HMS::update_Due_Date(int user_Defined_ID, int d) {
	homework_Map.at(user_Defined_ID).due = d;
}

HMS::HMS(int id, Assignment a) {
	homework_Map.insert({ id, a });
}

HMS::HMS() {}

void HMS::add_Assignment(int id, Assignment a) {
	homework_Map.insert({ id, a });
}

void HMS::update_Started(int user_Defined_ID, bool b) {
	homework_Map.at(user_Defined_ID).started = b;
}

void HMS::update_Estimate(int user_Defined_ID, int e) {
	homework_Map.at(user_Defined_ID).estimate = e;
}

void HMS::remove_Assignment(int user_Defined_ID) {
	homework_Map.erase(user_Defined_ID);
}

void HMS::print_All() {
	for (auto y : homework_Map)
		y.second.print();
}

void HMS::print_In_Progress() {
	for (auto i : in_Progress) {
		std::cout << "Assignment " << i << " is in progress.\n";
	}
}

void HMS::add_In_Progress(int i) {
	in_Progress.insert({ i });
}

void HMS::print_Due_Date(int d) {
	auto its = assignments_Due.equal_range(d);
	for (auto it = its.first; it != its.second; ++it)
		std::cout << "Assignment " << it->second << " is due in " << d << " days." << std::endl;
}

void HMS::print_Course(std::string c) {
	auto its = courses_Map.equal_range(c);
	for (auto it = its.first; it != its.second; ++it) {
		std::cout << "Assignment " << it->second << " belongs to course " << it->first << std::endl;
	}
}

void HMS::add_Due_Date(int i, int a) {
	assignments_Due.insert({ i, a });
}

void HMS::add_Course_Name(std::string c, int id) {
	courses_Map.insert({ c, id });
}
