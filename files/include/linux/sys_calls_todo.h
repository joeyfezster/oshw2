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

typedef struct _rankS {
	task_t *taskPtr;
	int rank;
	list_t listPtr;
} rankS;

/*list for ranks*/
extern list_t ranks;
int sys_register_mpi(void);
int sys_send_mpi_message(int rank,const char* message,int message_size);
int sys_receive_mpi_message(int rank,char* message,int message_size);

//functions

#endif
