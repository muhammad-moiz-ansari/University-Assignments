--USE Northwind_Database

--SELECT * FROM Customers
--SELECT * FROM Orders

--1. Write a query to display the number of orders placed by each customer.
SELECT c.CustomerID, COUNT(o.CustomerID) AS [No. of Orders]
FROM Customers c, Orders o 
WHERE c.CustomerID=o.CustomerID
GROUP BY c.CustomerID

--2. Write a query to display the average unit price of products in each category.
SELECT CategoryID, AVG(UnitPrice) AS [Average Price]
FROM Products
GROUP BY CategoryID

--3. Write a query to display customers who have placed more than 6 orders.
SELECT CustomerID
FROM Orders
GROUP BY CustomerID
HAVING COUNT(*)>6

--4. Write a query to display the total number of orders placed each year.
SELECT YEAR(OrderDate) AS Year, COUNT(*) AS [No. of Orders]
FROM Orders
GROUP BY YEAR(OrderDate)

--5. Write a query to find the total number of products supplied by each supplier.
SELECT COUNT(*) AS [No. of Products]
FROM Products
GROUP BY SupplierID

--6. Write a query to find the months in which more than 50 orders were placed that are also shipped.
SELECT MONTH(OrderDate) AS Month
FROM Orders
WHERE ShippedDate IS NOT NULL
GROUP BY MONTH(OrderDate)
HAVING COUNT(*)>50

--7. Write a query to find the customers who haven't placed any orders.
SELECT c.CustomerID
FROM Customers c
WHERE c.CustomerID NOT IN(
	SELECT o.CustomerID
	FROM Orders o
)

--8. Write a query to find the products that have never been ordered.
SELECT p.ProductID
FROM Products p
WHERE p.ProductID NOT IN(
	SELECT o.ProductID
	FROM [Order Details] o
)

--9. Write a query to find the average number of units ordered for each product.
SELECT ProductID, AVG(Quantity) AS [Avg Units Ordered]
FROM [Order Details]
GROUP BY ProductID
ORDER BY ProductID

--10. Write a query to list employees who have been hired after January 1, 1995.
SELECT EmployeeID
FROM Employees
WHERE HireDate > '1995-01-01'

--11. Write a query to find the products that have been discontinued.
SELECT ProductID, ProductName
FROM Products
WHERE Discontinued='True'

--12. Write a query to find the total number of units in stock for each category.
SELECT SUM(UnitsInStock) AS [No. of Units]
FROM Products
GROUP BY CategoryID

--13. Find a product category whose unit price is more than the average unit price of ALL product categories.
SELECT CategoryID
FROM Products
WHERE UnitPrice > ALL(
					SELECT AVG(UnitPrice)
					FROM Products
					GROUP BY CategoryID)

--14. Find all products that have a price higher than the average price in their category.
SELECT p1.ProductID, p1.ProductName
FROM Products p1
WHERE p1.UnitPrice > (
					SELECT AVG(p2.UnitPrice)
					FROM Products p2
					WHERE p1.CategoryID = p2.CategoryID)

--15. Without sorting the data, retrieve the employees whose hire date is earlier than all their subordinates (employees reporting to them).
SELECT e1.EmployeeID, e1.FirstName
FROM Employees e1
WHERE EmployeeID IN (
					SELECT e2.ReportsTo
					FROM Employees e2
					GROUP BY e2.ReportsTo) AND e1.HireDate < ALL (
																  SELECT e3.HireDate
																  FROM Employees e3
																  WHERE e3.ReportsTo=e1.EmployeeID)

--16. Find all customers who placed an order for a product supplied by 'Exotic Liquids'. 
--    (check tables Customers, Orders, OrderDetails, Products, and Suppliers)

SELECT c.CustomerID, c.Phone
FROM Customers c
WHERE c.CustomerID IN (
						SELECT o.CustomerID
						FROM Orders o
						WHERE o.OrderID IN (
											SELECT od.OrderID
											FROM [Order Details] od
											WHERE od.ProductID IN (
																	SELECT p.ProductID
																	FROM Products p
																	WHERE p.SupplierID IN (
																							SELECT s.SupplierID
																							FROM Suppliers s
																							WHERE s.CompanyName='Exotic Liquids'))))
