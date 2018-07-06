CREATE DATABASE mydb2

--练习一
CREATE TABLE student
(
	id         int          NOT NULL IDENTITY(1,1),
	student_id char(8)      PRIMARY KEY,
	name       varchar(20)  NOT NULL,
	sex        char(2)      NOT NULL DEFAULT '男',
	age        int,
	institute  nvarchar(10) NOT NULL DEFAULT '计算机软件',
	phone      char(50),
	email      char(50)
)

-- 1
INSERT INTO student
	(student_id,name,sex)
VALUES
	(15112003, '张三', '男')
INSERT INTO student
	(student_id,name,sex,age)
VALUES
	(15112004, '李四', '女', 21)
INSERT INTO student
	(student_id,name,sex,age,institute)
VALUES
	(15112005, '王刚', '男', 20, '会计')
INSERT INTO student
	(student_id,name,sex,age,institute)
VALUES
	(15112006, '赵梅', '女', 20, '计算机软件')
INSERT INTO student
	(student_id,name,sex,institute)
VALUES
	(15112007, '李敏勇', '男', '计算机科学')

-- 2
UPDATE student
SET institute = '外语'
WHERE (student_id = 15112005)

UPDATE student
SET age = age + 5
WHERE (name = '王刚')

-- 3
DELETE
FROM student
WHERE(student_id = 15112003)

DELETE
FROM student
WHERE(institute = '计算机软件')

-- 4
ALTER TABLE student
ADD IDCard char(18) DEFAULT 0 NOT NULL

ALTER TABLE student WITH NOCHECK
ADD UNIQUE (IDCard)

ALTER TABLE student
ADD CHECK(age BETWEEN 16 AND 65)

ALTER TABLE student
ADD CHECK((phone != NULL) AND (email != NULL))

--练习二
--1 to 5
SELECT *
FROM Customers

SELECT LastName +' '+ FirstName AS '姓名', HireDate AS '雇用时间', Address AS '地址', PostalCode AS '邮编'
FROM Employees

SELECT SupplierID
FROM Products

SELECT DISTINCT SupplierID
FROM Products

SELECT SupplierID, CategoryID
FROM Products

--6 to 9
SELECT DISTINCT SupplierID, CategoryID
FROM Products

SELECT OrderID, CustomerID, EmployeeID, OrderDate, RequiredDate
FROM Orders
ORDER BY OrderDate ASC

SELECT ProductName, SupplierID, UnitPrice, UnitsInStock
FROM Products
ORDER BY UnitPrice DESC,UnitsInStock ASC

SELECT TOP 10 PERCENT
	ProductName, SupplierID, UnitPrice, UnitsInStock
FROM Products
ORDER BY UnitPrice DESC,UnitsInStock ASC

--练习三
--(1)
SELECT sno, sname
FROM student

SELECT sname, sage
FROM student

SELECT sname, sage, sdept AS '系名'
FROM student

SELECT DISTINCT sno
FROM sc

--(2)
SELECT sname
FROM student
WHERE sdept = 'CS'

SELECT sname, sage
FROM student
WHERE sage < 20

SELECT sname, sdept, sage
FROM student
WHERE sage >= 20 AND sage <= 23

SELECT sname, ssex
FROM student
WHERE sdept != 'IS' AND sdept != 'CS'

SELECT sname, sno, ssex
FROM student
WHERE sname LIKE '刘%'

SELECT sname, sno
FROM student
WHERE sname LIKE '_敏%'

SELECT *
FROM student
ORDER BY sdept ASC, sage DESC

--(3)
SELECT COUNT(*)
FROM student

SELECT COUNT(*)
FROM (
SELECT DISTINCT sno
	FROM sc
) AS num

--select distinct COUNT(sno)
--from sc

SELECT AVG(grade)
FROM sc
WHERE cno = 2

SELECT TOP 1
	grade
FROM sc
WHERE cno = 3

SELECT Cno, COUNT(*)
FROM sc
GROUP BY Cno

SELECT sno, COUNT(*), MAX(grade)
FROM sc
GROUP BY sno

--(4)
SELECT sno, AVG(grade)
FROM sc
GROUP BY sno
HAVING COUNT(sno)>=2
ORDER BY AVG(grade) DESC

SELECT credit, COUNT(*)
FROM course
GROUP BY credit

SELECT ssex, COUNT(*)
FROM student
WHERE sdept = 'IS'
GROUP BY ssex

SELECT TOP 1
	sdept, COUNT(*)
FROM student
GROUP BY sdept
ORDER BY COUNT(*) DESC

SELECT sno
FROM sc JOIN course ON sc.cno = course.cno
WHERE cname = '数据库'

--select sname, AVG(grade)
--from student join sc as new on student.sno = sc.sno
--group by new.sno
--having MIN(grade) >= 85

SELECT sname, AVG(grade)
FROM student JOIN sc ON student.sno = sc.sno
GROUP BY sname
HAVING MIN(grade) >= 85
