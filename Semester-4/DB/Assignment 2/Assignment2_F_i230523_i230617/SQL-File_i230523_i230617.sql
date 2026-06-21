Create Database Brazil_database
Use Brazil_database

----------------------------------------------------------------------------------
---------------------------------             ------------------------------------
-------------------------------  TABLES CREATE  ----------------------------------
---------------------------------             ------------------------------------
----------------------------------------------------------------------------------

Create Table customers(
	customer_id varchar(40) PRIMARY KEY NOT NULL,
	customer_unique_id varchar(40) NOT NULL,
	customer_zip_code_prefix int NOT NULL,
	customer_city varchar(50) NOT NULL,
	customer_state varchar(3) NOT NULL,
	Foreign key (customer_zip_code_prefix) references geolocation(zip_code)
);

Create Table orders(
	order_id varchar(40) Primary Key Not Null,
	customer_id varchar(40) Not NULL,
	order_status varchar(20) NOT NULL,		-- created, shipped, canceled, approved, processing, unavailable, delivered, invoiced
	order_purchase_timestamp DateTime Not NUll,
	order_approved_at DateTime NUll,
	order_delivered_carrier_date DateTime NUll,
	order_delivered_customer_date DateTime null,
	order_estimated_delivery_date DateTime not null,
	Foreign Key (customer_id) references customers(customer_id)
);

Create Table order_reviews(
	review_id varchar(40) Not Null,
	order_id varchar(40) Not Null,
	review_score int not null,
	review_comment_title varchar(500) null,
	review_comment_message varchar(500) null,
	review_creation_date DateTime not null,
	review_answer_timestamp DateTime not null,
	Foreign Key (order_id) references orders(order_id),
	Primary Key(review_id,order_id)
);

Create Table order_payment(
	order_id varchar(40) Not Null,
	payment_sequential int not null,
	payment_type varchar(100) not null,
	payment_installments int not null,
	payment_value decimal(10,3) not null,
	Foreign Key (order_id) references orders(order_id),
	primary key(order_id,payment_sequential)
);

Create Table products(
	product_id varchar(40) Primary Key Not Null,
	product_category_name varchar(100) Null,
	product_name_lenght int Null,
	product_description_lenght int Null,
	product_photos_qty int Null,
	product_weight_g int Null,
	product_length_cm int Null,
	product_height_cm int Null,
	product_width_cm int Null
);

Create Table sellers(
	seller_id varchar(40) Primary Key Not Null,
	seller_zip_code_prefix int Not Null,
	seller_city varchar(100) Not Null,
	seller_state varchar(3) Not Null,
	Foreign key (seller_zip_code_prefix) references geolocation(zip_code)
);

Create Table order_items(
	order_id varchar(40) Not Null,
	order_item_id int not null,
	product_id varchar(40) Not Null,
	seller_id varchar(40) Not Null,
	shipping_limit_date DateTime Not Null,
	price decimal(10,3) not null,
	freight_value decimal(10,3) not null,
	Foreign Key (order_id) references orders(order_id),
	Foreign Key (product_id) references products(product_id),
	Foreign Key (seller_id) references sellers(seller_id),
    Primary Key (order_id, order_item_id)
);

Create Table geolocation(
	geolocation_zip_code_prefix int not null,
	geolocation_lat varchar(50) not null,
	geolocation_lng decimal(20,15) not null,
	geolocation_city varchar(50) not null,
	geolocation_state varchar(3) not null,
	zip_code int Identity(1,1) Primary key
);

Alter table customers add zip_code int
Alter table sellers add zip_code int

UPDATE c
SET c.zip_code = g.zip_code
FROM customers c
JOIN geolocation g ON c.customer_zip_code_prefix = g.geolocation_zip_code_prefix

UPDATE s
SET s.zip_code = g.zip_code
FROM sellers s
JOIN geolocation g ON s.seller_zip_code_prefix = g.geolocation_zip_code_prefix

ALTER TABLE customers ADD CONSTRAINT FK_customers_geolocation FOREIGN KEY (zip_code) REFERENCES geolocation(zip_code)

ALTER TABLE sellers ADD CONSTRAINT FK_sellers_geolocation FOREIGN KEY (zip_code) REFERENCES geolocation(zip_code)

