#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  // for dev_read

#define DEVICE_NAME "my_dummy_device"

static const int minor_number = 0;
static struct cdev my_dummy_cdev;
static dev_t my_dummy_dev = 0;
static int is_open = 0;
static char text[14] = "Hello, world!\n"; /* Текст, выдающийся при обращении к устройству */
static char* text_ptr = text;


//=======================================================================
static int dev_open(struct inode *inode, struct file *fp)
{
    if (is_open)
        return -EBUSY;  // device/resource is busy err
    is_open++;
    return 0;
}

static ssize_t dev_read(struct file *fp, char *buffer, size_t length, loff_t *offset)
{
	int byte_read = 0;

	if (*text_ptr == 0)
		return 0;

	while (length && *text_ptr)
	{
		put_user(*(text_ptr++), buffer++);
		length--;
		byte_read++;
	}
	return byte_read;
}

static ssize_t dev_write(struct file *fp, const char *buff, size_t len, loff_t *offset)
{
	printk(KERN_INFO "Unknown operation.\n");
	return -EINVAL;
}

static int dev_release(struct inode *inode, struct file *fp)
{
    is_open--;
    return 0;
}

static const struct file_operations my_dummy_fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};


//==================================================================================
static int __init cdevice_init_module(void)
{
    int major_number = alloc_chrdev_region(&my_dummy_dev, minor_number, 1, DEVICE_NAME);
    printk(KERN_INFO "my_dummy_device_driver: trying to register char device...\n");

    if (major_number != 0)
    {
        printk(KERN_ALERT "my_dummy_device: alloc_chrdev_region() error: %d\n", major_number);
        return major_number;
    }

    cdev_init(&my_dummy_cdev, &my_dummy_fops);
    if (cdev_add(&my_dummy_cdev, my_dummy_dev, 1) != 0)
    {
        printk(KERN_ALERT "my_dummy_device: cdev registration error. Unregistrating chardev\n");
        unregister_chrdev_region(my_dummy_dev, 1);
        return -1;
    }    

    printk(KERN_INFO "my_dummy_device_driver: registered. Major:Minor = %d:%d\n", MAJOR(my_dummy_dev), MINOR(my_dummy_dev));
    return 0;
}

static void __exit cdevice_exit_module(void)
{
    printk(KERN_INFO "my_dummy_device_driver: trying to unregistrate char device...\n");
    cdev_del(&my_dummy_cdev);
    unregister_chrdev_region(my_dummy_dev, 1);
    printk(KERN_INFO "my_dummy_device_driver: unregistration succeeded\n");

}

module_init(cdevice_init_module);
module_exit(cdevice_exit_module);