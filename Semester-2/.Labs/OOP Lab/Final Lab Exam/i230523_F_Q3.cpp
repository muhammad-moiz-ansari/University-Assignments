#include <iostream>
#include <cmath>
#include "i230523_F_Q3.h"
using namespace std;

Library::Library(string n, string add, Book*& boooks)
{
	name = n;
	address = add;
	books = boooks;
}

///////////////// Book ///////////////////

Book::Book(int isbn, std::string Title, string Author, string Subj, string Pub, int bar)
{
	ISBN = isbn;
	title = Title;
	author = Author;
	subject = Subj;
	publisher = Pub;
	barcode = bar;
	status = "Available";
}

void Book::Display()
{
	cout << "\nISBN: " << ISBN
		<< "\nTitle: " << title
		<< "\nAuthor: " << author
		<< "\nPublisher: " << publisher
		<< "\nBarcode: " << barcode
		<< "\nStatus: " << status << endl;
}

////////////// Users /////////////////

User::User(int id, string pass, string stat)
{
	ID = id;
	password = pass;
	status = stat;
}

void User::login()
{
	cout << "Login: \n"
		<< "Enter ID: ";
	cin >> ID;
	cout << "Enter Password: ";
	cin >> password;
}

void User::Display()
{
	cout << "ID: " << ID
		<< "Password: " << password
		<< "Status: " << status;
}

/////////// Students
Students::Students()// int id, string pass, string stat):User(id, pass, stat)
{
	User::login();
	status = "Active";

	User(ID, password, status);
}


///////// Faculty
Faculty::Faculty()// :User(id, pass, stat)
{
	User::login();
	status = "Active";

	User(ID, password, status);
}

///////////////// BookBorrowing ///////////////////

BookBorrowing::BookBorrowing()
{
	fine = 0;
}

void BookBorrowing::booklend(Book& book)
{
	int m, y, d;
	cout << "Enter Date of Issue (days, months): ";
	cin >> d >> m;

	book.issue_date = d + (m-1) * 30;

	cout << "Enter Due Date (days, months): ";
	cin >> d >> m;
	
	book.due_date = d + (m - 1) * 30;

	book.status = "Loaned";

}

void BookBorrowing::bookreturn(Book& book)
{
	if (book.due_date - book.return_date <= 0)
	{
		int dates = abs(book.due_date - book.return_date);
		fine += dates * 100;
	}

	book.status = "Available";
}


