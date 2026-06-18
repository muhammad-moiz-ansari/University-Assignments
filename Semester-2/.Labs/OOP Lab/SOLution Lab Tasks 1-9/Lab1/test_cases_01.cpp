#include "pch.h"
#include "../Lab1/Header.h"
TEST(TestCaseName, sumArray) {
    int arr[] = { 7,2,8,4,5,9 };
    ASSERT_EQ(35, sumArray(arr, 6));
    int arr1[] = { -1,-2,-7,3,-11,4,0 };
    ASSERT_EQ(-14, sumArray(arr1, 7));
}
TEST(TestCaseName, SQRT_PositiveNos)
{
    ASSERT_EQ(6.0, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
}
TEST(TestCaseName, SQRT_NegativeNos)
{
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}