#include "pch.h"
#include "../Asgn 2/Q-1/23i-0523_F_Q1.cpp"
#include "../Asgn 2/23i-0523_F_Q2.cpp"
#include "gtest/gtest.h"


// QUESTION 2

// TEST 1
TEST(String, Constructors) {
	char s[] = "Assignment2";
	String str(s);
	ASSERT_EQ(0, strcmp("Assignment2", str.getdata()));

	String str1(7);
	ASSERT_EQ(0, strcmp("", str1.getdata()));

	String str2(str);
	ASSERT_EQ(0, strcmp(str2.getdata(), str.getdata()));
	ASSERT_NE(str2.getdata(), str1.getdata());

}

//// TEST 2
//TEST(String, getdata) {
//	char s[] = "World!";
//	String str(s);
//	ASSERT_EQ('!', str.getdata(5));
//	ASSERT_EQ('\0', str.getdata(6));
//
//	String str1(str);
//	ASSERT_EQ('W', str.getdata(0));
//}

// TEST 3
TEST(String, isEmpty) {
	char st[] = "Assignment2";
	String str(st);
	ASSERT_EQ(false, !str);
	ASSERT_EQ(11, (int)str);

	String str1(7);
	ASSERT_EQ(true, !str1);
	ASSERT_EQ(0, (int)str1);
}

// TEST 4
TEST(String, index_at) {
	char st[] = "Asssignment-2";
	String str(st);
	ASSERT_EQ(0, str('A'));
	ASSERT_EQ(5, str('g'));
	ASSERT_EQ(1, str('s'));
	ASSERT_EQ(12, str('2'));
	ASSERT_EQ(-1, str('P'));

	char st1[] = "OOP-Assignment2";
	char t[] = "ment";
	String test(t);
	String str1(st1);
	ASSERT_EQ(6, str1("sign"));
	ASSERT_EQ(10, str1(test));
	ASSERT_EQ(10, str1(t));
}

// TEST 5
TEST(String, isEqual) {
	char st[] = "oop-A02";
	String str(st);

	char t1[] = "oop", t2[] = "A02", t3[] = "oop-a02", t4[] = "oop-A02";
	ASSERT_EQ(false, str==t1);
	ASSERT_EQ(false, str==t2);
	ASSERT_EQ(false, str==t3);
	ASSERT_EQ(true, str==t4);

	char st1[] = "Spring";
	String str1(st1);

	char t11[] = "spring", t12[] = "sprIng";
	ASSERT_EQ(false, str1==t11);
	ASSERT_EQ(false, str1==t12);
	ASSERT_EQ(true, str1==st1);
}

// TEST 6
TEST(String, append_string) {
	char st[] = "As";
	String str(st);
	char t1[] = "sign";
	char t2[] = "ment";
	String str1(str);
	char t3 = 'g';
	str+t1;
	ASSERT_EQ(0, strcmp(str.getdata(), "Assign"));
	str+t2;
	ASSERT_EQ(0, strcmp(str.getdata(), "Assignment"));
	str+str1;
	ASSERT_EQ(0, strcmp(str.getdata(), "AssignmentAs"));
	str+t3;
	ASSERT_EQ(0, strcmp(str.getdata(), "AssignmentAsg"));
}

// TEST 7
TEST(String, remove_string) {
	char st[] = "OOP-A02";
	String str(st);
	
	str-'-';
	ASSERT_EQ(0, strcmp(str.getdata(), "OOPA02"));
	ASSERT_EQ(6, (int)str);

	char t1[] = "A0";
	str-t1;
	ASSERT_EQ(0, strcmp(str.getdata(), "OOP2"));
	ASSERT_EQ(4, (int)str);

	char t2[] = "OO";
	str-t2;
	ASSERT_EQ(0, strcmp(str.getdata(), "P2"));
	ASSERT_EQ(2, (int)str);

	String str1("2");
	str-str1;
	ASSERT_EQ(0, strcmp(str.getdata(), "P"));
	ASSERT_EQ(1, (int)str);

}

// TEST 8
TEST(String, assign_string) {
	char st[] = "OOP-Assignment02";
	String str(st);
	
	str="Hello!";
	ASSERT_EQ(0, strcmp(str.getdata(), "Hello!"));
	ASSERT_EQ(6, (int)str);

	char t1[] = "OOP-A02";
	str=t1;
	ASSERT_EQ(0, strcmp(str.getdata(), "OOP-A02"));
	ASSERT_EQ(7, (int)str);

	String str1("1");
	str=str1;
	ASSERT_EQ(0, strcmp(str.getdata(), "1"));
	ASSERT_EQ(1, (int)str);

}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

