CREATE Database Library_Management

USE Library_Management

CREATE Table Books(
	BookID INT IDENTITY(1,1) PRIMARY KEY,
	Title VARCHAR(50) NOT NULL,
	Author VARCHAR(30) NOT NULL,
	Category VARCHAR(30) NOT NULL,
	Price DECIMAL(10, 2) NOT NULL CHECK(Price > 0),
	Quantity INT DEFAULT 1 NOT NULL CHECK(Quantity > 0)
);

CREATE Table Users(
	UserID INT IDENTITY(1,1) PRIMARY KEY,
	Name VARCHAR(50) NOT NULL,
	Email VARCHAR(70) NOT NULL,
	City VARCHAR(30) NULL,
	Membership_Status VARCHAR(8) DEFAULT 'Inactive' CHECK(Membership_Status IN ('Active', 'Inactive'))
);

CREATE Table Transactions(
	TransactionID INT IDENTITY(1,1) PRIMARY KEY,
	Bookid INT,
	Borrowerid INT,
	FOREIGN KEY(Bookid) REFERENCES Books(BookID),
	FOREIGN KEY(Borrowerid) REFERENCES Users(UserID),
	Borrow_Date DATE,
	Return_Date DATE NULL,
	TStatus VARCHAR(15) DEFAULT 'Borrowed' CHECK(TStatus IN ('Returned', 'Overdue', 'Borrowed'))
);

INSERT INTO Books (Title, Author, Category, Price, Quantity) VALUES
	('Dairy of a Wimpy Kid', 'Jeff Kinney', 'Comical', 499.99, 1),
	('Rodrick Rules', 'Jeff Kinney', 'Comical', 999.50, 3),
	('The Last Straw', 'Jeff Kinney', 'Comical', 1000.00, 4),
	('A Christmas Carol', 'Charles Dickens', 'Classic', 1299.99, 6),
	('Great Expectations', 'Charles Dickens', 'Classic', 1599.50, 4),
	('Oliver Twist', 'Charles Dickens', 'Classic', 1399.75, 5),
	('The Prince and The Pauper', 'Mark Twain', 'Classic', 1499.99, 3),
	('Animal Farm', 'George Orwell', 'Dystopian', 1199.50, 4),
	('Adventures of Huckleberry Finn', 'Mark Twain', 'Classic', 1799.99, 2),
	('The Adventures of Tom Sawyer', 'Mark Twain', 'Classic', 1699.50, 3);

INSERT INTO Users (Name, Email, City, Membership_Status) VALUES
	('Ahmed Kamran', 'ahmed.kamran@example.com', 'Karachi', 'Active'),
	('Basit Sher', 'basit.sher@example.com', 'Islamabad', 'Active'),
	('Ali Raza', 'ali.raza@example.com', 'Islamabad', 'Active'),
	('Ayesha Siddiqui', 'ayesha.siddiqui@example.com', 'Faisalabad', 'Inactive'),
	('Usman Tariq', 'usman.tariq@example.com', 'Rawalpindi', 'Active'),
	('Zain Javed', 'zain.javed@example.com', 'Peshawar', 'Inactive'),
	('Bilal Hussain', 'bilal.hussain@example.com', 'Quetta', 'Active'),
	('Hina Shah', 'hina.shah@example.com', 'Multan', 'Inactive'),
	('Kamran Abbas', 'kamran.abbas@example.com', 'Sialkot', 'Active'),
	('Sara Nadeem', 'sara.nadeem@example.com', 'Hyderabad', 'Inactive');

INSERT INTO Transactions (Bookid, Borrowerid, Borrow_Date, Return_Date, TStatus) VALUES
	(1, 1, '2025-02-01', '2025-02-10', 'Returned'),
	(2, 2, '2025-02-05', NULL, 'Borrowed'),
	(3, 3, '2025-02-07', '2025-02-15', 'Returned'),
	(4, 4, '2025-02-09', NULL, 'Borrowed'),
	(5, 5, '2025-02-10', NULL, 'Overdue'),
	(6, 6, '2025-02-12', '2025-02-20', 'Returned'),
	(7, 7, '2025-02-14', NULL, 'Borrowed'),
	(8, 8, '2025-02-16', NULL, 'Borrowed'),
	(9, 9, '2025-02-18', '2025-02-25', 'Returned'),
	(10, 10, '2025-02-20', NULL, 'Overdue');


SELECT * FROM Books
SELECT * FROM Users
SELECT * FROM Transactions
SELECT * FROM ArchievedMembers

