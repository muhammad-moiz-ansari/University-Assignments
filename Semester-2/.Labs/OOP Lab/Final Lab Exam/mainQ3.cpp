#include <iostream>
#include <string>

#include "i230523_F_Q3.h"
using namespace std;

int main()
{

	Book* books = new Book();
	books[0] = Book(1, "Book 1", "Ali", "Apha", "aplsskp", 123);
	books[1] = Book(2, "Book 2", "Bli", "Bpha", "Bplsskp", 456);
	books[2] = Book(3, "Book 3", "CCli", "Cpha", "Ccplsskp", 789);

	Library library("Fast", "H-11", books);

	User* student = new Students();
	User* librarian = new Faculty();

	student->Display();
	librarian->Display();


	for (int i = 0; i < 3; ++i)
		books[i].Display();

	return 0;
}