#pragma once
#include "Classroom.h"
#include "Courses.h"
#include "Teacher.h"
#include <string>
#include <vector>



using namespace std;


class Schedule
{	
	// 12 courses
	// 6 teachers (5 instructors + staff)
	// 7 times (10A - 4P)
	// 7 rooms
public:
	vector<Courses>		courseVec;			// 12 courses	// 4 vectors to setup for random selection
	vector<Classroom>	roomVec;			// 7 rooms
	vector<Teacher>		teachVec;			// 6 teachers 
	vector<int>			timeVec;			// 7 time slots

	Schedule();
};

