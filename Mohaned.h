#ifndef MOHANED_H
#define MOHANED_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "nlohmann/json.hpp"

// using clear with all OS.. 
#ifdef _WIN32
    #define __CLEAR system("cls")
#else 
    #define __CLEAR system("clear")
#endif

using nlohmann::json; // for the database.
using std::ifstream;  // for opning and reading the database file.
using std::ofstream;  // for opning and written the database file.
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

namespace Student {

	// Public Use.
	static const string& databaseFile = "StudentDatabase.json"; // name of database file.
    static const string& aboutFile = "About.txt"; // name of about programmer file.
	static const string MAJORS[4] = { "IT","IS","CS","CYS" } ; // using for match the major
	static const int academicNumber = 24160000; // using for generate the ID.
	struct StudentData {
		int id = 0;
		string firstName = "Unknown";           // the first letter should by uppercase and no (numbers or space).
		string lastName = "Anonymous";          // the first letter should by uppercase and no (numbers or space).
		string major = "Not Found";             // Should by in ("IT","IS","CS","CYS") and uppercase.
		short int level = 1 ;                   // Should by ( 1 <= level <= 4 ).
		static const short int SIZE = 6;        // the SIZE of marks Should by 6.
		short int marks[SIZE] = {0,0,0,0,0,0};  // Should by ( 0 <= marks[x] <= 100 ).
		short int totalMarks = 0;               // Should by ( 0 <= totalMarks <= 600 ).
		float grade = 0;                        // Should stor the (totalMarks/SIZE).
	};
	StudentData searchForStudentRecord(bool searchByName); // using for searching about a student.
	void displayAllStudentRecord(string choice); // using for display all the students records.
	void deleteStudentRecord(); // using for delete a student record.
	void editStudentRecord(); // using for edit the student record.
	void addNewStudent(); // using for add a new student.
    void displayAbout(); // using for display the about message.

	// Internal Use
	namespace Internal {
        void displayTable(vector<Student::StudentData> students, const int SIZE); // using for drawing the student table.
		StudentData searchValue(json data, string value, int id); // using for search in the data.
		bool pushDataToDatabase(StudentData student, bool edit ); // using for pushing the data to the database.
        void displayOrdered(json data, string choice); // using for ordered the student.
		void viewStudentData( StudentData student ); // using for display the student data.
		short int theTotalMarks( short int marks[]); // using for calculating the total marks.
		void toUpperCase(string& str, bool first ); // using for converting the string to upper case.
		vector<string> getKeys(json data); // using for getting keys from the database.
		string getKey(json data, int id); // using for getting a student key from the database.
		bool checkNames(string str); // using for cheching the name.
		bool checkMajor(string str); // using for cheching the major.
		bool checkLevel(string str); // using for cheching the level.
		bool checkMark(string str); // using for cheching the mark.
        json readFile(); // using for reading the files.
	}
}

#endif