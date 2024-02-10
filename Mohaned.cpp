#include "Mohaned.h"

// start internal bodys:
void Student::Internal::displayTable(vector<Student::StudentData> students,const int SIZE ) {
    /*
           ------------------------ The Documentation ------------------------
        - Belongs To :
            it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

        - About The Function:
            This function displayes the student on the screen.

        - It Used :
            -    Name                 Type                    belongs                   Information
            - StudentData		 -> struct		          - Student              - to receive information form the database.
    */
    string name;
    for (int i = 0; i < SIZE; i++ ) {
        name = students[i].firstName + " " + students[i].lastName;
        cout << "\t ";
        cout << std::left << std::setw(12) << std::to_string(students[i].id)
            << std::left << std::setw(20) << name
            << std::left << std::setw(7) << students[i].major
            << std::left << std::setw(7) << students[i].level 
            << std::left << std::setw(7) << std::to_string(students[i].totalMarks)
            << "%" << std::to_string(students[i].grade)
            << endl;
    }
}
Student::StudentData Student::Internal::searchValue(json data, string value ,int id ) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function receives data from the database (JSON File) and search for a match 
			between the values to return the target student.

		- It Used :
			-    Name                 Type                       belongs               Information
			- StudentData		 -> struct			        - Student           - to receive information form the database.
			- json               -> data Type Map           - nlohmann::json    - used to communicate with JSON files.
			- getKeys            -> string vector function  - Student::Internal - return the keys from the JSON file.
			
	*/
	string fullName;
	Student::StudentData student;
	Student::Internal::toUpperCase(value, 0);
	for (std::string key : Student::Internal::getKeys(data)) {
		 fullName = data[key]["firstName"].get<string>() + " " + data[key]["lastName"].get<string>() ;
		 Student::Internal::toUpperCase(fullName, 0);
		 if (fullName == value || data[key]["id"].get<int>() == id) {
			student.id         = data[key]["id"].get<int>();
			student.firstName  = data[key]["firstName"].get<string>();
			student.lastName   = data[key]["lastName"].get<string>() ;
			student.level      = data[key]["level"].get<int>();
			student.grade      = data[key]["grade"].get<float>() ;
			student.totalMarks = data[key]["totalMarks"].get<int>() ;
			student.major      = data[key]["major"].get<string>() ;
			for (int i = 0; i < Student::StudentData::SIZE; i++)
				student.marks[i] = data[key]["marks"][i].get<int>() ;
			return student ;
		}
	}
	return student;
}
bool Student::Internal::pushDataToDatabase(Student::StudentData student, bool edit ) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function enters the values receivrd from the user 
			into the database (JSON File).

		- It Used :
			-    Name                 Type                       belongs               Information
			- StudentData		 -> struct			        - Student           - to receive information form the database.
			- json               -> data Type Map           - nlohmann::json    - used to communicate with JSON files.
			- getKey             -> string function         - Student::Internal - return the key for the student by ID.
            - readFile           -> json function           - Student::Internal - return the data from the database.
	*/
	json data = Student::Internal::readFile() ;
	// add the student info to the data :
	int lastKey = (edit) ? std::stoi(Student::Internal::getKey(data,student.id)) : data["lastKey"].get<int>() + 1;
	string number = std::to_string(lastKey) ;
	data[number]["id"] = (edit) ? student.id : Student::academicNumber + data["idNumber"].get<int>() + 1 ;
	data[number]["firstName"] = student.firstName ;
	data[number]["lastName"] = student.lastName ;
	data[number]["grade"] = student.grade ;
	data[number]["level"] = student.level ;
	data[number]["major"] = student.major ;
	data[number]["marks"] = student.marks ;
	data[number]["totalMarks"] = student.totalMarks ;
	// change numberOfStudents value :
    data["numberOfStudents"] = (edit) ? data["numberOfStudents"].get<int>() : data["numberOfStudents"].get<int>() + 1;
	data["idNumber"] = (edit) ? data["idNumber"].get<int>() : data["idNumber"].get<int>() + 1;
	data["lastKey"] = (edit) ? data["lastKey"].get<int>() : lastKey ;
	// add the data to StudentDatabase :
	ofstream write("StudentDatabase.json");
	if ( write.is_open() ) {
		write << data.dump(4);
		write.close();
		return 1;
	}
	else {
		std::cerr << "Write File ERROR.. " << endl;
		return 0;
	}
}
void Student::Internal::viewStudentData( Student::StudentData student) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function receives a spaecific studnet and display his datails
			on the screen.

		- It Used :
			-    Name                 Type                       belongs               Information
			- StudentData		 -> struct			        - Student           - to receive information form the database.

	*/
	cout << endl;
	cout << "\t- ID : " << student.id << endl;
	cout << "\t- First Name : " << student.firstName << endl;
	cout << "\t- Last Name : " << student.lastName << endl;
	cout << "\t- Major : " << student.major << endl;
	cout << "\t- Level : " << student.level << endl;
	cout << "\t- Maks : " << endl;
	for (int i = 0; i < Student::StudentData::SIZE; i++)
		cout << "\t\t-- Subject " << i + 1 << " : " << student.marks[i] << endl;
	cout << "\t- Total Marks : " << student.totalMarks << endl;
	cout << "\t- Grade : %" << student.grade << endl;
	cout << endl;
}
void Student::Internal::displayOrdered( json data, string choice) {
    /*
           ------------------------ The Documentation ------------------------
        - Belongs To :
            it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

        - About The Function:
            This function arrages the student according to ID or name or grade and
            displayes the student on the screen.

        - It Used :
            -    Name                 Type                    belongs                   Information
            - StudentData		 -> struct		          - Student              - to receive information form the database.
            - json               -> data Type Map         - nlohmann::json       - used to communicate with JSON files.
            - displayTable       -> void function         - Student::Internal    - display the student info in the screen.
    */
    const int SIZE = data["numberOfStudents"];
    int i = 0;
    vector<Student::StudentData> students(SIZE) ;
    for (string key : Student::Internal::getKeys(data)) {
        students[i].id = data[key]["id"].get<int>();
        students[i].firstName = data[key]["firstName"].get<string>();
        students[i].lastName = data[key]["lastName"].get<string>();
        students[i].major = data[key]["major"].get<string>();
        students[i].level = data[key]["level"].get<int>();
        students[i].totalMarks = data[key]["totalMarks"].get<int>();
        students[i].grade = data[key]["grade"].get<float>();
        i++;
    }
    Student::StudentData s;
    if (choice == "ID" ) {
        for (int i = 0; i < SIZE; i++) {
            for (int x = 0; x < SIZE; x++) {
                if (students[i].id < students[x].id) {
                    s = students[i];
                    students[i] = students[x];
                    students[x] = s;
                }
            }
        }
    }
    else if (choice == "NAME") {
        for (int i = 0; i < SIZE; i++) {
            for (int x = 0; x < SIZE; x++) {
                if (students[i].firstName < students[x].firstName ) {
                    s = students[i];
                    students[i] = students[x];
                    students[x] = s;
                }
            }
        }
    }
    else if (choice == "GRADE" ) {
        for (int i = 0; i < SIZE; i++) {
            for (int x = 0; x < SIZE; x++) {
                if (students[i].grade > students[x].grade ) {
                    s = students[i];
                    students[i] = students[x];
                    students[x] = s;
                }
            }
        }
    }
    Student::Internal::displayTable(students, SIZE);
}
void Student::Internal::toUpperCase(string& str, bool first ) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function convert sentences or letter to uppercase.

		- It Used :
			-    Name                 Type                       belongs               Information
	*/
	string result="" ;
	if (first) {
		result += std::toupper(static_cast<unsigned char> (str[0]) );
		for (int i = 1; i < str.length() ; i++ ) {
			result += tolower( str[i] ) ;
		}
	}
	else {
		for (char letter : str) {
			result += std::toupper(static_cast<unsigned char>(letter));
		}
	}
	str = result;
	return;
}
short int Student::Internal::theTotalMarks(short int marks[]) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function return the total of marks.

		- It Used :
			-    Name                 Type                    belongs               Information
			- StudentData		 -> struct			        - Student           - to get the SIZE
	*/
	short int total = 0;
	for (int i = 0; i < Student::StudentData::SIZE ; i++) {
		total += marks[i];
	}
	return total;
}
vector<string> Student::Internal::getKeys(json data) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function receives data from the database (JSON File) and return the keys of students.

		- It Used :
			-    Name                 Type                       belongs                       Information
			- StudentData		 -> struct			        - Student                     - to receive information form the database.
			- interator          -> data type               - nlohmann::json::iterator    - navigate between obejct properties.
	*/
	vector<string> keys;
	for (json::iterator it = data.begin(); it != data.end(); ++it) {
		if (it.key() != "numberOfStudents" && it.key() != "lastKey" && it.key() != "idNumber" )
			keys.push_back(it.key());
	}
	return keys;
}
string Student::Internal::getKey(json data, int id) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function receives data from the database (JSON File) and ruturn sepcific student key.

		- It Used :
			-    Name                 Type                       belongs               Information
			- json               -> data Type Map           - nlohmann::json    - used to communicate with JSON files.
			- getKeys            -> string vector function  - Student::Internal - return the keys from the JSON file.
	*/
	for (std::string key : Student::Internal::getKeys(data)) {
		if (data[key]["id"].get<int>() == id) return key;
	}
}
bool Student::Internal::checkNames(string str) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function returns if boolean value if the string name equal to the conditins.

		- It Used :
			-    Name                 Type                       belongs               Information
	*/
	if (str.length() == 0) return 1;
	for (char letter : str ) {
		if (letter == ' ' || !( (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z'))) return 1;
	}
	return 0;
}
bool Student::Internal::checkMajor(string str) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function returns if boolean value if the string major equal to the conditins.

		- It Used :
			-    Name                 Type                       belongs               Information
	*/
	for (string major : Student::MAJORS ) {
		if (str == major) return 0;
	}
	return 1;
}
bool Student::Internal::checkLevel(string str) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function returns if boolean value if the int level equal to the conditins.

		- It Used :
			-    Name                 Type                       belongs               Information
	*/
	if (str.length() > 1 || str.empty()) return 1;
	else if (str[0] >= '1' && str[0] <= '4') return 0;
	return 1;
}
bool Student::Internal::checkMark(string str) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

		- About The Function:
			This function returns if boolean value if the int mark equal to the conditins.

		- It Used :
			-    Name                 Type                       belongs               Information
	*/
	if (str.length() == 0) return 1;
	try {
		int num = std::stoi(str);
		return (num >= 0 && num <= 100) ? 0 : 1;
	}
	catch (...) {
		return 1; 
	}
}
json Student::Internal::readFile() {
    /*
            ------------------------ The Documentation ------------------------
        - Belongs To :
            it belongs to (the child namespace `Internal` in the parent namespace `Student`) in header file named `Mohaned.h`.

        - About The Function:
            This function read database file and return the data.

        - It Used :
            -    Name                 Type                       belongs               Information
            - json               -> data Type Map           - nlohmann::json    - used to communicate with JSON files.
    */
    json data;
    ifstream readFile(Student::databaseFile);
    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    }
    else {
        std::cerr << "Read File ERROR.. " << endl;
    }
    return data;
}
// end internal bodys. 