----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
---------------------------------- DATA LOAD -------------------------------------
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

BULK INSERT customers FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_customers_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a'
);

BULK INSERT orders FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_orders_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a'
);

BULK INSERT order_reviews FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_order_reviews_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0D0a',
	TABLOCK
);

BULK INSERT order_payment FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_order_payments_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a',
	TABLOCK
);

BULK INSERT products FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_products_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a',
	TABLOCK
);

BULK INSERT sellers FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_sellers_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a',
	TABLOCK
);

BULK INSERT order_items FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_order_items_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a',
	TABLOCK
);

BULK INSERT geolocation FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 2\Brazilian_Dataset\olist_geolocation_dataset.csv'
WITH(
	format='CSV',
	FirstRow=2,
	FIELDTERMINATOR=',',
	ROWTERMINATOR='0x0a',
	TABLOCK
);

---------------------------------------------------------------------------
-----------------------                             -----------------------
--------------------            SQL QUERIES            --------------------
-----------------------                             -----------------------
---------------------------------------------------------------------------

---------------------------------------------------------------------------
----------------------------- ORDER ANALYSIS ------------------------------
---------------------------------------------------------------------------

--We often lose our customers as the orders are delayed with the estimated delivery date. You need to find the following information

--a. Percentage of orders that got delayed beyond the estimated date 
select CAST(COUNT(*) AS FLOAT)/(Select Count(order_id) from orders) * 100 as Percentages
from orders
where order_estimated_delivery_date < order_delivered_customer_date and order_delivered_customer_date is not null

--b. What are the peak months of order delays?
SELECT MONTH(order_delivered_customer_date) AS [Peak Month], COUNT(*) AS [No. of Orders Delayed]
FROM orders
WHERE order_delivered_customer_date > order_estimated_delivery_date 
	  AND 
	  MONTH(order_delivered_customer_date) = (
												SELECT TOP 1 MONTH(order_delivered_customer_date)
												FROM orders
												WHERE order_delivered_customer_date > order_estimated_delivery_date
												GROUP BY MONTH(order_delivered_customer_date)
												ORDER BY COUNT(*) DESC
											 )
GROUP BY MONTH(order_delivered_customer_date)
ORDER BY COUNT(*) DESC

--c. Which state experiences the highest order delays? 
Select c.customer_state, Count(*) as delays
from customers c
inner join orders o on c.customer_id=o.customer_id
where o.order_estimated_delivery_date < o.order_delivered_customer_date and o.order_delivered_customer_date is not null
group by c.customer_state
having Count(*) = (
					Select TOP 1 Count(*) as delays1
					from customers c
					inner join orders o on c.customer_id=o.customer_id
					where o.order_estimated_delivery_date < o.order_delivered_customer_date and o.order_delivered_customer_date is not null
					group by c.customer_state
					order by delays1 desc
				 )
order by delays desc

--d. See how many orders are still in “pending” status for each year
SELECT YEAR(o.order_purchase_timestamp) AS Year, COUNT(*) AS [Pending Orders]
FROM orders o
WHERE order_status  IN ('created', 'approved', 'processing', 'invoiced')
GROUP BY YEAR(o.order_purchase_timestamp)

--e. What is the average delay duration per seller?
Select s.seller_id, cast(SUM(abs(DATEDIFF(DAY,o.order_estimated_delivery_date,o.order_delivered_customer_date)))as float)/COUNT(*) as averages
from sellers s
inner join order_items oi on oi.seller_id=s.seller_id
inner join orders o on o.order_id=oi.order_id
where order_estimated_delivery_date<order_delivered_customer_date and o.order_delivered_customer_date is not null
group by s.seller_id

--f. How do shipping costs impact order delays? Find the average shipping cost for delayed and on-time orders.
SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for Delayed]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date > o.order_estimated_delivery_date

SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for On-Time]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date <= o.order_estimated_delivery_date

--g. Which product category experience the most order delays. 
Select p.product_category_name, COUNT(*) as delayedorders
from order_items oi
inner join products p on p.product_id=oi.product_id
inner join orders o on o.order_id=oi.order_id
where o.order_delivered_customer_date > o.order_estimated_delivery_date and o.order_delivered_customer_date is not null
group by p.product_category_name
having COUNT(*) = (
					Select TOP 1 COUNT(*) as delayedorders1
					from order_items oi
					inner join products p on p.product_id=oi.product_id
					inner join orders o on o.order_id=oi.order_id
					where o.order_delivered_customer_date>o.order_estimated_delivery_date and o.order_delivered_customer_date is not null
					group by p.product_category_name
					order by delayedorders1 desc
				  )
