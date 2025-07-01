#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

MODULE_AUTHOR("Fei Xie <donovanxie@gmail.com>");
MODULE_DESCRIPTION("Tiny buffered char device");
MODULE_LICENSE("GPL");

#define DEVNAME "demo_char"
#define BUF_SIZE 1024

static dev_t char_dev;
static struct class  *char_class;
static struct cdev  char_cdev;
static char           buf[BUF_SIZE]; //fixed size buffer
static size_t         data_len;






static ssize_t dev_read (struct file *fd, char __user *user_space_buffer, size_t c, loff_t *offset){

    if (*offset >= data_len)
        return 0; //EOF

    if(c > data_len - *offset)
        c = data_len - *offset; // not very necessary for here but keep it for extra safety

    if (copy_to_user(user_space_buffer, buf + *offset, c)) // pass date from kernel sapce to user space, very handy API
        return -EFAULT;


    *offset += c; // must increment, otherwise the 'cat' will keep printing non-stop
    return c;//return value required by 'cat' command
}

static ssize_t dev_write (struct file *fd, const char __user *user_space_buffer, size_t c, loff_t *offset){

    if(c > BUF_SIZE)
        c = BUF_SIZE;


    if (copy_from_user(buf, user_space_buffer, c))
        return -EFAULT;

    data_len = c;

    *offset = c;



    return c;
}

static const struct file_operations fops = {
        .owner  = THIS_MODULE,
        .read   = dev_read,
        .write  = dev_write,
};


static int __init char_driver_init(void){
    int ret;

    ret = alloc_chrdev_region(&char_dev, 0, 1, DEVNAME); // ask for a free major minor number

    if(ret) return ret; // return if fail

    cdev_init(&char_cdev, &fops);

    char_cdev.owner = THIS_MODULE;
    
    ret = cdev_add(&char_cdev, char_dev, 1);

    if (ret)
        goto out_of_reg;

    char_class = class_create("char_class"); // /sys/class/char_class

    if (IS_ERR(char_class)){
        ret = PTR_ERR(char_class);
        goto out_of_cdev;
    }



    if(IS_ERR(device_create(char_class, NULL, char_dev, NULL, "char_dev_driver"))){

        ret = PTR_ERR(char_class);
        goto out_of_class;
    }


    pr_info("char_dev_driver loaded major: %d minor: %d\n", MAJOR(char_dev), MINOR(char_dev));
    return 0;


out_of_class:
    class_destroy(char_class);

out_of_cdev:
    cdev_del(&char_cdev);


out_of_reg:
    unregister_chrdev_region(char_dev, 1);
    return ret;
}

static void __exit char_device_exit(void){

    device_destroy(char_class, char_dev);
    class_destroy(char_class);
    cdev_del(&char_cdev);
    unregister_chrdev_region(char_dev, 1);
    pr_info("char_device_driver: unloaded\n");


}


module_init(char_driver_init);
module_exit(char_device_exit);