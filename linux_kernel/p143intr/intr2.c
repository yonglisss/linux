#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

static int irq;
static char * interface;
static int count = 0;

module_param(interface,charp,0644);
module_param(irq,int,0644);

static irqreturn_t intr_handler(int irq,void * dev_id)
{
	pid_t pid;
	struct task_struct *p;
	static long interval = 0;

	if(count==0){
		interval=jiffies;
	}
	//count the interval between two irqs
	interval=jiffies-interval;
	printk("The interval between two interrupts is %ld\n",interval);
	interval=jiffies;
	//printk("Interrupt on %s —–%d /n",dev->name,dev->irq);
	count++;
	
	//pid = sys_getpid();
	asm(
		"movl $0x20,%%eax\n\t"
		"int $0x80\n\t"
		:"=a"(pid)
	);
	p = pid_task(find_vpid(pid),PIDTYPE_PID);
	printk("进程%d的状态:state=%ld   prio=%d   policy=%d\n",pid,p->state,p->prio,p->policy);

	return IRQ_NONE;
}

static int __init intr_init(void)
{
	printk ("My module worked!/n");
	//regist irq
	//if (request_irq(irq,&myinterrupt,SA_SHIRQ,interface,&irq)) { //early than 2.6.23
	if (request_irq(irq,&intr_handler,IRQF_SHARED,interface,&irq)) { //later than 2.6.23
		printk(KERN_ERR "Fails to register IRQ %d\n", irq);
		return -EIO;
	}
	printk("%s Request on IRQ %d succeeded\n",interface,irq);
	return 0;
}

static void __exit intr_exit(void)
{
	printk ("The %d interrupts happened on irq %d\n",count,irq);
	free_irq(irq, &irq); //release irq
	printk("Freeing IRQ %d\n", irq);
	return;
}

module_init(intr_init);
module_exit(intr_exit);
MODULE_LICENSE("GPL");
