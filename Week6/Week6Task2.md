# Week 6 Task 2

## 内核直接映射区边界范围

编译了一个内核模块 ```showmem```直接输出内存边界地址，输出地址之后移除模块，插入本次任务所需模块进行分析：

```bash
~ # ls
bin                   lost+found            simple_char_ioctl.ko
demo_char             proc                  simple_mem.ko
dev                   resize_demo           sys
etc                   sbin                  usr
lib                   showmem.ko
linuxrc               simple_char.ko
~ # insmod showmem.ko 
showmem: loading out-of-tree module taints kernel.
=== showmem_init ===
PAGE_OFFSET   = 80000000
high_memory   = a0000000
VMALLOC_START = a0800000
VMALLOC_END   = ff800000
====================
~ # rmmod showmem.ko 
showmem: exit
~ # cat /proc/buddyinfo
Node 0, zone   Normal      3      0      2      1      2      3      2      3      6      4    116 
~ # cat /proc/slabinfo
slabinfo - version: 2.1
# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab> : tunables <limit> <batchcount> <sharedfactor> : slabdata <active_slabs> <num_slabs> <sharedavail>
ubifs_inode_slab       0      0    504   16    2 : tunables    0    0    0 : slabdata      0      0      0
p9_req_t               0      0     96   42    1 : tunables    0    0    0 : slabdata      0      0      0
bio-72                32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
io_kiocb               0      0    256   16    1 : tunables    0    0    0 : slabdata      0      0      0
bfq_io_cq              0      0   1000   16    4 : tunables    0    0    0 : slabdata      0      0      0
bio-184               21     21    192   21    1 : tunables    0    0    0 : slabdata      1      1      0
v9fs_inode_cache       0      0    472   17    2 : tunables    0    0    0 : slabdata      0      0      0
jffs2_refblock         0      0    248   16    1 : tunables    0    0    0 : slabdata      0      0      0
jffs2_i                0      0    432   18    2 : tunables    0    0    0 : slabdata      0      0      0
nfs_direct_cache       0      0    104   39    1 : tunables    0    0    0 : slabdata      0      0      0
nfs_inode_cache        0      0    640   25    4 : tunables    0    0    0 : slabdata      0      0      0
fat_inode_cache        0      0    496   16    2 : tunables    0    0    0 : slabdata      0      0      0
fat_cache              0      0     24  170    1 : tunables    0    0    0 : slabdata      0      0      0
squashfs_inode_cache      0      0    448   18    2 : tunables    0    0    0 : slabdata      0      0      0
jbd2_journal_handle     85     85     48   85    1 : tunables    0    0    0 : slabdata      1      1      0
jbd2_journal_head     56     56     72   56    1 : tunables    0    0    0 : slabdata      1      1      0
ext2_inode_cache       0      0    512   16    2 : tunables    0    0    0 : slabdata      0      0      0
ext4_fc_dentry_update      0      0     88   46    1 : tunables    0    0    0 : slabdata      0      0      0
ext4_inode_cache      44     44    736   22    4 : tunables    0    0    0 : slabdata      2      2      0
ext4_prealloc_space      0      0     72   56    1 : tunables    0    0    0 : slabdata      0      0      0
pending_reservation    256    256     16  256    1 : tunables    0    0    0 : slabdata      1      1      0
extent_status        256    256     32  128    1 : tunables    0    0    0 : slabdata      2      2      0
mb_cache_entry       102    102     40  102    1 : tunables    0    0    0 : slabdata      1      1      0
posix_timers_cache      0      0    184   22    1 : tunables    0    0    0 : slabdata      0      0      0
rpc_inode_cache        0      0    448   18    2 : tunables    0    0    0 : slabdata      0      0      0
ip4-frags              0      0    136   30    1 : tunables    0    0    0 : slabdata      0      0      0
RAW                   23     23    704   23    4 : tunables    0    0    0 : slabdata      1      1      0
UDP                    0      0    832   19    4 : tunables    0    0    0 : slabdata      0      0      0
tw_sock_TCP            0      0    160   25    1 : tunables    0    0    0 : slabdata      0      0      0
request_sock_TCP       0      0    208   19    1 : tunables    0    0    0 : slabdata      0      0      0
TCP                    0      0   1856   17    8 : tunables    0    0    0 : slabdata      0      0      0
netfs_request        108    108    448   18    2 : tunables    0    0    0 : slabdata      6      6      0
bio-160               42     42    192   21    1 : tunables    0    0    0 : slabdata      2      2      0
ep_head                0      0      8  512    1 : tunables    0    0    0 : slabdata      0      0      0
bio-120               64     64    128   32    1 : tunables    0    0    0 : slabdata      2      2      0
biovec-max            40     40   3072   10    8 : tunables    0    0    0 : slabdata      4      4      0
biovec-128             0      0   1536   21    8 : tunables    0    0    0 : slabdata      0      0      0
sock_inode_cache      28     28    576   28    4 : tunables    0    0    0 : slabdata      1      1      0
skbuff_small_head     28     28    576   28    4 : tunables    0    0    0 : slabdata      1      1      0
skbuff_fclone_cache      0      0    384   21    2 : tunables    0    0    0 : slabdata      0      0      0
skbuff_head_cache     21     21    192   21    1 : tunables    0    0    0 : slabdata      1      1      0
tracefs_inode_cache    100    100    400   20    2 : tunables    0    0    0 : slabdata      5      5      0
file_lock_cache        0      0    112   36    1 : tunables    0    0    0 : slabdata      0      0      0
fsnotify_mark_connector      0      0     16  256    1 : tunables    0    0    0 : slabdata      0      0      0
proc_inode_cache      19     19    424   19    2 : tunables    0    0    0 : slabdata      1      1      0
sigqueue              85     85     48   85    1 : tunables    0    0    0 : slabdata      1      1      0
bdev_cache            16     16   1024   16    4 : tunables    0    0    0 : slabdata      1      1      0
shmem_inode_cache    153    153    464   17    2 : tunables    0    0    0 : slabdata      9      9      0
kernfs_iattrs_cache      0      0     72   56    1 : tunables    0    0    0 : slabdata      0      0      0
kernfs_node_cache  10212  10212     88   46    1 : tunables    0    0    0 : slabdata    222    222      0
filp                  32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
inode_cache           21     21    384   21    2 : tunables    0    0    0 : slabdata      1      1      0
dentry               330    330    136   30    1 : tunables    0    0    0 : slabdata     11     11      0
vma_lock             170    170     24  170    1 : tunables    0    0    0 : slabdata      1      1      0
vm_area_struct       153    153     80   51    1 : tunables    0    0    0 : slabdata      3      3      0
signal_cache         125    125    640   25    4 : tunables    0    0    0 : slabdata      5      5      0
sighand_cache         72     72   1344   24    8 : tunables    0    0    0 : slabdata      3      3      0
task_struct           75     75   2176   15    8 : tunables    0    0    0 : slabdata      5      5      0
anon_vma_chain       256    256     32  128    1 : tunables    0    0    0 : slabdata      2      2      0
anon_vma             146    146     56   73    1 : tunables    0    0    0 : slabdata      2      2      0
perf_event             0      0    784   20    4 : tunables    0    0    0 : slabdata      0      0      0
trace_event_file    1095   1095     56   73    1 : tunables    0    0    0 : slabdata     15     15      0
radix_tree_node      364    364    304   26    2 : tunables    0    0    0 : slabdata     14     14      0
mm_struct             21     21    768   21    4 : tunables    0    0    0 : slabdata      1      1      0
vmap_area           3468   3468     40  102    1 : tunables    0    0    0 : slabdata     34     34      0
kmalloc-rcl-8k         0      0   8192    4    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-4k         0      0   4096    8    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-2k         0      0   2048   16    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-1k         0      0   1024   16    4 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-512        0      0    512   16    2 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-256        0      0    256   16    1 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-128       32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
kmalloc-rcl-64        64     64     64   64    1 : tunables    0    0    0 : slabdata      1      1      0
kmalloc-rcl-192        0      0    192   21    1 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-8k             8      8   8192    4    8 : tunables    0    0    0 : slabdata      2      2      0
kmalloc-4k            16     16   4096    8    8 : tunables    0    0    0 : slabdata      2      2      0
kmalloc-2k           240    240   2048   16    8 : tunables    0    0    0 : slabdata     15     15      0
kmalloc-1k           208    208   1024   16    4 : tunables    0    0    0 : slabdata     13     13      0
kmalloc-512          384    384    512   16    2 : tunables    0    0    0 : slabdata     24     24      0
kmalloc-256          400    400    256   16    1 : tunables    0    0    0 : slabdata     25     25      0
kmalloc-128         1600   1600    128   32    1 : tunables    0    0    0 : slabdata     50     50      0
kmalloc-64          6066   6144     64   64    1 : tunables    0    0    0 : slabdata     96     96      0
kmalloc-192          147    147    192   21    1 : tunables    0    0    0 : slabdata      7      7      0
kmem_cache_node      128    128     64   64    1 : tunables    0    0    0 : slabdata      2      2      0
kmem_cache            96     96    128   32    1 : tunables    0    0    0 : slabdata      3      3      0
~ # insmod simple_mem.ko 
simple_mem: init
kmalloc addr: 81d00000
vmalloc addr: ab401000
kmalloc first: K, last: K
vmalloc first: V, last: V
~ # cat /proc/buddyinfo
Node 0, zone   Normal      2      1      2      2      2      2      2      3      6      3    116 
~ # cat /proc/slabinfo
slabinfo - version: 2.1
# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab> : tunables <limit> <batchcount> <sharedfactor> : slabdata <active_slabs> <num_slabs> <sharedavail>
ubifs_inode_slab       0      0    504   16    2 : tunables    0    0    0 : slabdata      0      0      0
p9_req_t               0      0     96   42    1 : tunables    0    0    0 : slabdata      0      0      0
bio-72                32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
io_kiocb               0      0    256   16    1 : tunables    0    0    0 : slabdata      0      0      0
bfq_io_cq              0      0   1000   16    4 : tunables    0    0    0 : slabdata      0      0      0
bio-184               21     21    192   21    1 : tunables    0    0    0 : slabdata      1      1      0
v9fs_inode_cache       0      0    472   17    2 : tunables    0    0    0 : slabdata      0      0      0
jffs2_refblock         0      0    248   16    1 : tunables    0    0    0 : slabdata      0      0      0
jffs2_i                0      0    432   18    2 : tunables    0    0    0 : slabdata      0      0      0
nfs_direct_cache       0      0    104   39    1 : tunables    0    0    0 : slabdata      0      0      0
nfs_inode_cache        0      0    640   25    4 : tunables    0    0    0 : slabdata      0      0      0
fat_inode_cache        0      0    496   16    2 : tunables    0    0    0 : slabdata      0      0      0
fat_cache              0      0     24  170    1 : tunables    0    0    0 : slabdata      0      0      0
squashfs_inode_cache      0      0    448   18    2 : tunables    0    0    0 : slabdata      0      0      0
jbd2_journal_handle     85     85     48   85    1 : tunables    0    0    0 : slabdata      1      1      0
jbd2_journal_head     56     56     72   56    1 : tunables    0    0    0 : slabdata      1      1      0
ext2_inode_cache       0      0    512   16    2 : tunables    0    0    0 : slabdata      0      0      0
ext4_fc_dentry_update      0      0     88   46    1 : tunables    0    0    0 : slabdata      0      0      0
ext4_inode_cache      44     44    736   22    4 : tunables    0    0    0 : slabdata      2      2      0
ext4_prealloc_space      0      0     72   56    1 : tunables    0    0    0 : slabdata      0      0      0
pending_reservation    256    256     16  256    1 : tunables    0    0    0 : slabdata      1      1      0
extent_status        256    256     32  128    1 : tunables    0    0    0 : slabdata      2      2      0
mb_cache_entry       102    102     40  102    1 : tunables    0    0    0 : slabdata      1      1      0
posix_timers_cache      0      0    184   22    1 : tunables    0    0    0 : slabdata      0      0      0
rpc_inode_cache        0      0    448   18    2 : tunables    0    0    0 : slabdata      0      0      0
ip4-frags              0      0    136   30    1 : tunables    0    0    0 : slabdata      0      0      0
RAW                   23     23    704   23    4 : tunables    0    0    0 : slabdata      1      1      0
UDP                    0      0    832   19    4 : tunables    0    0    0 : slabdata      0      0      0
tw_sock_TCP            0      0    160   25    1 : tunables    0    0    0 : slabdata      0      0      0
request_sock_TCP       0      0    208   19    1 : tunables    0    0    0 : slabdata      0      0      0
TCP                    0      0   1856   17    8 : tunables    0    0    0 : slabdata      0      0      0
netfs_request        108    108    448   18    2 : tunables    0    0    0 : slabdata      6      6      0
bio-160               42     42    192   21    1 : tunables    0    0    0 : slabdata      2      2      0
ep_head                0      0      8  512    1 : tunables    0    0    0 : slabdata      0      0      0
bio-120               64     64    128   32    1 : tunables    0    0    0 : slabdata      2      2      0
biovec-max            40     40   3072   10    8 : tunables    0    0    0 : slabdata      4      4      0
biovec-128             0      0   1536   21    8 : tunables    0    0    0 : slabdata      0      0      0
sock_inode_cache      28     28    576   28    4 : tunables    0    0    0 : slabdata      1      1      0
skbuff_small_head     28     28    576   28    4 : tunables    0    0    0 : slabdata      1      1      0
skbuff_fclone_cache      0      0    384   21    2 : tunables    0    0    0 : slabdata      0      0      0
skbuff_head_cache     21     21    192   21    1 : tunables    0    0    0 : slabdata      1      1      0
tracefs_inode_cache    100    100    400   20    2 : tunables    0    0    0 : slabdata      5      5      0
file_lock_cache        0      0    112   36    1 : tunables    0    0    0 : slabdata      0      0      0
fsnotify_mark_connector      0      0     16  256    1 : tunables    0    0    0 : slabdata      0      0      0
proc_inode_cache      19     19    424   19    2 : tunables    0    0    0 : slabdata      1      1      0
sigqueue              85     85     48   85    1 : tunables    0    0    0 : slabdata      1      1      0
bdev_cache            16     16   1024   16    4 : tunables    0    0    0 : slabdata      1      1      0
shmem_inode_cache    153    153    464   17    2 : tunables    0    0    0 : slabdata      9      9      0
kernfs_iattrs_cache      0      0     72   56    1 : tunables    0    0    0 : slabdata      0      0      0
kernfs_node_cache  10212  10212     88   46    1 : tunables    0    0    0 : slabdata    222    222      0
filp                  32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
inode_cache           21     21    384   21    2 : tunables    0    0    0 : slabdata      1      1      0
dentry               330    330    136   30    1 : tunables    0    0    0 : slabdata     11     11      0
vma_lock             170    170     24  170    1 : tunables    0    0    0 : slabdata      1      1      0
vm_area_struct       153    153     80   51    1 : tunables    0    0    0 : slabdata      3      3      0
signal_cache         125    125    640   25    4 : tunables    0    0    0 : slabdata      5      5      0
sighand_cache         72     72   1344   24    8 : tunables    0    0    0 : slabdata      3      3      0
task_struct           75     75   2176   15    8 : tunables    0    0    0 : slabdata      5      5      0
anon_vma_chain       256    256     32  128    1 : tunables    0    0    0 : slabdata      2      2      0
anon_vma             146    146     56   73    1 : tunables    0    0    0 : slabdata      2      2      0
perf_event             0      0    784   20    4 : tunables    0    0    0 : slabdata      0      0      0
trace_event_file    1095   1095     56   73    1 : tunables    0    0    0 : slabdata     15     15      0
radix_tree_node      364    364    304   26    2 : tunables    0    0    0 : slabdata     14     14      0
mm_struct             21     21    768   21    4 : tunables    0    0    0 : slabdata      1      1      0
vmap_area           3468   3468     40  102    1 : tunables    0    0    0 : slabdata     34     34      0
kmalloc-rcl-8k         0      0   8192    4    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-4k         0      0   4096    8    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-2k         0      0   2048   16    8 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-1k         0      0   1024   16    4 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-512        0      0    512   16    2 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-256        0      0    256   16    1 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-rcl-128       32     32    128   32    1 : tunables    0    0    0 : slabdata      1      1      0
kmalloc-rcl-64        64     64     64   64    1 : tunables    0    0    0 : slabdata      1      1      0
kmalloc-rcl-192        0      0    192   21    1 : tunables    0    0    0 : slabdata      0      0      0
kmalloc-8k             8      8   8192    4    8 : tunables    0    0    0 : slabdata      2      2      0
kmalloc-4k            16     16   4096    8    8 : tunables    0    0    0 : slabdata      2      2      0
kmalloc-2k           240    240   2048   16    8 : tunables    0    0    0 : slabdata     15     15      0
kmalloc-1k           208    208   1024   16    4 : tunables    0    0    0 : slabdata     13     13      0
kmalloc-512          384    384    512   16    2 : tunables    0    0    0 : slabdata     24     24      0
kmalloc-256          400    400    256   16    1 : tunables    0    0    0 : slabdata     25     25      0
kmalloc-128         1600   1600    128   32    1 : tunables    0    0    0 : slabdata     50     50      0
kmalloc-64          6127   6144     64   64    1 : tunables    0    0    0 : slabdata     96     96      0
kmalloc-192          147    147    192   21    1 : tunables    0    0    0 : slabdata      7      7      0
kmem_cache_node      128    128     64   64    1 : tunables    0    0    0 : slabdata      2      2      0
kmem_cache            96     96    128   32    1 : tunables    0    0    0 : slabdata      3      3      0
~ # 
```

