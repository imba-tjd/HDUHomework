#include <linux/init.h> // 包含模块初始化和清理函数的定义
#include <linux/module.h> // 加载模块需要的函数和符号
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h> // 在加载时允许用户传递参数
#include <linux/init_task.h>

static pid_t pid=1;
module_param(pid,int,0644); // 带参数的模块

static int hello_init(void)
{
    struct task_struct *p;
    struct list_head *pp;
    struct task_struct *psibling;

    // 当前进程的 PID
    p = pid_task(find_vpid(pid), PIDTYPE_PID);
    printk("me: %d %s\n", p->pid, p->comm);

    // 兄弟进程
    list_for_each(pp, &p->sibling)
    {
        psibling = list_entry(pp, struct task_struct, sibling);
        printk("sibling %d %s \n", psibling->pid, psibling->comm);
    }
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT"goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
                
MODULE_LICENSE("GPL"); // 模块许可声明
MODULE_AUTHOR("imba-tjd");
