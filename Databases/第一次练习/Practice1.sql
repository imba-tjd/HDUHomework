--part 1
--练习一
CREATE DATABASE ClassNorthwind
ON
(
	NAME=ClassNorthwind,
	FILENAME='d:\data\ClassNorthwind_Data.mdf',
	SIZE=25,
	MAXSIZE=100,
	FILEGROWTH=10%
)
LOG ON
(
	NAME=ClassNorthwind_Log,
	FILENAME='d:\data\ClassNorthwind_Log.ldf',
	SIZE=15,
	FILEGROWTH=10%,
	MAXSIZE=40
)

EXEC sp_helpdb ClassNorthwind

--练习二

ALTER DATABASE ClassNorthwind
ADD FILE
(
	NAME=ClassNorthwind_Data2,
	FILENAME='e:\data\ClassNorthwind_Data2.ndf',
	SIZE=30
)

--练习三
EXEC sp_helpdb
EXEC sp_helpdb ClassNorthwind

--练习四
ALTER DATABASE ClassNorthwind
MODIFY FILE
(
	NAME=ClassNorthwind_Log,
	MAXSIZE=50
)

SELECT *
FROM sysfiles
DBCC SHRINKFILE(3,10)

EXEC sp_helpdb ClassNorthwind

--part 2
--练习二

CREATE TABLE test
(
	test_id    int         PRIMARY KEY NOT NULL,
	test_name  varchar(20),
	teacher_id int         NOT NULL
)

CREATE TABLE test_score
(
	student_id int NOT NULL,
	test_id    int NOT NULL,
	score      int
)

--练习三
--(1-5)
ALTER TABLE student
ALTER COLUMN
student_id int

ALTER TABLE student
ADD
phone varchar(50)

ALTER TABLE teacher
ALTER COLUMN
name varchar(30) NOT NULL

ALTER TABLE student
ADD
institute varchar(20) NOT NULL DEFAULT '计算机软件'

ALTER TABLE student
DROP DF_student_sex

--(6-11)
ALTER TABLE student
ADD DEFAULT '女' FOR sex

ALTER TABLE teacher
ADD CHECK (age BETWEEN 18 AND 60)

ALTER TABLE teacher
ADD CHECK(birthdate>workdate)

ALTER TABLE test_score
ADD PRIMARY KEY (student_id,test_id)

ALTER TABLE test_score
ADD CHECK(score BETWEEN 0 AND 100)

ALTER TABLE test
ADD FOREIGN KEY REFERENCES teacher(teacher_id)

ALTER TABLE test_score
ADD FOREIGN KEY REFERENCES student(student_id)

ALTER TABLE test_score
ADD FOREIGN KEY REFERENCES test(test_id)
