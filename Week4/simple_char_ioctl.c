#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>         

MODULE_AUTHOR("Fei Xie <donovanxie@gmail.com>");
MODULE_DESCRIPTION("Buffered char device with resizable buffer");
MODULE_LICENSE("GPL");

#define DEVNAME        "demo_char"
#define INIT_BUFSIZE   1024          /* initial size, can grow later */
#define MAX_BUFSIZE    (1 << 20)     /* 1 MiB hard ceiling           */

#define DEMO_IOC_MAGIC     'd'
#define DEMO_IOC_SET_BUFSZ _IOW(DEMO_IOC_MAGIC, 1, size_t) // macro for ioctl called here
#define DEMO_IOC_GET_BUFSZ _IOR(DEMO_IOC_MAGIC, 2, size_t)

static dev_t           char_dev;
static struct class   *char_class;
static struct cdev     char_cdev;

static char   *buf;                 // buffer able to be resized
static size_t  buf_size  = INIT_BUFSIZE; // just set a initial value here
static size_t  data_len;             // same old data length

                                                             
static ssize_t dev_read(struct file *f, char __user *ubuf,
                        size_t count, loff_t *ppos)
{
        if (*ppos >= data_len)
                return 0;                 // EOF

        if (count > data_len - *ppos)          // extra safety
                count = data_len - *ppos;

        if (copy_to_user(ubuf, buf + *ppos, count))
                return -EFAULT;

        *ppos += count; // update ppos value so that cat will not printing non stop
        return count;
}


static ssize_t dev_write(struct file *f, const char __user *ubuf,
                         size_t count, loff_t *ppos)
{
        if (count > buf_size)                   // truncate to fit 
                count = buf_size;

        if (copy_from_user(buf, ubuf, count))
                return -EFAULT;

        data_len = count; // set the data length based on user command
        *ppos    = count;
        return count;
}


static long dev_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
        size_t new_sz;

        switch (cmd) {
        case DEMO_IOC_SET_BUFSZ:
                if (copy_from_user(&new_sz, (void __user *)arg, sizeof(new_sz))) // update the user desired buffer size
                        return -EFAULT;
                if (!new_sz || new_sz > MAX_BUFSIZE)
                        return -EINVAL;

                /* allocate new buffer, keep old data up to new size    */
                {
                        char *new_buf = kmalloc(new_sz, GFP_KERNEL); // resize the buffer
                        if (!new_buf) // error check
                                return -ENOMEM;

                        memcpy(new_buf, buf, min(data_len, new_sz)); // move everything from old buffer to the new buffer
                        kfree(buf);  // destory the old buf
                        buf       = new_buf; // update the old buf with the new buf and make it ready  to use for next cycle
                        buf_size  = new_sz; // update the old buf size
                        data_len  = min(data_len, new_sz); // update the data length
                }
                pr_info("demo_char: buffer resized to %zu bytes\n", buf_size);
                return 0;

        case DEMO_IOC_GET_BUFSZ:
                if (copy_to_user((void __user *)arg, &buf_size, sizeof(buf_size)))
                        return -EFAULT;
                return 0;

        default:
                return -ENOTTY;
        }
}

static const struct file_operations fops = {
        .owner          = THIS_MODULE,
        .read           = dev_read,
        .write          = dev_write,
        .unlocked_ioctl = dev_ioctl,
};

/* ------------------------------------------------------------------ */
/*  module init / exit                                                */
static int __init char_driver_init(void)
{
        int ret;

        /* 1. device number */
        ret = alloc_chrdev_region(&char_dev, 0, 1, DEVNAME);
        if (ret)
                return ret;

        /* 2. allocate initial buffer */
        buf = kmalloc(buf_size, GFP_KERNEL);
        if (!buf) {
                ret = -ENOMEM;
                goto err_reg;
        }

        /* 3. cdev */
        cdev_init(&char_cdev, &fops);
        char_cdev.owner = THIS_MODULE;
        ret = cdev_add(&char_cdev, char_dev, 1);
        if (ret)
                goto err_buf;

        /* 4. sysfs class + /dev node */

        char_class = class_create("char_class");

        if (IS_ERR(char_class)) {
                ret = PTR_ERR(char_class);
                goto err_cdev;
        }

        if (IS_ERR(device_create(char_class, NULL, char_dev, NULL, DEVNAME))) {
                ret = PTR_ERR(char_class);
                goto err_class;
        }

        pr_info("demo_char: loaded  major=%d minor=%d, buf=%zu\n",
                MAJOR(char_dev), MINOR(char_dev), buf_size);
        return 0;

err_class:
        class_destroy(char_class);
err_cdev:
        cdev_del(&char_cdev);
err_buf:
        kfree(buf);
err_reg:
        unregister_chrdev_region(char_dev, 1);
        return ret;
}

static void __exit char_driver_exit(void)
{
        device_destroy(char_class, char_dev);
        class_destroy(char_class);
        cdev_del(&char_cdev);
        kfree(buf);
        unregister_chrdev_region(char_dev, 1);
        pr_info("demo_char: unloaded\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);
