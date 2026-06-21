Create DATABASE Library_Management_System

Use Library_Management_System

CREATE Table Books(
	BookID INT IDENTITY(1,1) PRIMARY KEY,
	Title VARCHAR(50) NOT NULL,
	Genre VARCHAR(30) NOT NULL,
	PublicationYear INT NOT NULL CHECK (PublicationYear > 1000 AND PublicationYear <= YEAR(GETDATE())),
	Price DECIMAL(10, 2) NOT NULL CHECK(Price > 0),
);

CREATE Table Members(
	MemberID INT IDENTITY(1,1) PRIMARY KEY,
	FullName VARCHAR(50) NOT NULL,
	JoinDate DATE NOT NULL DEFAULT GETDATE() CHECK (JoinDate <= GETDATE())
);

CREATE Table Borrowings(
	BorrowID INT PRIMARY KEY IDENTITY(1,1),
	MemberID INT FOREIGN KEY REFERENCES Members(MemberID) ON DELETE CASCADE,
	BookID INT FOREIGN KEY REFERENCES Books(BookID) ON DELETE CASCADE,
	BorrowDate DATE NOT NULL DEFAULT GETDATE(),
	ReturnDate DATE NULL,
	Status VARCHAR(20) NOT NULL DEFAULT 'Borrowed' CHECK (Status IN ('Borrowed', 'Returned'))
);

INSERT INTO Books (Title, Genre, PublicationYear, Price) VALUES
	('Dairy of a Wimpy Kid', 'Comical', 2011, 499.99),
	('Rodrick Rules', 'Comical', 2012, 999.50),
	('The Last Straw', 'Comical', 2013, 1000.00),
	('A Christmas Carol', 'Classic', 1987, 1299.99),
	('Great Expectations', 'Classic', 1999, 1599.50),
	('Oliver Twist', 'Classic', 2000, 1399.75),
	('The Prince and The Pauper', 'Classic', 1969, 1499.99),
	('Animal Farm', 'Dystopian', 1700, 1199.50),
	('Adventures of Huckleberry Finn', 'Classic', 2025, 1799.99),
	('The Adventures of Tom Sawyer', 'Classic', 1999, 1699.50);

INSERT INTO Members (FullName, JoinDate) VALUES
    ('Abdullah Siddique', '2025-02-18'),
    ('Daniyal Kamran', '2024-11-10'),
    ('Basit Sher', '2023-07-05'),
    ('Ali Raza', '2022-09-15'),
    ('Ayesha Siddiqui', '2021-03-22'),
    ('Usman Tariq', '2020-06-30'),
    ('Zain Javed', '2019-12-10'),
    ('Bilal Hussain', '2018-08-27'),
    ('Hina Shah', '2017-05-14'),
    ('Kamran Abbas', '2016-01-29');

INSERT INTO Borrowings (MemberID, BookID, BorrowDate, ReturnDate, Status) VALUES
    (1, 3, '2025-02-10', NULL, 'Borrowed'),
    (2, 5, '2024-12-15', '2025-01-20', 'Returned'),
    (3, 7, '2023-08-01', '2023-08-20', 'Returned'),
    (4, 2, '2022-10-10', '2022-11-15', 'Returned'),
    (5, 1, '2021-04-05', NULL, 'Borrowed'),
    (6, 4, '2020-07-10', '2020-08-15', 'Returned'),
    (7, 6, '2019-12-25', '2020-01-20', 'Returned'),
    (8, 8, '2018-09-10', '2018-10-15', 'Returned'),
    (9, 9, '2017-06-05', NULL, 'Borrowed'),
    (10, 10, '2016-02-20', '2016-04-01', 'Returned');

UPDATE Books SET Price=1799.99 WHERE BookID=10

CREATE VIEW BookView AS SELECT BookID, Title, Genre, PublicationYear, Price FROM Books
SELECT * FROM [BookView]

