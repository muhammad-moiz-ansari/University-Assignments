USE AdventureWorks_Database

--1. 🧮 Calculate Revenue per Category
--Create a stored procedure GetRevenueByCategory that:

--Accepts a @CategoryName parameter
--Returns total revenue (TotalDue) of all products in that category

GO
CREATE OR ALTER PROCEDURE GetRevenueByCategory @CategoryName VARCHAR(50)
AS
BEGIN
	RETURN (SELECT SUM(od.UnitPrice * od.OrderQty)
			FROM SalesLT.Product p
			JOIN SalesLT.ProductCategory pc ON pc.ProductCategoryID = p.ProductCategoryID
			JOIN SalesLT.SalesOrderDetail od ON od.ProductID = p.ProductID
			WHERE pc.Name = @CategoryName
			GROUP BY pc.ProductCategoryID)
END
GO

DECLARE @CatName VARCHAR(50) = 'Mountain Bikes'
DECLARE @rev DECIMAL(15, 2)
EXEC @rev = GetRevenueByCategory @CategoryName = @CatName
PRINT 'Total Revenue of ' + @CatName + ': Rs. ' + CAST(@rev AS VARCHAR(30))


--SELECT SUM(od.UnitPrice * od.OrderQty) AS Revenue, pc.Name
--FROM SalesLT.Product p
--JOIN SalesLT.ProductCategory pc ON pc.ProductCategoryID = p.ProductCategoryID
--JOIN SalesLT.SalesOrderDetail od ON od.ProductID = p.ProductID
----WHERE pc.Name = @CategoryName
--GROUP BY pc.ProductCategoryID, pc.Name





--2. 🔄 Update Freight Based on Region
--Write a T-SQL block that:

--Iterates through each distinct City in the Address table using a WHILE loop
--Calculates the average freight for that city
--If average freight > 50, updates SalesOrderHeader for that city to add a 10% surcharge


GO
CREATE OR ALTER FUNCTION GetCity(@count INT)
RETURNS Table
AS
RETURN
(
	SELECT TOP 1 a1.City
	FROM SalesLT.Address a1
	WHERE a1.City NOT IN (SELECT DISTINCT TOP (@count) a.City
						  FROM SalesLT.Address a
						  ORDER BY a.City DESC)
	ORDER BY a1.City DESC
)
GO


GO
CREATE OR ALTER PROCEDURE UpdateFrieghtBasedOnRegion
AS
BEGIN
	DECLARE @city VARCHAR(50)
	DECLARE @count INT = (SELECT COUNT(DISTINCT a.City) FROM SalesLT.Address a)
	DECLARE @originalCount INT = @count
	SET @count = @count - 1
	DECLARE @i INT = 1

	WHILE (@i <= @originalCount)
	BEGIN
		SELECT @city = City
		FROM dbo.GetCity(@count)

		IF (@city IS NULL)
			BREAK

		-- Operations:
		PRINT ' '
		PRINT CAST(@i AS VARCHAR(5)) + ': ' + @city

		IF ((SELECT AVG(oh.Freight)
			 FROM SalesLT.Address a
			 JOIN SalesLT.SalesOrderHeader oh ON oh.BillToAddressID = a.AddressID
			 WHERE a.City = @city
			 GROUP BY a.City) > 50)
		BEGIN
			--UPDATE SalesLT.SalesOrderHeader
			--SET Freight = Freight * 1.10
			--FROM SalesLT.SalesOrderHeader oh
			--JOIN SalesLT.Address a ON a.AddressID = oh.BillToAddressID
			--WHERE a.City = @city
			PRINT 'Freight Updated!'
		END

		SET @count= @count - 1
		SET @i = @i + 1
	END
END
GO

EXEC UpdateFrieghtBasedOnRegion

/*
SELECT DISTINCT a.City
FROM SalesLT.Address a
*/


--3. 📦 Build a Scalar Function: fn_GetCustomerTier
--Create a scalar function that:

--Takes @CustomerID
--Calculates the total amount spent (TotalDue)
--Returns a customer tier:
--  Bronze < 1000
--  Silver 1000–5000
--  Gold > 5000