// start public bodys :
//1
void Student::addNewStudent() {
	/*
	       ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to the parent namespace `Student` in header file named `Mohaned.h`.

		- About The Function: 
			This function adds a new student to the database by
			taking values from the user, filtering them, and 
			analyzing them to suit the requirements of the database.

		- It Used :
			-    Name                 Type                   belongs               Information 
			- StudentData		 -> struct			   - Student           - to receive information form the user.
			- theTotalMarks		 -> short int function - Student::Internal - returns the sum of subject grades.
			- checkNames		 -> bool function      - Student::Internal - returns a boolean value if the name meets the database conditions.
			- toUpperCase	     -> void function      - Student::Internal - convert the string received by the function to upper case.
			- chackMajor		 -> bool function      - Student::Internal - returns a boolean value if the major meets the database conditions.
			- chackLevel		 -> bool function      - Student::Internal - returns a boolean value if the level meets the database conditions.
			- checkMark          -> bool function      - Student::Internal - returns a boolean value if the mark meets the database conditions.
			- pushDataToDatabase -> bool function      - Student::Internal - used to enter the data into the database.
	*/

	Student::StudentData student;
	cout << "\t___________ ADD STUDENT _____________" << endl << endl;
	firstNameError : // chacking the first name.
		cout << "\t- First Name (String Only) : ";
		getline(cin , student.firstName);
		Student::Internal::toUpperCase(student.firstName, 1);
		if ( Student::Internal::checkNames(student.firstName) ) {
			cout << "\t\t[?] Input Error: The input (have space or length of 0 or it has a number)." << endl;
			cout << "\t\t[!] Please try again.." << endl;
			goto firstNameError;
		}
	lastNameError : // chacking the last name.
		cout << "\t- Last Name (String Only) : ";
		getline(cin, student.lastName);
		Student::Internal::toUpperCase(student.lastName, 1);
		if ( Student::Internal::checkNames(student.lastName) ) {
			cout << "\t\t[?] Input Error: The input (have space or length of 0 or it has a number)." << endl;
			cout << "\t\t[!] Please try again.." << endl;
			goto lastNameError;
		}
	majorError : // chacking the major.
		cout << "\t- Major ('IT','IS','CS','CYS') : ";
		getline(cin, student.major) ;
		Student::Internal::toUpperCase(student.major, 0);
		if (Student::Internal::checkMajor(student.major)) {
			cout << "\t\t[?] Input Error: The input not in ('IT','IS','CS','CYS')." << endl;
			cout << "\t\t[!] Please try again.." << endl;
			goto majorError;
		}
	levelError : // chacking the level. 
		string level;
		cout << "\t- Level ( 1 <= x <= 4 ) : ";
		getline(cin, level) ;
		if ( Student::Internal::checkLevel(level) ) {
			cout << "\t\t[?] Input Error: The input is not on ( 1 <= x <= 4 )."<<endl ;
			cout << "\t\t[!] Please try again.." << endl;
			goto levelError;
		}
		student.level = std::stoi(level);
	cout << "\t- Marks ( 0 <= x <= 100 ) : " << endl;
	string mark;
	// the marks loop
	for (int i = 0; i < student.SIZE; i++ ) {
		markError : // chacking the mark.
			cout << "\t\t-- Subject " << i + 1 << " : ";
			getline(cin, mark );
			if (Student::Internal::checkMark(mark)) {
				cout << "\t\t[?] Input Error: the input is not in ( 0 <= x <= 100 )." << endl;
				cout << "\t\t[!] Please try again.." << endl;
				goto markError;
			}
			student.marks[i] = std::stoi(mark);
	}
	student.totalMarks = Student::Internal::theTotalMarks(student.marks);
	cout << "\t- Total : " << student.totalMarks << endl;
	student.grade = (float)student.totalMarks / student.SIZE;
	cout << "\t- Grade : " << student.grade << endl;
	// using pushDataToDatabase for add new student (not edit one).
	bool isDone = Student::Internal::pushDataToDatabase(student,0);
	if (isDone) {
		cout << endl;
		cout << "\t- It has been added successfully." << endl ;
	}
	else {
		cout << endl;
		cout << "\t[?] There is an error in the file (.json). Make sure to close it." << endl;
		cout << "\t[?] It was not added, please try again." << endl;
	}
}
//2
Student::StudentData Student::searchForStudentRecord( bool searchByName ) {
	/*
		   ------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to the parent namespace `Student` in header file named `Mohaned.h`.

		- About The Function:
			This function searches within the database for the target student
			by name or ID, so it returns complete data about the student using 
			`StudnetData` as the data container.

		- It Used :
			-    Name                 Type                      belongs               Information
			- StudentData		 -> struct			      - Student           - to receive information form the database.
			- json               -> data Type Map         - nlohmann::json    - used to communicate with JSON files.
			- ifstream           -> data Tyoe             - std::ifstream     - used to read JSON file content.
			- searchValue        -> StudentData function  - Student::Internal - used to returns the search for student in data received form JSON file.
			- viewStudentData    -> void function         - Student::Internal - used to view all student data.
            - readFile           -> json function         - Student::Internal - return the data from the database.
	*/
	json data = Student::Internal::readFile() ;
	Student::StudentData student;
	cout << "\t___________ SEARCH PAGE _____________" << endl << endl;
	if (searchByName) {
		string fullName;
		cout << "\t- Enter Student Name: ";
		getline(cin, fullName);
		student = Student::Internal::searchValue(data, fullName,0);
		if (student.id!=0) {
			Student::Internal::viewStudentData(student);
			return student;
		}
		else cout << "\t\t[!] Student With Name Not Found..." << endl;
	}
	else {
		string id;
		idError :
			cout << "\t- Enter the id : ";
			getline(cin, id);
			try {
                int ID = std::stoi(id);
                ID = (ID < Student::academicNumber) ? ID + Student::academicNumber : ID;
				student = Student::Internal::searchValue(data, "0", ID);
				if (student.id != 0) {
					Student::Internal::viewStudentData(student);
					return student;
				}
				else {
					cout << "\t\t[!] Student with ID Not Found..." << endl;
				}
			}
			catch (...) {
				cout << "\t\t[?] Input Error: Enter the full ID." << endl;
				cout << "\t\t[!] Please try again.." << endl;
				goto idError;
			}
	}
	return student;
}
//3 
void Student::editStudentRecord() {
	/*
			------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to the parent namespace `Student` in header file named `Mohaned.h`.

		- About The Function:
			This function is used to modfiy the student record specified by 
			ID, and then it works to implement the modifications to the database.

		- It Used :
			-    Name                    Type                      belongs               Information
			- StudentData		     -> struct			      - Student           - to receive information form the database.
			- searchForStudentRecord -> StudentData function  - Student           - returns student data by seaching about it by ID.
			- checkNames		     -> bool function         - Student::Internal - returns a boolean value if the name meets the database conditions.
			- toUpperCase	         -> void function         - Student::Internal - convert the string received by the function to upper case.
			- chackMajor		     -> bool function         - Student::Internal - returns a boolean value if the major meets the database conditions.
			- chackLevel		     -> bool function         - Student::Internal - returns a boolean value if the level meets the database conditions.
			- checkMark              -> bool function         - Student::Internal - returns a boolean value if the mark meets the database conditions.
			- pushDataToDatabase     -> bool function         - Student::Internal - used to enter the data into the database.
	*/
	Student::StudentData student = Student::searchForStudentRecord(0) ;
	if (student.id != 0) {
		string str;
		cout << "\t___________ EDIT PAGE _____________" << endl << endl;
		cout << "\t- If you want to leave the modification to a secific things," << endl;
		cout << "\t  press Enter." << endl;
		firstNameError:
			cout << "\t- (Edit) Frist Name: ";
			getline(cin, str);
			if (str.length() != 0) {
				if (Student::Internal::checkNames(str)) {
					cout << "\t\t[?] Input Error: The input (have space or it has a number)." << endl;
					cout << "\t\t[!] Please try again.." << endl;
					goto firstNameError;
				}
				else student.firstName = str;
			}
		lastNameError:
			cout << "\t- (Edit) Last Name: ";
			getline(cin, str);
			if (str.length() != 0) {
				if (Student::Internal::checkNames(str)) {
					cout << "\t\t[?] Input Error: The input (have space or it has a number)." << endl;
					cout << "\t\t[!] Please try again.." << endl;
					goto lastNameError;
				}
				else student.lastName = str;
			}
		majorError:
			cout << "\t- (Edit) Major: ";
			getline(cin, str);
			if (str.length() != 0) {
				Student::Internal::toUpperCase(str, 0);
				if (Student::Internal::checkMajor(str)) {
					cout << "\t\t[?] Input Error: The input not in ('IT','IS','CS','CYS')." << endl;
					cout << "\t\t[!] Please try again.." << endl;
					goto majorError;
				}
				else student.major = str;
			}
		levelError:
			cout << "\t- (Edit) Level: ";
			getline(cin, str);
			if (str.length() != 0) {
				if (Student::Internal::checkLevel(str)) {
					cout << "\t\t[?] Input Error: The input is not on ( 1 <= x <= 4 )." << endl;
					cout << "\t\t[!] Please try again.." << endl;
					goto levelError;
				}
				else student.level = std::stoi(str);
			}
		cout << "\t- (Edit) Marks: " << endl;
		for (int i = 0; i < student.SIZE; i++) {
			markError:
				cout << "\t\t-- (Edit) Subject " << i + 1 << " : ";
				getline(cin, str);
				if (str.length() != 0) {
					if (Student::Internal::checkMark(str)) {
						cout << "\t\t[?] Input Error: the input is not in ( 0 <= x <= 100 )." << endl;
						cout << "\t\t[!] Please try again.." << endl;
						goto markError;
					}
					else student.marks[i] = std::stoi(str);
				}
		}
		student.totalMarks = Student::Internal::theTotalMarks(student.marks);
		cout << "\t- Total Marks: " << student.totalMarks << endl;
		student.grade = student.totalMarks / student.SIZE;
		cout << "\t- Grade: " << student.grade << endl;
		// using pushDataToDatabase for edit and push.
		Student::Internal::pushDataToDatabase(student, 1);
	}
}
//4 
void Student::deleteStudentRecord() {
	/*
			------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to the parent namespace `Student` in header file named `Mohaned.h`.

		- About The Function:
			This function works to permanently delete the target student's
			record by ID form the database.

		- It Used :
			-    Name                    Type                      belongs               Information
			- StudentData		     -> struct			      - Student           - to receive information form the database.
			- searchForStudentRecord -> StudentData function  - Student           - returns student data by seaching about it by ID.
			- toUpperCase	         -> void function         - Student::Internal - convert the string received by the function to upper case.
			- getKey                 -> string function       - Student::Internal - returns student location in JSON file.
			- json                   -> data Type Map         - nlohmann::json    - used to communicate with JSON files.
			- ifstream               -> data Tyoe             - std::ifstream     - used to read JSON file content.
            - readFile               -> json function           - Student::Internal - return the data from the database.
	*/
	Student::StudentData student = Student::searchForStudentRecord(0);
	string isSure;
	cout << "\t___________ DELETE PAGE _____________" << endl << endl;
	isSureError :
		cout << "\t- Are You suer (Yes/No): ";
		getline(cin, isSure);
		Student::Internal::toUpperCase(isSure, 0);
		if (isSure == "YES" || isSure == "Y") {
			json data = Student::Internal::readFile() ;
			string key = Student::Internal::getKey(data, student.id);
			data.erase(key);
            data["numberOfStudents"] = data["numberOfStudents"].get<int>() - 1;
			ofstream write(Student::databaseFile);
			if (write.is_open()) write << data.dump(4) ;
		}
		else if (isSure == "NO" || isSure == "N") cout << "\t- Ok I Will not delet the student." << endl;
		else {
			cout << "\t\t[?] Input Error.. Enter ( Yes/No or Y/N )."<<endl;
			cout << "\t\t[!] Please try again.." << endl;
			goto isSureError;
		}
}
//5 
void Student::displayAllStudentRecord(string choice) {
	/*
			------------------------ The Documentation ------------------------
		- Belongs To :
			it belongs to the parent namespace `Student` in header file named `Mohaned.h`.

		- About The Function:
			This function displays all students in the database.

		- It Used :
			-    Name                    Type                      belongs               Information
			- json                   -> data Type Map         - nlohmann::json    - used to communicate with JSON files.
			- ifstream               -> data Tyoe             - std::ifstream     - used to read JSON file content.
			- setw                   -> manipulator           - iomanip::std      - used to fromat the table view.
            - displayOrdered         -> void function         - Student::Internal - display students sort by id or name or gared.
            - readFile               -> json function           - Student::Internal - return the data from the database.
	*/
	json data = Student::Internal::readFile();
	cout << "\t___________________________ STUDENTS ______________________________" << endl << endl;
	cout << std::left << std::setw(14) << "\t- ID" 
			<< std::left << std::setw(20) << "Name" 
            << std::left << std::setw(7)  << "Major"
            << std::left << std::setw(7)  << "Level"
			<< std::left << std::setw(7)  << "Total" << "Grade" << endl;
	cout << "\t-------------------------------------------------------------------" << endl;
    Student::Internal::displayOrdered(data, choice);
	cout << "\t-------------------------------------------------------------------" << endl;
    cout << "\t[*] Number Of Student in the database is : " << data["numberOfStudents"] << endl;
}
//6 
void Student::displayAbout() {
    ifstream read(Student::aboutFile);
    string line;
    if (read.is_open()) {
        while (getline(read, line)) {
            cout << line << endl;
        }
    }
}
// end public bodys 