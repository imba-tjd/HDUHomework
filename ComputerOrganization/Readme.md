# 计算机组成原理

* [PPT.zip](./PPT.zip) is a duplicate of <https://github.com/AcceptedDoge/HDU-Computer-Organization>
* [计组知识笔记](./计组知识笔记.md)是我**个人**做的笔记
* 考试说是只有两道题，但其实又多又难

## Xilinx ISE

* 安装后大概20GB多一点。含有大量的小文件所以个人建议装到VHDX里减少碎片
* 对中文的支持极差，代码我都是用VSC纯文本编辑好再copy过去的
* 官网上有支持win10的版本，但下载需要先注册；非win10专版需要修改某些文件后才能使用：
    > http://blog.csdn.net/u010725476/article/details/51878410
    > 1. Open the following directory: ...(安装目录):\Xilinx\14.7\ISE_DS\ISE\lib\nt64
    > 2. Find and rename libPortability.dll to libPortability.dll.orig
    > 3. Make a copy of libPortabilityNOSH.dll (copy and paste it to the same directory) and rename it libPortability.dll
    > 4. Copy libPortabilityNOSH.dll again, but this time navigate to C:\Xilinx\14.7\ISE_DS\common\lib\nt64 and paste it there
    > 5. In C:\Xilinx\14.7\ISE_DS\common\lib\nt64 Find and rename libPortability.dll to libPortability.dll.orig
    > 6. Rename libPortabilityNOSH.dll to libPortability.dll

## 实验

见[实验](./实验)