order by delayedorders desc

--h. How do number of items per order affect the delays? Find the average number of items for delayed and on time orders. 
SELECT AVG(oiii.o_item_count) AS [Avg No. of Items for Delayed]
FROM (
		SELECT COUNT(oi.order_item_id) AS o_item_count
		FROM orders o
		JOIN order_items oi
		ON o.order_id =  oi.order_id
		WHERE o.order_delivered_customer_date > o.order_estimated_delivery_date
		GROUP BY o.order_id
		) AS oiii

SELECT AVG(oiii.o_item_count) AS [Avg No. of Items for On-Time]
FROM (
		SELECT COUNT(oi.order_item_id) AS o_item_count
		FROM orders o
		JOIN order_items oi
		ON o.order_id =  oi.order_id
		WHERE o.order_delivered_customer_date <= o.order_estimated_delivery_date
		GROUP BY o.order_id
		) AS oiii

---------------------------------------------------------------------------
---------------------------- CUSTOMER ANALYSIS ----------------------------
---------------------------------------------------------------------------

--We want to find the pattern and buying behavior of our customers, hence a through analysis is
--required for the customers as well. You need to find the following information

--a. What percentage of customers have made only one order?
Select cast(Count(*) as float)/(Select Count(Distinct customer_unique_id) from customers) * 100 as percentages
from customers c
where exists (	Select count(*)
				from customers cus
				where cus.customer_unique_id = c.customer_unique_id
				having count(*) = 1 )

--b. Find the top five cities with the most repeat customers (customers who have placed orders more than once)
SELECT TOP 5 c.customer_city, (SELECT TOP 1 COUNT(DISTINCT cc.customer_unique_id) AS s
							   FROM customers cc
							   WHERE cc.customer_city = c.customer_city
							   ORDER BY s DESC) AS num
FROM customers c
GROUP BY c.customer_city
HAVING Count(c.customer_unique_id) > 1
ORDER BY num DESC

--c. Calculate the average order price of customers for each state 
Select c.customer_state, AVG(price) as avg_order_price
from order_items oi
inner join orders o on o.order_id=oi.order_id
inner join customers c on c.customer_id=o.customer_id
group by c.customer_state

--d. Find the top ten customers with the highest number of orders placed.
SELECT TOP 10 c.customer_unique_id, COUNT(*) AS [Orders Placed]
FROM customers c
JOIN orders o							-- JOIN is used so that we can have other info of customer as well apart from the id
ON c.customer_id = o.customer_id
GROUP BY c.customer_unique_id
ORDER BY COUNT(*) DESC

--e. Which customers have the longest average delivery time
Select c.customer_unique_id, AVG(abs(DATEDIFF(DAY,o.order_delivered_customer_date, o.order_purchase_timestamp))) as delay_in_Days
from customers c
inner join orders o on o.customer_id=c.customer_id
where o.order_delivered_customer_date is not null
group by c.customer_unique_id
order by delay_in_Days desc

--f. How does customer order frequency change over time? Find the average number of orders placed per customer per year.
SELECT orders_per_customer.year, AVG(orders_per_customer.orders_placed) AS [Avg Orders Placed per Customer per Year]
FROM (
		SELECT YEAR(o.order_purchase_timestamp) AS year, COUNT(o.order_id) AS orders_placed
		FROM customers c
		JOIN orders o ON c.customer_id = o.customer_id
		GROUP BY c.customer_unique_id, YEAR(o.order_purchase_timestamp)
) AS orders_per_customer
GROUP BY orders_per_customer.year
ORDER BY orders_per_customer.year

--g. Which top 5 customers have spent the most money in year 2017
Select TOP 5 c.customer_unique_id, SUM(op.payment_value) as amountspent
from customers c
inner join orders o on o.customer_id=c.customer_id
inner join order_payment op on op.order_id=o.order_id
WHERE datepart(YEAR, o.order_purchase_timestamp) = 2017
group by c.customer_unique_id
order by amountspent desc

