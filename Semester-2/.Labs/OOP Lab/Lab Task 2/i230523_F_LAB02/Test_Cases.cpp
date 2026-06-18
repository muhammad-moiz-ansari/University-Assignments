#include "pch.h"
#include "D:\Documents\Old Semesters\Semester-2\.Labs\OOP Lab\Lab Task 2\i230523_F_LAB02\Lab 2\Lab 2\Header.h"
#include <gtest/gtest.h>


// ques 1
TEST(AssignAndDisplayTest, TestValues) {

    std::string expectedOutput = "Value of 'a' through pointer ptrA: 3\nValue of 'b' through pointer ptrB: 7\n";

    ASSERT_EQ(assignAndDisplayValues(3, 7), expectedOutput);
}
//ques 2
TEST(PointerTest, TestDetails) {
    const char* inputStr = "A string.";
    int pointerPosition = 0;

    std::string expectedOutput = "Index 0: A, Pointer Position: 0, Letter 't': t\nPointer: 2, Letters 'r' and 'g': r g\n";

    ASSERT_EQ(printAndUpdatePointer(inputStr, pointerPosition), expectedOutput);
    ASSERT_EQ(printPointerAndLetters(inputStr, pointerPosition), expectedOutput);
}
//ques 3
TEST(calculateGrades, grade) {
    int arr[] = { 95, 63, 76, 40, 85 };
    char a[] = { 'A','C','B','F','B' };
    char* arr1 = calculateGrades(arr, 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(a[i], arr1[i]);
    }

    int arr2[] = { 35, 72, 59, 88, 100, 43 };
    char a1[] = { 'F','C','D','B','A','F' };
    char* arr3 = calculateGrades(arr2, 6);

    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(a1[i], arr3[i]);
    }

}
//ques 4
TEST(rotateArray, rotate) {
    int arr[] = { 1,2,3,4,5,6 };
    int a[] = { 2,3,1,5,6,4 };
    int* arr1 = rotateArray(arr, 6, 2, 2);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(a[i], arr1[i]);
    }

    int arr2[] = { 1,2,3,4,5,6,7,8 };
    int a1[] = { 3,4,1,2,7,8,5,6 };
    int* arr3 = rotateArray(arr2, 8, 2, 2);

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(a1[i], arr3[i]);
    }
}
////ques 9
//TEST(ResizeArrayTest, TestSuccess) {
//    int* arr = new int[5];
//    int capacity = 5;
//
//    int result = resizeArray(arr, capacity);
//
//    ASSERT_EQ(result, 0);
//
//    ASSERT_EQ(capacity, 10);
//
//    delete[] arr;
//}