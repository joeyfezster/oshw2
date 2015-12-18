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

int add_TODO(pid_t pid, const char *TODO_description, ssize_t description_size);
ssize_t read_TODO(pid_t pid, int TODO_index, char *TODO_description, ssize_t description_size, int* status);
int mark_TODO(pid_t pid, int TODO_index, int status);
int delete_TODO(pid_t pid, int TODO_index);


#endif
