#include "pch.h"
#include "D:\Documents\Semester-2\.Labs\OOP Lab\Lab Task 5\Project File\Header.h"
#include <gtest/gtest.h>

//question 1
TEST(Complex, case1) {
    Complex c1 = { 5,3 };
    Complex c2 = { 4,2 };
    Complex c3;
    c3 = c1.addComplex(c1, c2);
    ASSERT_EQ(9, c3.real);
    ASSERT_EQ(5, c3.imaginary);
}
TEST(Complex, case2) {
    Complex c1 = { 2,7 };
    Complex c2 = { 10,6 };
    Complex c3;
    c3 = c1.addComplex(c1, c2);
    ASSERT_EQ(12, c3.real);
    ASSERT_EQ(13, c3.imaginary);
}

//question 2
TEST(Student, getNames) {
    Student s;
    Student* std = new Student[5];
    string name[5] = { "John","karen","Jenny","David","Smith" };
    string roll_no[5] = { "21i-1234","21i-1243","21i-1765","21i-1422","21i-1846" };
    int age[5] = { 18,17,20,18,21 };
    for (int i = 0; i < 5; i++) {
        std[i].Name = name[i];
        std[i].roll_no = roll_no[i];
        std[i].age = age[i];
    }
    string arr1[] = { "John","David" };
    string* arr2 = s.getNames(std);
    for (int i = 0; i < 2; i++) {
        ASSERT_EQ(arr1[i], arr2[i]);
    }

    int age1[5] = { 18,17,20,18,18 };
    for (int i = 0; i < 5; i++) {
        std[i].age = age1[i];
    }
    string arr3[] = { "John","David","Smith" };
    string* arr4 = s.getNames(std);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(arr3[i], arr4[i]);
    }
}
TEST(Student, getEvenRollno) {
    Student s;
    Student* std = new Student[5];
    string name[5] = { "John","karen","Jenny","David","Smith" };
    string roll_no[5] = { "21i-1234","21i-1243","21i-1765","21i-1422","21i-1846" };
    int age[5] = { 18,17,20,18,21 };
    for (int i = 0; i < 5; i++) {
        std[i].Name = name[i];
        std[i].roll_no = roll_no[i];
        std[i].age = age[i];
    }
    //Student *std1=new Student[3];
    string name1[3] = { "John","David","Smith" };
    string roll_no1[3] = { "21i-1234","21i-1422","21i-1846" };
    int age1[3] = { 18,18,21 };
    Student* std1 = s.getEvenRollno(std);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(std1[i].Name, name1[i]);
        ASSERT_EQ(std1[i].roll_no, roll_no1[i]);
        ASSERT_EQ(std1[i].age, age1[i]);
    }

}

//question 3
TEST(CustomTime, timeToSecs) {
    CustomTime t1 = { 2,0,0 };
    ASSERT_EQ(7200, t1.timeToSecs(t1));
    CustomTime t2 = { 2,40,30 };
    ASSERT_EQ(9630, t2.timeToSecs(t2));
}
TEST(CustomTime, AddTimes) {
    CustomTime t1 = { 2,0,0 };
    CustomTime t2 = { 2,40,30 };
    CustomTime t3;
    ASSERT_EQ(16830, t3.AddTimes(t1, t2));

    CustomTime t4 = { 1,1,6 };
    CustomTime t5 = { 1,1,6 };
    CustomTime t6;
    ASSERT_EQ(7332, t6.AddTimes(t4, t5));
}

//question 4
TEST(SemesterRegistration, GetCreditHoursCount) {
    SemesterRegistration sem_reg;
    sem_reg.semesterCode = "Spring 2023";
    string courseCode[] = { "CL1004","EL2003","CL1001","CL2002","EL2020" };
    string courseTitle[] = { "OOP","COAL","PF","CNET","DLD" };
    int CreditHour[] = { 1,3,3,4,1 };
    char Section[] = { 'A','B','C','D','E' };
    for (int i = 0; i < 5; i++) {
        sem_reg.course_reg[i].courseCode = courseCode[i];
        sem_reg.course_reg[i].courseTitle = courseTitle[i];
        sem_reg.course_reg[i].CreditHour = CreditHour[i];
        sem_reg.course_reg[i].Section = Section[i];
    }
    ASSERT_EQ(12, sem_reg.GetCreditHoursCount(sem_reg));
}

TEST(SemesterRegistration, FindCourseInSemesterRegistration) {
    SemesterRegistration sem_reg;
    sem_reg.semesterCode = "Spring 2023";
    string courseCode[] = { "CL1004","EL2003","CL1001","CL2002","EL2020" };
    string courseTitle[] = { "OOP","COAL","PF","CNET","DLD" };
    int CreditHour[] = { 1,3,3,4,1 };
    char Section[] = { 'A','B','C','D','E' };
    for (int i = 0; i < 5; i++) {
        sem_reg.course_reg[i].courseCode = courseCode[i];
        sem_reg.course_reg[i].courseTitle = courseTitle[i];
        sem_reg.course_reg[i].CreditHour = CreditHour[i];
        sem_reg.course_reg[i].Section = Section[i];
    }
    ASSERT_EQ(1, sem_reg.FindCourseInSemesterRegistration(sem_reg, "CL1001"));
    ASSERT_EQ(0, sem_reg.FindCourseInSemesterRegistration(sem_reg, "CL2004"));
}

//question 5
TEST(SumOFDigits, case1) {
    int* result = sum_of_digits(100, 999, 45);
    int* correct_answer = new int[45] {110, 121, 132, 143, 154, 165, 176,
        187, 198, 220, 231, 242, 253, 264, 275, 286, 297, 330, 341, 352, 363, 374, 385, 396, 440, 451, 462,
        473, 484, 495, 550, 561, 572, 583, 594, 660, 671, 682, 693, 770, 781, 792, 880, 891, 990};
    for (int i = 0; i < 45; i++)
    {
        ASSERT_EQ(result[i], correct_answer[i]);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
