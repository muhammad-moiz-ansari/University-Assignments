#include<iostream>
#include "pch.h"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 2\Lab-2 Project File\23i-0523_Moiz Ansari_Q1.cpp"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 2\Lab-2 Project File\23i-0523_Moiz Ansari_Q2.cpp"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 2\Lab-2 Project File\23i-0523_Moiz Ansari_Q3.cpp"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 2\Lab-2 Project File\23i-0523_Moiz Ansari_Q4.cpp"
//#include "../Lab01/Calculator.h"
using namespace std;
// ques1
TEST(MostOccurredNumber, TypeInt) {
    int nums[] = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    int size = sizeof(nums) / sizeof(nums[0]);
    int arr[] = { 1, 3, 2, 3, 4, 1, 3 };
    int size1 = sizeof(arr) / sizeof(arr[0]);

    ASSERT_EQ(4, findMostFrequentElement(nums, size));
    ASSERT_EQ(3, findMostFrequentElement(arr, size1));
}
TEST(MostOccurredNumber, TypeDouble) {
    double nums[] = { 1.1, 2.2, 1.1, 2.2, 3.3, 2.2, 2.2 };
    int size = sizeof(nums) / sizeof(nums[0]);
    ASSERT_EQ(2.2, findMostFrequentElement(nums, size));
}

// question 2
TEST(RearrangeMaxMin, TypeInt) {
    int nums[] = { 10, 20, 30, 40, 50 };
    int size = sizeof(nums) / sizeof(nums[0]);
    int expected[] = { 50, 10, 40, 20, 30 }; // Manually computed expected output

    rearrangeArray(nums, size);

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(nums[i], expected[i]);
    }
}
 
//ques 3
TEST(SumOfArrays, TypeInt) {
    int arr1[] = { 1, 2, 3 };
    int arr2[] = { 4, 5, 6 };
    int size = sizeof(arr1) / sizeof(arr1[0]);
    int expected[] = { 5, 7, 9 };

    int* result = sumOfArrays(arr1, arr2, size);

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }

    delete[] result; // Clean up allocated memory
}
TEST(SumOfArrays, TypeDouble) {
    double arr1[] = { 1.1, 2.2, 2.2 };
    double arr2[] = { 4.4, 5.5, 6.6 };
    int size = sizeof(arr1) / sizeof(arr1[0]);
    double expected[] = { 5.5, 7.7, 8.8 };

    double* result = sumOfArrays(arr1, arr2, size);

    for (int i = 0; i < size; i++) {

        ASSERT_EQ(result[i], expected[i]);
    }

    // Clean up allocated memory
}
 
// ques 4

TEST(ArrayWave1, CreateWave)
{
    int nums[] = { 4, 5, 9, 9, 9, 22, 45, 7 };

    //int nums[] = { 4, 5, 9, 12, 9, 22, 45, 7 };
    int size = sizeof(nums) / sizeof(nums[0]);

    int expected[] = { 5, 4, 9, 9, 22, 9, 45, 7 };
    Container<int> wave(nums, size);


    int* p = wave.sortInWaveForm();

    cout << "Arr1: \n";
    for (int i = 0; i < size; ++i)
    {
        cout << p[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < size; ++i)
    {
        EXPECT_EQ(p[i], expected[i]);
    }

}

TEST(ArrayWave2, CreateWave)
{
    //////// Test 2
    int nums1[] = { 4, 5, 2, 3, 9, 22, 45, 7 };

    int size1 = sizeof(nums1) / sizeof(nums1[0]);

    int expected1[] = { 5,  2,  4,  3,  22,  9,  45,  7 };
    Container<int> wave1(nums1, size1);


    int* p1 = wave1.sortInWaveForm();

    cout << "Arr2: \n";
    for (int i = 0; i < size1; ++i)
    {
        cout << p1[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < size1; ++i)
    {
        EXPECT_EQ(p1[i], expected1[i]);
    }

}
