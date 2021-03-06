#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#define PRODUCT_NUMS 10

static struct semaphore sem_producer;
static struct semaphore sem_consumer;
static char product[12];	//参数
static atomic_t num;
static int producer(void *product);
static int consumer(void *product);
static int id = 1;
static int consume_num = 1;

static int producer(void *p){
	char *product = p;
	int i;

	atomic_inc(&num);					//原子操作，从1增加到×num
	printk("producer [%d] start...\n", current->pid);	//current->pid获取当前进程pid
	for(i = 0; i < PRODUCT_NUMS; ++i){
		down(&sem_producer);				//获取信号量
		snprintf(product, 12, "2010-01-%d", id++);	//将可变个参数按照  参数3的格式，格式化成字符串，然后将其复制到参数1中
		printk("producer [%d] produce %s\n", current->pid, product);
		up(&sem_consumer);				//释放信号量
	}
	printk("producer [%d] exit...\n", current->pid);
	return 0;
}

static int consumer(void *p){
	char *product = p;

	printk("consumer [%d] start...\n", current->pid);
	for(;;){
		msleep(100);		//休眠至少100ms
	//	down(&sem_consumer);
		down_interruptible(&sem_consumer);
		if(consume_num >= PRODUCT_NUMS * atomic_read(&num))
			break;
		printk("consumer [%d] consume %s\n", current->pid, product);
		consume_num++;
		memset(product, '\0', 12);
		up(&sem_producer);
	}
	printk("producer [%d] exit...\n", current->pid);
	return 0;
}

static int proc_init(void){
	printk(KERN_INFO"show producer and consumer\n");
//	sema_init(&sem_producer, 1);
//	sema_init(&sem_consumer, 0);
	sema_init(&sem_producer, 1);
	sema_init(&sem_consumer, 0);
	atomic_set(&num, 0);		//设置num为0
	kthread_run(producer, product, "mythread");
	kthread_run(consumer, product, "mythread");
	return 0;
}

static void proc_exit(void){
	printk(KERN_INFO"exit producer and consumer\n");
}

module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
