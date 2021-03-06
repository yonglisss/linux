#include<linux/init.h>
#include<linux/module.h>
#include<linux/semaphore.h>
#include<linux/sched.h>
#include<asm/atomic.h>
#include<linux/delay.h>
#define PRODUCT_NUMS 10

static struct semaphore sem_producer;
static struct semaphore sem_consumer;
static char product[12];
static atomic_t num;
static int producer(void *product);
static int consumer(void *product);
static int id = 1;
static int consume_num = 1;

static int producer(void *p) {
	char *product = (char *)p;
	int i;
	
	atomic_inc(&num);
	printk("producer[%d] start...\n",current->pid);
	for(i=0;i<PRODUCT_NUMS;i++) {
		down(&sem_producer);
		snprintf(product,12,"2010-01-%d",id++);
		printk("producer[%d] produce %s\n",current->pid,product);
		up(&sem_consumer);
	}
	printk("producer[%d] exit...\n",current->pid);
	return 0;
}

static int consumer(void *p) {
	char *product=(char *)p;
	
	printk("consumer[%d] start...\n",current->pid);
	for(;;){
		msleep(100);		
		down_interruptible(&sem_consumer);
		if(consume_num >= PRODUCT_NUMS * atomic_read(&num))
			break;
		printk("consumer[%d] consume %s\n",current->pid,product);
		consume_num++;
		memset(product,'\0',12);
		up(&sem_producer);
	}
	printk("consumer[%d] exit...\n",current->pid);
	return 0;
}

static int procon_init(void){
	printk(KERN_INFO"show producer and consumer\n");
	init_MUTEX(&sem_producer);
	init_MUTEX_LOCKED(&sem_consumer);
	atomic_set(&num,0);
	kernel_thread(producer,product,CLONE_KERNEL);
	kernel_thread(consumer,product,CLONE_KERNEL);
	return 0;
}

static void procon_exit(void){
	printk(KERN_INFO"exit producer and consumer\n");
}
module_init(procon_init);
module_exit(procon_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("producer and consumer Module");
MODULE_ALIAS("a simplest moudle");
