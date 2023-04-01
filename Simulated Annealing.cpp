#include <iostream>
#include <string>
#include <time.h>
#include "Schedule.h"
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int calculateFitness(vector<Courses>, vector<Classroom>, 
	vector<Teacher>, vector<int>);


int main() {

	const int SUCCESSFUL_CHANGE_LIMIT = 400;		// should be 400
	const int ATTEMPT_LIMIT = 10000;					// should be 4000
	const double e = 2.718281828;
	int changeCount = 0;
	int attemptCount = 0;
	int attemptNoChange = 0;
	int fitness1 = 0;
	int fitness2 = 0;
	double prob = 0.0;
	double tempurature = 2000;
	double eCalc = 0;
	int max = 0;

	srand(time(0));

	Schedule schedSetup;

	Teacher Hare("Hare", false);					// 9 qualified classes
	Hare.qualifications.push_back("101A");
	Hare.qualifications.push_back("101B");
	Hare.qualifications.push_back("201A");
	Hare.qualifications.push_back("201B");
	Hare.qualifications.push_back("291A");
	Hare.qualifications.push_back("291B");
	Hare.qualifications.push_back("303");
	Hare.qualifications.push_back("449");
	Hare.qualifications.push_back("461");

	Teacher Bingham("Bingham", false);				// 9 classes
	Bingham.qualifications.push_back("101A");
	Bingham.qualifications.push_back("101B");
	Bingham.qualifications.push_back("201A");
	Bingham.qualifications.push_back("201B");
	Bingham.qualifications.push_back("191A");
	Bingham.qualifications.push_back("191B");
	Bingham.qualifications.push_back("291A");
	Bingham.qualifications.push_back("291B");
	Bingham.qualifications.push_back("449");

	Teacher Kuhail("Kuhail", false);				// 2 classes 
	Kuhail.qualifications.push_back("303");
	Kuhail.qualifications.push_back("341");

	Teacher Mitchell("Mitchell", true);				// 6 classes graduate teacher
	Mitchell.qualifications.push_back("191A");
	Mitchell.qualifications.push_back("191B");
	Mitchell.qualifications.push_back("291A");
	Mitchell.qualifications.push_back("291B");
	Mitchell.qualifications.push_back("303");
	Mitchell.qualifications.push_back("341");

	Teacher Rao("Rao", true);						// 5 classes, graduate teacher
	Rao.qualifications.push_back("291A");
	Rao.qualifications.push_back("291B");
	Rao.qualifications.push_back("303");
	Rao.qualifications.push_back("341");
	Rao.qualifications.push_back("461");

	Teacher Staff("Staff", false);
	Staff.qualifications.push_back("101A");
	Staff.qualifications.push_back("101B");
	Staff.qualifications.push_back("201A");
	Staff.qualifications.push_back("201B");
	Staff.qualifications.push_back("191A");
	Staff.qualifications.push_back("191B");
	Staff.qualifications.push_back("291A");
	Staff.qualifications.push_back("291B");
	Staff.qualifications.push_back("303");
	Staff.qualifications.push_back("341");
	Staff.qualifications.push_back("449");
	Staff.qualifications.push_back("461");


	schedSetup.teachVec.push_back(Hare);			// push to vector of teachers for 
	schedSetup.teachVec.push_back(Bingham);		// random selection
	schedSetup.teachVec.push_back(Kuhail);
	schedSetup.teachVec.push_back(Mitchell);
	schedSetup.teachVec.push_back(Rao);
	schedSetup.teachVec.push_back(Staff);

	Courses CS_101A("101A", 40);
	Courses CS_101B("101B", 25);
	Courses CS_201A("201A", 30);
	Courses CS_201B("201B", 30);
	Courses CS_191A("191A", 60);
	Courses CS_191B("191B", 20);
	Courses CS_291A("291A", 20);
	Courses CS_291B("291B", 40);
	Courses CS_303("303", 50);
	Courses CS_341("341", 40);
	Courses CS_449("449", 55);
	Courses CS_461("461", 40);

	schedSetup.courseVec.push_back(CS_101A);		// vector for static course order
	schedSetup.courseVec.push_back(CS_101B);
	schedSetup.courseVec.push_back(CS_201A);
	schedSetup.courseVec.push_back(CS_201B);
	schedSetup.courseVec.push_back(CS_191A);
	schedSetup.courseVec.push_back(CS_191B);
	schedSetup.courseVec.push_back(CS_291A);
	schedSetup.courseVec.push_back(CS_291B);
	schedSetup.courseVec.push_back(CS_303);
	schedSetup.courseVec.push_back(CS_341);
	schedSetup.courseVec.push_back(CS_449);
	schedSetup.courseVec.push_back(CS_461);


	Classroom Haag301("Haag", 70, 301);
	Classroom Haag206("Haag", 30, 206);
	Classroom Royall204("Royall", 70, 204);
	Classroom Katz209("Katz", 50, 209);
	Classroom Flarsheim310("Flarsheim", 80, 310);
	Classroom Flarsheim260("Flarsheim", 25, 260);
	Classroom Bloch0009("Bloch", 30, 9);

	schedSetup.roomVec.push_back(Haag301);				// vector for random room selection
	schedSetup.roomVec.push_back(Haag206);
	schedSetup.roomVec.push_back(Royall204);
	schedSetup.roomVec.push_back(Katz209);
	schedSetup.roomVec.push_back(Flarsheim310);
	schedSetup.roomVec.push_back(Flarsheim260);
	schedSetup.roomVec.push_back(Bloch0009);

	schedSetup.timeVec.push_back(10);					// time vector for random selection
	schedSetup.timeVec.push_back(11);
	schedSetup.timeVec.push_back(12);
	schedSetup.timeVec.push_back(13);		// 1 o'clock
	schedSetup.timeVec.push_back(14);		// 2 o'clock
	schedSetup.timeVec.push_back(15);		// 3 o'clock
	schedSetup.timeVec.push_back(16);		// 4 o'clock

	vector<Courses>		randCourses = schedSetup.courseVec;
	vector<Classroom>	randRoom;
	vector<Teacher>		randTeach;
	vector<int>			randTime;


	for (int i = 0; i < 12; i++) {
		//	cout << schedSetup.teachVec[rand() % 6].instructorName << endl;		// testing randomization
		//	cout << schedSetup.roomVec[rand() % 7].roomName << endl;			// working
		//	cout << schedSetup.timeVec[rand() % 7] << endl << endl;

		randRoom.push_back(schedSetup.roomVec[rand() % 7]);			// random population of schedule
		randTeach.push_back(schedSetup.teachVec[rand() % 6]);
		randTime.push_back(schedSetup.timeVec[rand() % 7]);
	}
	//for (int x = 0; x < 12; x++) {			// testing containers for randomized objects (working)
	//	cout << randCourses[x].cName << " - Expected enrollment: "
	//		<< randCourses[x].cEnrolled << endl;
	//	cout << randRoom[x].buildingName << ' ' << randRoom[x].roomNumber << " - Capacity: "
	//		<< randRoom[x].roomCapacity << endl;
	//	cout << randTeach[x].instructorName << endl;
	//	cout << randTime[x] << endl << endl;
	//}

	fitness1 = calculateFitness(randCourses, randRoom, randTeach, randTime);
	// change one variable randomly
	// calculate new fitness assign to second fitness variable
	// compare and use Boltzman's distribution
	// 

	ofstream myFile2;
	myFile2.open("Max Schedule.txt");


	while (1) {
		tempurature = tempurature * .9;														
		attemptNoChange = 0;			// resetting counter to stop simulated annealing
		changeCount = 0;
		attemptCount = 0;

		while (changeCount < SUCCESSFUL_CHANGE_LIMIT
			&& attemptCount < ATTEMPT_LIMIT) {		// limit const variable comparisons

					// changing one variable
			int vecSelect = rand() % 3, columnSelect = rand() % 12;		// random every iteration

			Classroom tempRoom = randRoom[columnSelect];		// temp variables to switch back 
			Classroom tempRoom2 = schedSetup.roomVec[rand() % 7];		// in the case change is
																		// not accepted
			Teacher tempTeacher = randTeach[columnSelect];
			Teacher tempTeacher2 = schedSetup.teachVec[rand() % 6];

			int tempTime = randTime[columnSelect];
			int tempTime2 = schedSetup.timeVec[rand() % 7];

			switch (vecSelect) {
			case 0:				// room vector
				while (tempRoom.roomNumber == tempRoom2.roomNumber) {
					tempRoom2 = schedSetup.roomVec[rand() % 7];		// randomize til different from temp1
				}
				randRoom[columnSelect] = tempRoom2;	// cases dont check non-changing by chance
				break;
			case 1:				// teacher vector
				while (tempTeacher.instructorName == tempTeacher2.instructorName) {
					tempTeacher2 = schedSetup.teachVec[rand() % 6];
				}
				randTeach[columnSelect] = tempTeacher2;
				break;
			case 2:				// time vector
				while (tempTime == tempTime2) {
					tempTime2 = schedSetup.timeVec[rand() % 7];
				}
				randTime[columnSelect] = tempTime2;
				break;
			default:
				cout << "something went wrong";
				break;
			}

			fitness2 = calculateFitness(randCourses, randRoom, randTeach, randTime);

			prob = ((double)rand() / (RAND_MAX));		// random number between 0 and 1
			eCalc = pow(e, ((fitness2 - fitness1) / tempurature));

			// Boltzman's distribution
			if (prob < eCalc && fitness1 != fitness2) {	// change accepted				
				changeCount++;
				fitness1 = fitness2;
			}
			else {														// change not accepted
				switch (vecSelect) {
				case 0:
					randRoom[columnSelect] = tempRoom;
					break;
				case 1:
					randTeach[columnSelect] = tempTeacher;
					break;
				case 2:
					randTime[columnSelect] = tempTime;
					break;
				default:
					cout << "issue with second switch";
				}
				attemptNoChange++;
			}
			// if change accepted changeCount++ (limit 400), attemptCount++ (limit 4000) 
			// until 4000 attempts with not change made
			attemptCount++;


			if (fitness2 > max) {
				max = fitness2;

				for (int x = 0; x < 12; x++) {			// testing containers for randomized objects (working)
					if (randTime[x] > 12)
						randTime[x] -= 12;

					myFile2 << left << setw(15) << " Class name: " << setw(25) << "Expected enrollment: "
						<< setw(17) << "Classroom: " << setw(20) << "Room Capacity: "
						<< setw(15) << "Instructor: " << setw(10) << "Time:" << endl;
					myFile2 << ' ' << setw(15) << randCourses[x].cName << setw(25) << randCourses[x].cEnrolled
						<< setw(10) << randRoom[x].buildingName << setw(7) << randRoom[x].roomNumber
						<< setw(20) << randRoom[x].roomCapacity << setw(15) << randTeach[x].instructorName
						<< setw(10) << randTime[x] << endl << endl;
				}
			}
		}
		cout << fitness1  << "     " << max << endl;
		if (attemptNoChange == ATTEMPT_LIMIT)
			break;
	}

	cout << " Testing Complete" << endl << endl << "New Schedule:" << endl << endl;

	ofstream myFile;
	myFile.open("Final Schedule.txt");

	for (int x = 0; x < 12; x++) {			// testing containers for randomized objects (working)
		if (randTime[x] > 12)
			randTime[x] -= 12;

		myFile << left << setw(15) << " Class name: " << setw(25) << "Expected enrollment: "
			<< setw(17) << "Classroom: " << setw(20) << "Room Capacity: "
			<< setw(15) << "Instructor: " << setw(10) << "Time:" << endl;
		myFile << ' ' << setw(15) << randCourses[x].cName << setw(25) << randCourses[x].cEnrolled
			<< setw(10) << randRoom[x].buildingName << setw(7) << randRoom[x].roomNumber
			<< setw(20) << randRoom[x].roomCapacity << setw(15) << randTeach[x].instructorName
			<< setw(10) << randTime[x] << endl << endl;
	}

	myFile << " Final Fitness: " << fitness1 << "  Maximum score ever found: " << max << endl;
	myFile.close();

	return 0;
}


