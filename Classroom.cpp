#include "Classroom.h"
#include <string>

using namespace std;

Classroom::Classroom(string nameClassroom, int capacityClassroom, int numClassroom) {
	buildingName = nameClassroom;
	roomCapacity = capacityClassroom;
	roomNumber = numClassroom;
}

Classroom::~Classroom() {

}