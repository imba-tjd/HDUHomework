--（2）	创建视图vw_Top1perSpecial，查看每个专业总分排名第一的同学学号、姓名。
create view vw_Top1perSpecial
as
select [Specialityname],s.stuid,stuname
from [dbo].[G_stuinfo] s join [dbo].[G_SpecialityInfo] sp on s.specialityid = sp.Specialityid
join
(select t2.specialityid,stuid
from
(select specialityid,s.stuid,sum(score) as sumScore from [dbo].[G_stuinfo] s join [dbo].[Exam_Score] ex
on s.stuid = ex.stuid
group by specialityid,s.stuid) t2 join
(select specialityid,max(sumScore) as top1Score
from (
select specialityid,s.stuid,sum(score) as sumScore from [dbo].[G_stuinfo] s join [dbo].[Exam_Score] ex
on s.stuid = ex.stuid
group by specialityid,s.stuid) as t1
group by specialityid) as t3 on t2.specialityid = t3.specialityid
where t2.sumScore=t3.top1Score) as t4
on s.stuid=t4.stuid