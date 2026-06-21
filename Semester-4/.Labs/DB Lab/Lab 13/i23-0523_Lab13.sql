-- Use Library_Management_System

CREATE TABLE Books (
	BookID INT PRIMARY KEY,
	Title VARCHAR(255),
	AuthorName VARCHAR(100),
	Price DECIMAL(10,2),
	StockQuantity INT
);

CREATE TABLE Customers (
	CustomerID INT PRIMARY KEY,
	FirstName VARCHAR(100),
	LastName VARCHAR(100),
	Email VARCHAR(255)
);

CREATE TABLE Orders (
	OrderID INT IDENTITY(101, 1) PRIMARY KEY,
	CustomerID INT,
	OrderDate DATE,
	TotalAmount DECIMAL(10,2)
);

--DROP TABLE Books
--DROP TABLE Customers
--DROP TABLE Orders

INSERT INTO Books (BookID, Title, AuthorName, Price, StockQuantity) VALUES
	(1, 'A Case of Exploding Mangoes', 'Mohammed Hanif', 850.00, 50),
	(2, 'The Reluctant Fundamentalist', 'Mohsin Hamid', 750.00, 30),
	(3, 'Moth Smoke', 'Mohsin Hamid', 650.00, 25),
	(4, 'Kartography', 'Kamila Shamsie', 900.00, 40),
	(5, 'Train to Pakistan', 'Khushwant Singh', 700.00, 35);

INSERT INTO Customers (CustomerID, FirstName, LastName, Email) VALUES
	(41, 'Ahmed', 'Khan', 'ahmed.khan@email.pk'),
	(42, 'Sana', 'Malik', 'sana.malik@email.pk'),
	(43, 'Bilal', 'Ahmed', 'bilal.ahmed@email.pk'),
	(44, 'Ayesha', 'Siddiqui', 'ayesha.siddiqui@email.pk'),
	(45, 'Hassan', 'Raza', 'hassan.raza@email.pk');

INSERT INTO Orders (CustomerID, OrderDate, TotalAmount) VALUES
	(41, '2025-04-01', 850.00),
	(42, '2025-04-05', 1400.00),
	(43, '2025-04-10', 650.00),
	(44, '2025-04-15', 900.00),
	(45, '2025-04-20', 700.00);

SELECT * FROM Books
SELECT * FROM Customers
SELECT * FROM Orders

--1. Write an SQL transaction to update the email address of a specific customer and commit the transaction.
BEGIN TRANSACTION
	UPDATE Customers SET Email = 'iamahmed@gmail.com' WHERE CustomerID = 41
COMMIT;

--2. A customer with CustomerId 43 is ordering the book titled "The Great Gatsby". Write an SQL transaction to insert this order into the database. 
--   Use a savepoint before inserting the order details and commit after successful insertion.
BEGIN TRANSACTION
	SAVE TRANSACTION BeforeInsert
		INSERT INTO Orders (OrderID, CustomerID, OrderDate, TotalAmount)
		VALUES (106, 43, '2025-05-09', 750.00);
COMMIT;

--3. Suppose a customer wants to purchase a book, write a SQL transaction to process this purchase. Create a stored procedure 
--   “PurchaseBook” to handle the transaction. If an error occurs due to insufficient stock quantity of the book or due to any 
--   other reason, rollback the transaction and print an error message.

GO
CREATE or ALTER PROCEDURE PurchaseBook
	@CustomerID INT,
    @BookID INT,
    @Quantity INT
AS
BEGIN
	DECLARE @StockQuantity INT;
    DECLARE @Price DECIMAL(10,2);
    DECLARE @TotalAmount DECIMAL(10,2);

	BEGIN TRANSACTION
		SET @StockQuantity = (SELECT b.StockQuantity
							  FROM Books b
							  WHERE b.BookID = @BookID)

		IF @StockQuantity IS NULL
        BEGIN
            PRINT 'Error: Book not exists.';
            ROLLBACK;
            RETURN;
        END;

		IF @StockQuantity < @Quantity
		BEGIN
			print 'Error: Insufficient book stock';
			ROLLBACK;
			RETURN;
		END;

		SET @price = (SELECT b.Price
					  FROM Books b
					  WHERE b.BookID = @BookID)

		SET @TotalAmount = @Price * @Quantity;

		INSERT INTO Orders VALUES(@CustomerID, GETDATE(), @TotalAmount);

	COMMIT;
END;
GO

EXEC PurchaseBook @CustomerID = 43, @BookID = 5, @Quantity = 40;
