#include "Teacher.h"
#include <string>
#include <vector>

using namespace std;



Teacher::Teacher(string name, bool graduateLevel)
{
	instructorName = name;
	gradTeacher = graduateLevel;
}

Teacher::~Teacher() {

}