USE Northwind_Database

--1. Provide the order ids of all orders that are shipped using ‘Federal Shipping’.
SELECT OrderID
FROM Orders
INNER JOIN Shippers s
ON ShipVia = s.ShipperID
WHERE s.CompanyName = 'Federal Shipping'

--2. Select the name, address, city, and region of Customers that have placed orders to be delivered in Madrid.
SELECT DISTINCT c.ContactName, Address, City, Region
FROM Customers c
JOIN Orders o
ON c.CustomerID = o.CustomerID
WHERE o.ShipCity = 'Madrid'

--3. Extract the ids and the names in upper case for customers who haven’t placed any orders yet.
SELECT DISTINCT c.CustomerID, UPPER(c.ContactName) AS [Contact Name]
FROM Customers c
JOIN Orders o
ON c.CustomerID NOT IN (
						SELECT o1.CustomerID
						FROM Orders o1)

SELECT c.CustomerID, UPPER(c.ContactName) AS [Contact Name]
FROM Customers c
LEFT JOIN Orders o
ON o.CustomerID = c.CustomerID
WHERE o.OrderID IS NULL


--4. Find the total number of products ordered from each supplier, including suppliers who have not supplied any products.
SELECT s.SupplierID, COUNT(p.ProductID) AS [Total No. of Products]
FROM Products p
RIGHT JOIN Suppliers s
ON s.SupplierID = p.SupplierID
GROUP BY s.SupplierID

---

SELECT s.SupplierID, s.CompanyName, COUNT(p.ProductID) AS [Total No. of Products]
FROM Suppliers s
LEFT JOIN Products p
ON s.SupplierID = p.SupplierID
GROUP BY s.SupplierID, s.CompanyName;

--5. Provide the names of the customers and their cities who belong to the same city as the employee who processed their order. 
--   Also display the full names of the employees.
SELECT c.ContactName, c.City, e.FirstName, e.LastName
FROM Customers c
JOIN Orders o ON o.CustomerID = c.CustomerID
JOIN Employees e ON o.EmployeeID = e.EmployeeID
WHERE c.City = e.City

-------- 6. Display the employees (managers) who manage at least 3 employees.
SELECT DISTINCT m.FirstName
FROM Employees m
JOIN Employees e1
ON e1.ReportsTo = m.EmployeeID
GROUP BY m.EmployeeID, m.FirstName
HAVING COUNT(e1.ReportsTo) >= 3

--7. Fetch top 5 most popular products, products that have the maximum quantity of units sold.
SELECT TOP 5 p.ProductID, ProductName, SUM(od.Quantity) AS Total_Quantity
FROM Products p
JOIN [Order Details] od ON p.ProductID = od.ProductID
GROUP BY p.ProductID, p.ProductName
ORDER BY Total_Quantity DESC

--8. Create a view to find the total number of products ordered by each customer.
GO
CREATE OR ALTER VIEW [Customer Product Count] AS 
SELECT c.CustomerID, c.ContactName, SUM(od.Quantity) AS [No. of Products]
FROM Customers c
JOIN Orders o ON c.CustomerID = o.CustomerID
JOIN [Order Details] od ON od.OrderID = o.OrderID
GROUP BY c.CustomerID, c.ContactName;
GO

SELECT * FROM [Customer Product Count]

--9. Find all products and their corresponding supplier names, but only return products that have not been discontinued.
SELECT p.ProductID, p.ProductName, s.CompanyName
FROM Products p
JOIN Suppliers s ON s.SupplierID = p.SupplierID
WHERE p.Discontinued = 0

--10. Retrieve the most recent order (by order date) placed by each customer.
SELECT c.CustomerID, c.ContactName, o.OrderDate
FROM Customers c
JOIN Orders o ON c.CustomerID = o.CustomerID
WHERE o.OrderDate = (
					SELECT MAX(o2.OrderDate)
					FROM Orders o2
					WHERE o2.CustomerID = c.CustomerID);

--11. Identify employees who have processed more than 10 orders for any individual customer.
SELECT c.CustomerID, e.EmployeeID, COUNT(o.OrderID) AS [Order Count]
FROM Employees e
JOIN Orders o ON o.EmployeeID = e.EmployeeID
JOIN Customers c ON o.CustomerID = c.CustomerID
GROUP BY c.CustomerID, e.EmployeeID
HAVING COUNT(o.OrderID) > 10
ORDER BY COUNT(o.OrderID);

--12. List all products where the total quantity ordered exceeds 100 units.
SELECT p.ProductID, p.ProductName, SUM(od.Quantity) AS [Total Quantity]
FROM Products p
JOIN [Order Details] od ON p.ProductID = od.ProductID
GROUP BY p.ProductID, p.ProductName
HAVING SUM(od.Quantity) > 100
ORDER BY SUM(od.Quantity)

--13. Find suppliers that have supplied products to orders shipped by a specific shipper. (e.g., ShipperID = 1)
SELECT DISTINCT s.SupplierID, s.ContactName, sh.ShipperID, sh.CompanyName
FROM Suppliers s
JOIN Products p ON s.SupplierID = p.SupplierID
JOIN [Order Details] od ON p.ProductID = od.ProductID
JOIN Orders o ON od.OrderID = o.OrderID
JOIN Shippers sh ON o.ShipVia = sh.ShipperID
WHERE sh.ShipperID = 1

--14. Find employees who have handled orders for customers in the same country as the employee.
SELECT e.EmployeeID, e.FirstName, c.CustomerID, c.ContactName AS CustomerName, e.Country
FROM Employees e
JOIN Orders o ON e.EmployeeID = o.EmployeeID
JOIN Customers c ON o.CustomerID = c.CustomerID
WHERE e.Country = c.Country

--15. Create a view to retrieve the most expensive product from each category.
GO
CREATE or ALTER VIEW [Most Expensive Products] AS
SELECT c.CategoryID, c.CategoryName, p.UnitPrice, p.ProductID, p.ProductName
FROM Products p
JOIN Categories c ON p.CategoryID = c.CategoryID
WHERE p.UnitPrice = (SELECT MAX(p1.UnitPrice)
					FROM Products p1
					WHERE p1.CategoryID = p.CategoryID)
GO

SELECT * FROM [Most Expensive Products]
ORDER BY CategoryID