-- Query 1: Choose one book and update its category to Poetry.
UPDATE Books
SET Category='Poetry'
WHERE BookID=4

-- Query 2: List all the user ids and names for the users who haven’t provided their cities.
UPDATE Users
SET City=NULL
WHERE UserID=2 OR UserID=7 OR UserID=8

SELECT * FROM Users WHERE City is NULL

-- Query 3: Considering due date of 1 week, update status to overdue for overdue books.
UPDATE Transactions
SET TStatus='Overdue'
WHERE DATEDIFF(DAY, Borrow_Date, GETDATE()) BETWEEN 7 AND 14

-- Query 4: Display all book ids in descending order that are not returned yet.
SELECT Bookid FROM Transactions WHERE NOT TStatus='Returned' ORDER BY BookID DESC

-- Query 5: List all book where the price is more than Rs. 1000 and quantity is below 5.
SELECT * FROM Books WHERE Price >= 1000 AND Quantity < 5

-- Query 6: Display the transactionId and status of 3 most recent transactions.
SELECT TOP 3 TransactionID, TStatus FROM Transactions ORDER BY Return_Date DESC

-- Query 7: Retrieve distinct categories of books from the `Books` table.
SELECT DISTINCT Category FROM Books

-- Query 8: Update the price of all books in the &#39;Education&#39; category to decrease by 10%.
UPDATE Books
SET Category='Education'
WHERE BookID=9 OR BookID=10

UPDATE Books
SET Price=Price-(Price*0.1)
WHERE Category='Education'

-- Query 9: Select books where the price is either less than Rs. 1000 or quantity is between 5 and 10.
SELECT * FROM Books WHERE Price < 1000 OR Quantity BETWEEN 5 AND 10

-- Query 10: List all book titles that do not have 'w' as the third letter and are currently out of stock
SELECT name 
FROM sys.check_constraints 
WHERE parent_object_id = OBJECT_ID('Books') 
AND parent_column_id = COLUMNPROPERTY(OBJECT_ID('Books'), 'Quantity', 'ColumnId');

ALTER TABLE Books DROP CONSTRAINT CK__Books__Quantity__59FA5E80;
ALTER TABLE Books ADD CONSTRAINT CHK_Books_Quantity CHECK (Quantity >= 0);

UPDATE Books SET Quantity=0, Title='Few Straws Left' WHERE BookID=3
UPDATE Books SET Quantity=0 WHERE BookID=1

SELECT * FROM Books WHERE NOT Title LIKE '__w%' AND Quantity = 0

-- Query 11: Find all books that have ‘data’ in their name and do not belong to the Fiction Category.
UPDATE Books SET Title='Rodrick Data Rules', Category='Comical' WHERE BookID=2
UPDATE Books SET Title='Animal Data Farm', Category='Fiction' WHERE BookID=8

SELECT * FROM Books WHERE Title LIKE '%Data%' AND NOT Category='Fiction'

-- Query 12: Find all users who belong from New York, Chicago or Seattle as ‘CustomerCity’ without using OR operator.
SELECT * FROM Users WHERE City IN ('Islamabad', 'Rawalpindi', 'Karachi')

-- Query 13: Find all customers whose email addresses do not follow a valid format.
UPDATE Users 
SET Email='ahmed.kamran#example.com' WHERE UserID=1
UPDATE Users
SET Email='basit.sher@example.comm' WHERE UserID=2

SELECT * FROM Users WHERE NOT Email LIKE '%.com' OR NOT Email LIKE '%@%' OR Email LIKE '@%' OR Email LIKE '%@.com'

-- Query 14: Create a new table ArchivedMembers with attributes ArchivedUserId, name, email and city. Then transfer all data for the inactive members from the users table.
CREATE TABLE ArchievedMembers(
	ArchivedUserId INT PRIMARY KEY,
	Name VARCHAR(50) NOT NULL,
	Email VARCHAR(70) NOT NULL,
	City VARCHAR(30) NULL
);

INSERT INTO ArchievedMembers(ArchivedUserId, Name, Email, City)
SELECT UserID, Name, Email, City FROM Users WHERE Membership_Status='Inactive'

SELECT * FROM ArchievedMembers

-- Query 15: Delete all inactive members from the database.
DELETE FROM Transactions WHERE Borrowerid IN (SELECT UserID FROM Users WHERE Membership_Status='Inactive')

DELETE FROM Users WHERE Membership_Status='Inactive'

----------------------- RESTRICTED AREA -----------------------

DROP TABLE Books
DROP TABLE Users
DROP TABLE Transactions
DROP TABLE ArchievedMembers