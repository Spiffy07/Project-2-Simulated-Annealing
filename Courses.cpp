#include "Courses.h"
#include <string>

using namespace std;

Courses::Courses(string courseName, int numStudents) {
	cName = courseName;

	cEnrolled = numStudents;
}

Courses::~Courses() {

}