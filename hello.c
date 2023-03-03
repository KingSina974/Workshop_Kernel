#include "hello.h"

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("You");

module_exit(my_exit);
module_init(my_init);
static int n = 0;
static int open = 0;

module_param(n, int, S_IRUSR | S_IWUSR);

static int my_dev_open(struct inode *inode, struct file *file)
{
  if (open == 0) {
    printk("Device is not close\n");
    open = 1;
  }
  if (open != 0) {
    printk("Device already open\n");
  }
  return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
  if (open == 1) {
    printk("Device is not close\n");
    open = 0;
  }
  if (open != 1) {
    printk("Device is close\n");
  }
  return 0;
}

static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off)
{
  return 0;
}

static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
  return 0;
}

static struct file_operations fops = {
  .read = my_dev_read,
  .write = my_dev_write,
  .open = my_dev_open,
  .release = my_dev_close
};

static int __init my_init(void)
{
  int i = 0;
  int k = register_chrdev(0, "bob", &fops);
  printk("%d\n", k);
  for (i = 0; i < n; i++)
    printk("Hello Kernel\n");
  return 0;
}
static void __exit my_exit(void)
{
  int i = 0;
  for (i = 0; i < n; i++)
    printk("Good bye Kernel\n");
  return;
}