其中插入模块的日至输出如下：
```bash
~ # insmod simple_mem.ko 
simple_mem: init
kmalloc addr: 81d00000
vmalloc addr: ab401000
kmalloc first: K, last: K
vmalloc first: V, last: V
```

```kmalloc```地址为 ```81d0 0000```

```0x8000 0000 ≤ 0x81d0 0000 < 0xa000 0000``` 因此我们可以得出结论落在 low‑mem，物理页连续。

```vmalloc```地址为```ab40 1000```

```0xa080 0000 ≤ 0xab40 1000 < 0xff80 0000```因此我们可以得出结论位于```vmalloc```区，物理页离散映射。

在该内核模块中我尝试直接访问边界地址，终端输出一切正常，说明访问成功。

Buddy system变化对比：
插入模块前：
```bash
~ # cat /proc/buddyinfo
Node 0, zone   Normal      3      0      2      1      2      3      2      3      6      4    116 

```

插入后：
```bash
~ # cat /proc/buddyinfo
Node 0, zone   Normal      2      1      2      2      2      2      2      3      6      3    116 
```

```kmalloc```(1MiB)=256页=order-8块

但实际对比看出order-8计数并未减少，依然保持6,可能是内核拆分了更高阶块。

```vmalloc```则是逐页分配，多数消耗order0/1。

结论：```kmalloc```直接影响高阶空闲块，```vmalloc```则是主要消耗低阶页。

Slab分配器信息则是变化不大，说明```kmalloc``` 和 ```vmalloc```分配超过8KiB就会绕过slab直接走伙伴系统。