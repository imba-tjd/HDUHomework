--1 to 5
ALTER TABLE sc
ADD
scid int NOT NULL IDENTITY(1,1)

ALTER TABLE sc
DROP CONSTRAINT pk_sc

ALTER TABLE sc
ADD PRIMARY KEY(scid)

ALTER TABLE sc
ADD
testtime date

UPDATE sc
SET testtime='2007-4-10'

--6 to 10
INSERT INTO sc
    (sno,cno,grade,testtime)
VALUES(95003, 1, 95, '2007-4-22')
INSERT INTO sc
    (sno,cno,grade,testtime)
VALUES(95003, 2, 85, '2007-4-22')
INSERT INTO sc
    (sno,cno,grade,testtime)
VALUES(95003, 3, 83, '2007-4-22')
INSERT INTO sc
    (sno,cno,grade,testtime)
VALUES(95002, 1, 94, '2007-4-22')

SELECT cno, grade
FROM sc JOIN student ON sc.sno = student.sno
WHERE sname = '李敏勇' AND grade > 80

--*重要*
SELECT sname, AVG(grade)
FROM (
SELECT student.sno, sname, grade
    FROM sc INNER JOIN student ON sc.sno = student.sno
) AS new
GROUP BY new.sno, sname
--或
SELECT sname, AVG(grade)
FROM sc INNER JOIN student ON sc.sno = student.sno
GROUP BY sc.sno, sname

SELECT sname
FROM student JOIN sc ON student.sno = sc.sno
    JOIN course ON sc.cno = course.cno
WHERE cname = '信息系统'

SELECT sname
FROM student JOIN sc ON student.sno = sc.sno
GROUP BY sc.sno,sname
HAVING MAX(grade) > 90

--11 to 15
SELECT sname
FROM student JOIN sc ON student.sno = sc.sno
GROUP BY sc.sno, sname
HAVING MIN(grade) > 85

SELECT sname, cno, testtime, grade
FROM student LEFT JOIN sc ON student.sno = sc.sno

SELECT cname, sno, testtime, grade
FROM course LEFT JOIN sc ON course.cno = sc.cno

SELECT cname, COUNT(grade)
FROM course LEFT JOIN sc ON course.cno = sc.cno
GROUP BY cname

SELECT sname, cname, testtime, grade
FROM student JOIN sc ON student.sno = sc.sno
    JOIN course ON sc.cno = course.cno

--16 to 20
SELECT s1.sname, s1.sdept, s2.sname
FROM student AS s1, student AS s2
WHERE s1.sno != s2.sno AND s1.sdept = s2.sdept

SELECT c1.cname, c1.credit, c2.cname
FROM course AS c1, course AS c2
WHERE c1.credit = c2.credit AND c1.cno != c2.cno

SELECT sname
FROM(
SELECT sno, COUNT(*) AS num
    FROM sc
    GROUP BY sno
) AS new
    JOIN student ON student.sno = new.sno
WHERE num > 3

SELECT sname
FROM(
SELECT sno, AVG(grade) AS avgg
    FROM sc
    GROUP BY sno
) AS new
    JOIN student ON student.sno = new.sno
WHERE avgg > 85

SELECT sname
FROM(
SELECT sno, testtime AS date
    FROM sc
    GROUP BY sno,testtime
) AS new
    JOIN student ON student.sno = new.sno
WHERE date = '2007-4-22'

--21 to 26
SELECT COUNT(*)
FROM student
WHERE sdept = (
SELECT sdept
FROM student
WHERE sname = '李敏勇'
)

SELECT AVG(grade)
FROM sc
GROUP BY sno
HAVING MIN(grade) < 60

SELECT sdept, COUNT(*)
FROM (
SELECT sdept
    FROM student JOIN sc ON student.sno = sc.sno
    GROUP BY sc.sno,sdept
    HAVING COUNT(*) >= 3
) AS new
GROUP BY sdept

SELECT cname, avgGrade
FROM (
SELECT cname, AVG(grade) AS avgGrade, RANK() OVER (ORDER BY COUNT(*) DESC) AS rank
    FROM sc JOIN course ON sc.cno = course.cno
    GROUP BY sc.cno,cname
) AS new

UPDATE sc
SET grade = grade + 5
WHERE sc.cno = (
SELECT cno
    FROM course
    WHERE cname = '数据库'
) AND sc.sno IN (
SELECT sno
    FROM sc
    GROUP BY sno
    HAVING AVG(grade) > 85
)

--26 to 27
UPDATE course
SET cpno = (
SELECT cpno
FROM course
WHERE cname = '信息系统'
)
WHERE cname = '数据结构'

SELECT sc.sno, cno, grade
FROM sc, (SELECT sno, max(grade) AS mgrade
    FROM sc
    GROUP BY sno ) AS new
WHERE new.sno = sc.sno AND new.mgrade = sc.grade
