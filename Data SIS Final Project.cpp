#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <set>

using namespace std;

struct EnrolledCourse;

struct EnrolledCourseList {
	EnrolledCourse* head, * tail;
};

struct Student
{
	int studentID;
	char firstName[30], lastName[30], emailAddress[50], password[20];
	Student* next;
	EnrolledCourseList enrolledCourses;
};


struct EnrolledStudent {
	Student* studentReference;
	EnrolledStudent* next;
};

struct Course {
	int courseID, courseCapacity;
	char courseName[50], instructorName[50];
	//defineYourTimeScheduleType timeSchedule;
	EnrolledStudent* attendees;
	Course* next;
	Course* previous;
};

struct EnrolledCourse {
	Course* courseReference;
	EnrolledCourse* next;
	EnrolledCourse* previous;
};

struct UniversityCourseList {
	Course* head, * tail;
};

void getList(Course* course)
{

	ifstream file("Course.txt");
	string x;
	while (std::getline(file, x))
	{
		int start = 0;
		int end = 0;
		int counter = 0;
		Course* curr = new Course();
		for (int h = 0; h < x.length(); h++) //read line in txt file
		{
			if (x[h] == ',')
			{
				//reading Id
				if (counter == 0)
				{
					int end = h;
					for (int z = start; z != 0; z++)
					{
						if (x[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = x.substr(start, end);
					int num;
					stringstream ss;
					ss << str;
					ss >> num;
					curr->courseID = num;
					start = h + 1;
				}
				//reading Capacity
				if (counter == 1)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (x[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = x.substr(start, end);
					strcpy(curr->courseCapacity, str.c_str());
					start = h + 1;
				}
				//reading Name
				if (counter == 2)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (x[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = x.substr(start, end);
					strcpy(curr->courseName, str.c_str());
					start = h + 1;
				}
				//reading instructor name
				if (counter == 3)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{
						if (x[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = x.substr(start, end);
					strcpy(curr->instructorName, str.c_str());
					start = h + 1;
				}
				//reading list of students
				if (counter == 3)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{
						if (x[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = x.substr(start, end);
					strcpy(curr->attendees[], str.c_str());
					start = h + 1;
				}
				counter++;
			}
		}

		if (course->next == NULL)  //first elemnet
		{
			course->head = curr;
			course->tail = curr;
		}

		else  //insert at tail
		{
			curr->prev = company->tail;
			company->tail->next = curr;
			curr->next = NULL;
			company->tail = curr;
		}
	}
}



bool Login(EnrolledStudent* enrolledStudent)
{
	int studentId;
	char pass[20];
	cout << "Login to your system" << endl;
	cout << "Enter your University Id" << endl;
	cin >> studentId;
	cout << endl;
	cout << "Enter your password" << endl;
	cin.getline(pass,20);
	cout << endl;

	Student* curr = enrolledStudent->studentReference;

	while (curr != NULL)
	{
		if (curr->studentID == studentId)
		{
			if (curr->password == pass)
			{
				cout << "You are Logged In" << endl;
				return true;
			}
		}
		curr = curr->next;
	}

	return false;
}

void addCourse(UniversityCourseList *un)
{

	Course* c = new Course;
	cout << "Enter Course Id" << endl;
	cin >> c->courseID;
	cout << "Enter Course Name" << endl;
	cin >> c->courseName;

	c = un->head;

	while (c != NULL)

	{
		cout << c->courseName;
		c = c->next;
	}

	int id;
	string x;
	bool found = false;
	do {
		do {
			cout << "enter Course Id assigned for this student" << endl;
			cin >> id;
			//if (SearchEmployee(un, id) != NULL)
			//{
			//	found = true;
			//};
		} while (id < 0 || found == false);
		Course* c = un->head;
		while (c != NULL)
		{
			if (c->courseID == id)
			{
				EnrolledCourse* enc = c->attendees;
				bool haveIt = false;
				while (enc != NULL) {
					if (enc->courseReference->courseName == c->courseName)
					{
						cout << "This Student is already registered in this course" << endl;
						haveIt = true;
					}
					enc = enc->next;
				}

				if (haveIt == false)
					if (c != NULL)
						enc->next = c;
			}
			c = c->next;
		}
		cout << "To exit enter q" << endl;
		cin >> x;
	} while (x != "q");
}



EnrolledCourseList* dropCourse(EnrolledCourseList* en, char courseName[20])
{

	cout << "Enter the name of the course you need to drop" << endl;
	cin.getline(courseName,20);
	
	while (en->head != NULL)
	{
		if (en->head->courseReference->courseName == courseName)
		{
			en->head->next = en->head->next->next;
			en->head->next;
			
		}
	}

	delete en;
}


int main(string args[])
{

	EnrolledStudent* enrolledStudent = new  EnrolledStudent;
	bool state = true;

	do {

		state = Login(enrolledStudent);
	} while (state = false);

}

