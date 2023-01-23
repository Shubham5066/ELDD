#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/err.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/timer.h>
#include<linux/delay.h>
#define TIMEOUT 5000
#define mem_size 1024
#define WA_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('a','b',int32_t*)

int32_t val=0;

dev_t dev=0;
static struct timer_list chr_timer;
static struct cdev dev_cdev;
static struct class *device_class;
int8_t *kernel_buff;
unsigned int i=0;
static int __init driver3_init(void);
static void __exit driver3_exit(void);
static int file_open(struct inode *inode,struct file *file);
static int file_release(struct inode *inode,struct file *file);
static ssize_t file_read(struct file *filp,char __user *buf,size_t len,loff_t *off);
static ssize_t file_write(struct file *filp,const char __user *buf,size_t len,loff_t *off);
static long chr_ioctl(struct file *file,unsigned int cmd,unsigned long arg);
static struct file_operations fops=
{
    .owner      =THIS_MODULE,
    .read       =file_read,
    .write      =file_write,
    .open       =file_open,
    .release      =file_release,
    .unlocked_ioctl   =chr_ioctl,
};
void timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO"In timer call back function[%d]\n",i++);;

    mod_timer(&chr_timer,msecs_to_jiffies(TIMEOUT));
}
static int file_open(struct inode *inode,struct file *file)
{
    printk(KERN_INFO"\nfile not opening");
    return 0;
}
static int file_release(struct inode *inode,struct file *file)
{
     printk(KERN_INFO"\nfile not closing");
    return 0;
}
static ssize_t file_read(struct file *filp,char __user *buf,size_t len,loff_t *off)
{
    if(copy_to_user(buf,kernel_buff,mem_size))
    {
         printk(KERN_INFO"\nfile not reading");
    }
    return mem_size;
}
static ssize_t file_write(struct file *filp,const char __user *buf,size_t len,loff_t *off)
{
     if(copy_from_user(kernel_buff,buf,len))
    {
         printk(KERN_INFO"\nfile not writeing");
    }
    return len;

}
 static long chr_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
    {
        switch(cmd)
        {
            case WA_DATA:
                        copy_from_user(&val,(int32_t*)arg,sizeof(val));
                        printk(KERN_INFO"\nval=%d",val);
                        break;
                        
                        
            case RD_DATA:
                        copy_to_user((int32_t*)arg,&val,sizeof(val));
                        break;
        }
        return 0;
    }

static int __init driver3_init(void)
{
    if((alloc_chrdev_region(&dev,0,1,"driver4_dev"))<0)
    {
        printk(KERN_INFO"\ncannot allocate memory for major");
        return -1;
    }
    printk(KERN_INFO"\n MAJOR (%d) and MINOR (%d)",MAJOR(dev),MINOR(dev));
    cdev_init(&dev_cdev,&fops);
    if((cdev_add(&dev_cdev,dev,1))<0)
    {
        printk(KERN_INFO"\nfile is not adding in system");
        goto r_class;
    }
    if((device_class=class_create(THIS_MODULE,"driver4_class"))==0)
    {
        printk(KERN_INFO"\nCannot creating Device class");
        goto r_class;
    }
    if((device_create(device_class,NULL,dev,NULL,"driver4_device"))==0)
    {
        printk(KERN_INFO"\ncannot adding DEVICE IN THE SYSTEM");
        goto r_device;
    }
    if((kernel_buff=kmalloc(mem_size,GFP_KERNEL))==0)
    {
        printk(KERN_INFO"\ncannot creating memeory");
        goto r_device;
    }

   timer_setup(&chr_timer,timer_callback,0);
    mod_timer(&chr_timer,jiffies + msecs_to_jiffies(TIMEOUT));
    strcpy(kernel_buff,"Hello world");
    printk("Device driver insert properly...\n");
    return 0;
    printk(KERN_INFO"\nModule successfully inserted");


    r_device:
            class_destroy(device_class);
    r_class:
            unregister_chrdev_region(dev,1);
            return -1;
}

static void __exit driver3_exit(void)
{
    del_timer(&chr_timer);
    device_destroy(device_class,dev);
    class_destroy(device_class);
    cdev_del(&dev_cdev);
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO"\nMODULE Successfully removed");
}
module_init(driver3_init);
module_exit(driver3_exit);

MODULE_AUTHOR("SHUBHAM");
MODULE_LICENSE("GPL");