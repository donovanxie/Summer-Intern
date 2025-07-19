#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>     
#include <linux/vmalloc.h> 

#define DEV_NAME "simple_mem"
#define MEM_SIZE (1 * 1024 * 1024)  // 1MB

static void *kmalloc_ptr = NULL;
static void *vmalloc_ptr = NULL;

static int __init simple_mem_init(void)
{
    pr_info("%s: init\n", DEV_NAME);
    // kmalloc 1MB
    kmalloc_ptr = kmalloc(MEM_SIZE, GFP_KERNEL);
    if (!kmalloc_ptr) {
        pr_err("kmalloc failed!\n");
        return -ENOMEM;
    }
    pr_info("kmalloc addr: %px\n", kmalloc_ptr);

    // vmalloc 1MB
    vmalloc_ptr = vmalloc(MEM_SIZE);
    if (!vmalloc_ptr) {
        pr_err("vmalloc failed!\n");
        kfree(kmalloc_ptr);
        return -ENOMEM;
    }
    pr_info("vmalloc addr: %px\n", vmalloc_ptr);

    // Test read/write first and last byte
    ((char *)kmalloc_ptr)[0] = 'K';
    ((char *)kmalloc_ptr)[MEM_SIZE - 1] = 'K';
    pr_info("kmalloc first: %c, last: %c\n",
            ((char *)kmalloc_ptr)[0],
            ((char *)kmalloc_ptr)[MEM_SIZE - 1]);

    ((char *)vmalloc_ptr)[0] = 'V';
    ((char *)vmalloc_ptr)[MEM_SIZE - 1] = 'V';
    pr_info("vmalloc first: %c, last: %c\n",
            ((char *)vmalloc_ptr)[0],
            ((char *)vmalloc_ptr)[MEM_SIZE - 1]);

    return 0;
}

static void __exit simple_mem_exit(void)
{
    pr_info("%s: exit\n", DEV_NAME);

    if (kmalloc_ptr) {
        kfree(kmalloc_ptr);
        pr_info("freed kmalloc memory\n");
    }
    if (vmalloc_ptr) {
        vfree(vmalloc_ptr);
        pr_info("freed vmalloc memory\n");
    }
}

module_init(simple_mem_init);
module_exit(simple_mem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fei Xie donovanxie@gmail.com");
MODULE_DESCRIPTION("Simple driver to compare kmalloc and vmalloc");
