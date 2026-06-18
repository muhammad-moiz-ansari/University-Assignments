#include <iostream>
#include <string>

// Recursive function to reverse a word
std::string reverseWord(std::string word, int start, int end) {
    // Base case: if the start index exceeds the end index, return the empty string
    if (start >= end) {
        return "";
    }

    // Swap characters at start and end indices
    char temp = word[start];
    word[start] = word[end];
    word[end] = temp;

    // Recursive call to reverse the substring between start+1 and end-1
    return reverseWord(word, start + 1, end - 1);
}

int main() {
    std::string inputWord = "hello";

    // Call the recursive function to reverse the word
    std::string reversedWord = reverseWord(inputWord, 0, inputWord.length() - 1);

    std::cout << "Input: " << inputWord << std::endl;
    std::cout << "Reversed: " << reversedWord << std::endl;

    return 0;
}
