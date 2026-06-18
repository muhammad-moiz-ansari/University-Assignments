#pragma once
#include <string>
#include <string.h>
#include <string>
using namespace std;

class Library
{
protected:
	string name;
	string address;
	BookBorrowing bookborrow;
	Book* books;

public:
	Library(string n, string add, Book*& boooks);

	void booklend();

};

class BookBorrowing
{
protected:
	int fine;


public:
	BookBorrowing();
	void booklend(Book& book);
	void bookreturn(Book& book);


};

class Book
{
//protected:
public:
	int ISBN;
	string title,
		author,
		subject,
		publisher;
	int barcode;
	string status;


	int issue_date,
		due_date,
		return_date;

	//int d_issue,
	//	d_due,
	//	d_return;

public:
	Book(int isbn = 0, std::string Title = "", string Author = "", string Subj = "", string Pub = "", int bar = 0);

	void Display();

	//friend void BookBorrowing::booklend();
};

class User
{
protected:
	int ID;
	string password,
		status;


public:
	User(int id = 0, string pass = "", string stat = "");


	void login();
	void Display();


};

class Students :public virtual User
{
private:



public:
	Students();// int id = 0, string pass = "", string stat = "");

};

class Faculty :public virtual User
{
private:
	


public:
	Faculty();// int id = 0, string pass = "", string stat = "");

};