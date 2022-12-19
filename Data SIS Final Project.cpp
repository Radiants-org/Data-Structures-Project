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

struct Time {
	int Day, Hour, Minute, Second;
};

struct Course {
	int courseID, courseCapacity;
	char courseName[50], instructorName[50];
	Time *timeSchedule;
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

void initializeUniversityCourse(UniversityCourseList* un) {
	un->head = NULL;
	un->tail = NULL;
}
void initiallizeCourse(Course* c, EnrolledStudent* en) {
	c->next = NULL;
	en->next = NULL;
}

bool isEmpty(UniversityCourseList* un) {
	return un->head == NULL;
}


void readCourse(UniversityCourseList* university_course_list)

{
	ifstream file("Course.txt");
	string a;
	while (std::getline(file, a))
	{
		int start = 0;
		int end = 0;
		int counter = 0;
		Course* c = new Course();

		for (int x = 0; x < a.length(); x++) //Start by reading the line in the Student Text File
		{
			if (a[x] == ',')
			{
				//read university Id
				if (counter == 0)
				{
					int end = x;

					for (int z = start; z != 0; z++)
					{
						if (a[z] == ',')
						{
							break;
						}
						end++;
					}

					string str = a.substr(start, end);
					int num;
					stringstream ss;
					ss << str;
					ss >> num;
					c->courseID = num;
					start = x + 1;
				}

				//reading capacity
				if (counter == 1)
				{
					int end = x;

					for (int z = start; z != 0; z++)
					{
						if (a[z] == ',')
						{
							break;
						}
						end++;
					}

					string str = a.substr(start, end);
					int num;
					stringstream ss;
					ss << str;
					ss >> num;
					c->courseCapacity = num;
					start = x + 1;
				}

				//reading Course Name
				if (counter == 2)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (a[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = a.substr(start, end);
					strcpy_s(c->courseName, str.c_str());
					start = x + 1;
				}

				//reading Instructor Name
				if (counter == 3)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (a[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = a.substr(start, end);
					strcpy_s(c->instructorName, str.c_str());
					start = x + 1;
					cout << c->instructorName << endl;
				}
				counter++;
			}
		}

		if (university_course_list->head == NULL)  //first element
		{
			university_course_list->head = c;
			university_course_list->tail = c;
		}

		else  //insert at tail
		{
			c->previous = university_course_list->tail;
			university_course_list->tail->next = c;
			c->next = NULL;
			university_course_list->tail = c;
		}

	}
}

Student* readStudents(Student* student)

{
	ifstream file("Student.txt");
	string a;
	while (std::getline(file, a))
	{
		int start = 0;
		int end = 0;
		int counter = 0;
		Student* st = new Student();

		for (int x = 0; x < a.length(); x++) //Start by reading the line in the Student Text File
		{
			if (a[x] == ',')
			{
				//read university Id
				if (counter == 0)
				{
					int end = x;

					for (int z = start; z != 0; z++)
					{
						if (a[z] == ',')
						{
							break;
						}
						end++;
					}

					string str = a.substr(start, end);
					int num;
					stringstream ss;
					ss << str;
					ss >> num;
					st->studentID = num;
					start = x + 1;
				}

				//reading Student First Name
				if (counter == 1)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (a[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = a.substr(start, end);
					strcpy_s(st->firstName, str.c_str());
					start = x + 1;
					cout << st->firstName << endl;
				}

				//reading Student Last Name
				if (counter == 2)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (a[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = a.substr(start, end);
					strcpy_s(st->lastName, str.c_str());
					start = x + 1;
				}

				//reading Student Email Address
				if (counter == 1)
				{
					int end = 0;
					for (int z = start; z != 0; z++)
					{

						if (a[z] == ',')
						{
							break;
						}
						end++;
					}
					string str = a.substr(start, end);
					strcpy_s(st->emailAddress, str.c_str());
					start = x + 1;
				}

				counter++;
			}
		}

		if (student == NULL)  //first elemnet
		{
			student = st;
			student->next = NULL;
		}

		else  //insert at tail
		{
			st->next = student;
			student = st;
		}

	}	
	return student;
	}


Course* searchStudent(UniversityCourseList* ct, int id)
	{
		if (isEmpty(ct)) {

			return NULL;
		}

		Course* course = ct->head;
		for (course = ct->head; course != NULL; course = course->next) {
			if (course->courseID == id)
			{
				cout << "Course name:" << course->courseName << " "  << "; Instructor Name:" << course->instructorName << endl;
				return course;
			}
		}
		return NULL;
	}


void addStudent(EnrolledStudent* ent)
{
	//Create New Student
	Student* student = new Student;
	cout << "Enter Student Id" << endl;
	cin >> student->studentID;
	cout << "Enter First Name" << endl;
	cin >> student->firstName;
	cout << "Enter Last Name" << endl;
	cin >> student->lastName;
	cout << "Enter Email Address" << endl;
	cin >> student->emailAddress;

	student->next = NULL;

	//add employee to the empty list
	if (isEmpty(ent)) {
		ent->head = student;
		ent->tail = student;
	}

	//append the employee at tail
	else {
		e->prev = c->tail;
		c->tail->next = e;
		c->tail = e;
	}
}





//void getList(Course* course)
//{
//
//	ifstream file("Course.txt");
//	string x;
//	while (std::getline(file, x))
//	{
//		int start = 0;
//		int end = 0;
//		int counter = 0;
//		Course* curr = new Course();
//		for (int h = 0; h < x.length(); h++) //read line in txt file
//		{
//			if (x[h] == ',')
//			{
//				//reading Id
//				if (counter == 0)
//				{
//					int end = h;
//					for (int z = start; z != 0; z++)
//					{
//						if (x[z] == ',')
//						{
//							break;
//						}
//						end++;
//					}
//					string str = x.substr(start, end);
//					int num;
//					stringstream ss;
//					ss << str;
//					ss >> num;
//					curr->courseID = num;
//					start = h + 1;
//				}
//				//reading Capacity
//				if (counter == 1)
//				{
//					int end = 0;
//					for (int z = start; z != 0; z++)
//					{
//
//						if (x[z] == ',')
//						{
//							break;
//						}
//						end++;
//					}
//					string str = x.substr(start, end);
//					strcpy(curr->courseCapacity, str.c_str());
//					start = h + 1;
//				}
//				//reading Name
//				if (counter == 2)
//				{
//					int end = 0;
//					for (int z = start; z != 0; z++)
//					{
//
//						if (x[z] == ',')
//						{
//							break;
//						}
//						end++;
//					}
//					string str = x.substr(start, end);
//					strcpy(curr->courseName, str.c_str());
//					start = h + 1;
//				}
//				//reading instructor name
//				if (counter == 3)
//				{
//					int end = 0;
//					for (int z = start; z != 0; z++)
//					{
//						if (x[z] == ',')
//						{
//							break;
//						}
//						end++;
//					}
//					string str = x.substr(start, end);
//					strcpy(curr->instructorName, str.c_str());
//					start = h + 1;
//				}
//				//reading list of students
//				if (counter == 3)
//				{
//					int end = 0;
//					for (int z = start; z != 0; z++)
//					{
//						if (x[z] == ',')
//						{
//							break;
//						}
//						end++;
//					}
//					string str = x.substr(start, end);
//					strcpy(curr->attendees[], str.c_str());
//					start = h + 1;
//				}
//				counter++;
//			}
//		}
//
//		if (course->next == NULL)  //first element
//		{
//			course->head = curr;
//			course->tail = curr;
//		}
//
//		else  //insert at tail
//		{
//			curr->prev = company->tail;
//			company->tail->next = curr;
//			curr->next = NULL;
//			company->tail = curr;
//		}
//	}
//}



//bool Login(EnrolledStudent* enrolledStudent)
//{
//	int studentId;
//	char pass[20];
//	cout << "Login to your system" << endl;
//	cout << "Enter your University Id" << endl;
//	cin >> studentId;
//	cout << endl;
//	cout << "Enter your password" << endl;
//	cin.getline(pass,20);
//	cout << endl;
//
//	Student* curr = enrolledStudent->studentReference;
//
//	while (curr != NULL)
//	{
//		if (curr->studentID == studentId)
//		{
//			if (curr->password == pass)
//			{
//				cout << "You are Logged In" << endl;
//				return true;
//			}
//		}
//		curr = curr->next;
//	}
//
//	return false;
//}

//void addCourse(UniversityCourseList *un)
//{
//
//	Course* c = new Course;
//	cout << "Enter Course Id" << endl;
//	cin >> c->courseID;
//	cout << "Enter Course Name" << endl;
//	cin >> c->courseName;
//
//	c = un->head;
//
//	while (c != NULL)
//
//	{
//		cout << c->courseName;
//		c = c->next;
//	}
//
//	int id;
//	string x;
//	bool found = false;
//	do {
//		do {
//			cout << "enter Course Id assigned for this student" << endl;
//			cin >> id;
//			//if (SearchEmployee(un, id) != NULL)
//			//{
//			//	found = true;
//			//};
//		} while (id < 0 || found == false);
//		Course* c = un->head;
//		while (c != NULL)
//		{
//			if (c->courseID == id)
//			{
//				EnrolledCourse* enc = c->attendees;
//				bool haveIt = false;
//				while (enc != NULL) {
//					if (enc->courseReference->courseName == c->courseName)
//					{
//						cout << "This Student is already registered in this course" << endl;
//						haveIt = true;
//					}
//					enc = enc->next;
//				}
//
//				if (haveIt == false)
//					if (c != NULL)
//						enc->next = c;
//			}
//			c = c->next;
//		}
//		cout << "To exit enter q" << endl;
//		cin >> x;
//	} while (x != "q");
//}



//EnrolledCourseList* dropCourse(EnrolledCourseList* en, char courseName[20])
//{
//
//	cout << "Enter the name of the course you need to drop" << endl;
//	cin.getline(courseName,20);
//	
//	while (en->head != NULL)
//	{
//		if (en->head->courseReference->courseName == courseName)
//		{
//			en->head->next = en->head->next->next;
//			en->head->next;
//			
//		}
//	}
//
//	delete en;
//}


int main(int argc, char** argv)
{

	UniversityCourseList* un = new UniversityCourseList();
	EnrolledCourseList *enrolledStudent = new EnrolledCourseList();
	EnrolledStudent* enrolled_student = new EnrolledStudent();
	Student* s = new Student();
	Course* c = new Course();

	s = readStudents(s);

	//readStudents(enrolled_student);
	readCourse(un);

	//EnrolledStudent* enrolledStudent = new  EnrolledStudent;
	//bool state = true;

	//do {

	//	state = Login(enrolledStudent);
	//} while (state = false);

}