int calculateFitness(vector<Courses> courses, vector<Classroom> rooms,
	vector<Teacher> teachers, vector<int> times) {

	int fitness = 0;
	int numHare = 0, numBingham = 0, numKuhail = 0, numMitchell = 0, numRao = 0;

	for (int w = 0; w < 12; w++) {
	vector<string>::iterator courseIterEnd = teachers[w].qualifications.end();
	vector<string>::iterator courseIter = teachers[w].qualifications.begin();	

					// course taught by qualified teacher

	if (teachers[w].instructorName == "Staff") {		// index corresponds to which course
		fitness++;
		//	cout << endl << w + 1 << " " << fitness << endl;  // working fitness
	}
	else {
		for (vector<string>::iterator x = courseIter; x < courseIterEnd; x++) {
			if (courses[w].cName == *x) {	// was testing for later course
				fitness += 3;
				break;			
			}
		}

		// instructors teaching more than 4 classes: -5 per course over 4 (counter)

		if (teachers[w].instructorName == "Hare")
			numHare++;
		else if (teachers[w].instructorName == "Bingham")
			numBingham++;
		else if (teachers[w].instructorName == "Kuhail")
			numKuhail++;
		else if (teachers[w].instructorName == "Mitchell")
			numMitchell++;
		else if (teachers[w].instructorName == "Rao")
			numRao++;
	}

			// no conflicting room and time	
			// i added the "roomNumber" variable in the classroom object. made changes to if statement

		fitness += 10;		// change to +5 when activating one functions, +10 for both functions
		for (int b = w + 1; b < 12; b++) {
			if (rooms[w].buildingName == rooms[b].buildingName && times[w] == times[b] 
				&& rooms[w].roomNumber == rooms[b].roomNumber)  // added the last case due 
				fitness -= 5;									// to removing room number from "name"


					//no multi-booking teachers at a time

			if (teachers[w].instructorName != "Staff" // staff has no constraints for multi-booking
				&& teachers[w].instructorName == teachers[b].instructorName 
				&& times[w] == times[b])  
				fitness -= 5;
		}


					// room large enough to accomdate and capacity no more that 2x enrolled

		if (courses[w].cEnrolled <= rooms[w].roomCapacity) {
			fitness += 5;
			if (courses[w].cEnrolled >= rooms[w].roomCapacity / 2)
				fitness += 2;
		}
	}


					// instructors teaching more that 4 classes: -5 fitness (fitness calculation)

	if (numHare > 4)
		fitness = fitness - 5 * (numHare - 4);
	if (numBingham	> 4)
		fitness = fitness - 5 * (numBingham - 4);
	if (numKuhail	> 4)
		fitness = fitness - 5 * (numKuhail - 4);
	if (numMitchell	> 4)
		fitness = fitness - 5 * (numMitchell - 4);
	if (numRao		> 4)
		fitness = fitness - 5 * (numRao - 4);


					// if graduate instructors teaching more than non-graduate: -10

	if (numMitchell > numHare || numMitchell < numBingham || numRao > numHare || numRao > numBingham)
		fitness -= 10;


					// 101 & 191 same-time testing

	if (times[0] == times[4])						// same time			// times[0] is 101A
		fitness -= 15;
	else if (abs(times[0] - times[4]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[0].buildingName == rooms[4].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[0].buildingName == "Katz" || rooms[0].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[4].buildingName == "Katz" || rooms[4].buildingName == "Bloch")
				fitness -= 3;
		}
	} // copy all of else if and change indices

	if (times[0] == times[5])												// times[1] is 101B
		fitness -= 15;
	else if (abs(times[0] - times[5]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[0].buildingName == rooms[5].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[0].buildingName == "Katz" || rooms[0].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[5].buildingName == "Katz" || rooms[5].buildingName == "Bloch")
				fitness -= 3;
		}
	}

	if (times[1] == times[4])												// times[4] is 201A
		fitness -= 15;
	else if (abs(times[1] - times[4]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[1].buildingName == rooms[4].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[1].buildingName == "Katz" || rooms[1].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[4].buildingName == "Katz" || rooms[4].buildingName == "Bloch")
				fitness -= 3;
		}
	}

	if (times[1] == times[5])												// times[5] is 201B
		fitness -= 15;									// still a work in progress
	else if (abs(times[1] - times[5]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[1].buildingName == rooms[5].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[1].buildingName == "Katz" || rooms[1].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[5].buildingName == "Katz" || rooms[5].buildingName == "Bloch")
				fitness -= 3;
		}
	}

			// 201 & 291 testing

	if (times[2] == times[6])						// same time			// times[0] is 101A
		fitness -= 15;
	else if (abs(times[2] - times[6]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[2].buildingName == rooms[6].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[2].buildingName == "Katz" || rooms[2].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[6].buildingName == "Katz" || rooms[6].buildingName == "Bloch")
				fitness -= 3;
		}
	} // copy all of else if and change indices

	if (times[2] == times[7])												// times[1] is 101B
		fitness -= 15;
	else if (abs(times[2] - times[7]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[2].buildingName == rooms[7].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[2].buildingName == "Katz" || rooms[2].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[7].buildingName == "Katz" || rooms[7].buildingName == "Bloch")
				fitness -= 3;
		}
	}

	if (times[3] == times[6])												// times[4] is 201A
		fitness -= 15;
	else if (abs(times[3] - times[6]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[3].buildingName == rooms[6].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[3].buildingName == "Katz" || rooms[3].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[6].buildingName == "Katz" || rooms[6].buildingName == "Bloch")
				fitness -= 3;
		}
	}

	if (times[3] == times[7])												// times[5] is 201B
		fitness -= 15;									// still a work in progress
	else if (abs(times[3] - times[7]) == 1) {		// adjacent times
		fitness += 5;
		if (rooms[3].buildingName == rooms[7].buildingName)	// same building
			fitness += 5;
		else {												// classes not in same building
			if (rooms[3].buildingName == "Katz" || rooms[3].buildingName == "Bloch")
				fitness -= 3;								// one in katz or bloch, other isnt
			if (rooms[7].buildingName == "Katz" || rooms[7].buildingName == "Bloch")
				fitness -= 3;
		}
	}


			// if 101A and 101B are scheduled 3+ hours apart
	if (abs(times[0] - times[1]) >= 3)
		fitness += 10;
			

			// if 191A and 191B are scheduled 3+ hours apart
	if (abs(times[4] - times[5]) >= 3)
		fitness += 10;


//	cout				// testing course counting
//		<< "Hare: "		<< numHare		<< endl
//		<< "Bingham: "	<< numBingham	<< endl
//		<< "Kuhail: "	<< numKuhail	<< endl
//		<< "Mitchell: " << numMitchell	<< endl
//		<< "Rao: "		<< numRao		<< endl;

		return fitness;
}

