#include <iostream>
#include <string>

// Define the Student structure
struct Student {
    std::string name;
    std::string roll_no;
    int age;
};

// Function to check if a roll number is even (based on the last digit)
bool isEvenRollNo(const std::string& roll_no) {
    // Get the last character of the roll number
    char last_digit = roll_no.back();
    // Convert it to an integer
    int digit = last_digit - '0';
    // Check if it's even
    return (digit % 2 == 0);
}

// Member function to get names of students having age 18
std::string* getNames(Student* std) {
    // Allocate memory for storing names of students having age 18
    std::string* names = new std::string[5];
    int count = 0;

    // Loop through the array of students
    for (int i = 0; i < 5; ++i) {
        // Check if the student's age is 18
        if (std[i].age == 18) {
            // Store the name of the student
            names[count] = std[i].name;
            count++;
        }
    }

    // Resize the array of names to fit the actual number of students with age 18
    std::string* resizedNames = new std::string[count];
    for (int i = 0; i < count; ++i) {
        resizedNames[i] = names[i];
    }

    // Free the memory allocated for the original array of names
    delete[] names;

    // Return the array of names of students with age 18
    return resizedNames;
}

// Member function to get information of students with even roll numbers
Student* getEvenRollno(Student* std) {
    // Allocate memory for storing information of students with even roll numbers
    Student* evenRollStudents = new Student[5];
    int count = 0;

    // Loop through the array of students
    for (int i = 0; i < 5; ++i) {
        // Check if the roll number is even
        if (isEvenRollNo(std[i].roll_no)) {
            // Store the information of the student
            evenRollStudents[count] = std[i];
            count++;
        }
    }

    // Resize the array of students to fit the actual number of students with even roll numbers
    Student* resizedStudents = new Student[count];
    for (int i = 0; i < count; ++i) {
        resizedStudents[i] = evenRollStudents[i];
    }

    // Free the memory allocated for the original array of students
    delete[] evenRollStudents;

    // Return the array of students with even roll numbers
    return resizedStudents;
}

int main() {
    // Create an array of Student objects
    Student students[5];

    // Input information for each student from the user
    for (int i = 0; i < 5; ++i) {
        std::cout << "Enter details for student " << i + 1 << ":" << std::endl;
        std::cout << "Name: ";
        std::cin >> students[i].name;
        std::cout << "Roll Number: ";
        std::cin >> students[i].roll_no;
        std::cout << "Age: ";
        std::cin >> students[i].age;
    }

    // Call the getNames function to get names of students with age 18
    std::string* names = getNames(students);

    // Output the names of students with age 18
    std::cout << "Names of students with age 18:" << std::endl;
    for (int i = 0; i < sizeof(names); ++i) {
        std::cout << names[i] << std::endl;
    }

    // Free the memory allocated for the array of names
    delete[] names;

    // Call the getEvenRollno function to get information of students with even roll numbers
    Student* evenRollStudents = getEvenRollno(students);

    // Output the information of students with even roll numbers
    std::cout << "Information of students with even roll numbers:" << std::endl;
    for (int i = 0; i < sizeof(evenRollStudents); ++i) {
        std::cout << "Name: " << evenRollStudents[i].name << ", Roll Number: " << evenRollStudents[i].roll_no << ", Age: " << evenRollStudents[i].age << std::endl;
    }

    // Free the memory allocated for the array of students with even roll numbers
    delete[] evenRollStudents;

    return 0;
}
