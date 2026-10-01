#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;
    std::ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open StudentData.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string lastName, firstName;

        if (std::getline(ss, lastName, ',') && std::getline(ss, firstName, ',')) {
            // Trim leading whitespace
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;
            students.push_back(student);
        }
    }
    inputFile.close();

    // Step 4: Print all student information ONLY in Debug mode
#ifdef _DEBUG
    std::cout << "[DEBUG MODE: Displaying " << students.size() << " Student Records]" << std::endl;
    for (const auto& student : students) {
        std::cout << student.lastName << ", " << student.firstName << std::endl;
    }
#endif

    return 1;
}