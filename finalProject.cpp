#include "Mohaned.h"

int main() {
	string choice;
	while (true) {
		cout << "\t___________ HOME PAGE _____________" << endl
			<< "\t|                                 |" << endl
			<< "\t| 1- Add a New Student.           |" << endl
			<< "\t| 2- Search For a Student.        |" << endl
			<< "\t| 3- Edit Studetn Recored.        |" << endl
			<< "\t| 4- Delete Student Recored.      |" << endl
			<< "\t| 5- Display All Students Record. |" << endl
			<< "\t| 6- Exit.                        |" << endl
			<< "\t|_________________________________|" << endl;
		choiceError :
			cout << "\t$ ";
			getline(cin, choice);
			if (choice == "1" ) {
				__CLEAR;
				Student::addNewStudent();
				cout << "\t- Press Enter..";
				getline(cin, choice);
				__CLEAR;
			}
			else if ( choice == "2" ) {
				searchError:
					cout << endl;
					cout << "\t\t1- Search by ID *(Recominded)." << endl
						<< "\t\t2- Search by Name *(Not Recominded)" << endl
						<< "\t\t$ ";
					getline(cin, choice);
					__CLEAR;
					if (choice == "1") {
                        Student::searchForStudentRecord(0);
                        cout << "\t- Press Enter..";
                        getline(cin, choice);
                        __CLEAR;
					}
					else if (choice == "2") {
                        Student::searchForStudentRecord(1);
                        cout << "\t- Press Enter..";
                        getline(cin, choice);
                        __CLEAR;
					}
                    else if (choice == "back") continue;
					else {
						cout << endl;
						cout << "\t     - Error Input.." << endl;
						cout << "\t     - Please try again.." << endl;
						goto searchError;
					}
			}
			else if (choice == "3") {
				__CLEAR;
				Student::editStudentRecord();
				cout << "\t- Press Enter..";
				getline(cin, choice);
				__CLEAR;
			}
			else if (choice == "4") {
				__CLEAR;
				Student::deleteStudentRecord();
				cout << "\t- Press Enter..";
				getline(cin, choice);
				__CLEAR;
			}
			else if (choice == "5") {
                orderError:
                    
                    cout << endl;
                    cout << "\t- Choice the Order by: "<<endl ;
                    cout << "\t\t1- ID. " << endl
                        << "\t\t2- Name." << endl
                        << "\t\t3- Grade." << endl
                        << "\t\t$ ";
                    getline(cin, choice);
                    __CLEAR;
                    if (choice == "1") Student::displayAllStudentRecord("ID");
                    else if (choice == "2") Student::displayAllStudentRecord("NAME");
                    else if (choice == "3") Student::displayAllStudentRecord("GRADE");
                    else if (choice == "back") continue;
                    else {
                        cout << endl;
                        cout << "\t\t[?] Error Input..." << endl;
                        cout << "\t\t[!] Please try again.." << endl;
                        goto orderError;
                    }
				    cout << "\t- Press Enter..";
				    getline(cin, choice);
				    __CLEAR;
			}
			else if (choice == "6" || choice == "99") {
				__CLEAR;
				cout << "\t -I Will Miss You.." << endl;
				return 0;
			}
			else if (choice == "about" ) {
                __CLEAR;
                Student::displayAbout();
                cout << endl;
                cout << "* Press Enter..";
                getline(cin, choice);
                __CLEAR;
			}
			else {
				cout << "\t     - Error Input..." << endl;
				cout << "\t     - Please try again.." << endl;
				goto choiceError;
			}
	}
}