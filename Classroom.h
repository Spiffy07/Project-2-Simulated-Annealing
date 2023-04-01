#pragma once
#include <string>

using namespace std;


class Classroom
{
public:
	string buildingName;
	int roomCapacity;
	int roomNumber;

	Classroom(string, int, int);

	~Classroom();
};

