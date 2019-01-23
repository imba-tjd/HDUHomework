obj-m:=e2.o # 生成的模块名为e2.ko
#e2-objs:=e2.o # 如果有多个源代码，在这里写
KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules # -C指定内核源码目录；M指定模块源码目录
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
