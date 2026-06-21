CREATE DATABASE ECommerce

-- Customers Table
CREATE TABLE Customers(
	Customer_ID INT Identity(1,1) PRIMARY KEY,
	Customer_Name VARCHAR(60) NOT NULL,
	Email VARCHAR(40) NOT NULL,
	PhoneNo VARCHAR(15) NOT NULL,
	Customer_Address VARCHAR(300) NOT NULL,
	Signup_Date DATE NOT NULL
);

-- Products Table
CREATE TABLE Products(
	Product_ID INT Identity(1,1) PRIMARY KEY,
	Product_Name VARCHAR(100) NOT NULL,
	Product_Description VARCHAR(500) NULL,
	Price DECIMAL(15, 2) NOT NULL CHECK(Price>=0),
	Quantity INT DEFAULT 1 CHECK(Quantity>0),
	Price_per_unit DECIMAL(15, 2) NOT NULL,
	Total_Price DECIMAL(15, 2) NOT NULL,
	Stock INT NOT NULL CHECK(Stock>0),
	Category VARCHAR(60) NOT NULL,
	Rating DECIMAL(3, 1) NULL CHECK(Rating >= 0 AND Rating <=10)
);

-- Orders Table
CREATE TABLE Orders(
	Order_ID INT Identity(1,1) PRIMARY KEY,
	C_ID INT
	FOREIGN KEY(C_ID) REFERENCES Customers(Customer_ID),
	Order_Date DATE NOT NULL,
	Order_Status VARCHAR(50) DEFAULT 'Pending' CHECK(Order_Status IN ('Pending', 'Processing', 'Shipped', 'Delivered', 'Canceled', 'Returned', 'Failed')),
	Total_Amount INT NOT NULL CHECK(Total_Amount>=0),
);

-- Order_Details Table
CREATE TABLE Order_Details(
	O_ID INT,
	P_ID INT,
	FOREIGN KEY(O_ID) REFERENCES Orders(Order_ID),
	FOREIGN KEY(P_ID) REFERENCES Products(Product_ID),
	PRIMARY KEY(O_ID, P_ID),
	Quantity INT DEFAULT 1 CHECK(Quantity>0),
	Price_per_unit DECIMAL(15, 2) NOT NULL CHECK(Price_per_unit>=0),
	Total_Price DECIMAL(15, 2) NOT NULL CHECK(Total_Price>=0)
);

-- Payments Table
CREATE TABLE Payments(
	Payment_ID  INT Identity(1,1) PRIMARY KEY,
	O_ID INT,
	FOREIGN KEY(O_ID) REFERENCES Orders(Order_ID),
	Payment_Date DATE NOT NULL,
	Amount DECIMAL(15, 2) NOT NULL CHECK(Amount>=0),
	Payment_Method VARCHAR(30) NOT NULL CHECK(Payment_Method IN ('Card', 'Credit Card', 'Cash'))
);

ALTER TABLE Products
ADD Discount DECIMAL(4, 2) DEFAULT 0

-- (Can't truncate because of presence of foreign keys)
TRUNCATE TABLE Customers
TRUNCATE TABLE Orders

DROP TABLE Order_Details

SELECT * FROM Products