GO
CREATE OR ALTER FUNCTION fn_GetCustomerTier(@CustomerID INT)
RETURNS VARCHAR(50)
AS 
BEGIN
	DECLARE @sum DECIMAL(30, 2) = (
	SELECT SUM(oh.TotalDue)
	FROM SalesLT.Customer c
	JOIN SalesLT.SalesOrderHeader oh ON oh.CustomerID = c.CustomerID
	WHERE c.CustomerID = @CustomerID
	GROUP BY oh.CustomerID
	)

	IF (@sum < 1000)
		RETURN 'Bronze'
	ELSE IF (@sum >= 1000 AND @sum <= 5000)
		RETURN 'Silver'
	ELSE IF (@sum > 5000)
		RETURN 'Gold'

	RETURN 'N/A'
END
GO

DECLARE @ctier VARCHAR(50), @id INT = 1
SELECT @ctier = dbo.fn_GetCustomerTier(@id)
PRINT 'Customer ' + CAST(@id AS VARCHAR(10)) + ' tier: ' + @ctier



--4. 📈 Generate Report of Top 5 Customers by Year
--Create a stored procedure TopCustomersByYear that:
--Accepts a year (e.g., 2023)
--Returns the top 5 customers by total amount spent that year

GO
CREATE OR ALTER PROCEDURE TopCustomersByYear @year INT
AS
BEGIN
	SELECT TOP 5 oh.CustomerID, CONCAT(c.FirstName, ' ', c.LastName) AS Name, SUM(oh.TotalDue) AS Total_Amount_Spent
	FROM SalesLT.Customer c
	JOIN SalesLT.SalesOrderHeader oh ON c.CustomerID = oh.CustomerID
	WHERE YEAR(oh.OrderDate) = @year
	GROUP BY oh.CustomerID, c.FirstName, c.LastName
	ORDER BY Total_Amount_Spent DESC
END
GO

EXEC TopCustomersByYear @year = 2008



--5. 🔍 Lookup Product Details Dynamically
--Create a procedure GetProductInfo that:
--Accepts a @ProductID
--Returns: Product Name, Category Name, Price, Model Name, and Total Quantity Sold

GO
CREATE OR ALTER PROCEDURE GetProductInfo @ProductID INT
AS
BEGIN
	SELECT p.Name, pc.Name, p.ListPrice, pm.Name, SUM(od.OrderQty) AS Quantity
	FROM SalesLT.Product p
	JOIN SalesLT.ProductCategory pc ON pc.ProductCategoryID = p.ProductCategoryID
	JOIN SalesLT.ProductModel pm ON pm.ProductModelID = p.ProductModelID
	JOIN SalesLT.SalesOrderDetail od ON od.ProductID = p.ProductID
	WHERE p.ProductID = @ProductID
	GROUP BY p.Name, pc.Name, p.ListPrice, pm.Name
END
GO

EXEC GetProductInfo @productID = 712


--6. 🔁 Simulate Order Discounts with LOOP
--Create a WHILE loop that:
--Iterates through the top 10 most expensive products
--If ListPrice > 1000, reduce it by 10%
--Log original and updated price using PRINT

GO
CREATE or ALTER PROCEDURE GetProduct @count INT, @price DECIMAL(20, 2) OUTPUT, @id INT OUTPUT
AS
BEGIN
	SELECT TOP 1 @price = p.ListPrice, @id = p.ProductID
	FROM SalesLT.Product p
	WHERE p.ProductID NOT IN (SELECT TOP (@count) p1.ProductID
							  FROM SalesLT.Product p1
							  ORDER BY p1.ListPrice DESC)
	ORDER BY p.ListPrice DESC
END
GO


GO
CREATE or ALTER PROCEDURE Top10Products
AS 
BEGIN
	DECLARE @c INT = 9, @i INT = 1, @pid INT
	DECLARE @oldprice DECIMAL(20, 2)

	WHILE (@i <= 10)
	BEGIN
		EXEC GetProduct @count = @c, @price = @oldprice OUTPUT, @id= @pid OUTPUT
		
		IF (@oldprice > 1000)
		BEGIN
			--UPDATE SalesLT.Product
			--SET ListPrice = ListPrice - ListPrice * 0.10
			--FROM SalesLT.Product p
			--WHERE p.ProductID = @pid

			PRINT 'Price Updated!'
			PRINT 'Old price: ' + CAST(@oldprice AS VARCHAR(25)) + ', ' +  + ' New price: ' + CAST(@oldprice * 0.9 AS VARCHAR(25))
			PRINT ' '
			SET @i = @i
		END

		SET @c = @c - 1
		SET @i = @i + 1
	END
END
GO

EXEC Top10Products