--h. Which customers have the highest order cancellations
SELECT c1.customer_unique_id, COUNT(c1.customer_id) AS [Orders Cancelled]
FROM customers c1
JOIN orders o1
ON o1.customer_id = c1.customer_id
WHERE o1.order_status = 'canceled'
GROUP BY c1.customer_unique_id
HAVING COUNT(c1.customer_id) = (
								SELECT TOP 1 COUNT(c2.customer_id)
								FROM customers c2
								JOIN orders o2
								ON o2.customer_id = c2.customer_id
								WHERE o2.order_status = 'canceled'
								GROUP BY c2.customer_unique_id
								ORDER BY COUNT(c2.customer_unique_id) DESC)

---------------------------------------------------------------------------
----------------------------- PRODUCT ANALYSIS ----------------------------
---------------------------------------------------------------------------

--a. What is the most profitable product category per state? Find the most profitable product category in each state based on total sales. 
select c.customer_state, (select TOP 1 p.product_category_name
						  from products p,order_items oi, orders o, order_payment op, customers c2
						  where c.customer_state=c2.customer_state and oi.product_id=p.product_id and
						  o.order_id=oi.order_id and c2.customer_id=o.customer_id and op.order_id=o.order_id
						  group by p.product_category_name
						  order by SUM(op.payment_value) desc
						) as product_category
from customers c
group by c.customer_state
order by c.customer_state

--b. What are the peak hours for order placements per product category? Find which hours of the day have the highest number
--   of order placements for each product category.
SELECT p1.product_category_name, DATEPART(HOUR, o1.order_purchase_timestamp) as hour_order_placed, COUNT(*) AS orders_placed
FROM orders o1
JOIN order_items oi1 ON o1.order_id = oi1.order_id
JOIN products p1 ON oi1.product_id = p1.product_id
GROUP BY p1.product_category_name, DATEPART(HOUR, o1.order_purchase_timestamp)
HAVING COUNT(*) = (
					SELECT TOP 1 COUNT(*)
					FROM orders o2
					JOIN order_items oi2 ON o2.order_id = oi2.order_id
					JOIN products p2 ON oi2.product_id = p2.product_id
					WHERE p1.product_category_name = p2.product_category_name
					GROUP BY p2.product_category_name, DATEPART(HOUR, o2.order_purchase_timestamp)
					ORDER BY COUNT(*) DESC
				  )

--c. Which product categories experience the most delays? Find the top 5 product categories with the highest number of delayed orders. 
Select TOP 5 p.product_category_name,COUNT(*) as delayedorders
from order_items oi
inner join products p on p.product_id=oi.product_id
inner join orders o on o.order_id=oi.order_id
where o.order_delivered_customer_date>o.order_estimated_delivery_date and o.order_delivered_customer_date is not null
group by p.product_category_name
order by delayedorders desc

--d. What is the impact of product price on sales volume? Find whether higher-priced products sell less by comparing average 
--   price vs. total sales.
SELECT p.product_id, p.product_category_name, COUNT(oi.order_item_id) AS units_sold, AVG(oi.price) AS avg_price, SUM(oi.price) AS total_sales
FROM order_items oi
JOIN products p
ON oi.product_id = p.product_id
GROUP BY p.product_id, p.product_category_name
ORDER BY total_sales DESC;

--e. Which products are most frequently bought together? Find the most frequently purchased product pairs
SELECT p1.product_category_name AS product_category_name_1, p2.product_category_name AS product_category_name_2, COUNT(*) AS frequency
FROM products p1
JOIN order_items oi1 ON p1.product_id = oi1.product_id
JOIN order_items oi2 ON oi1.order_id = oi2.order_id
JOIN products p2 ON oi2.product_id = p2.product_id
WHERE p1.product_category_name < p2.product_category_name
GROUP BY p1.product_category_name, p2.product_category_name
HAVING COUNT(*) = (
					SELECT TOP 1 COUNT(*)
					FROM products p1
					JOIN order_items oi1 ON p1.product_id = oi1.product_id
					JOIN order_items oi2 ON oi1.order_id = oi2.order_id
					JOIN products p2 ON oi2.product_id = p2.product_id
					WHERE p1.product_category_name < p2.product_category_name
					GROUP BY p1.product_category_name, p2.product_category_name
					ORDER BY COUNT(*) DESC
				  )
