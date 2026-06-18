#include <iostream>

class IntegerList {
private:
    int* list;
    int numElements;
    int index;

public:
    // Constructor
    IntegerList(int size) {
        numElements = size;
        list = new int[size];
        index = 0;
        // Initialize all elements to zero
        for (int i = 0; i < size; ++i) {
            list[i] = 0;
        }
    }

    // Destructor
    ~IntegerList() {
        delete[] list;
    }

    // Function to validate a subscript
    bool isValid(int subscript) {
        return subscript >= 0 && subscript < numElements;
    }

    // Function to add an element to the list
    bool addElement(int v) {
        if (isValid(index)) {
            list[index++] = v;
            return true;
        }
        return false;
    }

    // Function to remove the last element from the list
    int removeElement() {
        if (index > 0) {
            return list[--index];
        }
        return -1;
    }

    // Function to get an element from the list
    int getElement(int subscript) {
        if (isValid(subscript)) {
            return list[subscript];
        }
        return -1;
    }

    // Function to display all elements of the list
    void displayElements() {
        for (int i = 0; i < index; ++i) {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Example 1
    IntegerList list(5);
    std::cout << "Example 1:" << std::endl;
    std::cout << "- Create a list of 5 elements" << std::endl;
    std::cout << "- Add the following elements to the list: 1, 7, -6, 8, 9" << std::endl;
    list.addElement(1);
    list.addElement(7);
    list.addElement(-6);
    list.addElement(8);
    list.addElement(9);
    std::cout << "- Display the list: ";
    list.displayElements();
    std::cout << "- Now add another element 11 and display the list again" << std::endl;
    list.addElement(11);
    std::cout << "- Display the list: ";
    list.displayElements();
    std::cout << "- Now call removeElement() two times" << std::endl;
    list.removeElement();
    list.removeElement();
    std::cout << "- Display the list: ";
    list.displayElements();

    return 0;
}
