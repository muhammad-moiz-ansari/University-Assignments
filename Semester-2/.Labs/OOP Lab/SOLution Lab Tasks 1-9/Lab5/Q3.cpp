#include <iostream>

// Define the CustomTime structure
struct CustomTime {
    int hours;
    int mins;
    int secs;
};

// Member function to convert CustomTime object to total seconds
int timeToSecs(CustomTime t1) {
    // Calculate total seconds in time
    int totalSeconds = t1.hours * 3600 + t1.mins * 60 + t1.secs;
    return totalSeconds;
}

// Member function to add two CustomTime objects
int AddTimes(CustomTime t1, CustomTime t2) {
    // Convert both CustomTime objects to total seconds
    int totalSeconds1 = timeToSecs(t1);
    int totalSeconds2 = timeToSecs(t2);

    // Add both seconds
    int total = totalSeconds1 + totalSeconds2;
    return total;
}

int main() {
    // Create CustomTime objects
    CustomTime t1 = { 10, 20, 30 };
    CustomTime t2 = { 1, 2, 3 };

    // Call the AddTimes function to add the times
    int totalSeconds = AddTimes(t1, t2);

    std::cout << "Total seconds: " << totalSeconds << std::endl;

    return 0;
}
