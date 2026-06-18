#pragma once
#include <iostream>
using namespace std;

class Complex
{
	double real;
	double imaginary;

public:
	Complex()
	{
		real = 0.000;
		imaginary = 0.000;
	}

	Complex(double r, double i)
	{
		real = r;
		imaginary = i;
	}

	void setReal(double r)
	{
		real = r;
	}
	double getReal()
	{
		return real;
	}
	void setImaginary(double i)
	{
		imaginary = i;
	}
	double getImaginary()
	{
		return imaginary;
	}
	void display()
	{
		cout << real << " + " << imaginary << "i" << endl;
	}
	Complex addComplex(Complex& c1)
	{
		Complex RESULT;

		RESULT.setReal(c1.real+real);
		RESULT.setImaginary(c1.imaginary + imaginary);

		return RESULT;
	}

	Complex subComplex(Complex& c1)
	{
		Complex RESULT;

		RESULT.setReal(real - c1.real);
		RESULT.setImaginary(imaginary - c1.imaginary);

		return RESULT;
	}

	Complex mulComplex(Complex& c1)
	{
		Complex RESULT;

		RESULT.setReal((c1.real * real) - (c1.imaginary * imaginary));
		RESULT.setImaginary((real* c1.imaginary) + (c1.real * imaginary));

		return RESULT;
	}

};