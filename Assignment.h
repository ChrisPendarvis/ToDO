#ifndef Assignment_h
#define Assignment_h

class Assignment
{
public:
	std::string name; // Name of assignment
	std::string course_name;
	int due; // Number of days until assignment is due
	int ID;	 // Unique ID that will be used in the unordered map
	bool started;
	int estimate; // Estimated time to completion

	void update_name(std::string); // Updates the assignment name

	void update_due(int); // Updates the assignment due date

	Assignment(std::string, std::string, int, int, bool, int); // Constructor
	~Assignment() {}

	void print(); // Standard print function
};

#endif