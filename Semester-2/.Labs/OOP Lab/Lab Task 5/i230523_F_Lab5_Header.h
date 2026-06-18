#pragma once
#include <iostream>
#include <string>

using namespace std;

//------------------ Q- ------------------
//------------------ Q-1 ------------------

struct Complex
{
	int real;
	int imaginary;
	Complex addComplex(Complex c1, Complex& c2)
	{
		Complex result;
		result.real = c1.real + c2.real;
		result.imaginary = c1.imaginary + c2.imaginary;
		return result;
	}
};

//------------------ Q-2 ------------------

const int sizeq2 = 5;

struct Student
{
	std::string Name;
	std::string roll_no;
	int age;
	string* getNames(Student* std)
	{
		int index_n = 0;
		string* namesq2 = new string[sizeq2];
		for (int i = 0; i < sizeq2; ++i)
		{
			if (std[i].age == 18)
				namesq2[index_n++] = std[i].Name;
		}
		return namesq2;
	}

	Student* getEvenRollno(Student* std)
	{
		int indexq2 = 0, strsizeq2;
		Student* even_r = new Student[sizeq2];
		for (int i = 0; i < sizeq2; ++i)
		{
			strsizeq2 = 0;
			for (; (std[i].roll_no)[strsizeq2] != '\0'; ++strsizeq2);
			if ((((std[i].roll_no)[strsizeq2 - 1]) - 48) % 2 == 0)
			{
				even_r[indexq2++] = std[i];
			}
		}
		return even_r;
	}
};


//------------------ Q-3 ------------------

struct CustomTime
{
	int hours;
	int mins;
	int secs;

	int timeToSecs(CustomTime t1)
	{
		int secsq3 = 0;
		secsq3 = (t1.hours * 3600) + (t1.mins * 60) + (t1.secs);
		return secsq3;
	}

	int AddTimes(CustomTime t1, CustomTime t2)
	{
		int s1, s2, sumq3;
		s1 = timeToSecs(t1);
		s2 = timeToSecs(t2);
		sumq3 = s1 + s2;

		return sumq3;
	}
};

//------------------ Q-4 ------------------

struct CourseRegistration
{
	string courseCode;
	string courseTitle;
	int CreditHour;
	char Section;
};

int sizeq4 = 5;
struct SemesterRegistration
{
	string semesterCode;
	CourseRegistration* course_reg = new CourseRegistration[sizeq4];

	int GetCreditHoursCount(SemesterRegistration s)
	{
		int sumq4 = 0;
		for (int i = 0; i < sizeq4; ++i)
		{
			sumq4 += s.course_reg[i].CreditHour;
		}
		return sumq4;
	}

	bool FindCourseInSemesterRegistration(SemesterRegistration s, string courseCode)
	{
		bool charq4 = 0, checkq4 = 1;
		int strsizeq4 = 0;

		for (int i = 0; i < sizeq4 && !charq4 ; ++i)
		{
			for (; s.course_reg[i].courseCode[strsizeq4] != '\0'; ++strsizeq4);

			for (int j = 0; courseCode[j] != '\0' && s.course_reg[i].courseCode[j] != '\0'; ++j)
			{
				if (s.course_reg[i].courseCode[j] == courseCode[j])
					charq4 = 1;
				else
				{
					checkq4 = 0;
					charq4 = 0;
				}

				if (!charq4)
					break;
			}
			if (charq4)
			{
				checkq4 = 1;
				break;
			}
		}
		return checkq4;
	}
};

//------------------ Q-5 ------------------

int numbersize(int n, int size) {
	if (n != 0) {
		++size;
		n = n / 10;
		numbersize(n, size);
	}
	else if (size == 0) {
		size = 1;
		return size;
	}
	else
		return size;
}

int extractnum(int n, int size, int i) {
	int result;
	if (i == size) {
		result = n % 10;
		return result;
	}
	else {
		n = n / 10;
		extractnum(n, size, ++i);
	}
}

void sumdig(int n, int& evens, int& odds, int size, int i) {
	if (i < size) {
		if (i % 2 == 0) {
			evens += extractnum(n, size, size - i);
		}
		else {
			odds += extractnum(n, size, size - i);
		}
		sumdig(n, evens, odds, size, ++i);
	}
}

int* sum_of_digits(int start, int end, int N) {
	static int once = 0, index = 0;
	int num_size = 0, evens = 0, odds = 0;

	static int* arr = new int[N];

	if (start <= end && index < N) {
		num_size = numbersize(start, 0);

		sumdig(start, evens, odds, num_size, 0);

		if (evens == odds) {
			arr[index++] = start;
		}

		sum_of_digits(++start, end, N);
	}

	return arr;
}
