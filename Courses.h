#pragma once
#include <string>

using namespace std;


class Courses
{
public:
	string cName;  // num + section
	int cEnrolled;

	Courses(string, int);

	~Courses();
};