SELECT p.Name, p.ListPrice
FROM SalesLT.Product p
ORDER BY p.ListPrice DESC



--7. 🧾 Generate an Order Summary Function
--Create an inline table-valued function fn_GetOrderSummary(@SalesOrderID INT) that:
--Returns: ProductName, Quantity, UnitPrice, LineTotal for a given order

GO
CREATE OR ALTER FUNCTION fn_GetOrderSummary(@SalesOrderID INT)
RETURNS Table
RETURN
(
	SELECT p.Name as Product_Name, SUM(od.OrderQty) AS Quantity, od.UnitPrice, od.LineTotal
	FROM SalesLT.Product p
	JOIN SalesLT.SalesOrderDetail od ON od.ProductID = p.ProductID
	WHERE od.SalesOrderID = @SalesOrderID
	GROUP BY p.Name, od.UnitPrice, od.LineTotal
)
GO

DECLARE @id INT = 71783
SELECT *
FROM dbo.fn_GetOrderSummary(@id)


--SELECT od.SalesOrderID
--FROM SalesLT.SalesOrderDetail od



--8. 🏷️ Categorize Products by Weight
--Write a CASE-based query that adds a virtual column:
--Lightweight (< 10)
--Medium (10–30)
--Heavy (> 30)

SELECT p.ProductID, p.Name, p.Weight, 
										CASE 
											WHEN p.Weight < 10 THEN 'Lightweight'
											WHEN p.Weight >= 10 AND p.Weight<=30 THEN 'Medium'
											WHEN p.Weight > 30 THEN 'Heavy'
											ELSE 'Unknown'
										END AS Weight_Cat
FROM SalesLT.Product p




--9. 🧠 Complex Join with Nested Aggregation
--Return a list of:
--Product Categories
--Average Unit Price
--Total Quantity Sold
--Only for orders after 2007


SELECT pc.Name, AVG(od.UnitPrice) AS AvgUnitPrice, SUM(od.OrderQty) AS TotalQuantity
FROM SalesLT.Product p
JOIN SalesLT.ProductCategory pc ON pc.ProductCategoryID = p.ProductCategoryID
JOIN SalesLT.SalesOrderDetail od ON od.ProductID = p.ProductID
JOIN SalesLT.SalesOrderHeader oh ON oh.SalesOrderID = od.SalesOrderID
WHERE YEAR(oh.OrderDate) > 2007
GROUP BY pc.Name



--10. 🛒 Procedure to Insert a New Order
--Create a stored procedure InsertOrder that:
--Accepts @CustomerID, @ProductID, @Quantity
--Inserts into SalesOrderHeader and SalesOrderDetail with auto-calculated values (e.g., Freight = 5% of Subtotal)

GO
CREATE OR ALTER PROCEDURE InsertOrder
    @CustomerID INT,
    @ProductID INT,
    @Quantity INT
AS
BEGIN
    DECLARE @OrderID INT,
            @UnitPrice MONEY,
            @SubTotal MONEY,
            @Freight MONEY

    -- Get Unit Price
    SELECT @UnitPrice = ListPrice FROM SalesLT.Product WHERE ProductID = @ProductID

    -- Calculate subtotal and freight
    SET @SubTotal = @UnitPrice * @Quantity
    SET @Freight = @SubTotal * 0.05

    -- Insert SalesOrderHeader
    INSERT INTO SalesLT.SalesOrderHeader (CustomerID, OrderDate, DueDate, ShipDate, SubTotal, Freight, TotalDue, Status, OnlineOrderFlag, BillToAddressID, ShipToAddressID)
    VALUES (@CustomerID, GETDATE(), GETDATE() + 3, NULL, @SubTotal, @Freight, @SubTotal + @Freight, 1, 1,
            (SELECT TOP 1 AddressID FROM SalesLT.CustomerAddress WHERE CustomerID = @CustomerID),
            (SELECT TOP 1 AddressID FROM SalesLT.CustomerAddress WHERE CustomerID = @CustomerID))

    -- Get newly created SalesOrderID
    SET @OrderID = SCOPE_IDENTITY()

    -- Insert SalesOrderDetail
    INSERT INTO SalesLT.SalesOrderDetail (SalesOrderID, ProductID, OrderQty, UnitPrice, UnitPriceDiscount, LineTotal)
    VALUES (@OrderID, @ProductID, @Quantity, @UnitPrice, 0, @SubTotal)
END
GO


