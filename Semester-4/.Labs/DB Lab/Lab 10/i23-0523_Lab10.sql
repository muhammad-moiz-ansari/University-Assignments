USE Northwind_Database

--• Create a stored procedure that accepts a country name as a parameter and returns all customers from that country.
CREATE PROCEDURE Func1
	@countryname VARCHAR(60)
AS
BEGIN
	SELECT * FROM Customers c WHERE c.Country = @countryname
END

EXEC Func1 @countryname = 'Germany'

--• Create a stored procedure that takes a minimum order date as a (an optional) parameter and returns all orders placed on or after that date.
CREATE or ALTER PROCEDURE Func2
	@minodate DATE = '1997-09-11'
AS
BEGIN
	SELECT * FROM Orders o WHERE o.OrderDate >= @minodate ORDER BY o.OrderDate
END

--DROP PROCEDURE Func2;

EXEC Func2

--• Create a DDL trigger that logs a message into a log table whenever a table is created in the Northwind database. First create log table 
--  with two columns (Event Type, Event Description)
CREATE TABLE LogTable(
	EventType VARCHAR(100),
	EventDesc VARCHAR(100)
);

GO
CREATE or ALTER TRIGGER Logging ON DATABASE
FOR
	CREATE_TABLE
AS
BEGIN
	INSERT INTO LogTable (EventType, EventDesc)
	VALUES ('Create Table', 'A table has been successfully created in the database')
END
GO

CREATE TABLE A (x INT);
CREATE TABLE B (x INT);
CREATE TABLE C (x INT);

SELECT * FROM LogTable

--• Create an AFTER INSERT DML trigger on the Orders table that logs an entry in a custom table whenever a new order is added. 
--  (Do explore Inserted in triggers for this purpose).
GO
CREATE OR ALTER TRIGGER iNtrIGGER ON Orders
	AFTER INSERT
AS
BEGIN
	INSERT INTO LogTable (EventType, EventDesc)
	SELECT 'Order inserted', CONCAT('Order # ', i.OrderID, ' added') FROM Inserted i
END
GO

INSERT INTO Orders( CustomerID, EmployeeID, OrderDate, RequiredDate, ShippedDate, ShipVia, Freight, ShipName, ShipAddress, ShipCity, ShipRegion, ShipPostalCode, ShipCountry) 
VALUES (
    'ALFKI', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
);

--• Create a function that takes an Order ID as a parameter and returns the total amount for that order 
--  (calculated as UnitPrice * Quantity for each item).
GO
CREATE or ALTER FUNCTION Func5 (@oid INT)
RETURNS DECIMAL(15, 2)
AS
BEGIN
	RETURN (SELECT SUM(od.UnitPrice * od.Quantity) FROM [Order Details] od WHERE od.OrderID = @oid)
END
GO

drop function func5

SELECT dbo.Func5(10248) AS SUM