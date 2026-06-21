USE Chinook

-- Task 1
CREATE VIEW EmployeesInoviceView AS
SELECT e.EmployeeId, e.FirstName, e.LastName, MAX(i.Total) AS Max_Invoice
FROM Employee e
JOIN Customer c ON c.SupportRepId = e.EmployeeId
JOIN Invoice i ON i.CustomerId = c.CustomerId
GROUP BY e.EmployeeId, e.FirstName, e.LastName

SELECT * FROM EmployeesInoviceView

-- Task 2
SELECT c.FirstName, c.LastName, UPPER(c.City) AS City, ROUND(i.Total, 2) AS Total_invoice, YEAR(i.InvoiceDate) AS Invoice_Year
FROM Customer c
JOIN Invoice i on c.CustomerId = i.CustomerId
WHERE YEAR(i.InvoiceDate) = (
								SELECT MIN(YEAR(i1.InvoiceDate)) AS I_Year
								FROM Customer c1
								JOIN Invoice i1 on c1.CustomerId = i1.CustomerId
								WHERE c1.CustomerId = c.CustomerId AND i.InvoiceId = i1.InvoiceId
								)

-- Task 3
SELECT m.EmployeeId, m.FirstName
FROM Employee m
WHERE m.ReportsTo IS NULL

-- Task 4
SELECT c.CustomerId, c.FirstName, c.LastName, a.Name
FROM Customer c
JOIN Invoice i ON c.CustomerId = i.CustomerId
JOIN InvoiceLine il ON il.InvoiceId = i.InvoiceId
JOIN Track t ON t.TrackId = il.TrackId
JOIN Album al ON al.AlbumId = t.AlbumId
JOIN Artist a ON a.ArtistId = al.ArtistId
WHERE a.Name LIKE 'O%O' AND a.Name LIKE '___%'

-- Task 5
SELECT TOP 3 a.Name, il.Quantity
FROM InvoiceLine il 
JOIN Track t ON t.TrackId = il.TrackId
JOIN Album al ON al.AlbumId = t.AlbumId
JOIN Artist a ON a.ArtistId = al.ArtistId
ORdER BY il.Quantity DESC

-- Task 6
SELECT e.EmployeeId, e.FirstName
FROM Employee e
JOIN Employee m ON e.ReportsTo = m.EmployeeId
WHERE e.BirthDate < ALL (
							SELECT e1.BirthDate
							FROM Employee e1
							WHERE e1.EmployeeId = m.EmployeeId) AND
					e.FirstName LIKE '__n%'

-- Task 7
CREATE TABLE Departments(
	DeptID INT IDENTITY(1,1) primary key,
	DeptName VARCHAR(100) Unique NOT NULL,
	Location VARCHAR(50) NOT NULL,
	CreatedDate DATE Default GETDATE()
);
INSERT into Departments VALUES
('CS', 'Isb', GETDATE()), 
('DS', 'Isb', '2024-11-9')

alter table employee
add DeptID INT
alter table employee
add foreign key (DeptID) references departments(DeptID)

-- Task 8
SELECT DISTINCT c.CustomerId, c.FirstName, i.InvoiceDate, (i.Total)
FROM Customer c
JOIN Invoice i ON i.CustomerId = c.CustomerId
JOIN InvoiceLine il On il.InvoiceId = i.InvoiceId
WHERE ABS(DATEDIFF(DAY, i.InvoiceDate, GETDATE())) < 365 AND (i.Total) > 100
-- It is considered that purchase is withinh one year duration time

-- Task 9
SELECT t1.TrackId, t1.UnitPrice
FROM Track t1
WHERE t1.UnitPrice > ALL (
						SELECT AVG(t2.UnitPrice) AS Avg_Price
						FROM Track t2
						WHERE t2.AlbumId=t1.AlbumId
						)

-- Task 10
SELECT SUM(il.Quantity) AS Number_of_Invoices
FROM InvoiceLine il

--FROM Customer c
--JOIN Invoice i ON i.CustomerId = c.CustomerId
--JOIN InvoiceLine il On il.InvoiceId = i.InvoiceId

