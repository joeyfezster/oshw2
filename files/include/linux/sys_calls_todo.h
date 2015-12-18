#ifndef SYS_CALLS_TODO_
#define SYS_CALLS_TODO_
#define MODULE
#define LINUX
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

int sys_add_TODO(pid_t pid, const char *TODO_description, ssize_t description_size);
ssize_t sys_read_TODO(pid_t pid, int TODO_index, char *TODO_description, ssize_t description_size, int* status);
int sys_mark_TODO(pid_t pid, int TODO_index, int status);
int sys_delete_TODO(pid_t pid, int TODO_index);
int sys_sanity_test();


#endif
