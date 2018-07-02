# 实验四：Linux设备驱动程序开发

## 可能有用的代码

* <https://blog.csdn.net/creazyapple/article/details/7290680>：该作者貌似是原创，反而GitHub上一堆抄他不标明出处的
* <https://github.com/XzAmrzs/University/tree/master/os/DeviceDriver>：是上一项代码上的改进版
* <https://www.cnblogs.com/chen-farsight/p/6155518.html>
* <https://github.com/wuzf/Driver/tree/master/chardev>，他的makefile有问题，不过代码注释可以看看
* <https://github.com/Codle/Driver-Programming-Notes/tree/master/labs2>

## 问题

### compound_literal

```c
struct file_operations pStruct =
{ open:my_open, release:my_release, read:my_read, write:my_write, };
```

这种初始化方式真的没问题吗？compound_literal并不是这样的语法吧？这是bit_field的语法。

### ioctl

现在的Linux的file_operations已经没有ioctl成员了，而是unlocked_ioctl。而且两者签名还不同，前者多了`struct inode *inode`参数。因为是使用别人的代码，直接注释掉这个函数指针就好