ORDER BY COUNT(*) DESC

--f. Calculate the total revenue per product category by summing order item prices.
SELECT p.product_category_name, SUM(oi.price) AS [Total Revenue per product category]
FROM order_items oi
JOIN products p ON oi.product_id = p.product_id
WHERE p.product_category_name IS NOT NULL
GROUP BY p.product_category_name
ORDER BY SUM(oi.price) DESC

--g. Compute the average review score for each product category
Select p.product_category_name, AVG(cast (ore.review_score as float)) as AVGscore
from products p
inner join order_items oi on oi.product_id=p.product_id
inner join orders o on o.order_id=oi.order_id
inner join order_reviews ore on ore.order_id=o.order_id
WHERE ore.review_score IS NOT NULL
group by p.product_category_name

--h. Retrieve the top 5 products based on total sales revenue
SELECT TOP 5 p.product_id, p.product_category_name, SUM(oi.price) AS [Total Sales Revenue]
FROM order_items oi
JOIN products p ON oi.product_id = p.product_id
WHERE p.product_category_name IS NOT NULL
GROUP BY p.product_id, p.product_category_name
ORDER BY SUM(oi.price) DESC

---------------------------------------------------------------------------
---------------------- SELLER AND SHIPMENT ANALYSIS -----------------------
---------------------------------------------------------------------------

--a. What is the return rate per seller? 
Select s.seller_id, (Select cast(Count(*)as float) 
					 from order_items oi, orders o
					 where oi.order_id=o.order_id and s.seller_id=oi.seller_id and o.order_status='canceled')
					 /
					 (Select Count(*)
					 from order_items oi2, orders o2
					 where oi2.order_id=o2.order_id and s.seller_id=oi2.seller_id)
					 as return_rate
from sellers s
group by s.seller_id
order by return_rate desc

--b. Which sellers sell the most expensive products on average? Find sellers whose products have the highest average price.
SELECT s.seller_id, AVG(oi.price) AS [Highest Avg Price]
FROM sellers s
JOIN order_items oi ON s.seller_id = oi.seller_id
JOIN products p ON p.product_id = oi.product_id
GROUP BY s.seller_id
HAVING AVG(oi.price) = (
						SELECT MAX(avg_price)
						FROM (
								SELECT AVG(oi1.price) AS avg_price
								FROM sellers s1
								JOIN order_items oi1 ON s1.seller_id = oi1.seller_id
								JOIN products p1 ON p1.product_id = oi1.product_id
								GROUP BY s1.seller_id
							 ) AS avg_price_table
					   )

--c. What is the profit margin per seller? Find the profit margin per seller, assuming:
SELECT oi.seller_id, SUM(oi.price - oi.freight_value) AS profit_margin
FROM order_items oi
GROUP BY oi.seller_id
ORDER BY profit_margin DESC;

--d. How do shipping costs impact order delays? Find the average shipping cost (freight_value) for delayed vs. non-delayed orders.
SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for Delayed]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date > o.order_estimated_delivery_date

SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for On-Time]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date <= o.order_estimated_delivery_date

--e. What is the number of delayed shipments in 2017 
select Count(*) as delayed_shipments
from orders o
inner join order_items oi on o.order_id=oi.order_id
where oi.shipping_limit_date < o.order_delivered_carrier_date
	  and o.order_delivered_carrier_date is not null
	  and datepart(year,o.order_delivered_carrier_date) = 2017

--f. What is the correlation between shipping cost and delivery speed? Find the average shipping cost (freight_value) for delayed vs. on-time shipments.
SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for Delayed]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date > o.order_estimated_delivery_date

SELECT AVG(oi.freight_value) AS [Avg Shipping Cost for On-Time]
FROM orders o
JOIN order_items oi
ON o.order_id =  oi.order_id
WHERE o.order_delivered_customer_date <= o.order_estimated_delivery_date

--g. Sum the total freight cost for each seller
Select s.seller_id, SUM(oi.freight_value) as total_freight_cost
from order_items oi
inner join sellers s on s.seller_id=oi.seller_id
group by s.seller_id
order by total_freight_cost desc