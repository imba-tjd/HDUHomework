# POSIX信号量

## 理论知识

* 在 POSIX 标准中，信号量分两种，一种是无名信号量，一种是有名信号量。无名信号量一般用于线程间同步或互斥，而有名信号量一般用于进程间同步或互斥。它们的区别和管道及命名管道的区别类似，无名信号量则直接保存在内存中，而有名信号量要求创建一个文件。

## 使用

* 头文件：fcntl.h、sys/stat.h、semaphore.h
* 函数：sem_init、sem_open、sem_close、sem_wait、sem_post、sem_getvalue、sem_close、sem_unlink
* 编译选项：-lpthread

## 参考

* <https://www.cnblogs.com/jfyl1573/p/6820372.html>
* <https://www.cnblogs.com/xiaojiang1025/p/5937746.html>
* <https://blog.csdn.net/tennysonsky/article/details/46496201>
* <https://blog.csdn.net/meetings/article/details/47254685>
