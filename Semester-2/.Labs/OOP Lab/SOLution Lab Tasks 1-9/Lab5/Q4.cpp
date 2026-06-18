#include <iostream>
#include <string>

// Define the CourseRegistration structure
struct CourseRegistration {
    std::string courseCode;
    std::string courseTitle;
    int creditHours;
    char section;
};

// Define the SemesterRegistration structure
struct SemesterRegistration {
    std::string semesterCode;
    CourseRegistration* course_reg; // Dynamic array of CourseRegistration
};

// Member function to get total credit hours registered in a semester
int GetCreditHoursCount(SemesterRegistration s) {
    int totalCreditHours = 0;
    // Loop through the array of course registrations
    for (int i = 0; i < 5; ++i) {
        totalCreditHours += s.course_reg[i].creditHours;
    }
    return totalCreditHours;
}

// Member function to find a course in the semester registration
bool FindCourseInSemesterRegistration(SemesterRegistration s, std::string courseCode) {
    // Loop through the array of course registrations
    for (int i = 0; i < 5; ++i) {
        // Check if the course code matches
        if (s.course_reg[i].courseCode == courseCode) {
            return true; // Course found
        }
    }
    return false; // Course not found
}

int main() {
    // Create a SemesterRegistration object
    SemesterRegistration s;
    s.semesterCode = "2024 Spring";

    // Allocate memory for the array of course registrations
    s.course_reg = new CourseRegistration[5];

    // Input information for each course registration from the user
    for (int i = 0; i < 5; ++i) {
        std::cout << "Enter details for course registration " << i + 1 << ":" << std::endl;
        std::cout << "Course Code: ";
        std::cin >> s.course_reg[i].courseCode;
        std::cout << "Course Title: ";
        std::cin >> s.course_reg[i].courseTitle;
        std::cout << "Credit Hours: ";
        std::cin >> s.course_reg[i].creditHours;
        std::cout << "Section: ";
        std::cin >> s.course_reg[i].section;
    }

    // Call the GetCreditHoursCount function to get total credit hours
    int totalCreditHours = GetCreditHoursCount(s);
    std::cout << "Total credit hours registered in the semester: " << totalCreditHours << std::endl;

    // Check if a course is registered in the semester
    std::string courseCodeToFind;
    std::cout << "Enter the course code to find: ";
    std::cin >> courseCodeToFind;
    if (FindCourseInSemesterRegistration(s, courseCodeToFind)) {
        std::cout << "The course " << courseCodeToFind << " is registered in the semester." << std::endl;
    }
    else {
        std::cout << "The course " << courseCodeToFind << " is not registered in the semester." << std::endl;
    }

    // Free the memory allocated for the array of course registrations
    delete[] s.course_reg;

    return 0;
}
