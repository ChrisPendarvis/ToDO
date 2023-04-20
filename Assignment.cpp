#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Assignment.h"


void Assignment::update_name(std::string n) {
	name = n;
}

void Assignment::update_due(int d) {
	due = d;
}

Assignment::Assignment(std::string n, std::string course, int due_date, int assignment_ID, bool started_Y_N, int estimated_Time) {
	Assignment::name = n;
	Assignment::course_name = course;
	Assignment::due = due_date;
	Assignment::ID = assignment_ID;
	Assignment::started = started_Y_N;
	Assignment::estimate = estimated_Time;
}

void Assignment::print() {
	std::cout  << "ID: " << ID << " | Assignment name: " << name << " | Course name: " << course_name << " | Amount of days until due: " << std::to_string(due) << " | Started (0 for NO, 1 for YES): " << std::to_string(started) << " | Estimated days to complete: " << std::to_string(estimate) << std::endl;

}
