#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Struct to store student details
struct STUDENT_DATA {
    string firstName;
    string lastName;
#ifdef PRE_RELEASE
    string email;
#endif
};

int main() {
    // Mode banner message
#ifdef PRE_RELEASE
    cout << "Application is running: PRE-RELEASE MODE" << endl;
    string filename = "StudentData_Emails.txt";
#else
    cout << "Application is running: STANDARD MODE" << endl;
    string filename = "StudentData.txt";
#endif

    vector<STUDENT_DATA> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string lastName, firstName;

        if (getline(ss, lastName, ',') && getline(ss, firstName, ',')) {
            // Remove leading space from first name if present
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;

#ifdef PRE_RELEASE
            string email;
            if (getline(ss, email, ',')) {
                // Remove leading space from email if present
                if (!email.empty() && email[0] == ' ') {
                    email.erase(0, 1);
                }
                student.email = email;
            }
#endif
            students.push_back(student);
        }
    }
    file.close();

    // Debug output: print student records to console
#ifdef _DEBUG
    cout << "\n[DEBUG MODE: Student Records (" << students.size() << " loaded)]" << endl;
    for (const auto& s : students) {
        cout << s.lastName << ", " << s.firstName;
#ifdef PRE_RELEASE
        cout << " | " << s.email;
#endif
        cout << endl;
    }
#endif

    return 1;
}