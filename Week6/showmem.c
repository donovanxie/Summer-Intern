// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>        /* high_memory, PAGE_OFFSET */
#include <linux/vmalloc.h>   /* VMALLOC_* 宏 */

static int __init showmem_init(void)
{
    pr_info("=== showmem_init ===\n");
    pr_info("PAGE_OFFSET   = %px\n", (void *)PAGE_OFFSET);

    /* 高端映射上界 */
    pr_info("high_memory   = %px\n", high_memory);

#ifdef VMALLOC_START
    pr_info("VMALLOC_START = %px\n", (void *)VMALLOC_START);
    pr_info("VMALLOC_END   = %px\n", (void *)VMALLOC_END);
#else
    pr_info("此架构未定义 VMALLOC_START/END 宏\n");
#endif
    pr_info("====================\n");
    return 0;
}

static void __exit showmem_exit(void)
{
    pr_info("showmem: exit\n");
}

module_init(showmem_init);
module_exit(showmem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fei Xie donovanxie@gmail.com");
MODULE_DESCRIPTION("Print PAGE_OFFSET / high_memory / VMALLOC range");
