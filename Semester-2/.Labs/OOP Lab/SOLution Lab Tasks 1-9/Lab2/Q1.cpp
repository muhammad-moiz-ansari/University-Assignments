#include <iostream>

int myStrLen(char* str) {
    int length = 0;
    // Loop until the null terminator is encountered
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int main() {
    char str[] = "Hello, World!";
    int length = myStrLen(str);
    std::cout << "Length of the string: " << length << std::endl;
    return 0;
}
