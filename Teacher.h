// teacher.h
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Teacher {
public:
	string instructorName;
	vector<string> qualifications;
	int numCoursesTeaching;
	bool gradTeacher;


	Teacher(string, bool);

	~Teacher();
};