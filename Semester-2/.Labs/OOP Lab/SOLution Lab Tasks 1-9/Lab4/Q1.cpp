#include <iostream>

// Recursive function to count occurrences of a specific character in a string
int getCharCount(const char* ptr, char c) {
    // Base case: if the pointer is pointing to the null terminator, return 0
    if (*ptr == '\0') {
        return 0;
    }

    // If the current character matches the specified character, increment count
    int count = (*ptr == c) ? 1 : 0;

    // Recursive call to count occurrences of the character in the remaining substring
    return count + getCharCount(ptr + 1, c);
}

int main() {
    const char* ptr = "wavelength";
    char c = 'e';

    // Call the recursive function to get the count of the character
    int count = getCharCount(ptr, c);

    std::cout << "Count of character '" << c << "' in the string: " << count << std::endl;

    return 0;
}
