USE Northwind_Database

--1. Write a query that declares a variable for storing an employee's full name and assigns it the full name of the employee with
--   employee_id 1. Output the full name.
DECLARE @fullname VARCHAR(50)
SET @fullname = (SELECT CONCAT(e.FirstName, ' ', e.LastName)
				 FROM Employees e
				 WHERE e.EmployeeID = 1)
PRINT 'Full name: ' + @fullname

--2. Declare a variable for the maximum salary allowed in the company, assign it a value of 100000, and print this value.
DECLARE @maxsalary INT = 100000
PRINT @maxsalary

--3. Create a query that checks if the HireDate of the employee with EmployeeID = 3 is before '1995-01-01'. If true, print "Long-time
--   employee"; otherwise, print "New employee."
DECLARE @chhiredate DATE = (SELECT e.HireDate FROM Employees e WHERE e.EmployeeID = 3)
IF @chhiredate < '1995-01-01'
Begin
	PRINT 'Long-time employee'
End
ELSE
Begin
	PRINT 'New employee'
End

--4. Write a query that retrieves the Title of the employee with EmployeeID = 4 and uses a CASE statement to output a description based on the title.
DECLARE @title VARCHAR(60) = (SELECT e.Title FROM Employees e WHERE e.EmployeeID = 4)
PRINT (
	CASE @title
		WHEN 'Sales Representative' THEN 'SR'
		WHEN 'Vice President, Sales' THEN 'VP'
		WHEN 'Sales Manager' THEN 'SM'
		WHEN 'Inside Sales Coordinator' THEN 'ISC'
		ELSE 'None'
	END )
	
--5. Write a query that uses a WHILE loop to print the EmployeeIDs of the first 5 employees in the Employees table.
DECLARE @i INT = 0
DECLARE @j INT = (SELECT TOP 1  e.EmployeeID FROM Employees e ORDER BY e.EmployeeID ASC)
DECLARE @id INT
WHILE @i < 5
BEGIN
	SET @id = (SELECT e.EmployeeID FROM Employees e WHERE e.EmployeeID = @j)
	PRINT @id
	SET @i = @i + 1
	SET @j = @j + 1
END;

--6. Create a loop that iterates through employees and use a break condition to exit the loop if an employee's HireDate is after '1990-01-01'. 
--   Output the employee's EmployeeID and HireDate.
DECLARE @hi INT = 1
DECLARE @i1 INT = 1
DECLARE @j1 INT = (SELECT TOP 1  e.EmployeeID FROM Employees e ORDER BY e.EmployeeID)
DECLARE @id1 INT
DECLARE @hiredate DATE
WHILE @hi = 1
BEGIN
	SET @hiredate = (SELECT e.HireDate FROM Employees e WHERE e.EmployeeID = @j1)
	SET @id1 = (SELECT e.EmployeeID FROM Employees e WHERE e.EmployeeID = @j1)
	IF @hiredate > '1993-01-01'
	BEGIN
		GOTO l1
	END
	PRINT @id1
	PRINT @hiredate
	PRINT ' '
	SET @j1 = @j1 + 1
END
L1:

--7. Write a query that declares a variable for storing the number of orders placed by the employee with EmployeeID = 2 
--   and prints this count.
DECLARE @count INT = (SELECT COUNT(*)
					  FROM Employees e
					  JOIN Orders o ON e.EmployeeID = o.EmployeeID
					  WHERE e.EmployeeID = 2)
PRINT @count

--8. Write a query that retrieves the Country of a customer with CustomerID = 'ALFKI' and uses a CASE statement to 
--   categorize the region as 'Europe', 'Asia', or 'Other' based on the country.
DECLARE @country VARCHAR(70) = (SELECT c.Country FROM Customers c WHERE c.CustomerID = 'ALFKI')
PRINT (
	CASE @country
		WHEN 'Germany' THEN 'Europe'
		WHEN 'Pakistan' THEN 'Asia'
		WHEN 'Mexico' THEN 'North America'
		WHEN 'Canada' THEN 'North America'
		ELSE 'Other'
	END
)

--9. Write a query that creates a labeled loop to print the ProductIDs of the first 5 products from the Products table, 
--   and demonstrates how to structure a labeled block of code.
DECLARE @i2 INT = 0
DECLARE @j2 INT = (SELECT TOP 1  p.ProductID FROM Products p ORDER BY p.ProductID)
DECLARE @id2 INT
Loop1:
	IF @i2 >= 5
	BEGIN
		GOTO Exit_loop1
	END
	SET @id2 = (SELECT p.ProductID FROM Products p WHERE p.ProductID = @j2)
	PRINT @id2
	SET @i2 = @i2 + 1
	SET @j2 = @j2 + 1
	GOTO Loop1
Exit_loop1:

--10. Write a query that uses the above task to demonstrate the use of GOTO by skipping a section of code that prints a message and jumps to a labeled
--    section that prints "This section was reached."
GOTO Skip
	PRINT 'I am IGNOOOOORED!!! :('
Skip:
PRINT 'This section was reached.'

--11. Write a query that retrieves the number of orders placed in 1997 and categorizes them as 'Low', 'Medium', or 'High' based on the total number 
--    of orders using a CASE statement.
DECLARE @ocount INT = ( SELECT COUNT(*)
						FROM Orders o
						WHERE YEAR(o.OrderDate) = '1997')

PRINT (
	CASE
		WHEN @ocount < 300 THEN 'Low'
		WHEN @ocount = 300 THEN 'Medium'
		ELSE 'High'
	END
	+ CHAR(13) + CHAR(10) + 'quantity'
	)