-- UPDATES --
-- Task 5:
UPDATE Books
SET Title='Advanced Expectations' WHERE BookID=5
UPDATE Books
SET Title='The Advanced Last Straw' WHERE BookID=3

-- Task 14:
DELETE FROM Borrowings WHERE BookID=7

-- Task 16:
UPDATE Books
SET Title='The Famous Five' WHERE BookID=1


SELECT * FROM Books
SELECT * FROM Borrowings
SELECT * FROM Members


------- SQL Tasks -------

-- 1. Retrieve the total count of books available in the library.
SELECT COUNT(*) AS [Number of Books] FROM Books

-- 2. Display all books published before the year 2000, sorted in descending order by publication year.
SELECT * FROM Books WHERE PublicationYear < 2000 ORDER BY PublicationYear DESC

-- 3. Identify the highest and lowest-priced books in the library along with their titles and prices.
SELECT Title AS [Highest Priced Book], Price FROM Books WHERE Price = (SELECT MAX(Price) FROM Books)
SELECT Title AS [Lowest Priced Book], Price FROM Books WHERE Price = (SELECT MIN(Price) FROM Books)

-- 4. Extract and display the first three characters of each book title, ensuring that duplicate entries are removed from the results.
SELECT DISTINCT LEFT(Title, 3) AS [First Three Char] FROM Books

-- 5. List all books that have the word "Advanced" in their title, sorted alphabetically.
SELECT * FROM Books WHERE Title LIKE '%Advanced%' ORDER BY Title

-- 6. Convert and display all book titles in uppercase format and order them by title length in descending order.
SELECT UPPER(Title) AS [Upper Cased Titles] FROM Books ORDER BY LEN(Title) DESC

-- 7. Compute the total cost of all books available in the library, rounding the result to two decimal places.
SELECT ROUND(SUM(Price),2) AS [Total Cost] FROM Books 

-- 8. Determine the total number of years since each book was published and display the book title along with its age.
SELECT Title, YEAR(GETDATE()) - PublicationYear AS Age FROM Books;

-- 9. Identify books that were published within the last 10 years and order the results by the most recent publication year.
SELECT * FROM Books WHERE YEAR(GETDATE()) - PublicationYear <= 10

-- 10. Retrieve the most recent borrow date from the records, ensuring that the result is displayed in MM-DD-YYYY format.
SELECT TOP 1 FORMAT(BorrowDate, 'MM-dd-yyyy') AS [Most Recent] FROM Borrowings ORDER BY (SELECT MAX(YEAR(BorrowDate)) FROM Borrowings) DESC

-- 11. List books that have been borrowed for more than 30 days before being returned, including the book title          // and the number of days borrowed. (hint: use sub-query)
SELECT * FROM Books WHERE BookID IN (SELECT BookID FROM Borrowings WHERE DATEDIFF(DAY, BorrowDate, ReturnDate) > 30)

-- 12. Find books that are priced higher than the overall average book price in the library.
SELECT * FROM Books WHERE Price > (SELECT AVG(Price) FROM Books)

-- 13. Retrieve the absolute price difference between the most expensive and the least expensive book in the library as PriceDifference.
SELECT (ABS(MAX(Price) - MIN(Price))) AS PriceDifference FROM Books

-- 14. Find and display books that have never been borrowed, ensuring the results include the book title and genre.
SELECT Title AS [Books Not Borrowed (Title)], Genre FROM Books WHERE BookID NOT IN (SELECT BookID FROM Borrowings)

-- 15. Display all the books that have the least price in library.
SELECT Title AS [Least Priced Books], Price FROM Books WHERE Price = (SELECT MIN(Price) FROM Books)

-- 16. Find the books whose price is greater than the book titled ‘The Famous Five’ and belongs to the same genre.
SELECT * FROM Books WHERE Price > (SELECT Price FROM Books WHERE Title='The Famous Five') AND Genre=(SELECT Genre FROM Books WHERE Title='The Famous Five')
