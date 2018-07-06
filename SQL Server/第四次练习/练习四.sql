--part 1
-- 1 to 5
SELECT classid, AVG(CONVERT(float,score))
FROM G_stuinfo JOIN Exam_Score ON G_stuinfo.stuid = Exam_Score.stuid
WHERE courseid = '10000005'
GROUP BY classid
ORDER BY AVG(CONVERT(float,score)) DESC

SELECT SpecialityName, AVG(CONVERT(float,score))
FROM G_SpecialityInfo JOIN G_stuinfo ON G_SpecialityInfo.Specialityid = G_stuinfo.specialityid
    JOIN Exam_Score ON G_stuinfo.stuid = Exam_Score.stuid
WHERE courseid = (
SELECT courseid
FROM G_CourseInfo
WHERE course = '程序设计基础'
)
GROUP BY SpecialityName
ORDER BY AVG(CONVERT(float,score)) DESC

SELECT specialityid, COUNT(*)
FROM G_stuinfo
WHERE specialityid IN (
SELECT specialityid
FROM G_stuinfo
WHERE stuname = '张三'
)
GROUP BY specialityid

SELECT DISTINCT i1.stuid, i1.stuname, i1.sexcode, i1.classid, i1.specialityid
FROM G_stuinfo AS i1 JOIN G_stuinfo AS i2 ON i1.stuname = i2.stuname
WHERE i1.stuid != i2.stuid
ORDER BY stuname ASC,stuid ASC

SELECT COUNT(*)
FROM Exam_Score
WHERE Exam_Score.courseid = (
SELECT courseid
    FROM G_CourseInfo
    WHERE course = '数学'
) AND score > 75
    AND stuid IN (
SELECT G_stuinfo.stuid
    FROM G_stuinfo JOIN G_SexInfo ON G_stuinfo.sexcode = G_SexInfo.sexcode
    WHERE sexname = '男'
)

-- 6 to 10
SELECT TOP 1
    score
FROM Exam_Score JOIN G_stuinfo ON Exam_Score.stuid = G_stuinfo.stuid
WHERE stuname LIKE '王%' AND courseid = (
SELECT courseid
    FROM G_CourseInfo
    WHERE course = '计算机数学'
)
ORDER BY score DESC

SELECT COUNT(*)
FROM G_stuinfo JOIN G_SexInfo ON G_stuinfo.sexcode = G_SexInfo.sexcode
WHERE (stuname LIKE '周%' OR stuname LIKE '吴%' OR stuname LIKE '郑%' OR stuname LIKE '王%'
) AND sexname = '男'

SELECT *
FROM G_stuinfo LEFT JOIN Exam_Score ON Exam_Score.stuid = G_stuinfo.stuid
WHERE score IS NULL

SELECT stuid, stuname, G_stuinfo.sexcode, classid, specialityid
FROM G_stuinfo JOIN G_SexInfo ON G_stuinfo.sexcode = G_SexInfo.sexcode
WHERE LEFT(RIGHT(rtrim(stuid),2),1)='3'
    AND sexname = '男'
    AND specialityid = (
SELECT specialityid
    FROM G_SpecialityInfo
    WHERE Specialityname = '电子商务'
)

SELECT stuid, SUM(score)
FROM Exam_Score
GROUP BY stuid
ORDER BY SUM(score) DESC

--part 2
UPDATE Exam_Score
SET score = score + 2
WHERE
score > (
SELECT AVG(score)
    FROM G_CourseInfo JOIN Exam_Score ON Exam_Score.courseid = G_CourseInfo.Courseid
    WHERE course = '计算机数学'
) AND courseid = (
SELECT DISTINCT G_CourseInfo.courseid
    FROM G_CourseInfo JOIN Exam_Score ON Exam_Score.courseid = G_CourseInfo.Courseid
    WHERE course = '计算机数学'
)

UPDATE G_stuinfo
SET specialityid = (
SELECT specialityid
FROM G_SpecialityInfo
WHERE Specialityname = '电子商务'
)
WHERE stuname = '张三'

UPDATE G_CourseInfo
SET credithour = credithour - 1
WHERE 15 > (
SELECT COUNT(courseid)
FROM Exam_Score
WHERE Exam_Score.courseid = G_CourseInfo.Courseid
GROUP BY courseid
);

--part 3
-- 1 to 5
GO
CREATE VIEW vw_CourceInfo
(
    Num,
    AVGScore
)
AS
    SELECT COUNT(*), AVG(score)
    FROM Exam_Score
GO

-- 第二题不会
--create view vw_Top1perSpecial(SNo, SName)
--as select G_stuinfo.stuid, stuname
--from G_stuinfo join Exam_Score on G_stuinfo.stuid = Exam_Score.stuid
--group by specialityid, G_stuinfo.stuname, G_stuinfo.stuid
--order by SUM(score) desc
--go

--select specialityid, G_stuinfo.stuid
--from G_stuinfo join Exam_Score on G_stuinfo.stuid = Exam_Score.stuid
--group by specialityid, G_stuinfo.stuid
--order by SUM(score) desc
--go

CREATE PROCEDURE up_GetSCinfoBySno(@SNo char(10))
AS
SELECT course, score
FROM Exam_Score JOIN G_CourseInfo ON G_CourseInfo.Courseid = Exam_Score.courseid
WHERE stuid = @SNo
GO

CREATE PROCEDURE up_GetScoreByName(@SName varchar(10),
    @CourseName varchar(20))
AS
SELECT course
FROM G_stuinfo JOIN Exam_Score ON G_stuinfo.stuid = Exam_Score.stuid
    JOIN G_CourseInfo ON G_CourseInfo.Courseid = Exam_Score.courseid
WHERE stuname = @SName AND course = @CourseName
GO

CREATE PROCEDURE up_GetInfoBySpecialID(@SpecialityID char(10))
AS
SELECT sexname, COUNT(*)
FROM G_stuinfo JOIN G_SexInfo ON G_stuinfo.sexcode = G_SexInfo.sexcode
WHERE Specialityid = @SpecialityID
GROUP BY sexname
GO

--6 to 7
CREATE PROCEDURE up_AddStudent(@SID char(10),
    @SName varchar(10),
    @Sex char(2),
    @ClassID char(10),
    @SpecialityName char(20))
AS
DECLARE @sexCode char(1) = (
SELECT sexcode
FROM G_SexInfo
WHERE @Sex = sexname
), @specialityID char(10) = (
SELECT Specialityid
FROM G_SpecialityInfo
WHERE @SpecialityName = Specialityname
)
INSERT INTO G_stuinfo
    (stuid, stuname, sexcode, classid, specialityid)
VALUES(@SID, @SName, @sexCode, @ClassID, @SpecialityID)

EXEC up_AddStudent '96001','王倩','女','211','网络'
GO

CREATE PROCEDURE up_UpdateScoreByName(@SID char(10),
    @CourseName varchar(20),
    @NewScore tinyint
)
AS
UPDATE Exam_Score
SET score = @NewScore
WHERE stuid = @SID AND
    courseid = (
SELECT courseid
    FROM G_CourseInfo
    WHERE course = @CourseName
)
